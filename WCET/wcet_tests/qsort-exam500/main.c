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
/*  FILE: qsort-exam.c                                                   */
/*  SOURCE : Numerical Recipes in C - The Second Edition                 */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     Non-recursive version of quick sort algorithm.                    */
/*     This example sorts 20 floating point numbers, arr[].              */
/*                                                                       */
/*  REMARK :                                                             */
/*                                                                       */
/*  EXECUTION TIME :                                                     */
/*                                                                       */
/*                                                                       */
/*************************************************************************/
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

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
#define SWAP(a,b) temp=(a);(a)=(b);(b)=temp;
#define M 7
#define NSTACK 50

float arr[500] = {
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88,
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99
};

int istack[100];

void sort(unsigned long n)
{
  unsigned long i,ir=n,j,k,l=1;
  int jstack=0;
  float a,temp;

  GPIO_SetBits(GPIOB, GPIO_Pin_3);     // PIN PB3 ACTIVATED
  for (;;) {
    if (ir-l < M) {
      for (j=l+1;j<=ir;j++) {
        a=arr[j];
        for (i=j-1;i>=l;i--) {
          if (arr[i] <= a){
            GPIO_ResetBits(GPIOB, GPIO_Pin_3);   // PIN PB3 DEACTIVATED
            break;
          }
          arr[i+1]=arr[i];
        }
        arr[i+1]=a;
      }
      if (jstack == 0) {
        GPIO_ResetBits(GPIOB, GPIO_Pin_3);   // PIN PB3 DEACTIVATED
        break;
      }
      ir=istack[jstack--];
      l=istack[jstack--];
    } else {
      k=(l+ir) >> 1;
      SWAP(arr[k],arr[l+1])
      if (arr[l] > arr[ir]) {
        SWAP(arr[l],arr[ir])
      }
      if (arr[l+1] > arr[ir]) {
        SWAP(arr[l+1],arr[ir])
      }
      if (arr[l] > arr[l+1]) {
        SWAP(arr[l],arr[l+1])
      }
      i=l+1;
      j=ir;
      a=arr[l+1];
      for (;;) {
        i++; while (arr[i] < a) i++;
        j--; while (arr[j] > a) j--;
        if (j < i){
          GPIO_ResetBits(GPIOB, GPIO_Pin_3);   // PIN PB3 DEACTIVATED
          break;
        }
        SWAP(arr[i],arr[j]);
      }
      arr[l+1]=arr[j];
      arr[j]=a;
      jstack += 2;

      if (ir-i+1 >= j-l) {
        istack[jstack]=ir;
        istack[jstack-1]=i;
        ir=j-1;
      } else {
        istack[jstack]=j-1;
        istack[jstack-1]=l;
        l=i;
      }
    }
  }
}


void pin_init(void){
   GPIO_InitTypeDef GPIO_InitStruct;
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
   GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3; // we want to configure pb3
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; // we want the pins to be an output
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; // this sets the GPIO modules clock speed
   GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // this sets the pin type to push / pull (as opposed to open drain)
   GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; // this sets the pullup / pulldown resistors to be inactive
   GPIO_Init(GPIOB, &GPIO_InitStruct); // this finally passes all the values to the GPIO_Init function which takes care of setting the corresponding bits.
}

int main(void)
{
	pin_init();
	ms_delay(100);
	while(1){
 		sort(500);
		ms_delay(1000);                     // 1 seconde avec led rouge allumée
	}
}