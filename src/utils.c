#include "utils.h"
#include "stm32f103xb.h"
#include "stm32f1xx_ll_gpio.h"

void ErrorFlash(void) {
  LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
  delay(50);
  LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
  delay(50);
}


void delay(int ms) {
  for (int i = 0; i < ms; i++) {
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
      ;
  }
}

void reverse_str(char *dest, char *str, int length) {
  length--;
  int i = 0;
  while (length >= 0) {
    dest[i++] = str[length--];
  }
  dest[i] = '\0';
}

void itos(char *dest, int num) {
  if (num == 0) {
    dest[0] = '0';
    dest[1] = '\0';
    return;
  }
  char str[255];
  int neg = num < 0 ? 1 : 0;
  if (neg) {
    num = ~num + 1;
  }
  int i = 0;
  while (num != 0) {
    int rem = num % 10;
    str[i++] = rem + '0';
    num /= 10;
  }
  if (neg) {
    str[i++] = '-';
  }
  str[i] = '\0';
  reverse_str(dest, str, i);
}
