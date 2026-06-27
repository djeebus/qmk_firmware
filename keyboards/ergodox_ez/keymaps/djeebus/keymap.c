#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    BASE,  // default layer
    SYMB,  // symbols
    MDIA,  // media keys
};

enum custom_keycodes {
#ifdef ORYX_CONFIGURATOR
    VRSN = EZ_SAFE_RANGE,
#else
    VRSN = SAFE_RANGE,
#endif
};

#define MAGIC_CAPS MT(MOD_LCTL|MOD_LSFT,KC_CAPS)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_ergodox_pretty(
    QK_GESC,        KC_1,       KC_2,       KC_3,    KC_4,      KC_5,      KC_6,            KC_6,       KC_7,       KC_8,     KC_9,    KC_0,    KC_MINUS,         KC_EQUAL,
    KC_TAB,         KC_Q,       KC_W,       KC_E,    KC_R,      KC_T,      KC_PGUP,         KC_PSCR,    KC_Y,       KC_U,     KC_I,    KC_O,    KC_P,             KC_BSLS,
    MAGIC_CAPS,     KC_A,       KC_S,       KC_D,    KC_F,      KC_G,                                   KC_H,       KC_J,     KC_K,    KC_L,    LT(MDIA,KC_SCLN), KC_QUOT,
    KC_LSFT,        KC_Z,       KC_X,       KC_C,    KC_V,      KC_B,      KC_PGDN,         KC_PAUSE,   KC_N,       KC_M,     KC_COMM, KC_DOT,  KC_SLASH,         KC_RSFT,
    MO(MDIA),       KC_LCTL,    MO(SYMB),   KC_LALT, KC_SPACE,                                                      KC_SPACE, KC_TRNS, KC_RALT, KC_RCTL,         MO(SYMB),
                                                                KC_MPRV,   KC_MNXT,         KC_TRNS,    KC_TRNS,
                                                                           KC_VOLU,         KC_TRNS,
                                                     KC_BSPC,   KC_DELETE, KC_VOLD,         MO(MDIA),   KC_LGUI,    KC_ENTER
),

[SYMB] = LAYOUT_ergodox_pretty(
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                    KC_F7,      KC_F8,   KC_F9, KC_F10,  KC_F11,  KC_F12,  KC_HOME,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS,                  KC_TRNS,    KC_TRNS, KC_7,  KC_8,    KC_9,    KC_ASTR, KC_END,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_LPRN, KC_RPRN, KC_GRV,                                        KC_TRNS, KC_4,  KC_5,    KC_6,    KC_PLUS, KC_PGUP,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS,                  KC_TRNS,    KC_TRNS, KC_1,  KC_2,    KC_3,    KC_BSLS, KC_PGDN,
    QK_BOOT, EE_CLR,          KC_TRNS, KC_TRNS, KC_TRNS,                                                         KC_0,  KC_TRNS, KC_DOT,  KC_EQL,  KC_TRNS,
                                                UG_NEXT, KC_TRNS,                   UG_TOGG,    KC_TRNS,
                                                            KC_F3,                  KC_TRNS,
                                        UG_VALD, UG_VALU, KC_TRNS,                  KC_RCTL,  UG_HUED, UG_HUEU
),

[MDIA] = LAYOUT_ergodox_pretty(
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,     KC_F7, KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_PGUP, KC_UP, KC_HOME, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ENTER,                       KC_TRNS, KC_RCTL, KC_RSFT, KC_RALT, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_PGDN, KC_TRNS, KC_END, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                                                KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,
                                                            KC_TRNS,     KC_TRNS,
                                        KC_WWW_BACK, KC_TRNS, KC_WWW_FORWARD,     KC_TRNS, KC_RGUI, KC_WBAK
),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case VRSN:
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
                return false;
        }
    }
    return true;
}

// Runs just one time when the keyboard initializes.
void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case 0:
#ifdef RGBLIGHT_COLOR_LAYER_0
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
            break;
        case 1:
            ergodox_right_led_1_on();
#ifdef RGBLIGHT_COLOR_LAYER_1
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
#endif
            break;
        case 2:
            ergodox_right_led_2_on();
#ifdef RGBLIGHT_COLOR_LAYER_2
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
#endif
            break;
        case 3:
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_3
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
#endif
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
#ifdef RGBLIGHT_COLOR_LAYER_4
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
#endif
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_5
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
#endif
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_6
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
#endif
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_7
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
#endif
            break;
        default:
            break;
    }

    return state;
};
