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
#include "OLED.h"  //OLED显示�??
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
// ����һ
float distance = 0;
int cnt = 30;
int displayValue = 0;
int integerPart = 0;
int decimalPart = 0;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
// �����
// �������Ŷ���
#define Key1 GPIO_PIN_10  // ��Ļ�·�������� A10 ������
#define Key2 GPIO_PIN_15  // ��Ļ�·��м����� B15 ������
#define Key3 GPIO_PIN_14  // ��Ļ�·��Ҽ����� B14 ������
#define Key4 GPIO_PIN_9   // ��ת�������������� A9 ������  ��Ҫ�޸�

// LED ���Ŷ���
#define LED1 GPIO_PIN_6   // ��һ�� LED�������� A6����һ�˽�����
#define LED2 GPIO_PIN_4   // �ڶ��� LED�������� A4����һ�˽�����
#define LED3 GPIO_PIN_2   // ������ LED�������� A2����һ�˽�����

uint8_t voice = 1;      //��ɫ���
uint8_t knob = 1;       //��ť���ܱ��
uint8_t tsp = 5;        //�Ƶ���������Χ0��11����Ļ��ʾΪ-5��+6
uint8_t sft = 3;        //����ƽ�Ʋ�������Χ0��6����Ļ��ʾΪ-3��+3
uint8_t oct = 1;        //�˶Ȳ�����0���Ͱ˶ȡ�1��������2���߰˶�
uint8_t sharp = 0;      //������������0���ء�1����
uint8_t mode = 1;       //ģʽ��ţ�1����ɫģʽ��2������ģʽ
uint8_t style = 1;      //��������
uint16_t tempo = 120;   //�ٶȣ���λΪbpm
uint8_t chordType = 0;  //��������
uint8_t isPlaying = 0;  //�����Ƿ��ڲ��ţ�0�����ڲ��š�1���ڲ���
uint8_t track = 0;      //���쿪��״̬��0����1��������졢1����1��͹�2�졢2��������
uint8_t section = 0;    //ǰ��β�����俪��״̬��0��ǰ���β����1��ǰ�ࡢ2��β����3���ر�
uint8_t arpVoice = 1;   //������ɫ���

/* �������Ƶ��       G   A   B   C   D   E   F   G   A   B   C   D   E   */
uint16_t scale[] = {196,220,247,262,294,330,349,392,440,494,523,587,659};

/* �Ƶ�ϵ��           -5   -4   -3   -2   -1   0   +1   +2   +3   +4   +5   +6   */
float transpose[] = {0.75,0.79,0.84,0.89,0.94,1.0,1.06,1.12,1.19,1.26,1.33,1.41};

/* ��ɫ����ռ�ձ� */
uint8_t voiceDuties[5] = {50,40,30,20,10};

/* OLED��ʾ����ʾ��Ϣ */
// ���ڴ洢�������Ƶ��ַ������顣����6���������ƣ����ɹܡ��ܷ��١��ַ��١�˫�ɹܡ����Ⱥ͹ġ�
char* voiceNames[6] = {"Clarinet","Pipe Organ","Accordion","Oboe","Trumpet","Drums"};
// ���ڴ洢���ַ�����Ƶ��ַ������飬����6�ַ��8�ġ�16�ġ���ҡ����ҡ�ڡ��������ͻ����ȡ�
char* styleNames[6] = {"8Beat","16Beat","Slow Rock","Swing","March","Waltz"};
// ���ڴ洢����״̬���ַ������飬����3��״̬�����ࣨDr&Ap����������Drums����������Arpgo����
char* trackStatus[3] = {"Dr&Ap","Drums","Arpgo"};
// ���ڴ洢����״̬���ַ������飬����4��״̬��ǰ���β����In&Ed����ǰ�ࣨIntro����β����Endng���͹رգ�OFF����
char* sectionStatus[4] = {"In&Ed","Intro","Endng"," OFF "};
// ���ڴ洢�������Ƶ��ַ������飬����8�ֺ������ƣ�C��Dm��Em��E7��F��G��G7��Am��
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
    // ����һ
    Ultrasonic_Init();
    MAX7219_Init();
    OLED_Init();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
    // �����
    /* ��ʼ�� */
    LED_Init_A(LED1|LED2|LED3);//����LED�������Ҹ������ν�A6��A4��A2����һ�˽�����
    Key_Init_A(Key1|Key4);     //��Ļ�·��������ת�������������ֱ��A10��A9����һ�˽�����
    Key_Init_B(Key2|Key3);     //��Ļ�·��м����Ҽ����ֱ��B15��B14����һ�˽�����
    Passive_Buzzer_Init();             //����������������Դ���������������ֱ��A0��A7����һ�˽Ӹ���
//    Encoder_Init();            //��ת��������A��B1��B��B0
//    Keyboard_Init();           //�߸��ټ������������ν�B12��B13��A8��A11��B3��B6��B9����һ�˽�����
    JoyStick_Init();           //PS2ҡ��ģ�飬VRX��A5��VRY��A3��SW��A1
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
    // ����һ
//      OLED_ShowNum(3, 1, cnt, 4);
      // ���µ���ֵ��ʾ���߶������
      Write_Max7219(1, cnt / 10);        // ��ʾʮλ
      Write_Max7219(2, cnt % 10);        // ��ʾ��λ
      // ��ʾ "F" �ڵ�1λ�͵�2λ
      Write_Max7219(3, 15);  // ��ַ1 ��ʾ��һ�� F
      Write_Max7219(4, 15);  // ��ַ2 ��ʾ�ڶ��� F

      distance = Hcsr04GetLength();
      displayValue = (int)(distance * 100);  // 转换为整数，保持两位小数
      integerPart = displayValue / 100;  // 整数部分
      decimalPart = displayValue % 100;   // 小数部分
      if (integerPart > 99)
      {
          integerPart = 99;  // 显示上限
          decimalPart = 0;   // 小数部分设置�??0
      }
      // 显示在数码管�??
      Write_Max7219(5, (integerPart / 10));        // �??3位：十位�??
      Write_Max7219(6, (integerPart % 10) | 0x80);        // �??2位：个位�??
      Write_Max7219(7, (decimalPart / 10));        // �??1位：小数点前�??�??
      Write_Max7219(8, (decimalPart % 10)); // �??0位：小数点后（显示小数点�??

      // ����Ƿ�ﵽ��ֵa
      if (displayValue <= cnt*100)
      {
          Buzzer_Alarm((int)distance); // ���ñ�������
      }


      //�����/**********************************************//************************************************/
      //�����/**********************************************//************************************************/
      //�����/**********************************************//************************************************/
      //�����/**********************************************//************************************************/
      //�����/**********************************************//************************************************/
//      Passive_Buzzer_Timing(3600,20,60,0);
      /* ��ɫģʽ */
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
//          /* ����ģʽ */
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
