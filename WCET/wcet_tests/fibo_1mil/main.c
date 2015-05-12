#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

//Quick hack, approximately 1ms delay
void ms_delay(int ms){
   while (ms-- > 0) {
      volatile int x=5971;
      while (x-- > 0)
         __asm("nop");
   }
}

int fib(int n) {
   int first = 0, second = 1;
   int tmp = 0;

   GPIO_SetBits(GPIOB, GPIO_Pin_3);
   /*ms_delay(100);
   GPIO_ResetBits(GPIOB, GPIO_Pin_3);
   GPIO_SetBits(GPIOB, GPIO_Pin_3);*/
   while (n--) {
      tmp = first+second;
      first = second;
      second = tmp;
   }
   
   GPIO_ResetBits(GPIOB, GPIO_Pin_3);
   return tmp;
}



int main(){
   int a;
   a = 1000000;                         // fibonnaci 1 000 000

   GPIO_InitTypeDef GPIO_InitStruct;
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
   GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3; // we want to configure pb3
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; // we want the pins to be an output
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; // this sets the GPIO modules clock speed
   GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // this sets the pin type to push / pull (as opposed to open drain)
   GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; // this sets the pullup / pulldown resistors to be inactive
   GPIO_Init(GPIOB, &GPIO_InitStruct); // this finally passes all the values to the GPIO_Init function which takes care of setting the corresponding bits.

   ms_delay(100);
   while(1){
      fib(a);                             // fibo avec temps de calcul avec pin pb3
      ms_delay(1000);
   }
}
