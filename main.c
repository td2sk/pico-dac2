#include <stdint.h>

#include "audio_device.h"
#include "blink.h"
#include "hardware/clocks.h"
#include "log.h"
#include "pico/stdlib.h"
#include "usb.h"
#include "usb_audio.h"
#include "usb_hid.h"

int main() {
  // CPU 周波数が標準の 125 MHz だと PIO のクロック分周に誤差が出る
  // そのため 48kHz/96kHz で都合が良いように 126 MHz を設定
  // set_sys_clock_khz(126000, true);
  // 92.16MHz だと整数分周になる
  set_sys_clock_pll(12 * MHZ * 192u, 5, 5);

  stdio_init_all();

  blink_init(pio1, PICO_DEFAULT_LED_PIN);
  audio_device_init();
  usb_device_init();
  usb_audio_init();
#ifdef HID_ENABLE
  usb_hid_init();
#endif

  LOG_INFO("Booted");

  while (true) {
    usb_device_task();

    audio_device_task();
  }
}
