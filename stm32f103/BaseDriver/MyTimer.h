#ifndef _MYTIMER_H_
#define _MYTIMER_H_
#include "stm32f10x.h"

typedef void (*FUNC_ITHANDLER)(void);

typedef struct{
	uint8_t           isAPB1;
	uint32_t          rcc;
	uint8_t           irqn;
	TIM_TypeDef *     name;
	uint16_t          itflag;
	uint16_t          it;
	uint8_t           cnl;
	FUNC_ITHANDLER    ithandler;
	uint32_t          arr;
	uint16_t          psc;
}Tim_Info;

//My Timer tim 6
#define MYTIMER_ISAPB1      1
#define MYTIMER_TIM_RCC     RCC_APB1Periph_TIM6
#define MYTIMER_TIM_IRQN    TIM6_IRQn
#define MYTIMER_TIM         TIM6
#define MYTIMER_TIM_ITFLAG  TIM_FLAG_Update
#define MYTIMER_TIM_IT      TIM_IT_Update
#define MYTIMER_TIM_CNL     TIMR_CNL_1

void MyTimer_Start(void);
void MyTimer_IT_Handler(void);

void Timer_Init(Tim_Info timer);
void Timer_Start(Tim_Info timer);
void Timer_Stop(Tim_Info timer);

#endif