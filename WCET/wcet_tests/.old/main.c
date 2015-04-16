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

int fib(int n){
   int  i, Fnew, Fold, temp,ans;
   GPIOD->MODER = (1 << 24);             // set pin 12 to be general purpose output
   GPIOD->ODR ^= (1 << 12);              // allumer la led verte
   Fnew = 1;  Fold = 0;
   for ( i = 2; i <= n; i++ ){
      temp = Fnew;
      Fnew = Fnew + Fold;
      Fold = temp;
   }
   ans = Fnew;
   GPIOD->ODR ^= (1 << 12);               // eteindre la led verte

   return ans;
}


int main(){
   int a;
   a = 10000000;                         // fibonnaci 10 000 000 ; semble durer un tout petit peu moins que 1 seconde
   RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;  // enable the clock to GPIOD
   ms_delay(100);
   while(1){
      fib(a);                             // fibo avec temps de calcul avec led verte allumée
      ms_delay(1000);                     // 1 seconde avec led rouge allumée
   }
}
