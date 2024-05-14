#include "custom_rgb_matrix.h"
#include QMK_KEYBOARD_H

void rgb_matrix_sethsv_wrap_around(uint16_t hue, uint16_t sat, uint16_t val) {
    HSV hsv = (HSV){
        hue,
        sat,
        (val > RGB_MATRIX_MAXIMUM_BRIGHTNESS && val < RGB_MATRIX_MAXIMUM_BRIGHTNESS + ((uint8_t)~RGB_MATRIX_MAXIMUM_BRIGHTNESS >> 1)) ? 0 : (val > RGB_MATRIX_MAXIMUM_BRIGHTNESS + ((uint8_t)~RGB_MATRIX_MAXIMUM_BRIGHTNESS >> 1)) ? RGB_MATRIX_MAXIMUM_BRIGHTNESS : val
    };
    rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
}

void rgb_matrix_wrap_around_hue(bool decrease) {
    rgb_matrix_sethsv_wrap_around(rgb_matrix_config.hsv.h + (!decrease ? RGB_MATRIX_HUE_STEP : - RGB_MATRIX_HUE_STEP), rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v);
}

void rgb_matrix_wrap_around_sat(bool decrease) {
    rgb_matrix_sethsv_wrap_around(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s + (!decrease ? RGB_MATRIX_HUE_STEP : - RGB_MATRIX_HUE_STEP), rgb_matrix_config.hsv.v);
}

void rgb_matrix_wrap_around_val(bool decrease) {
    rgb_matrix_sethsv_wrap_around(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v + (!decrease ? RGB_MATRIX_HUE_STEP : - RGB_MATRIX_HUE_STEP));
}

void set_color(int index, uint8_t hue, uint8_t sat, uint8_t val) {
    HSV hsv = (HSV){ hue, sat, val };
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}
