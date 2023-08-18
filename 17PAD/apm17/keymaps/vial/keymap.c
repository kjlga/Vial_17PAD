#include QMK_KEYBOARD_H
#include "analog.h"
#include "pointing_device.h"

bool joyoffon = 1;
/*  https://docs.qmk.fm/#/feature_pointing_device?id=manipulating-mouse-reports   */

/*  Layouts  */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] =	LAYOUT(
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,   KC_MUTE,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_P0,            KC_PDOT
    ),

    [1] =	LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    ),

    [2] =	LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    ),

    [3] =	LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    ),

    [4] =	LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    ),

    [5] =	LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    )
};

/*  encoder  */
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {  //Do NOT edit the number '2' in this line
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [4] =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [5] =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
/*  RGB Matrix  */
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    {  16,      15,  14,      13 },
    {  12,      11,  10,       9 },
    {   8,       7,   6,  NO_LED },
    {   5,       4,   3,       2 },
    {   1,  NO_LED,   0,  NO_LED }
    }, {
    // LED Index to Physical Position (Arrange the physical coordinates in the order of the LED lights)
    { 150, 64 }, { 75, 64 }, {  224, 48 }, { 149, 48 },
    {  75, 48 }, {   0, 48 }, { 149, 32 }, {  75, 32 },
    {   0, 32 }, { 224, 16 }, { 149, 16 },
    {  75, 16 }, {   0, 16 }, { 224,  0 }, { 149,  0 }, 
    {   75, 0 },              {   0,  0 }
    //x = 224 / (NUMBER_OF_COLS - 1) * COL_POSITION
    //y =  64 / (NUMBER_OF_ROWS - 1) * ROW_POSITION

    }, {
    // LED Index to Flag
    4, 4, 4, 4,
    4, 4, 4, 4,
    4, 4, 4,
    4, 4, 4, 4,
    4,    4
    } 
};
#endif
/*    joyStick    */
// Set Pins
pin_t VrxPin   = B0;   // VRx   B0
pin_t VryPin   = B1;   // VRy   B1
pin_t SwPin    = A7;   // SW    A7
// Set Parameters
uint16_t minAxisValue_dev = 0;
uint16_t maxAxisValue_dev = 1023;
uint8_t maxCursorSpeed_dev = 2;
uint8_t precisionSpeed = 1;
uint8_t speedRegulator_dev = 10;  // Lower Values Create Faster Movement
int8_t xPolarity = 1;
int8_t yPolarity = 1;
uint8_t cursorTimeout = 10;
int16_t xOrigin, yOrigin;
uint16_t lastCursor_dev = 0;

int16_t axisCoordinate_dev(pin_t pin, uint16_t origin) {
    int8_t  direction;
    int16_t distanceFromOrigin;
    int16_t range;
    int16_t position = analogReadPin(pin);
    if (origin == position) {
        return 0;
    } else if (origin > position) {
        distanceFromOrigin = origin - position;
        range              = origin - minAxisValue_dev;
        direction          = -1;
    } else {
        distanceFromOrigin = position - origin;
        range              = maxAxisValue_dev - origin;
        direction          = 1;
    }
    float   percent    = (float)distanceFromOrigin / range;
    int16_t coordinate = (int16_t)(percent * 100);
    if (coordinate < 0) {
        return 0;
    } else if (coordinate > 100) {
        return 100 * direction;
    } else {
        return coordinate * direction;
    }
}

int8_t axisToMouseComponent_dev(pin_t pin, int16_t origin, uint8_t maxSpeed, int8_t polarity) {
    int coordinate = axisCoordinate_dev(pin, origin);
    if (coordinate != 0) {
            float percent = (float)coordinate / 100;
            if (get_mods() & MOD_BIT(KC_LSFT)) {
                return percent * precisionSpeed * polarity * (abs(coordinate) / speedRegulator_dev);
        } else {
            return percent * maxCursorSpeed_dev * polarity * (abs(coordinate) / speedRegulator_dev);
        }
    } else {
        return 0;
    }
}

void pointing_device_task(void) {
    if(joyoffon){
        report_mouse_t report = pointing_device_get_report();

        if (timer_elapsed(lastCursor_dev) > cursorTimeout) {
            lastCursor_dev = timer_read();
            report.x   = -1 * axisToMouseComponent_dev(VrxPin, xOrigin, maxCursorSpeed_dev, xPolarity);
            report.y   = axisToMouseComponent_dev(VryPin, yOrigin, maxCursorSpeed_dev, yPolarity);
        }

        if (!readPin(SwPin)) {
            report.buttons |= MOUSE_BTN1;
        } else {
            report.buttons &= ~MOUSE_BTN1;
        }
        pointing_device_set_report(report);
        pointing_device_send();
    }
}

void matrix_init_keymap(void) {

    setPinInputHigh(SwPin);

    xOrigin = analogReadPin(VrxPin);
    yOrigin = analogReadPin(VryPin);
}

/*     vial custom keycode     */
enum blender_keycode {
    B_CSD = USER00, 
    B_CSU, 
    B_CSO,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case B_CSU:
            if ((speedRegulator_dev > 2 ) && (record->event.pressed)) {
                speedRegulator_dev -= 1 ;
            }
            return 0;
        case B_CSD:
            if ((speedRegulator_dev < 80 ) && (record->event.pressed)) {
                speedRegulator_dev += 1 ;
            }
            return 0;
        case B_CSO:
        if (record->event.pressed) { joyoffon ^= 1; }
            return 0;
        default:
            return 1;
    }
}
