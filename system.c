#include "stm32f4xx.h"
#include "system.h"

static volatile unsigned long s_ms = 0ul;

void SysTick_Handler(void)
{
    s_ms++;
}

unsigned long Millis(void)
{
    return s_ms;   /* 32-bit read is atomic on Cortex-M4 */
}

void SysTick_Init_1ms(void)
{
    (void)SysTick_Config(SystemCoreClock / 1000u);
}

/* IWDG clocked by LSI (~32 kHz, 17..47 kHz over temperature).
   Prescaler /32 -> ~1 kHz, reload 100 -> ~100 ms (worst case ~68 ms).
   Main loop runs in microseconds, so this only fires on a firmware hang;
   after reset all pins float/low and the H-bridges are disabled. */
void IWDG_Init_100ms(void)
{
#if IWDG_ENABLE
    DBGMCU->APB1FZ |= DBGMCU_APB1_FZ_DBG_IWDG_STOP;   /* freeze on breakpoint */
    IWDG->KR  = 0x5555u;          /* unlock PR/RLR      */
    IWDG->PR  = 0x3u;             /* /32                */
    IWDG->RLR = 100u;
    IWDG->KR  = 0xAAAAu;          /* reload             */
    IWDG->KR  = 0xCCCCu;          /* start              */
#endif
}

void IWDG_Kick(void)
{
#if IWDG_ENABLE
    IWDG->KR = 0xAAAAu;
#endif
}

void Clock_Init(void){

			// Conf clock : 84 MHz using HSI 16MHz crystal w/ PLL M= 16, N= 336, P=4, AHB preescaler = 1, APB1 preescaler = 2, APB2 PRESSCALES =1 */

			RCC->CR |=  ((uint32_t)0x0000001 << 0);   //enable HSI clock (uint32_t)0x0000001 (CR:bit 0)
			while( !(RCC->CR & (0x1<<1)));            //wait for the HSIREADY flag  (CR:bit 1)
	
			RCC->APB1ENR |= (1 << 28);      			    //Power interface clock enable (APB1ENB:bit 28)

			RCC->CFGR |= (0 << 7);      			    		//set prescale AHB1 = HCLK (CFGR:bits 7:4) sin preescaler
			RCC->CFGR |= (0x4 << 10);                 //set APB low speed prescaler to /2 (APB1) (CFGR:bits 12:10)  42 Mhz
      RCC->CFGR |= (0 << 15);                   //set ABP high speed prescaper to /1 (ABP2) (CFGR:bits 15:13) 84 Mhz

			//Set M, N and P dividers
			RCC->PLLCFGR &= (~(0x3FU) << 0);
			RCC->PLLCFGR |=  (0x10U << 0);                     //set PLLM division factor by 16d (vco input frecuency 1 MHz) (PLLCFGR:bits 0:5)
			
	    RCC->PLLCFGR &= ~((0x1FFU <<6));
	    RCC->PLLCFGR |= (0x150U <<6);              //set PLLN multiplication factor by 336d (vco output frecuency 336 MHz) (PLLCFGR:bits 6:14)
			
			RCC->PLLCFGR &= ~(0x3U <<16);
			RCC->PLLCFGR |= (0x01 <<16); 	            //set PLLP main PLL division factor 4 (PLLCFGR:bits 16:17)

			//Enable PLL 
			RCC->CR |= (0x1 <<24);                    //enable the PLL (CR:bits 24)
			while( !(RCC->CR & (0x1 << 25)));         //wait for the PLLRDY flag
	
			FLASH->ACR = (1 << 8) | (1 << 9) | (1 << 10 ) | (2 << 0);  //Define latency

			
			//Select PLL as system clock source
			RCC->CFGR &= ~(3U << 0);                  //(CFG:bits 0:1)
			RCC->CFGR |= (0x2 << 0);                  // PLL as a system clock (CFG:bits 0:1)


			while( !(RCC->CFGR & (0x2 << 2)));        //wait for system clock switch status to PLL as used as system clock source (CFG:bits 2:3)
			SystemCoreClockUpdate();
}
