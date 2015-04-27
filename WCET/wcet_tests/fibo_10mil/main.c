/* $Id: fibcall.c,v 1.2 2005/04/04 11:34:58 csg Exp $ */

/*************************************************************************/
/*                                                                       */
/*   SNU-RT Benchmark Suite for Worst Case Timing Analysis               */
/*   =====================================================               */
/*                              Collected and Modified by S.-S. Lim      */
/*                                           sslim@archi.snu.ac.kr       */
/*                                         Real-Time Research Group      */
/*                                        Seoul National University      */
/*                                                                       */
/*                                                                       */
/*        < Features > - restrictions for our experimental environment   */
/*                                                                       */
/*          1. Completely structured.                                    */
/*               - There are no unconditional jumps.                     */
/*               - There are no exit from loop bodies.                   */
/*                 (There are no 'break' or 'return' in loop bodies)     */
/*          2. No 'switch' statements.                                   */
/*          3. No 'do..while' statements.                                */
/*          4. Expressions are restricted.                               */
/*               - There are no multiple expressions joined by 'or',     */
/*                'and' operations.                                      */
/*          5. No library calls.                                         */
/*               - All the functions needed are implemented in the       */
/*                 source file.                                          */
/*                                                                       */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/*  FILE: fibcall.c                                                      */
/*  SOURCE : Public Domain Code                                          */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     Summing the Fibonacci series.                                     */
/*                                                                       */
/*  REMARK :                                                             */
/*                                                                       */
/*  EXECUTION TIME :                                                     */
/*                                                                       */
/*                                                                       */
/*************************************************************************/
//#define USE_STDPERIPH_DRIVER
//#include "stm32f4_discovery.h"
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

int fib(int n){
   int  i, Fnew, Fold, temp,ans;

   Fnew = 1;  Fold = 0;
   for ( i = 2; i <= n; i++ ){
      temp = Fnew;
      Fnew = Fnew + Fold;
      Fold = temp;
   }
   ans = Fnew;


   return ans;
}


int main(){
   int a;
   a = 10000000;                         // fibonnaci 10 000 000 ; semble durer un tout petit peu moins que 1 seconde
   GPIO_InitTypeDef GPIO_InitStruct;
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
   GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3; // we want to configure pd3
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; // we want the pins to be an output
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; // this sets the GPIO modules clock speed
   GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // this sets the pin type to push / pull (as opposed to open drain)
   GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; // this sets the pullup / pulldown resistors to be inactive
   GPIO_Init(GPIOD, &GPIO_InitStruct); // this finally passes all the values to the GPIO_Init function which takes care of setting the corresponding bits.

   ms_delay(100);
   while(1){
      GPIO_ToggleBits(GPIOD, GPIO_Pin_3);
      fib(a);                             // fibo avec temps de calcul avec pin pd3  
      GPIO_ToggleBits(GPIOD, GPIO_Pin_3);   
      ms_delay(1000);
   }
}
