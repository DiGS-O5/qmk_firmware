// Copyright 2023 DiGS-O5 (@DiGS-O5)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP16
#define I2C1_SCL_PIN GP17
#define OLED_DISPLAY_128X64

#define EE_HANDS
#define SPLIT_TRANSACTION_IDS_KB KEYBOARD_SYNC
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_TRANSPORT_MIRROR

#define WS2812_DI_PIN GP25
#define RGB_MATRIX_LED_COUNT 68
#define RGB_MATRIX_SPLIT { 34, 34 }

#define NOP_FUDGE 1

#define RGB_MATRIX_DEFAULT_HUE 132
#define RGB_MATRIX_DEFAULT_SAT 102

#define RGB_MATRIX_HUE_STEP 1
#define RGB_MATRIX_SAT_STEP 1
#define RGB_MATRIX_VAL_STEP 1

#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100
