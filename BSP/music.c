//
// Created by 刘嘉俊 on 24-10-10.
//

#include "music.h"
#include "Key.h"
#include "OLED.h"
#include "Encoder.h"
#include "JoyStick.h"
#include "Passive_Buzzer.h"
#include "math.h"
#include "stm32f1xx_hal.h"

// 按键引脚定义
#define Key1 GPIO_PIN_10  // 屏幕下方左键，接 A10 和正极
#define Key2 GPIO_PIN_15  // 屏幕下方中键，接 B15 和正极
#define Key3 GPIO_PIN_14  // 屏幕下方右键，接 B14 和正极
#define Key4 GPIO_PIN_9   // 旋转编码器按键，接 A9 和正极  需要修改

// LED 引脚定义
#define LED1 GPIO_PIN_6   // 第一颗 LED，负极接 A6，另一端接正极
#define LED2 GPIO_PIN_4   // 第二颗 LED，负极接 A4，另一端接正极
#define LED3 GPIO_PIN_2   // 第三颗 LED，负极接 A2，另一端接正极

extern uint8_t voice;      //音色编号
extern uint8_t knob;       //旋钮功能编号
extern uint8_t tsp;        //移调参数，范围0至11，屏幕显示为-5至+6
extern uint8_t sft;        //键盘平移参数，范围0至6，屏幕显示为-3至+3
extern uint8_t oct;        //八度参数，0：低八度、1：正常、2：高八度
extern uint8_t sharp;      //升半音参数，0：关、1：开
extern uint8_t mode;       //模式编号，1：音色模式、2：伴奏模式
extern uint8_t style;      //伴奏风格编号
extern uint16_t tempo;   //速度，单位为bpm
extern uint8_t chordType;  //和弦类型
extern uint8_t isPlaying;  //伴奏是否在播放，0：不在播放、1：在播放
extern uint8_t track;      //音轨开关状态，0：鼓1轨和琶音轨、1：鼓1轨和鼓2轨、2：琶音轨
extern uint8_t section;    //前奏尾声段落开关状态，0：前奏和尾声、1：前奏、2：尾声、3：关闭
extern uint8_t arpVoice;   //琶音音色编号

/* 大调音阶频率       G   A   B   C   D   E   F   G   A   B   C   D   E   */
extern uint16_t scale[];

/* 移调系数           -5   -4   -3   -2   -1   0   +1   +2   +3   +4   +5   +6   */
extern float transpose[];

/* 音色方波占空比 */
extern uint8_t voiceDuties[5];

/* OLED显示屏显示信息 */
extern char* voiceNames[6];
extern char* styleNames[6];
extern char* trackStatus[3];
extern char* sectionStatus[4];
extern char* chordNames[8];
/**
  * @brief  和弦音符频率生成函数，用于伴奏琶音播放，和弦类型由全局变量chordType决定
  * @param  number：和弦的第几个音，1至4为和弦的第1至第4个音，5至8算做高八度的1至4
  * @retval 和弦音符频率
  */
int chord(char number){
    uint16_t freq = 0;
    if(number == 0){
        return 0;
    }
    uint16_t major[] = {131,165,196,262};    //大三和弦1、3、5、1
    uint16_t minor[] = {131,156,196,262};    //小三和弦1、b3、5、1
    uint16_t seventh[] = {131,165,196,233};  //属七和弦1、3、5、b7
    number = number - 1;
    switch(chordType){
        case 0:  //C
            freq = major[number%4]*pow(2,number/4);
            break;
        case 1:  //Dm
            freq = minor[number%4]*pow(2,number/4)*transpose[7];
            break;
        case 2:  //Em
            freq = minor[number%4]*pow(2,number/4)*transpose[9];
            break;
        case 3:  //E7
            freq = seventh[number%4]*pow(2,number/4)*transpose[9];
            break;
        case 4:  //F
            freq = major[number%4]*pow(2,number/4)*transpose[10];
            break;
        case 5:  //G
            freq = major[number%4]*pow(2,number/4)*transpose[0];
            break;
        case 6:  //G7
            freq = seventh[number%4]*pow(2,number/4)*transpose[0];
            break;
        case 7:  //Am
            freq = minor[number%4]*pow(2,number/4)*transpose[2];
            break;
    }
    return freq*transpose[tsp];
}


