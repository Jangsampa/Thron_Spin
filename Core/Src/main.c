/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile uint32_t step_acc = 0;
volatile uint32_t step_inc = 0;
volatile uint8_t step_state = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define TIMER_BASE_HZ 1000000UL
#define REST_FREQ 0
#define NOTE_4 322
#define NOTE_8 161
#define NOTE_16 80

typedef struct
{
    uint16_t freq;
    uint16_t ms;
} NOTE;

#define C2     65
#define CS2    69
#define D2     73
#define DS2    78
#define E2     82
#define F2     87
#define FS2    93
#define G2     98
#define GS2    104
#define A2     110
#define AS2    117
#define B2     123

#define C3     131
#define CS3    139
#define D3     147
#define DS3    156
#define E3     165
#define F3     175
#define FS3    185
#define G3     196
#define GS3    208
#define A3     220
#define AS3    233
#define B3     247

#define C4     262
#define CS4    277
#define D4     294
#define DS4    311
#define E4     330
#define F4     349
#define FS4    370
#define G4     392
#define GS4    415
#define A4     440
#define AS4    466
#define B4     494

#define C5     523
#define CS5    554
#define D5     587
#define DS5    622
#define E5     659
#define F5     698
#define FS5    740
#define G5     784
#define GS5    831
#define A5     880
#define AS5    932
#define B5     988

#define C6     1047
#define CS6    1109
#define D6     1175
#define DS6    1245
#define E6     1319
#define F6     1397
#define FS6    1480
#define G6     1568
#define GS6    1661
#define A6     1760
#define AS6    1865
#define B6     1976

#define C7     2093
#define CS7    2217
#define D7     2349
#define DS7    2489
#define E7     2637
#define F7     2794
#define FS7    2960
#define G7     3136
#define GS7    3322
#define A7     3520
#define AS7    3729
#define B7     3951




