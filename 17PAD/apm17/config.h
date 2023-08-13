/* Copyright 2021 MT
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef RGB_MATRIX_ENABLE
// The pin connected to the data pin of the LEDs
    #define WS2812_DI_PIN B9
    #define RGB_DI_PIN B9
// The number of LEDs connected
    #define DRIVER_LED_TOTAL 17
    #define RGB_MATRIX_LED_COUNT 17
    #define RGB_DISABLE_WHEN_USB_SUSPENDED

    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // Limit to vendor-recommended value
/*  PWM rgb_pin = B9  */
    #define WS2812_PWM_DRIVER PWMD4
    #define WS2812_PWM_CHANNEL 4
    #define WS2812_PWM_PAL_MODE 2
    #define WS2812_DMA_STREAM STM32_DMA1_STREAM7
    #define WS2812_DMA_CHANNEL 7
/*  RGB Matrix effect */
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_ALL // Sets the default mode
    #define RGB_MATRIX_DEFAULT_VAL 120 // Sets the default brightness value
    #define RGB_MATRIX_DEFAULT_HUE 152 // Sets the default hue value
    #define RGB_MATRIX_DEFAULT_SAT 232 // Sets the default saturation value

    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGB_MATRIX_KEYPRESSES

    #define ENABLE_RGB_MATRIX_CYCLE_ALL
    #define ENABLE_RGB_MATRIX_SOLID_COLOR
    #define ENABLE_RGB_MATRIX_ALPHAS_MODS
    #define ENABLE_RGB_MATRIX_BREATHING
    #define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
    #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    #define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
    #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
    #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
    #define ENABLE_RGB_MATRIX_DUAL_BEACON
    #define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
    #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS    //size 7.2KB
    #define ENABLE_RGB_MATRIX_PIXEL_RAIN 
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    #define ENABLE_RGB_MATRIX_SPLASH
    #define ENABLE_RGB_MATRIX_SOLID_SPLASH
#endif