/**
  * @brief  前奏播放函数
  * @param  introDrums[]：前奏鼓点1轨的数组
  * @param  introCymbals[]：前奏鼓点2轨的数组
	*	@param	beat：前奏的节拍，
	*								6表示以8分音符量化的3/4拍，
	*								8表示以8分音符量化的4/4拍，
	*								16表示以16分音符量化的4/4拍，
	*								12表示以三连音音符量化的6/8拍
  * @retval 无
  */
void introPlay(char introDrums[],char introCymbals[],char beat){
    isPlaying = 1;
    OLED_ShowString(2,12,"     ");
    OLED_ShowString(4,1,"OctDw OctUp Shrp");
    if(section == 0 || section == 1){
        OLED_ShowString(3,1,"Intro           ");
        for(int j=0;j<beat;j++){
            if(beat==6){
                switch(j/2%3){
                    case 0:
                    //    LED_ON_A(LED1|LED2|LED3);
                        break;
                    case 1:
                    //    LED_ON_A(LED2);
                        break;
                    case 2:
                    //    LED_ON_A(LED3);
                        break;
                }
            }
            else{
                switch(j/(beat/4)%4){
                    case 0:
                    //    LED_ON_A(LED1|LED2|LED3);
                        break;
                    case 1:
                    //    LED_ON_A(LED1);
                        break;
                    case 2:
                    //    LED_ON_A(LED2);
                        break;
                    case 3:
                    //    LED_ON_A(LED3);
                        break;
                }
            }
            if(track == 0 || track == 1){
                Passive_Buzzer_Drum(introDrums[j]);
                Passive_Buzzer_Drum(introCymbals[j]);
            }
            else{
                HAL_Delay(60);
            }
            switch(beat){
                case 6:
                    HAL_Delay(30000/tempo-60);
                    break;
                case 8:
                    HAL_Delay(30000/tempo-60);
                    break;
                case 16:
                    HAL_Delay(30000/(tempo*2)-60);
                    break;
                case 12:
                    HAL_Delay(20000/tempo-60);
                    break;
            }
            Passive_Buzzer_OFF(2);
        //    LED_OFF_A(LED1|LED2|LED3);
            if(Encoder_Get() != 0){
                tempo = Encoder_Var(tempo,5,40,240,40,240);
                OLED_ShowNum(2,8,tempo,3);
            }
        }
    }
}


/**
  * @brief  尾声播放函数
  * @param  无
  * @retval 无
  */
void endingPlay(void){
    if(section == 0 || section == 2){
        if(track != 1){
            OLED_ShowString(3,1,"Ending Chord:   ");
            OLED_ShowString(3,15,chordNames[chordType]);
            uint16_t vrX = JoyStick_GetX();
            uint16_t vrY = JoyStick_GetY();
            if(vrX<1024 && vrY<1024){  // 左下 Dm和弦
                chordType = 1;
                OLED_ShowString(3,15,chordNames[chordType]);
            }
            else if(vrX>3072 && vrY<1024){  // 左上 E7和弦
                chordType = 3;
                OLED_ShowString(3,15,chordNames[chordType]);
            }
            else if(vrX<1024 && vrY>3072){  // 右下 Am和弦
                chordType = 7;
                OLED_ShowString(3,15,chordNames[chordType]);
            }
            else if(vrX>3072 && vrY>3072){  // 右上 G和弦
                chordType = 5;
                OLED_ShowString(3,15,chordNames[chordType]);
            }
            else if(vrX<1024){  // 下 C和弦
                chordType = 0;
                OLED_ShowString(3,15,chordNames[chordType]);
            }
            else if(vrX>3072){  // 上 F和弦
                chordType = 4;
                OLED_ShowString(3,15,chordNames[chordType]);
            }
            else if(vrY<1024){  // 左 Em和弦
                chordType = 2;
                OLED_ShowString(3,15,chordNames[chordType]);
            }
            else if(vrY>3072){  // 右 G7和弦
                chordType = 6;
                OLED_ShowString(3,15,chordNames[chordType]);
            }
        }
        else{
            OLED_ShowString(3,1,"Ending          ");
        }
        if(track != 2){
            Passive_Buzzer_Drum(1);
            Passive_Buzzer_Drum(4);
        }
        if(track != 1){
            Passive_Buzzer_Timing(chord(1),60,voiceDuties[arpVoice-1],2);
            Passive_Buzzer_Timing(chord(2),60,voiceDuties[arpVoice-1],2);
            Passive_Buzzer_Timing(chord(3),60,voiceDuties[arpVoice-1],2);
            Passive_Buzzer_Timing(chord(4),60,voiceDuties[arpVoice-1],2);
        }
        else{
            HAL_Delay(240);
        }
        Passive_Buzzer_OFF(2);
    }
    HAL_Delay(500);
    isPlaying = 0;
    OLED_ShowString(3,1,"                ");
    OLED_ShowString(4,1,"                ");
}


