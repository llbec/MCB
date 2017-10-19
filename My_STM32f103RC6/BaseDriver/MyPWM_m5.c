/**
  ******************************************************************************
  * @file    MyPWM_m5.c
  * @author  Bic
  * @version V1.0.0
  * @date    17-October-2017
  * @brief   This file provides all the Motor functions.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "MyPWM_m5.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define  A_ON          TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable)
#define  A_OFF         TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable)
#define  AN_ON         TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCxN_Enable)
#define  AN_OFF        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable)
#define  A_H           TIM_SetCompare1(TIM1, (FullPulse + 100))
#define  A_ADD_0       TIM_SetCompare1(TIM1, (EmptyPulse + ((pulseCount+1)*CCR_Val)))
#define  A_ADD_HALF    TIM_SetCompare1(TIM1, (DefaultPulse + ((pulseCount+1)*CCR_Val)))
#define  A_SUB_FULL    TIM_SetCompare1(TIM1, (FullPulse - ((pulseCount+1)*CCR_Val)))
#define  A_SUB_HALF    TIM_SetCompare1(TIM1, (DefaultPulse - ((pulseCount+1)*CCR_Val)))

#define  B_ON          TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable)
#define  B_OFF         TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable)
#define  BN_ON         TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCxN_Enable)
#define  BN_OFF        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable)
#define  B_H           TIM_SetCompare2(TIM1, (FullPulse + 100))
#define  B_ADD_0       TIM_SetCompare2(TIM1, (EmptyPulse + ((pulseCount+1)*CCR_Val)))
#define  B_ADD_HALF    TIM_SetCompare2(TIM1, (DefaultPulse + ((pulseCount+1)*CCR_Val)))
#define  B_SUB_FULL    TIM_SetCompare2(TIM1, (FullPulse - ((pulseCount+1)*CCR_Val)))
#define  B_SUB_HALF    TIM_SetCompare2(TIM1, (DefaultPulse - ((pulseCount+1)*CCR_Val)))

#define  C_ON          TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Enable)
#define  C_OFF         TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable)
#define  CN_ON         TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCxN_Enable)
#define  CN_OFF        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable)
#define  C_H           TIM_SetCompare3(TIM1, (FullPulse + 100))
#define  C_ADD_0       TIM_SetCompare3(TIM1, (EmptyPulse + ((pulseCount+1)*CCR_Val)))
#define  C_ADD_HALF    TIM_SetCompare3(TIM1, (DefaultPulse + ((pulseCount+1)*CCR_Val)))
#define  C_SUB_FULL    TIM_SetCompare3(TIM1, (FullPulse - ((pulseCount+1)*CCR_Val)))
#define  C_SUB_HALF    TIM_SetCompare3(TIM1, (DefaultPulse - ((pulseCount+1)*CCR_Val)))

#define  F_ON          TIM_CCxCmd(TIM8, TIM_Channel_1, TIM_CCx_Enable)
#define  F_OFF         TIM_CCxCmd(TIM8, TIM_Channel_1, TIM_CCx_Disable)
#define  FN_ON         TIM_CCxCmd(TIM8, TIM_Channel_1, TIM_CCxN_Enable)
#define  FN_OFF        TIM_CCxCmd(TIM8, TIM_Channel_1, TIM_CCxN_Disable)
#define  F_H           TIM_SetCompare1(TIM8, (FullPulse + 100))
#define  F_ADD_0       TIM_SetCompare1(TIM8, (EmptyPulse + ((pulseCount+1)*CCR_Val)))
#define  F_ADD_HALF    TIM_SetCompare1(TIM8, (DefaultPulse + ((pulseCount+1)*CCR_Val)))
#define  F_SUB_FULL    TIM_SetCompare1(TIM8, (FullPulse - ((pulseCount+1)*CCR_Val)))
#define  F_SUB_HALF    TIM_SetCompare1(TIM8, (DefaultPulse - ((pulseCount+1)*CCR_Val)))

#define  D_ON          F_ON;TIM_CCxCmd(TIM8, TIM_Channel_2, TIM_CCx_Enable)
#define  D_OFF         F_OFF;TIM_CCxCmd(TIM8, TIM_Channel_2, TIM_CCx_Disable)
#define  DN_ON         FN_ON;TIM_CCxCmd(TIM8, TIM_Channel_2, TIM_CCxN_Enable)
#define  DN_OFF        FN_OFF;TIM_CCxCmd(TIM8, TIM_Channel_2, TIM_CCxN_Disable)
#define  D_H           F_H;TIM_SetCompare2(TIM8, (FullPulse + 100))
#define  D_ADD_0       F_ADD_0;TIM_SetCompare2(TIM8, (EmptyPulse + ((pulseCount+1)*CCR_Val)))
#define  D_ADD_HALF    F_ADD_HALF;TIM_SetCompare2(TIM8, (DefaultPulse + ((pulseCount+1)*CCR_Val)))
#define  D_SUB_FULL    F_SUB_FULL;TIM_SetCompare2(TIM8, (FullPulse - ((pulseCount+1)*CCR_Val)))
#define  D_SUB_HALF    F_SUB_HALF;TIM_SetCompare2(TIM8, (DefaultPulse - ((pulseCount+1)*CCR_Val)))

#define  E_ON          TIM_CCxCmd(TIM8, TIM_Channel_3, TIM_CCx_Enable)
#define  E_OFF         TIM_CCxCmd(TIM8, TIM_Channel_3, TIM_CCx_Disable)
#define  EN_ON         TIM_CCxCmd(TIM8, TIM_Channel_3, TIM_CCxN_Enable)
#define  EN_OFF        TIM_CCxCmd(TIM8, TIM_Channel_3, TIM_CCxN_Disable)
#define  E_H           TIM_SetCompare3(TIM8, (FullPulse + 100))
#define  E_ADD_0       TIM_SetCompare3(TIM8, (EmptyPulse + ((pulseCount+1)*CCR_Val)))
#define  E_ADD_HALF    TIM_SetCompare3(TIM8, (DefaultPulse + ((pulseCount+1)*CCR_Val)))
#define  E_SUB_FULL    TIM_SetCompare3(TIM8, (FullPulse - ((pulseCount+1)*CCR_Val)))
#define  E_SUB_HALF    TIM_SetCompare3(TIM8, (DefaultPulse - ((pulseCount+1)*CCR_Val)))
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t TimerPeriod = 0, TIM6Period = 0;
uint16_t DefaultPulse = 0, EmptyPulse = 0, FullPulse = 0/*, HalfPulse = 0*/;

