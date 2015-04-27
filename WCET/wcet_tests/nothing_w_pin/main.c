/* Does nothing, just tests the power consumption with a pin on */

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

int main(){
   /* Toggle the pin PD3 */
   GPIO_InitTypeDef GPIO_InitStruct;
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
   GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3; // we want to configure pd3
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; // we want the pins to be an output
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; // this sets the GPIO modules clock speed
   GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // this sets the pin type to push / pull (as opposed to open drain)
   GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; // this sets the pullup / pulldown resistors to be inactive
   GPIO_Init(GPIOD, &GPIO_InitStruct); // this finally passes all the values to the GPIO_Init function which takes care of setting the corresponding bits.
   GPIO_ToggleBits(GPIOD, GPIO_Pin_3)GPIOD;
   
   /* Does nothing */
   while(1){}
}
