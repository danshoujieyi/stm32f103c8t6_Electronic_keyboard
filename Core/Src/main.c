/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "OLED.h"  //OLED鏄剧ず锟??
#include "buzzer.h"
#include "MAX7219_Tube.h"
#include "HCSR04.h"
#include "Passive_Buzzer.h"
#include "JoyStick.h"
#include "music.h"
#include "keyboard.h"
#include "LED.h"
#include "Key.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// 任务一
float distance = 0;
int cnt = 30;
int displayValue = 0;
int integerPart = 0;
int decimalPart = 0;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
// 任务二
// 按键引脚定义
#define Key1 GPIO_PIN_10  // 屏幕下方左键，接 A10 和正极
#define Key2 GPIO_PIN_15  // 屏幕下方中键，接 B15 和正极
#define Key3 GPIO_PIN_14  // 屏幕下方右键，接 B14 和正极
#define Key4 GPIO_PIN_9   // 旋转编码器按键，接 A9 和正极  需要修改

// LED 引脚定义
#define LED1 GPIO_PIN_6   // 第一颗 LED，负极接 A6，另一端接正极
#define LED2 GPIO_PIN_4   // 第二颗 LED，负极接 A4，另一端接正极
#define LED3 GPIO_PIN_2   // 第三颗 LED，负极接 A2，另一端接正极

uint8_t voice = 1;      //音色编号
uint8_t knob = 1;       //旋钮功能编号
uint8_t tsp = 5;        //移调参数，范围0至11，屏幕显示为-5至+6
uint8_t sft = 3;        //键盘平移参数，范围0至6，屏幕显示为-3至+3
uint8_t oct = 1;        //八度参数，0：低八度、1：正常、2：高八度
uint8_t sharp = 0;      //升半音参数，0：关、1：开
uint8_t mode = 1;       //模式编号，1：音色模式、2：伴奏模式
uint8_t style = 1;      //伴奏风格编号
uint16_t tempo = 120;   //速度，单位为bpm
uint8_t chordType = 0;  //和弦类型
uint8_t isPlaying = 0;  //伴奏是否在播放，0：不在播放、1：在播放
uint8_t track = 0;      //音轨开关状态，0：鼓1轨和琶音轨、1：鼓1轨和鼓2轨、2：琶音轨
uint8_t section = 0;    //前奏尾声段落开关状态，0：前奏和尾声、1：前奏、2：尾声、3：关闭
uint8_t arpVoice = 1;   //琶音音色编号

/* 大调音阶频率       G   A   B   C   D   E   F   G   A   B   C   D   E   */
uint16_t scale[] = {196,220,247,262,294,330,349,392,440,494,523,587,659};

/* 移调系数           -5   -4   -3   -2   -1   0   +1   +2   +3   +4   +5   +6   */
float transpose[] = {0.75,0.79,0.84,0.89,0.94,1.0,1.06,1.12,1.19,1.26,1.33,1.41};

/* 音色方波占空比 */
uint8_t voiceDuties[5] = {50,40,30,20,10};

/* OLED显示屏显示信息 */
// 用于存储乐器名称的字符串数组。包含6种乐器名称：单簧管、管风琴、手风琴、双簧管、喇叭和鼓。
char* voiceNames[6] = {"Clarinet","Pipe Organ","Accordion","Oboe","Trumpet","Drums"};
// 用于存储音乐风格名称的字符串数组，包含6种风格：8拍、16拍、慢摇滚、摇摆、进行曲和华尔兹。
char* styleNames[6] = {"8Beat","16Beat","Slow Rock","Swing","March","Waltz"};
// 用于存储音轨状态的字符串数组，包含3种状态：伴奏（Dr&Ap）、鼓声（Drums）和琶音（Arpgo）。
char* trackStatus[3] = {"Dr&Ap","Drums","Arpgo"};
// 用于存储段落状态的字符串数组，包含4种状态：前奏和尾声（In&Ed）、前奏（Intro）、尾声（Endng）和关闭（OFF）。
char* sectionStatus[4] = {"In&Ed","Intro","Endng"," OFF "};
// 用于存储和弦名称的字符串数组，包含8种和弦名称：C、Dm、Em、E7、F、G、G7和Am。
char* chordNames[8] = {"C ","Dm","Em","E7","F ","G ","G7","Am"};
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
    // 任务一
    Ultrasonic_Init();
    MAX7219_Init();
    OLED_Init();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
    // 任务二
    /* 初始化 */
    LED_Init_A(LED1|LED2|LED3);//三颗LED，从左到右负极依次接A6、A4、A2，另一端接正极
    Key_Init_A(Key1|Key4);     //屏幕下方左键和旋转编码器按键，分别接A10和A9，另一端接正极
    Key_Init_B(Key2|Key3);     //屏幕下方中键和右键，分别接B15和B14，另一端接正极
    Passive_Buzzer_Init();             //两个扬声器（或无源蜂鸣器），正极分别接A0和A7，另一端接负极
