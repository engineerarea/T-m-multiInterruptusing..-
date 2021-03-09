#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM


void gpioConfig(){

GPIO_InitTypeDef  GpioInitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	GpioInitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GpioInitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GpioInitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC,&GpioInitStructure);

}

void TimerConfig(){

TIM_TimeBaseInitTypeDef TimerInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	
	TimerInitStructure.TIM_ClockDivision=1;
	TimerInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TimerInitStructure.TIM_Period=5999;
	TimerInitStructure.TIM_Prescaler=1999;
	TimerInitStructure.TIM_RepetitionCounter=0;
	
	TIM_TimeBaseInit(TIM3,&TimerInitStructure);
  TIM_Cmd(TIM3,ENABLE);
	
	TimerInitStructure.TIM_ClockDivision=1;
	TimerInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TimerInitStructure.TIM_Period=5999;
	TimerInitStructure.TIM_Prescaler=3999;
	TimerInitStructure.TIM_RepetitionCounter=0;
	
TIM_TimeBaseInit(TIM4,&TimerInitStructure);
TIM_Cmd(TIM4,ENABLE);

}

void NvicConfig(){

	NVIC_InitTypeDef   NvicInitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NvicInitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NvicInitStructure.NVIC_IRQChannelCmd=ENABLE;
	NvicInitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NvicInitStructure.NVIC_IRQChannelSubPriority=0;
	
	NVIC_Init(&NvicInitStructure);

	
	
	NvicInitStructure.NVIC_IRQChannel=TIM4_IRQn;
	NvicInitStructure.NVIC_IRQChannelCmd=ENABLE;
	NvicInitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NvicInitStructure.NVIC_IRQChannelSubPriority=0;
  
	NVIC_Init(&NvicInitStructure);

}


void toogle(){

uint16_t led_read=GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_0|GPIO_Pin_1);
	
	if(led_read==(uint16_t)Bit_SET){
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1);
	
	}
	else{
	
	GPIO_SetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1);
	
	}


}


void TIM3_IRQHandler(){


toogle();
	
	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	
}


void TIM4_IRQHandler(){


toogle();


TIM_ClearITPendingBit(TIM4,TIM_IT_Update);


}

int main(){

gpioConfig();
	TimerConfig();
	NvicConfig();
	
	while(1){

		//////////////////////////////

}


}