uint16_t CCR_Val = 0;
uint16_t stepSpeed = 8;/*PWM_DEFAULT_PERIOD / stepPerPWM*/
uint32_t stepPerPWM = 0;

uint16_t pulseStep = 0, pulseCount = 0, stepCount = 0;
//uint8_t startPulse_A = 0;
//uint8_t pulseMove_A = 0;

/* Private function prototypes -----------------------------------------------*/
void M5_TIM1_RCC_Configuration(void);
void M5_TIM1_GPIO_Configuration(void);
void M5_StateStep(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void M5_TIM1_RCC_Configuration(void)
{
  /* TIM1, GPIOA, GPIOB, GPIOE and AFIO clocks enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE|
                         RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO, ENABLE);
}

void M5_TIM8_RCC_Configuration(void)
{
  /* TIM8, GPIOA, GPIOB and GPIOC clocks enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 | RCC_APB2Periph_GPIOC, ENABLE);
}

/**
  * @brief  Configure the TIM1 Pins.
  * @param  None
  * @retval None
  */
void M5_TIM1_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

#ifdef STM32F10X_CL
  /* GPIOE Configuration: Channel 1/1N, 2/2N, 3/3N and 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14|
                                GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOE, &GPIO_InitStructure);

  /* TIM1 Full remapping pins */
  GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE); 

#else
  /* GPIOA Configuration: Channel 1, 2 and 3 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* GPIOB Configuration: Channel 1N, 2N and 3N as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

#endif
}

void M5_TIM8_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* GPIOA Configuration: Channel 1, 2 and 3 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* GPIOB Configuration: Channel 1N, 2N and 3N as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

/**
  * @brief  Configures the TIM1 nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void M5_TIM1_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the TIM1 Interrupt */
#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL)
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_TRG_COM_TIM17_IRQn;
#else
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_TRG_COM_IRQn;
#endif
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 

}

/**
  * @brief  Configures the TIM6 nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void M5_TIM6_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
		/* Enable the TIM6 for motor0 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/* Public functions ---------------------------------------------------------*/
