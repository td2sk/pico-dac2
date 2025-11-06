#if HID_ENABLE

#include "usb_hid.h"

#include <assert.h>

#include "audio_device.h"
#include "log.h"
#include "usb.h"
#include "usb_config.h"

bool usb_hid_set_interface(uint8_t alt) {
  // 新しい alt を設定する
  LOG_INFO("Set interface HID alt %d\r", alt);

  assert(alt == 0);
  static uint8_t zero[16] = {0};
  usb_ep_n_start_transfer(EP_HID_IN & 0x7F, true, zero, sizeof(zero));
  usb_ep_n_start_transfer(EP_HID_OUT, false, NULL, 16);
  return true;
}

bool usb_hid_control_out_request(const struct usb_setup_packet_t *pkt,
                                 const uint8_t *buf, uint16_t len) {
  if (pkt->bmRequestType == 0x21 && pkt->bRequest == 0x0A && pkt->wValue == 0 &&
      (pkt->wIndex & 0xFF) == INTERFACE_HID) {
    LOG_DEBUG("unhandled CLEAR");
    return true;
  }

  LOG_INFO(
      "unhandled OUT request(type=0x%02x, request=0x%02x, value=0x%04x, "
      "index=0x%04x, length=0x%04x)",
      pkt->bmRequestType, pkt->bRequest, pkt->wValue, pkt->wIndex,
      pkt->wLength);
  // デフォルトは未処理
  return false;
}

static void ep_hid_out_handler(const uint8_t *buf, uint16_t len) {
  LOG_INFO("ep_hid_out_handler: %d byte", len);
  usb_ep_n_start_transfer(EP_HID_OUT, false, NULL, 16);
}

static uint8_t zero[16] = {0};
static void ep_hid_in_handler() {
  // LOG_INFO("ep_hid_in_handler");
  usb_ep_n_start_transfer(EP_HID_IN & 0x7F, true, zero, sizeof(zero));
}

void usb_hid_init() {
  usb_device_set_ep_out_handler(EP_HID_OUT, ep_hid_out_handler);
  usb_device_set_ep_in_handler(EP_HID_IN & 0x7F, ep_hid_in_handler);

  usb_device_set_control_out_handler(INTERFACE_HID,
                                     usb_hid_control_out_request);

  usb_device_set_set_interface_handler(INTERFACE_HID, usb_hid_set_interface);
}

#endif