NOTE gt1[] =
{
    // ===== C =====
    {C4, NOTE_8}, {REST_FREQ, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8},
    {A4, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {D5, NOTE_8},

    {REST_FREQ, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {A4, NOTE_8},
    {REST_FREQ, NOTE_8}, {B4, NOTE_8}, {A4, NOTE_8}, {G4, NOTE_8},

    {C4, NOTE_8}, {REST_FREQ, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8},
    {A4, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {D5, NOTE_8},

    {REST_FREQ, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {A4, NOTE_8},
    {REST_FREQ, NOTE_8}, {B4, NOTE_8}, {A4, NOTE_8}, {G4, NOTE_8},

    // ===== Em =====
    {E4, NOTE_8}, {REST_FREQ, NOTE_8}, {E5, NOTE_8}, {REST_FREQ, NOTE_8},
    {D5, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {A4, NOTE_8},

    {REST_FREQ, NOTE_8}, {A4, NOTE_8}, {B4, NOTE_8}, {D5, NOTE_8},
    {REST_FREQ, NOTE_8}, {B4, NOTE_8}, {A4, NOTE_8}, {D4, NOTE_8},

    {E4, NOTE_8}, {REST_FREQ, NOTE_8}, {E5, NOTE_8}, {REST_FREQ, NOTE_8},
    {D5, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {A4, NOTE_8},

    {REST_FREQ, NOTE_8}, {A4, NOTE_8}, {B4, NOTE_8}, {D5, NOTE_8},
    {REST_FREQ, NOTE_8}, {E5, NOTE_16}, {D5, NOTE_16}, {B4, NOTE_8}, {REST_FREQ, NOTE_8},

    // ===== C =====
    {C4, NOTE_8}, {REST_FREQ, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8},
    {A4, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {D5, NOTE_8},

    {REST_FREQ, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {A4, NOTE_8},
    {REST_FREQ, NOTE_8}, {B4, NOTE_8}, {A4, NOTE_8}, {G4, NOTE_8},

    {C4, NOTE_8}, {REST_FREQ, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8},
    {A4, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {D5, NOTE_8},

    {REST_FREQ, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {A4, NOTE_8},
    {REST_FREQ, NOTE_8}, {B4, NOTE_8}, {A4, NOTE_8}, {G4, NOTE_8},

      // ===== Em =====
    {E4, NOTE_8}, {REST_FREQ, NOTE_8}, {E5, NOTE_8}, {REST_FREQ, NOTE_8},
    {D5, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {A4, NOTE_8},

    {REST_FREQ, NOTE_8}, {A4, NOTE_8}, {B4, NOTE_8}, {D5, NOTE_8},
    {REST_FREQ, NOTE_8}, {B4, NOTE_8}, {A4, NOTE_8}, {D4, NOTE_8},

    {E4, NOTE_8}, {REST_FREQ, NOTE_8}, {E5, NOTE_8}, {REST_FREQ, NOTE_8},
    {D5, NOTE_8}, {B4, NOTE_8}, {D5, NOTE_8}, {E5, NOTE_4},

    {G5, NOTE_8}, {A5, NOTE_8}, {B5, NOTE_8}, {D6, NOTE_8},
    {B5, NOTE_8}, {A5, NOTE_8}, {B5, NOTE_8}, {REST_FREQ, NOTE_8},
};

void Motor_SetFreq(uint16_t freq)
{
    if(freq == 0)
    {
        LL_TIM_DisableCounter(TIM2);
        LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_0);
        return;
    }

    uint32_t arr = (TIMER_BASE_HZ / (freq * 2UL)) - 1;

    LL_TIM_DisableCounter(TIM2);
    LL_TIM_SetAutoReload(TIM2, arr);
    LL_TIM_SetCounter(TIM2, 0);
    LL_TIM_EnableCounter(TIM2);
}
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
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* System interrupt init*/
  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /** NOJTAG: JTAG-DP Disabled and SW-DP Enabled
  */
  LL_GPIO_AF_Remap_SWJ_NOJTAG();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2); // EN LOW
LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_1); // DIR LOW
LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_0); // STEP LOW

LL_TIM_EnableIT_UPDATE(TIM2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    for(uint16_t i = 0; i < sizeof(gt1) / sizeof(gt1[0]); i++)
    {
        Motor_SetFreq(gt1[i].freq);
        LL_mDelay(gt1[i].ms);
    }

    Motor_SetFreq(0);
    LL_mDelay(1000);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_2)
  {
  }
  LL_RCC_HSE_EnableBypass();
  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_Init1msTick(72000000);
  LL_SetSystemCoreClock(72000000);
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  LL_TIM_InitTypeDef TIM_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

  /* TIM2 interrupt Init */
  NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(TIM2_IRQn);

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  TIM_InitStruct.Prescaler = 72-LL_TIM_IC_FILTER_FDIV1_N2;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 50-LL_TIM_IC_FILTER_FDIV1_N2;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  LL_TIM_Init(TIM2, &TIM_InitStruct);
  LL_TIM_DisableARRPreload(TIM2);
  LL_TIM_SetClockSource(TIM2, LL_TIM_CLOCKSOURCE_INTERNAL);
  LL_TIM_SetTriggerOutput(TIM2, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(TIM2);
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);

  /**/
  LL_GPIO_ResetOutputPin(GPIOA, Motor_1_STEP_Pin|Motor_1_DIR_Pin|Motor_1_EN_Pin|Motor_2_STEP_Pin
                          |Motor_2_DIR_Pin|Motor_2_EN_Pin);

  /**/
  LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTC, LL_GPIO_AF_EXTI_LINE13);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_13;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  LL_GPIO_SetPinMode(B1_GPIO_Port, B1_Pin, LL_GPIO_MODE_FLOATING);

  /**/
  GPIO_InitStruct.Pin = Motor_1_STEP_Pin|Motor_1_DIR_Pin|Motor_1_EN_Pin|Motor_2_STEP_Pin
                          |Motor_2_DIR_Pin|Motor_2_EN_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  NVIC_SetPriority(EXTI15_10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(EXTI15_10_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
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
#ifdef USE_FULL_ASSERT
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