/**
  * @brief  Configure the TIM1 and enable.
  * @param  uint32_t period (Hz)
  * @retval None
  */
void M5_TIM1_Init(uint32_t period)
{
	/* System Clocks Configuration */
  M5_TIM1_RCC_Configuration();

  /* GPIO Configuration */
  M5_TIM1_GPIO_Configuration();
	
	/* NVIC Configuration */
  //M5_TIM1_NVIC_Configuration();

  /* TIM1 Configuration ---------------------------------------------------
   Generate 7 PWM signals with 4 different duty cycles:
   TIM1CLK = SystemCoreClock, Prescaler = 0, TIM1 counter clock = SystemCoreClock
   SystemCoreClock is set to 72 MHz for Low-density, Medium-density, High-density
   and Connectivity line devices and to 24 MHz for Low-Density Value line and
   Medium-Density Value line devices
   
   The objective is to generate 7 PWM signal at 17.57 KHz:
     - TIM1_Period = (SystemCoreClock / (17570 * (psc+1))) - 1
   The channel 1 and channel 1N duty cycle is set to 50%
   The channel 2 and channel 2N duty cycle is set to 37.5%
   The channel 3 and channel 3N duty cycle is set to 25%
   The channel 4 duty cycle is set to 12.5%
   The Timer pulse is calculated as follows:
     - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100
  ----------------------------------------------------------------------- */
  /* Compute the value to be set in ARR regiter to generate signal frequency at 17.57 Khz */
  //TimerPeriod = (SystemCoreClock / 17570 ) - 1;
	TimerPeriod = (SystemCoreClock / period ) - 1;
	
	DefaultPulse = (uint16_t) (((uint32_t) 50 * (TimerPeriod - 1)) / 100);
	CCR_Val = (uint16_t) (uint16_t) (((uint32_t) 2 * (TimerPeriod - 1)) / 100);
	EmptyPulse = (uint16_t) (uint16_t) (((uint32_t) 2 * (TimerPeriod - 1)) / 100);
	FullPulse = TimerPeriod - 1;
  /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 and 1N */
  //Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);
  /* Compute CCR2 value to generate a duty cycle at 37.5%  for channel 2 and 2N */
  //Channel2Pulse = (uint16_t) (((uint32_t) 375 * (TimerPeriod - 1)) / 1000);
  /* Compute CCR3 value to generate a duty cycle at 25%  for channel 3 and 3N */
  //Channel3Pulse = (uint16_t) (((uint32_t) 25 * (TimerPeriod - 1)) / 100);
  /* Compute CCR4 value to generate a duty cycle at 12.5%  for channel 4 */
  //Channel4Pulse = (uint16_t) (((uint32_t) 125 * (TimerPeriod- 1)) / 1000);

  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  /* Channel 1, 2,3 and 4 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = DefaultPulse;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = DefaultPulse;
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = DefaultPulse;
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);

  //TIM_OCInitStructure.TIM_Pulse = Channel4Pulse;
  //TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	/* TIM1 Arr reload Enable */
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	//TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM1, ENABLE);
	
  /* TIM IT enable */
  //TIM_ITConfig(TIM1, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);

  /* TIM1 counter enable */
  //TIM_Cmd(TIM1, ENABLE);

  /* TIM1 Main Output Enable */
  //TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void M5_TIM8_Init(uint32_t period)
{
	/* System Clocks Configuration */
  M5_TIM8_RCC_Configuration();

  /* GPIO Configuration */
  M5_TIM8_GPIO_Configuration();

  /* TIM8 Configuration ---------------------------------------------------
   Generate 7 PWM signals with 4 different duty cycles:
   TIM1CLK = SystemCoreClock, Prescaler = 0, TIM1 counter clock = SystemCoreClock
   SystemCoreClock is set to 72 MHz for Low-density, Medium-density, High-density
   and Connectivity line devices and to 24 MHz for Low-Density Value line and
   Medium-Density Value line devices
   
   The objective is to generate 7 PWM signal at 17.57 KHz:
     - TIM1_Period = (SystemCoreClock / 17570) - 1
   The channel 1 and channel 1N duty cycle is set to 50%
   The channel 2 and channel 2N duty cycle is set to 37.5%
   The channel 3 and channel 3N duty cycle is set to 25%
   The channel 4 duty cycle is set to 12.5%
   The Timer pulse is calculated as follows:
     - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100
  ----------------------------------------------------------------------- */
  /* Compute the value to be set in ARR regiter to generate signal frequency at 17.57 Khz */
  //TimerPeriod = (SystemCoreClock / 17570 ) - 1;
	//TimerPeriod = (SystemCoreClock / period ) - 1;
	//CCR_Val = (uint16_t) (((uint32_t) 25 * (TimerPeriod - 1)) / 1000);
	//DefaultPulse = (uint16_t) (((uint32_t) 50 * (TimerPeriod - 1)) / 100);
	//EmptyPulse = 0;
	//FullPulse = TimerPeriod - 1;
  /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 and 1N */
  //Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);
  /* Compute CCR2 value to generate a duty cycle at 37.5%  for channel 2 and 2N */
  //Channel2Pulse = (uint16_t) (((uint32_t) 375 * (TimerPeriod - 1)) / 1000);
  /* Compute CCR3 value to generate a duty cycle at 25%  for channel 3 and 3N */
  //Channel3Pulse = (uint16_t) (((uint32_t) 25 * (TimerPeriod - 1)) / 100);
  /* Compute CCR4 value to generate a duty cycle at 12.5%  for channel 4 */
  //Channel4Pulse = (uint16_t) (((uint32_t) 125 * (TimerPeriod- 1)) / 1000);

  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

  /* Channel 1, 2,3 and 4 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = DefaultPulse;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  TIM_OC1Init(TIM8, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = DefaultPulse;
  TIM_OC2Init(TIM8, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = DefaultPulse;
  TIM_OC3Init(TIM8, &TIM_OCInitStructure);

  //TIM_OCInitStructure.TIM_Pulse = Channel4Pulse;
  //TIM_OC4Init(TIM8, &TIM_OCInitStructure);

	/* TIM1 Arr reload Enable */
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	//TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM8, ENABLE);
	
  /* TIM IT enable */
  //TIM_ITConfig(TIM8, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);

  /* TIM8 counter enable */
  //TIM_Cmd(TIM8, ENABLE);

  /* TIM8 Main Output Enable */
  //TIM_CtrlPWMOutputs(TIM8, ENABLE);
}

void M5_IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_11);
	GPIO_ResetBits(GPIOA, GPIO_Pin_12);
}