/**
  * @brief  伴奏播放函数
  * @param  arp[]：伴奏琶音轨的数组
  * @param  drums[]：伴奏鼓点1轨的数组
  * @param  cymbals[]：伴奏鼓点2轨的数组，仅在关闭琶音轨时发声
  * @param  fillDrums[]：加花鼓点1轨的数组
  * @param  fillCymbals[]：加花鼓点2轨的数组
	*	@param	number：伴奏数组大小，需为beat的整数倍
	*	@param	beat：伴奏的节拍，
	*								6表示以8分音符量化的3/4拍，
	*								8表示以8分音符量化的4/4拍，
	*								16表示以16分音符量化的4/4拍，
	*								12表示以三连音音符量化的6/8拍
  * @retval 无
  */
void acmpPlay(char arp[],char drums[],char cymbals[],char fillDrums[],char fillCymbals[],char number,char beat){
    int n;
    introPlay(fillDrums,fillCymbals,beat);  //此处直接将加花数组同时用于前奏播放，可按个人需求修改代码
    if(track != 1){
        OLED_ShowString(3,1,"Main   Chord:   ");
        OLED_ShowString(3,15,chordNames[chordType]);
    }
    else{
        OLED_ShowString(3,1,"Main            ");
    }
    while(1){
        for(int i=0;i<number;i++){

            /* 和弦识别代码 */
            if(track != 1){
                uint16_t vrX = JoyStick_GetX();
                uint16_t vrY = JoyStick_GetY();
                if(vrX<1024 && vrY<1024){  // 左下 Dm和弦
                    chordType = 1;
                    OLED_ShowString(3,15,chordNames[chordType]);
                }
                else if(vrX>3072 && vrY<1024){  // 左上 E7和弦
                    chordType = 3;
                    OLED_ShowString(3,15,chordNames[chordType]);
                }
                else if(vrX<1024 && vrY>3072){  // 右下 Am和弦
                    chordType = 7;
                    OLED_ShowString(3,15,chordNames[chordType]);
                }
                else if(vrX>3072 && vrY>3072){  // 右上 G和弦
                    chordType = 5;
                    OLED_ShowString(3,15,chordNames[chordType]);
                }
                else if(vrX<1024){  // 下 C和弦
                    chordType = 0;
                    OLED_ShowString(3,15,chordNames[chordType]);
                }
                else if(vrX>3072){  // 上 F和弦
                    chordType = 4;
                    OLED_ShowString(3,15,chordNames[chordType]);
                }
                else if(vrY<1024){  // 左 Em和弦
                    chordType = 2;
                    OLED_ShowString(3,15,chordNames[chordType]);
                }
                else if(vrY>3072){  // 右 G7和弦
                    chordType = 6;
                    OLED_ShowString(3,15,chordNames[chordType]);
                }
            }

            /* 加花代码 */
            if(JoyStick_GetSW()){
                OLED_ShowString(3,1,"Fill In         ");
                n = i%beat;
                for(int j=n;j<beat;j++){
                    if(beat==6){
                        switch(j/2%3){
                            case 0:
                            //    LED_ON_A(LED1|LED2|LED3);
                                break;
                            case 1:
                            //    LED_ON_A(LED2);
                                break;
                            case 2:
                            //    LED_ON_A(LED3);
                                break;
                        }
                    }
                    else{
                        switch(j/(beat/4)%4){
                            case 0:
                            //    LED_ON_A(LED1|LED2|LED3);
                                break;
                            case 1:
                            //    LED_ON_A(LED1);
                                break;
                            case 2:
                            //   LED_ON_A(LED2);
                                break;
                            case 3:
                            //    LED_ON_A(LED3);
                                break;
                        }
                    }
                    if(track == 0 || track == 1){
                        Passive_Buzzer_Drum(fillDrums[j]);
                        Passive_Buzzer_Drum(fillCymbals[j]);
                    }
                    else{
                        HAL_Delay(60);
                    }
                    switch(beat){
                        case 6:
                            HAL_Delay(30000/tempo-60);
                            break;
                        case 8:
                            HAL_Delay(30000/tempo-60);
                            break;
                        case 16:
                            HAL_Delay(30000/(tempo*2)-60);
                            break;
                        case 12:
                            HAL_Delay(20000/tempo-60);
                            break;
                    }
                    Passive_Buzzer_OFF(2);
                //    LED_OFF_A(LED1|LED2|LED3);
                    if(Encoder_Get() != 0){
                        tempo = Encoder_Var(tempo,5,40,240,40,240);
                        OLED_ShowNum(2,8,tempo,3);
                    }
                    if(Key_Read_A(Key4)){
                        break;
                    }
                }
                if(track != 1){
                    OLED_ShowString(3,1,"Main   Chord:   ");
                    OLED_ShowString(3,15,chordNames[chordType]);
                }
                else{
                    OLED_ShowString(3,1,"Main            ");
                }
                break;
            }

            /* 节拍指示灯代码 */
            if(beat==6){
                switch(i/2%3){
                    case 0:
                    //   LED_ON_A(LED1|LED2|LED3);
                        break;
                    case 1:
                    //    LED_ON_A(LED2);
                        break;
                    case 2:
                    //    LED_ON_A(LED3);
                        break;
                }
            }
            else{
                switch(i/(beat/4)%4){
                    case 0:
                    //    LED_ON_A(LED1|LED2|LED3);
                        break;
                    case 1:
                    //    LED_ON_A(LED1);
                        break;
                    case 2:
                    //    LED_ON_A(LED2);
                        break;
                    case 3:
                    //    LED_ON_A(LED3);
                        break;
                }
            }

            /* 伴奏播放代码 */
            if(track != 2){
                Passive_Buzzer_Drum(drums[i]);
            }
            else{
                HAL_Delay(30);
            }
            if(track == 1){
                Passive_Buzzer_Drum(cymbals[i]);
                switch(beat){
                    case 6:
                        HAL_Delay(30000/tempo-60);
                        break;
                    case 8:
                        HAL_Delay(30000/tempo-60);
                        break;
                    case 16:
                        HAL_Delay(30000/(tempo*2)-60);
                        break;
                    case 12:
                        HAL_Delay(20000/tempo-60);
                        break;
                }
            }
            else{
                if(arp[i] != 0){
                    switch(beat){
                        case 6:
                            Passive_Buzzer_Timing(chord(arp[i]),30000/tempo-30,voiceDuties[arpVoice-1],2);
                            break;
                        case 8:
                            Passive_Buzzer_Timing(chord(arp[i]),30000/tempo-30,voiceDuties[arpVoice-1],2);
                            break;
                        case 16:
                            Passive_Buzzer_Timing(chord(arp[i]),30000/(tempo*2)-30,voiceDuties[arpVoice-1],2);
                            break;
                        case 12:
                            Passive_Buzzer_Timing(chord(arp[i]),20000/tempo-30,voiceDuties[arpVoice-1],2);
                            break;
                    }
                }
                else{
                    switch(beat){
                        case 6:
                            HAL_Delay(30000/tempo-30);
                            break;
                        case 8:
                            HAL_Delay(30000/tempo-30);
                            break;
                        case 16:
                            HAL_Delay(30000/(tempo*2)-30);
                            break;
                        case 12:
                            HAL_Delay(20000/tempo-30);
                            break;
                    }
                }
            }
            Passive_Buzzer_OFF(2);
        //    LED_OFF_A(LED1|LED2|LED3);
            if(Encoder_Get() != 0){
                tempo = Encoder_Var(tempo,5,40,240,40,240);
                OLED_ShowNum(2,8,tempo,3);
            }
            if(Key_Read_A(Key4)){
                break;
            }
        }
        if(Key_Read_A(Key4)){
            endingPlay();
            break;
        }
    }
}