//    Encoder_Init();            //旋转编码器，A接B1，B接B0
//    Keyboard_Init();           //七个琴键，从左到右依次接B12、B13、A8、A11、B3、B6、B9，另一端接正极
    JoyStick_Init();           //PS2摇杆模块，VRX接A5，VRY接A3，SW接A1
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
//    OLED_ShowString(1, 1, "Freq:00000Hz");
//    OLED_ShowString(2, 1, "Duty:00%");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // 任务一
//      OLED_ShowNum(3, 1, cnt, 4);
      // 将新的阈值显示到七段数码管
      Write_Max7219(1, cnt / 10);        // 显示十位
      Write_Max7219(2, cnt % 10);        // 显示个位
      // 显示 "F" 在第1位和第2位
      Write_Max7219(3, 15);  // 地址1 显示第一个 F
      Write_Max7219(4, 15);  // 地址2 显示第二个 F

      distance = Hcsr04GetLength();
      displayValue = (int)(distance * 100);  // 杞崲涓烘暣鏁帮紝淇濇寔涓や綅灏忔暟
      integerPart = displayValue / 100;  // 鏁存暟閮ㄥ垎
      decimalPart = displayValue % 100;   // 灏忔暟閮ㄥ垎
      if (integerPart > 99)
      {
          integerPart = 99;  // 鏄剧ず涓婇檺
          decimalPart = 0;   // 灏忔暟閮ㄥ垎璁剧疆锟??0
      }
      // 鏄剧ず鍦ㄦ暟鐮佺锟??
      Write_Max7219(5, (integerPart / 10));        // 锟??3浣嶏細鍗佷綅锟??
      Write_Max7219(6, (integerPart % 10) | 0x80);        // 锟??2浣嶏細涓綅锟??
      Write_Max7219(7, (decimalPart / 10));        // 锟??1浣嶏細灏忔暟鐐瑰墠锟??锟??
      Write_Max7219(8, (decimalPart % 10)); // 锟??0浣嶏細灏忔暟鐐瑰悗锛堟樉绀哄皬鏁扮偣锟??

      // 检查是否达到阈值a
      if (displayValue <= cnt*100)
      {
          Buzzer_Alarm((int)distance); // 调用报警函数
      }


      //任务二/**********************************************//************************************************/
      //任务二/**********************************************//************************************************/
      //任务二/**********************************************//************************************************/
      //任务二/**********************************************//************************************************/
      //任务二/**********************************************//************************************************/
//      Passive_Buzzer_Timing(3600,20,60,0);
      /* 音色模式 */
//      if(mode == 1){
//          OLED_ShowNum(1,1,voice,1);
//          OLED_ShowString(1,3,voiceNames[voice-1]);
//          OLED_ShowString(2,1,"Tsp: ");
//          OLED_ShowSignedNum(2,6,tsp-5,1);
//          OLED_ShowString(2,8,"  Sft: ");
//          OLED_ShowSignedNum(2,15,sft-3,1);
//          OLED_ShowString(3,11,"M: Voc");
//          OLED_ShowString(4,1,"OctDw OctUp Shrp");
//          if(Key_Read_A(Key4)){
//              knob = Key_Var_Plus(knob,1,3,1);
//              HAL_Delay(200);
//          }
//          if(JoyStick_GetSW()){
//              mode = Key_Var_Plus(mode,1,2,1);
//              knob = 1;
//              if(voice == 6){
//                  voice = 1;
//              }
//              HAL_Delay(200);
//              OLED_Clear();
//          }
////          if(knob == 1){
////              OLED_ShowString(3,1,"K: Voice  ");
////              if(Encoder_Get() != 0){
////                  voice = Encoder_Var(voice,1,1,6,6,1);
////                  OLED_ShowString(1,3,"              ");
////              }
////          }
////          else if(knob == 2){
////              OLED_ShowString(3,1,"K: Transp ");
////              tsp = Encoder_Var(tsp,1,0,11,0,11);
////          }
////          else if(knob == 3){
////              OLED_ShowString(3,1,"K: Shift  ");
////              sft = Encoder_Var(sft,1,0,6,0,6);
////          }
//      }
//
//          /* 伴奏模式 */
//      else if(mode == 2){
//          OLED_ShowNum(1,1,style,1);
//          OLED_ShowString(1,3,styleNames[style-1]);
//          OLED_ShowString(2,1,"Tempo: ");
//          OLED_ShowNum(2,8,tempo,3);
//          OLED_ShowString(2,11," ArpV");
//          OLED_ShowNum(2,16,arpVoice,1);
//          OLED_ShowString(3,11,"M: Sty");
//          OLED_ShowString(4,1,"Play ");
//          OLED_ShowString(4,6,trackStatus[track]);
//          OLED_ShowString(4,12,sectionStatus[section]);
//          if(Key_Read_A(Key1)){
//              HAL_Delay(200);
//              acmp(style);
//          }
//          if(Key_Read_B(Key2)){
//              track = Key_Var_Plus(track,1,2,0);
//              HAL_Delay(200);
//          }
//          if(Key_Read_B(Key3)){
//              section = Key_Var_Plus(section,1,3,0);
//              HAL_Delay(200);
//          }
//          if(Key_Read_A(Key4)){
//              knob = Key_Var_Plus(knob,1,3,1);
//              HAL_Delay(200);
//          }
//          if(JoyStick_GetSW()){
//              mode = Key_Var_Plus(mode,1,2,1);
//              knob = 1;
//              HAL_Delay(200);
//              OLED_Clear();
//          }
//          if(knob == 1){
//              OLED_ShowString(3,1,"K: Style  ");
//              if(Encoder_Get() != 0){
//                  style = Encoder_Var(style,1,1,6,6,1);
//                  OLED_ShowString(1,3,"              ");
//              }
//          }
//          else if(knob == 2){
//              OLED_ShowString(3,1,"K: Tempo  ");
//              tempo = Encoder_Var(tempo,5,40,240,40,240);
//          }
//          else if(knob == 3){
//              OLED_ShowString(3,1,"K: ArpVoc ");
//              arpVoice = Encoder_Var(arpVoice,1,1,5,5,1);
//          }
//      }


  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
