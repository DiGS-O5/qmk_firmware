// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

uint8_t re_sel1 = 0;
uint8_t re_sel2 = 1;
bool re_chg1 = false;
bool re_chg2 = false;
uint32_t oled_flashing_timer;
bool oled_flashing = false;


enum layer_names {
    _Default,
    _Fn,
};

enum cc_keycodes {
    CC_RE1 = SAFE_RANGE,
    CC_RE2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
     * ┌────┐          ┌────┬────┬──     ─────┬────┬─┐           ┌────┐
     * │Esc│ 1 │          │ 2 │ 3 │ 4 │ 5 │ - │   │ = │ 6 │ 7 │ 8 │ 9 │          │ 0 │Del│
     * └┬───┴┐      ┌┴───┬┴───┬┴──     ──┴┬───┴┬───┴┐      ┌┴───┬┘
     *   │Tab│ Q │      │ W │ E │ R │ T │ [ │       │ ] │ Y │ U │ I │ O │      │ P │ ` │
     *   └┬───┴┐  ┌┴───┬┴───┬┴──         ──┴┬───┴┬───┴┐  ┌┴───┬┘
     *     │Cap│ A │  │ S │ D │ F │ G │ / │           │ \ │ H │ J │ K │ L │  │ ↑│ ' │
     *     └┬───┴┬┴───┬┴───┬┴──             ──┴┬───┴┬───┴┬┴───┬┘
     *       │Sht│ Z │ X │ C │ V │ B │ < │               │ > │ N │ M │ ; │ ←│↓ │→ │
     *       └─────────┼────┼──                 ──┼────┼─────┬──┬┘
     *         │Ctrl│Win │Alt │Fn │ S │ B │               │ E │ S │   │Alt │Ctrl│Shft│
     *         └──┴──┴──┴──  P │ S │               │ n │ P  ───────────┘
     *                                │   │   │               │   │   │
     *                                └────┘               └────┘
     * 
     */
    [_Default] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_LBRC,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_SLSH,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_COMM,
        KC_LCTL, KC_LGUI, KC_LALT, MO(_Fn), KC_SPC,  KC_BSPC,
        KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_DEL,
        KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   KC_GRV,
        KC_BSLS, KC_H,    KC_J,    KC_K,    KC_L,    KC_UP,  KC_QUOT,
        KC_DOT,  KC_N,    KC_M,    KC_SCLN, KC_LEFT, KC_DOWN,KC_RGHT,
        KC_ENT,  KC_SPC,  RGB_MOD, KC_RALT, KC_RCTL, KC_RSFT,
        CC_RE1,  CC_RE2
    ),

    [_Fn] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5  , KC_F11,
        _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        KC_SPC,  KC_SPC
    )
};

#define NL NO_LED

led_config_t g_led_config = { {
    { 0,  1,  2,  3,  4,  5,  6, NL, NL},
    {13, 12, 11, 10,  9,  8,  7, NL, NL},
    {14, 15, 16, 17, 18, 19, 20, NL, NL},
    {27, 26, 25, 24, 23, 22, 21, NL, NL},
    {NL, 28, 29, 30, 31, 32, 33, NL, NL},
    {NL, NL, 40, 39, 38, 37, 36, 35, 34},
    {NL, NL, 41, 42, 43, 44, 45, 46, 47},
    {NL, NL, 54, 53, 52, 51, 50, 49, 48},
    {NL, NL, 55, 56, 57, 58, 59, 60, 61},
    {NL, NL, 67, 66, 65, 64, 63, 62, NL},
},{
    {  0,  1 }, { 14,  0 }, { 36,  0 }, { 50,  1 }, { 64,  3 }, { 78,  4 }, { 92,  5 },
    { 91, 18 }, { 77, 17 }, { 63, 16 }, { 49, 14 }, { 35, 13 }, { 15, 13 }, {  1, 14 },
    {  3, 27 }, { 17, 26 }, { 34, 26 }, { 48, 27 }, { 62, 29 }, { 76, 30 }, { 90, 31 },
    { 88, 31 }, { 74, 30 }, { 60, 29 }, { 46, 27 }, { 32, 26 }, { 18, 26 }, {  4, 27 },
    {  6, 53 }, { 23, 52 }, { 41, 53 }, { 58, 55 }, { 71, 62 }, { 80, 64 },
    { 224,  1 }, { 210,  0 }, { 188,  0 }, { 174,  1 }, { 160,  3 }, { 146,  4 }, { 132,  5 },
    { 133, 18 }, { 147, 17 }, { 161, 16 }, { 175, 14 }, { 189, 13 }, { 194, 13 }, { 218, 14 },
    { 220, 27 }, { 207, 26 }, { 191, 26 }, { 177, 27 }, { 163, 29 }, { 149, 30 }, { 135, 31 },
    { 137, 44 }, { 150, 43 }, { 163, 42 }, { 176, 40 }, { 189, 39 }, { 206, 39 }, { 221, 40 },
    { 203, 53 }, { 187, 52 }, { 169, 53 }, { 166, 55 }, { 152, 62 }, { 138, 64 }
},{
    4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4, 4,
    1, 1, 1, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 1,
    4, 4, 4, 1, 1, 1
} };

void matrix_init_user(void) {
    writePinHigh(GP16);
    writePinHigh(GP17);
}

void re_func(uint8_t index, bool clockwise) {
    switch (index) {
        case 0:
            if (clockwise) {
                tap_code(KC_PGDN);
            }
            else {
                tap_code(KC_PGUP);
            }
            break;
        case 1:
            if (clockwise) {
                tap_code(KC_VOLU);
            }
            else {
                tap_code(KC_VOLD);
            }
            break;
        case 2:
            if (clockwise) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                tap_code(KC_Z);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            else {
                register_code(KC_LCTL);
                tap_code(KC_Z);
                unregister_code(KC_LCTL);
            }
            break;
        case 3:
            if (clockwise) {
                register_code(KC_LCTL);
                tap_code(KC_Y);
                unregister_code(KC_LCTL);
            }
            else {
                register_code(KC_LCTL);
                tap_code(KC_Z);
                unregister_code(KC_LCTL);
            }
            break;
        case 4:
            if (clockwise) {
                register_code(KC_LCTL);
                tap_code(KC_TAB);
                unregister_code(KC_LCTL);
            }
            else {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                tap_code(KC_TAB);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            break;
        case 5:
            if (clockwise) {
                tap_code(KC_DEL);
            }
            else {
                tap_code(KC_BSPC);
            }
            break;
        case 6:
            if (clockwise) {
                register_code(KC_LSFT);
                tap_code(KC_6);
                unregister_code(KC_LSFT);
            }
            else {
                tap_code(KC_MINS);
            }
            break;
        case 7:
            if (clockwise) {
                register_code(KC_LCTL);
                tap_code(KC_SCLN);
                unregister_code(KC_LCTL);
            }
            else {
                register_code(KC_LCTL);
                tap_code(KC_MINS);
                unregister_code(KC_LCTL);
            }
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
    case CC_RE1:
        if (record->event.pressed) {
            re_chg1 = !re_chg1;
        }
        return false;
        break;
    case CC_RE2:
        if (record->event.pressed) {
            re_chg2 = !re_chg2;
        }
        return false;
        break;
    default:
        return true;
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (re_chg1) {
            if (clockwise) {
                re_sel1 = (re_sel1 + 1) % 8;
            }
            else {
                re_sel1 = (re_sel1 + 7) % 8;
            }
        }
        else {
            re_func(re_sel1, clockwise);
        }
    }
    else if (index == 1) {
        if (re_chg2) {
            if (clockwise) {
                re_sel2 = (re_sel2 + 1) % 8;
            }
            else {
                re_sel2 = (re_sel2 + 7) % 8;
            }
        }
        else {
            re_func(re_sel2, clockwise);
        }
    }
    return false;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

void re_oled(uint8_t index) {
    switch (index) {
        case 0:
            oled_write_P(PSTR("  PageUp  / PageDown "), false);
            break;
        case 1:
            oled_write_P(PSTR("  VolDown /  VolUp   "), false);
            break;
        case 2:
            oled_write_P(PSTR("   Undo   / Redo (Z) "), false);
            break;
        case 3:
            oled_write_P(PSTR("   Undo   / Redo (Y) "), false);
            break;
        case 4:
            oled_write_P(PSTR("  PrevTab / NextTab  "), false);
            break;
        case 5:
            oled_write_P(PSTR("BackSpace /  Delete  "), false);
            break;
        case 6:
            oled_write_P(PSTR(" ZoomOut  /  ZoomIn  "), false);
            break;
        case 7:
            oled_write_P(PSTR(" L-Rotate / R-Rotate "), false);
            break;
    }
}


bool oled_task_user(void) {
    if (timer_elapsed(oled_flashing_timer) > 600) {
        oled_flashing_timer = timer_read();
        oled_flashing = !oled_flashing;
    }
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("---------------------"), false);
    oled_set_cursor(0, 1);
    oled_write_P(PSTR("  Rotary Encoder 1   "), false);
    oled_set_cursor(0, 2);
    if (re_chg1 && oled_flashing) {
         oled_write_P(PSTR("                     "), false);
    }
    else {
        re_oled(re_sel1);
    }
    oled_set_cursor(0, 3);
    oled_write_P(PSTR("---------------------"), false);
    oled_set_cursor(0, 4);
    oled_write_P(PSTR("  Rotary Encoder 2   "), false);
    oled_set_cursor(0, 5);
    if (re_chg2 && oled_flashing) {
        oled_write_P(PSTR("                     "), false);
    }
    else {
        re_oled(re_sel2);
    }
    oled_set_cursor(0, 6);
    oled_write_P(PSTR("---------------------"), false);
    return false;
}

void set_color(int index, uint8_t hsvred, uint8_t hsvgreen, uint8_t hsvblue) {
    HSV hsv = (HSV){ hsvred, hsvgreen, hsvblue };
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (rgb_matrix_get_mode() != 1) {
        return true;
    }

    rgb_matrix_set_color_all(RGB_OFF);

    switch (get_highest_layer(layer_state | default_layer_state)) {
    case _Default:
        if (is_keyboard_left()) {
            for (uint8_t i = 0; i < 34; i++) {
                set_color(i, HSV_AZURE);
            }
        }
        else {
            for (uint8_t i = 34; i < 68; i++) {
                set_color(i, HSV_AZURE);
            }
        }
        break;
    case _Fn:
        if (is_keyboard_left()) {
            set_color(0, HSV_AZURE);
            for (uint8_t i = 1; i < 7; i++) {
                set_color(i, HSV_CYAN);
            }
            for (uint8_t i = 7; i < 34; i++) {
                set_color(i, HSV_AZURE);
            }
        }
        else {
            set_color(34, HSV_AZURE);
            for (uint8_t i = 35; i < 41; i++) {
                set_color(i, HSV_CYAN);
            }
            for (uint8_t i = 41; i < 68; i++) {
                set_color(i, HSV_AZURE);
            }
        }
        break;
    default:
        break;
    }
    return true;
}