/**
  * @brief  伴奏启动函数,输入编号以启动对应风格的伴奏
  * @param  style：伴奏风格编号
  * @retval 无
  */
void acmp(char style){
    if(style==1){  // 8Beat
        char arp[16] = {1,2,3,2,4,3,2,3,1,2,3,2,4,2,3,2};
        char drums[16]={1,3,2,1,1,3,2,3,1,3,2,1,1,3,2,1};
        char cymbals[16]={3,0,3,3,3,0,3,0,3,0,3,3,3,0,3,3};
        char fillDrums[8]={1,2,2,2,2,2,2,2};
        char fillCymbals[8]={3,3,3,4,5,5,6,7};
        acmpPlay(arp,drums,cymbals,fillDrums,fillCymbals,16,8);
    }

    if(style==2){  // 16Beat
        char arp[32] = {1,2,3,4,6,4,3,2,1,2,3,4,6,4,3,2,1,2,3,4,6,4,3,2,4,3,2,1,3,2,1,2};
        char drums[32]={1,3,3,3,2,3,3,1,1,3,3,3,2,3,3,1,1,3,3,3,2,3,3,1,1,3,1,3,2,1,3,4};
        char cymbals[32]={3,0,0,0,3,0,0,3,3,0,0,0,3,0,0,3,3,0,0,0,3,0,0,3,3,0,3,0,3,3,0,0};
        char fillDrums[16]={1,0,0,0,2,0,2,2,1,2,0,2,5,5,6,7};
        char fillCymbals[16]={3,3,3,3,3,3,3,3,4,0,0,0,0,0,0,0};
        acmpPlay(arp,drums,cymbals,fillDrums,fillCymbals,32,16);
    }

    if(style==3){  // Slow Rock
        char arp[24] = {1,2,3,4,3,2,1,2,3,4,3,2,1,2,3,4,3,2,4,3,2,3,2,3};
        char drums[24]={1,3,3,2,3,1,1,3,3,2,3,3,1,3,3,2,3,1,1,3,3,2,3,1};
        char cymbals[24]={3,0,0,3,0,3,3,0,0,3,0,0,3,0,0,3,0,3,3,0,0,3,0,4};
        char fillDrums[12]={1,0,0,2,0,2,1,2,2,5,6,7};
        char fillCymbals[12]={3,3,3,3,3,3,4,0,0,0,0,0};
        acmpPlay(arp,drums,cymbals,fillDrums,fillCymbals,24,12);
    }

    if(style==4){  // Swing
        char arp[12] = {5,0,0,6,0,4,3,0,0,6,0,3};
        char drums[12]={1,0,0,2,0,0,1,0,0,2,0,0};
        char cymbals[12]={4,0,0,3,0,4,4,0,0,3,0,4};
        char fillDrums[12]={1,0,0,2,0,2,1,2,2,5,6,7};
        char fillCymbals[12]={4,0,0,3,0,4,4,0,0,0,0,0};
        acmpPlay(arp,drums,cymbals,fillDrums,fillCymbals,12,12);
    }

    if(style==5){  // March
        char arp[32] = {1,0,6,0,3,0,6,0,1,0,6,0,3,0,6,0,1,0,6,0,3,0,6,0,1,0,5,4,5,0,5,0};
        char drums[32]={1,0,2,0,1,0,2,0,1,0,2,0,1,0,2,0,1,0,2,0,1,0,2,0,1,0,2,2,2,0,2,0};
        char cymbals[32]={3,0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,4,0};
        char fillDrums[16]={1,0,2,2,1,0,1,0,1,2,2,2,2,0,2,2};
        char fillCymbals[16]={4,0,3,0,4,0,4,0,4,0,3,0,3,0,4,0};
        acmpPlay(arp,drums,cymbals,fillDrums,fillCymbals,32,16);
    }

    if(style==6){  // Waltz
        char arp[12] = {1,2,3,2,3,2,4,2,3,2,3,2};
        char drums[12]={1,0,2,0,2,0,1,0,2,0,2,0};
        char cymbals[12]={3,3,4,3,4,3,3,3,4,3,4,3};
        char fillDrums[6]={1,2,2,0,2,2};
        char fillCymbals[6]={3,3,3,3,4,0};
        acmpPlay(arp,drums,cymbals,fillDrums,fillCymbals,12,6);
    }
}
