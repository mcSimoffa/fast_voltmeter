#define DEBUG_MODE
#include "stm32f10x_dma_dihalt.h"
#include "stm32F10x_usart1.h"

void SendStringUsart1WithDMA(const char *AdresOfString,uint16_t quantil)
{    
  DMA_Disable(DMA1_Channel4);
  DMA_Set_Mem_Addr(DMA1_Channel4,(uint32_t)AdresOfString);
  DMA_Set_Size(DMA1_Channel4,quantil);
  DMA1->IFCR = DMA_IFCR_CTCIF4;
  USART1->SR &= ~USART_SR_TC;
  DMA_Enable (DMA1_Channel4);
}

