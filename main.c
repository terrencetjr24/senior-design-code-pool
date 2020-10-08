/**
  ******************************************************************************
  * @file    main.c
  * @author  Eric Bankert
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

//++++[->++++<]>[-<++++>]<+++++.---.

#include "stm32f4xx.h"

#define PIXELCOUNT 200
#define IPIX 7

void initGPIO();
void initTIM1();
void initTIM3();
void initTIM4();
void initDMA2C6S5();

void drawNewLine();

uint8_t dmaTarget[8] = {1, 2, 3, 4, 5, 6, 7, 0};
int notDMA[8] = {0, 1, 2, 3, 4, 5, 6, 7};
int inFrame = 1;

int nextLine = 0;
int linePX = 0;
int newLine = 0;

uint8_t bufferA[PIXELCOUNT + 1];
uint8_t bufferB[PIXELCOUNT + 1];
uint8_t *nextBuffer = bufferB;
int nextBufferN = 1;

int main(void)
{
	FLASH -> ACR |= FLASH_ACR_LATENCY_2WS;
	FLASH -> ACR |= FLASH_ACR_PRFTEN;

	//Now configure the bufferA to just increment;
	for (int i = 0; i < PIXELCOUNT; i++)
	{
		//int j = i % 64;
		//bufferA[i] = (j ^ (j >> 1)) % 256;
		bufferA[i] = i % 256;
		bufferB[i] = 255;
	}
	//Reset to 0 after all pixels transfered
	bufferA[PIXELCOUNT] = 0;
	bufferA[PIXELCOUNT - 1] = 255;
	bufferA[0] = 255;
	bufferB[PIXELCOUNT] = 0;
	bufferB[PIXELCOUNT - 1] = 255;
	bufferB[0] = 255;

	initGPIO();
	initDMA2C6S5();
	initTIM4();
	initTIM3();
	initTIM1();

	for(;;)
	{
		if (newLine)
		{
			if (nextBufferN == 1)
			{
				nextBufferN = 0;
				nextBuffer = bufferA;
			}
			else
			{
				nextBufferN = 1;
				nextBuffer = bufferB;
			}
			//Vars used here:
			//nextLine: The line to process data for
			//nextBuffer: The address of the next buffer
			//nextBufferN: quick reference refering to A(0) or B(1)
			drawNewLine();

			newLine = 0;
		}
	}
}

void initGPIO()
{
	//Enable clock to GPIO port C
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	//Configure lower 8 bits of GPIO port C
	GPIOC -> MODER = 0x5555;
	GPIOC -> OSPEEDR = 0xFFFF;

	//GPIOA PA12 as TIM1 input
	//PA 9 as timer output
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA -> MODER |= 0x2000000;
	GPIOA -> AFR[1] |= 0x10000;

	//Set PA8 as TIm1 ch2?
	//GPIOA -> AFR[1] |= 0x1;
	//GPIOA -> MODER |= 0x20000;
	//GPIOA -> OSPEEDR |= 0x30000;

	//PB0 as TIM3_CH3, PB1 as TIM3_CH4
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB -> AFR[0] |= 0x22;
	GPIOB -> MODER |= 0xA;
	GPIOB -> OSPEEDR |= 0xF;

	//PB6 as TIM4_CH1
	GPIOB -> AFR[0] |= 0x02000000;
	GPIOB -> MODER |= 0x2000;
	GPIOB -> OSPEEDR |= 0x3000;
}

void initTIM1()
{
	RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;

	TIM1 -> CR1 &= ~TIM_CR1_CEN;

	TIM1 -> SMCR |= TIM_SMCR_ECE;
	//TIM1 -> CCR1 = 49;
	//TIM1 -> CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
	//TIM1 -> CCER |= TIM_CCER_CC1E;

	TIM1 -> PSC = 0;
	TIM1 -> ARR = 1;

	//Configure as master
	TIM1 -> CR2 |= TIM_CR2_MMS_1;
	TIM1 -> SMCR |= TIM_SMCR_MSM;

	TIM1 -> DIER |= TIM_DIER_UDE;

	TIM1 -> CR1 |= TIM_CR1_CEN;
}

void initTIM3()
{
	RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;

	TIM3 -> PSC = 0;
	TIM3 -> ARR = 263;

	//TIM2 -> DIER |= TIM_DIER_UDE;

	// |--BP--|------Frame------|--FP--|--SP--|

	//Hzync gen
	TIM3 -> CCR3 = 231;
	TIM3 -> CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1;
	TIM3 -> CCER |= TIM_CCER_CC3E;

	//Interrupt gen
	TIM3 -> CCR1 = 21 - IPIX;//(TIM3 -> ARR) - IPIX;
	TIM3 -> DIER |= TIM_DIER_CC1IE;
	NVIC -> ISER[0] |= 1 << TIM3_IRQn;

	TIM3 -> CCR2 = 21;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC2M;
	TIM3 -> CCER |= TIM_CCER_CC2E;
	TIM3 -> CR2 |= TIM_CR2_MMS_2 | TIM_CR2_MMS_0;

	//Slave mode
	TIM3 -> SMCR |= TIM_SMCR_SMS;
	//Generate Output events
	//TIM3 -> CR2 |= TIM_CR2_MMS_1;
	//TIM2 -> SMCR |= TIM_SMCR_TS;

	TIM3 -> CR1 |= TIM_CR1_CEN;
}

void TIM3_IRQHandler()
{
	TIM3 -> SR &= ~TIM_SR_CC1IF;
	if (inFrame == 1)
	{
		//DMA2_Stream5 -> CR &= ~DMA_SxCR_EN;
		DMA2 -> HIFCR |= DMA_HIFCR_CTCIF5;
		DMA2_Stream5 -> PAR = nextBuffer;
		DMA2_Stream5 -> CR |= DMA_SxCR_EN;

		linePX += 1;
		if (linePX == 4)
		{
			linePX = 0;
			nextLine += 1;
			newLine = 1;
		}
	}
}

void initTIM4()
{
	RCC -> APB1ENR |= RCC_APB1ENR_TIM4EN;

	TIM4 -> PSC = 0;
	TIM4 -> ARR = 627;

	//Visible area, front, back for VSYNC Generation
	TIM4 -> CCR1 = 624;
	TIM4 -> CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
	TIM4 -> CCER |= TIM_CCER_CC1E;

	//Configure CCR2 and 3 to monitor for VSYNC and HSYNC blocking
	//CCR2 disables frames
	TIM4 -> CCR2 = 22; // Enable video here
	TIM4 -> CCR3 = 622; // Disable here
	TIM4 -> DIER |= TIM_DIER_CC2IE | TIM_DIER_CC3IE;
	NVIC -> ISER[0] |= 1 << TIM4_IRQn;

	//Slave as TIM2
	TIM4 -> SMCR |= TIM_SMCR_SMS;
	TIM4 -> SMCR |= TIM_SMCR_TS_1;

	TIM4 -> CR1 |= TIM_CR1_CEN;
}
//1, 2, 5 3, 4, 9, 10, 11

void TIM4_IRQHandler()
{
	if (((TIM4 -> SR) & TIM_SR_CC2IF) == TIM_SR_CC2IF)
	{
		TIM4 -> SR &= ~TIM_SR_CC2IF;
		inFrame = 1;
	}
	else
	{
		TIM4 -> SR &= ~TIM_SR_CC3IF;
		inFrame = 0;
		nextLine = 0;
		newLine = 1;
		linePX = 0;
	}
}


void initDMA2C6S5()
{
	RCC -> AHB1ENR |= RCC_AHB1ENR_DMA2EN;

	//Select channel 6
	DMA2_Stream5 -> CR |= DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_1;
	//Enable Peripheral increment
	DMA2_Stream5 -> CR |= DMA_SxCR_PINC;
	//Circular mode
	//DMA2_Stream5 -> CR |= DMA_SxCR_CIRC;

	DMA2_Stream5 -> CR &= ~(DMA_SxCR_PSIZE | DMA_SxCR_MSIZE);
	//DMA2_Stream5 -> CR |= DMA_SxCR_DIR_1;

	//Transfer 8 data
	DMA2_Stream5 -> NDTR = PIXELCOUNT + 1;
	//Configure source as perph
	DMA2_Stream5 -> PAR = (uint32_t) bufferA;
	//Configure gpio dest as mem
	DMA2_Stream5 -> M0AR = (uint32_t) 0x40020814;

	//DMA2_Stream5 -> FCR |= DMA_SxFCR_DMDIS;
	//DMA2_Stream5 -> FCR |= DMA_SxFCR_FTH;

	DMA2_Stream5 -> CR |= DMA_SxCR_EN;
}


void drawNewLine()
{
	//Simple demo for screen
	int* nbp = (int*) nextBuffer;
	if (nextLine < 100)
	{
		for (int i = 0; i < PIXELCOUNT; i ++)
		{
			if (i < 27)
				nextBuffer[i] = 0b00010101;
			else if (i < 55)
				nextBuffer[i] = 0b00001111;
			else if (i < 83)
				nextBuffer[i] = 0b00110110;
			else if (i < 111)
				nextBuffer[i] = 0b00001110;
			else if (i < 139)
				nextBuffer[i] = 0b00010001;
			else if (i < 167)
				nextBuffer[i] = 0b00000001;
			else
				nextBuffer[i] = 0b00011000;
		}
	}
	else if (nextLine < 114)
	{
		for (int i = 0; i < PIXELCOUNT; i++)
		{
			if (i < 27)
				nextBuffer[i] = 0b00110010;
			else if (i < 55)
				nextBuffer[i] = 0b00000000;
			else if (i < 83)
				nextBuffer[i] = 0b00010001;
			else if (i < 111)
				nextBuffer[i] = 0b00000000;
			else if (i < 139)
				nextBuffer[i] = 0b00111100;
			else if (i < 167)
				nextBuffer[i] = 0b00000000;
			else
				nextBuffer[i] = 0b00010101;
		}
	}
	else
	{
		for (int i = 0; i < PIXELCOUNT; i++)
		{
			if (i < 34)
				nextBuffer[i] = 0b00011000;
			else if (i < 69)
				nextBuffer[i] = 0b00111111;
			else if (i < 104)
				nextBuffer[i] = 0b00010010;
			else if (i < 139)
				nextBuffer[i] = 0b00101010;
			else if (i < 167)
				nextBuffer[i] = 0b00010101;
			else
				nextBuffer[i] = 0b00111111;
		}
	}
}
