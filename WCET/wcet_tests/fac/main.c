/* MDH WCET BENCHMARK SUITE */
/*
 * Changes: CS 2006/05/19: Changed loop bound from constant to variable.
 */
#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
//Quick hack, approximately 1ms delay
void ms_delay(int ms){
   GPIOD->MODER = (1 << 28);             // set pin 14 to be general purpose output
   GPIOD->ODR ^= (1 << 14);              // allumer la led rouge
   while (ms-- > 0) {
      volatile int x=5971;
      while (x-- > 0)
         __asm("nop");
   }
   GPIOD->ODR ^= (1 << 14);              // enteindre la led rouge
}
int fac (int n)
{
  if (n == 0)
     return 1;
  else
     return (n * fac (n-1));
}

int main (void)
{
  int i;
  int s = 0;
  volatile int n;
 RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;  // enable the clock to GPIOD
 ms_delay(100);
 while(1){
  n = 5;
  for (i = 0;  i <= n; i++)
      s += fac (i);
      ms_delay(1000); 
 }
}

