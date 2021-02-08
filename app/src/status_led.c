/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <bluetooth/services/bas.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/usb.h>
#include <zmk/events/usb_conn_state_changed.h>
#include <zmk/event_manager.h>
#include <zmk/events/battery_state_changed.h>

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

static bool style_initialized = false;

void battery_status_init() {
    if (style_initialized) {
        return;
    }

    style_initialized = true;
}

void set_led() {
  
    uint8_t level = bt_bas_get_battery_level();

    if (level < 10) {
        // LED ON 
    } else {
        // LED OFF 
    }
}

int zmk_status_led_init() {
    battery_status_init();
  
    set_led();

    return 0;
}

int battery_status_listener(const zmk_event_t *eh) {
    set_led();
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(status_led, battery_status_listener)
ZMK_SUBSCRIPTION(status_led, zmk_battery_state_changed);
#if IS_ENABLED(CONFIG_USB)
ZMK_SUBSCRIPTION(status_led, zmk_usb_conn_state_changed);
#endif /* IS_ENABLED(CONFIG_USB) */
