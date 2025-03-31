#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
volatile int up;
volatile int down;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge // teste
    up = 1;
  } else if (events == 0x8) { // rise edge
    down = 1;
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {

    if (up){
      printf("fall \n");
      up = 0;
    }
    if (down){
      printf("down \n");
      down = 0;
    }

  }
}
