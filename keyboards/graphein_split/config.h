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

#define ENCODER_RESOLUTION 2

#define ENCODERS_PAD_A { GP11, GP14 }
#define ENCODERS_PAD_B { GP12, GP15 }

#define WS2812_DI_PIN GP25
#define RGB_MATRIX_LED_COUNT 68
#define RGB_MATRIX_SPLIT { 34, 34 }

#define NOP_FUDGE 1
#define SPLIT_LAYER_STATE_ENABLE
#define ENABLE_RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
