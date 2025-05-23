#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;
const int LED_PIN_R = 4;
const int LED_PIN_G = 6;
volatile int led_state_r = 0;
volatile int led_state_g = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge // teste
    //if (gpio == BTN_PIN_R){
    led_state_r = !led_state_r;
    gpio_put(LED_PIN_R, led_state_r);
    //}
  } else if (events == 0x8) { // rise edge
    //if (gpio == BTN_PIN_G){
      led_state_g = !led_state_g;
      gpio_put(LED_PIN_G, led_state_g);
      //}
  }
}

int main() {
  stdio_init_all();

  gpio_init(LED_PIN_R);
  gpio_set_dir(LED_PIN_R, GPIO_OUT);

  gpio_init(LED_PIN_G);
  gpio_set_dir(LED_PIN_G, GPIO_OUT);

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  // callback led r (first)
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true,
    &btn_callback);

  // callback led g (nao usar _with_callback)
  gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true);

  while (true) {
  }
}
