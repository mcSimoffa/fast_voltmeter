#include "main.h"
#include "stm32f10x.h"
#include "stm32F10x_gpioMY.h"
#include "stm32F10x_usart1.h"
#include "stm32f10x_dma_dihalt.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
  RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN |RCC_APB2ENR_AFIOEN;      //GPIO A & C & AFIO
  RCC->APB1ENR |= RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN;// PWR & Backup Enable
  PinParametr GPIO_descript[1];
 
  GPIO_descript[0].PinPos=ADCIN;
  GPIO_descript[0].PinMode=GPIO_MODE_INPUT_ANALOG;
  CLL_GPIO_SetPinMode(HC05_PORT,GPIO_descript,1);   //HC05_PORT init
   
  GPIO_descript[0].PinPos=LED_13_PIN;
  GPIO_descript[0].PinMode=GPIO_MODE_OUTPUT50_PUSH_PULL;  
  CLL_GPIO_SetPinMode(LED_PORT,GPIO_descript,1);   //GPIOC init
  GPIO_SET(GPIOC,1<<LED_13_PIN);
  GPIO_RESET(GPIOC,1<<LED_13_PIN);
  
   //SWO debug ON
  DBGMCU->CR &= ~(DBGMCU_CR_TRACE_MODE_0 | DBGMCU_CR_TRACE_MODE_0);
  DBGMCU->CR |= DBGMCU_CR_TRACE_IOEN;
  
  // JTAG-DP Disabled and SW-DP Enabled
  AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_1;
  
   RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; //ADC click ON
  RCC->CFGR |= RCC_CFGR_ADCPRE_DIV8; //36/8=4.5MHz for ADC
  ADC1->CR1 = 0;
  ADC1->CR2 |= ADC_CR2_ADON;    // A/D conversion ON
  ADC1->CR2 |= ADC_CR2_RSTCAL;  //Rset calibration
  while((ADC1->CR2 & ADC_CR2_RSTCAL))
    asm("NOP");
  for (int i=0;i<10000;i++)
   asm("NOP");
  ADC1->CR2 |= ADC_CR2_CAL; 
  while (ADC1->CR2 & ADC_CR2_CAL)
    asm("NOP");
  
  ADC1->SMPR2 = ADC_SMPR2_SMP1_0; // 7.5 sample cycles
  ADC1->CR2 |= ADC_CR2_EXTSEL;   // SWSTART
  ADC1->CR2 |= ADC_CR2_EXTTRIG; //conversion on external event enabled
  ADC1->SQR1 = 0x00000000; //1 conversion
  ADC1->SQR2 = 0x00000000;
  ADC1->SQR3 = 0x00000006; //channel 6
  
  

  while (1)
  {
    //Start conversion
  ADC1->CR2 |= ADC_CR2_SWSTART; 
  do
    asm("NOP");
  while((ADC1->SR & ADC_SR_EOC) != ADC_SR_EOC);
  
 uint16_t aa=ADC1->DR;
 printf ("\r\n %d", aa);
     
  }
}
