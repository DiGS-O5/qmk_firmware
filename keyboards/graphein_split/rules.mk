# This file intentionally left blank

SERIAL_DRIVER = vendor

OLED_ENABLE = yes
OLED_DRIVER = ssd1306

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812
WS2812_DRIVER = vendor
KEY_OVERRIDE_ENABLE = yes

EEPROM_ENABLE = yes
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = rp2040_flash

SRC += custom_rgb_matrix.c
