#pragma once

void rgb_matrix_sethsv_wrap_around(uint16_t hue, uint16_t sat, uint16_t val);
void rgb_matrix_wrap_around_hue(bool decrease);
void rgb_matrix_wrap_around_sat(bool decrease);
void rgb_matrix_wrap_around_val(bool decrease);
void set_color(int index, uint8_t hue, uint8_t sat, uint8_t val);
