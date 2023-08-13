/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once
/*  python3 util/vial_generate_keyboard_uid.py   */
#define VIAL_KEYBOARD_UID {0x5D, 0x8D, 0x19, 0xDA, 0xC3, 0x85, 0x90, 0x84}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 4 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 2 }

#define MATRIX_ROWS 5
#define MATRIX_COLS 4
#define MATRIX_ROW_PINS { A5, A4,  A3, A2, A1 }
#define MATRIX_COL_PINS { B7, B6,  B5, B4     }
#define DIODE_DIRECTION ROW2COL

#define DYNAMIC_KEYMAP_LAYER_COUNT 6   /* number Layers，default 4 */
#define VIAL_TAP_DANCE_ENTRIES 16       /* Tap Dance(reuse Keys) number，default 32 */
#define VIAL_COMBO_ENTRIES 16           /* Combo(key_combinations) numbar，default 32 */
#define VIAL_KEY_OVERRIDE_ENTRIES 8     /*Key Overrides number, default 32 */
/*  joyStick  */
#define ANALOG_JOYSTICK_X_AXIS_PIN B0
#define ANALOG_JOYSTICK_Y_AXIS_PIN B1
#define ANALOG_JOYSTICK_CLICK_PIN  A7
/*  RBG Matrix  */
#define RGB_MATRIX_KEYPRESSES