/**
  * @brief  Configure the TIM6
  * @param  uint32_t period (Hz)
  * @retval None
  */
void M5_tim6_testIO(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
/*
	period = Hz*(psc + 1)
*/
void M5_TIM6_Init(uint32_t period)
{
	/*test io configuration*/
	//M5_tim6_testIO();
	M5_IO_Init();
	
	/* NVIC Configuration */
  M5_TIM6_NVIC_Configuration();
	
	/* System Clocks Configuration */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	//TimerPeriod = (SystemCoreClock / period ) - 1;
	TIM6Period = (SystemCoreClock / period ) - 1;
	
	stepPerPWM = period / (2*stepSpeed);
	//CCR_Val = (uint16_t) (((uint32_t) (100 / (stepPerPWM * 2)) * (TimerPeriod - 1)) / 100);
	//CCR_Val = (uint16_t) ((TimerPeriod - 1) / (stepPerPWM * 2));
	
	/* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TIM6Period;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	
	/* TIM IT enable */
	TIM_ITConfig(TIM6, TIM_IT_Update | TIM_IT_Trigger, ENABLE);
	
	//TIM_Cmd(TIM6, ENABLE);
}

void M5_Start(void)
{
	/* TIM1&8 counter enable */
	TIM_Cmd(TIM1, ENABLE);
  TIM_Cmd(TIM8, ENABLE);

  /* TIM1&8 Main Output Enable */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
  TIM_CtrlPWMOutputs(TIM8, ENABLE);
	
	/* TIM6 counter enable */
	TIM_Cmd(TIM6, ENABLE);
	
	//GPIO_SetBits(GPIOA, GPIO_Pin_11);
	//GPIO_SetBits(GPIOA, GPIO_Pin_12);
}

/**
  * @brief  steps function
  * @param  None
  * @retval None
  */
void M5_Step(void)
{
	//uint16_t pulse = 0;
	//capture = TIM_GetCapture1(TIM1);
	//TIM_SetCompare1(TIM1, capture + CCR_Val);
	//pulseStep++;
	/*if(pulseStep%2 == 0)
		GPIO_SetBits(GPIOC, GPIO_Pin_8);
	else
		GPIO_ResetBits(GPIOC, GPIO_Pin_8);*/
	if(pulseStep == 0)
	{
		M5_StateStep();
	}
	if(pulseStep++ > 136)
	{
		pulseCount++;
		if(pulseCount >21)
		{
			stepCount++;
			if(stepCount > 9)
				stepCount = 0;
			pulseCount = 0;
		}
		pulseStep = 0;
	}
	//M5_StateStep();
}

/*
	The following Table  describes the steps states:
              -------------------------------------------------------------------------------
             | Step1 | Step2 | Step3 | Step4 | Step5 | Step6 | Step7 | Step8 | Step9 | Step10|
   ------------------------------------------------------------------------------------------
  |    a     |   1   |   0   |   0   |   0   |   0   |   0   |   1   |   1   |   1   |   1   |
   ------------------------------------------------------------------------------------------
  |    b     |   1   |   1   |   1   |   0   |   0   |   0   |   0   |   0   |   1   |   1   |
   ------------------------------------------------------------------------------------------
  |    c     |   1   |   1   |   1   |   1   |   1   |   0   |   0   |   0   |   0   |   0   |
   ------------------------------------------------------------------------------------------
  |    d     |   0   |   0   |   1   |   1   |   1   |   1   |   1   |   0   |   0   |   0   |
   ------------------------------------------------------------------------------------------
  |    e     |   0   |   0   |   0   |   0   |   1   |   1   |   1   |   1   |   1   |   0   |
   ------------------------------------------------------------------------------------------
  |          |   0   |   0   |   0   |   0   |   0   |   0   |   0   |   0   |   0   |   0   |
   ------------------------------------------------------------------------------------------
*/
void M5_StateStep(void)
{
	switch(stepCount)
	{
		case 0:
			A_SUB_FULL;
			
			B_H;
		
			C_ADD_HALF;
		
			D_OFF;
		
			E_OFF;
			EN_ON;
			E_H;
			//stepCount = 1;
			break;
		case 1:
			A_SUB_HALF;
		
			B_H;
		
			C_H;
		
			DN_OFF;
			D_ON;
			D_ADD_0;
		
			E_OFF;
			//stepCount = 2;
			break;
		case 2:
			//A_ON;
			A_OFF;
			AN_ON;
			A_H;
		
			B_SUB_FULL;
		
			C_H;
		
			D_ADD_HALF;
		
			E_OFF;
			//stepCount = 3;
			break;
		case 3:
			//A_ON;
			A_OFF;
		
			B_SUB_HALF;
		
			C_H;
		
			D_H;
		
			EN_OFF;
			E_ON;
			E_ADD_0;
			//stepCount = 4;
			break;
		case 4:
			//A_ON;
			A_OFF;
		
			B_OFF;
			BN_ON;
			B_H;
		
			C_SUB_FULL;
		
			D_H;
		
			E_ADD_HALF;
			//stepCount = 5;
			break;
		case 5:
			AN_OFF;
			A_ON;
			A_ADD_0;
		
			B_OFF;
		
			C_SUB_HALF;
		
			D_H;
		
			E_H;
			//stepCount = 6;
			break;
		case 6:
			A_ADD_HALF;
		
			B_OFF;
		
			C_OFF;
			CN_ON;
			C_H;
		
			D_SUB_FULL;
		
			E_H;
			//stepCount = 7;
			break;
		case 7:
			A_H;
		
			BN_OFF;
			B_ON;
			B_ADD_0;
		
			C_OFF;
		
			D_SUB_HALF;
		
			E_H;
			//stepCount = 8;
			break;
		case 8:
			A_H;
		
			B_ADD_HALF;
		
			C_OFF;
		
			D_OFF;
			DN_ON;
		
			E_SUB_FULL;
			//stepCount = 9;
			break;
		default:
			A_H;
		
			B_H;
		
			CN_OFF;
			C_ON;
			C_ADD_0;
		
			D_OFF;
		
			E_SUB_HALF;
			//stepCount = 0;
			break;
	}
}
