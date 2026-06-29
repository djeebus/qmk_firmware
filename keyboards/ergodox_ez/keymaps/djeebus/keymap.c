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

// Tap dance indices
enum {
    TD_LCBR,  // tap: {  hold: Left Ctrl
    TD_RCBR,  // tap: }  hold: Left Alt
};

// Generic tap-hold tap dance: tap sends `tap` (may be a shifted keycode),
// hold registers `hold` (a modifier).
typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} td_tap_hold_t;

void td_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    td_tap_hold_t *tap_hold = (td_tap_hold_t *)user_data;
    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            tap_code16(tap_hold->tap);
        }
    } else {
        tap_code16(tap_hold->tap);
    }
}

void td_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    td_tap_hold_t *tap_hold = (td_tap_hold_t *)user_data;
    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, td_tap_hold_finished, td_tap_hold_reset}, .user_data = (void *)&((td_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [TD_LCBR] = ACTION_TAP_DANCE_TAP_HOLD(KC_LCBR, KC_LCTL),
    [TD_RCBR] = ACTION_TAP_DANCE_TAP_HOLD(KC_RCBR, KC_LALT),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_ergodox_pretty(
    QK_GESC,        KC_1,       KC_2,       KC_3,    KC_4,      KC_5,      KC_EQUAL,        KC_MINUS,   KC_6,       KC_7,     KC_8,      KC_9,    KC_0,    KC_MINUS,
    KC_TAB,         KC_Q,       KC_W,       KC_E,    KC_R,      KC_T,      KC_PGUP,         KC_PSCR,    KC_Y,       KC_U,     KC_I,    KC_O,    KC_P,             KC_BSLS,
    MAGIC_CAPS,     KC_A,       KC_S,       KC_D,    KC_F,      KC_G,                                   KC_H,       KC_J,     KC_K,    KC_L,    LT(MDIA,KC_SCLN), KC_QUOT,
    MT(MOD_LSFT,KC_EQUAL), KC_Z, KC_X,       KC_C,    KC_V,      KC_B,      KC_PGDN,        KC_PAUSE,   KC_N,       KC_M,     KC_COMM, KC_DOT,  KC_SLASH,         MT(MOD_RSFT,KC_MINUS),
    MO(MDIA),       TD(TD_LCBR), TD(TD_RCBR), KC_GRV, KC_SPACE,                                                    KC_SPACE, KC_TRNS, MT(MOD_RALT,KC_LBRC), MT(MOD_RCTL,KC_RBRC), MO(SYMB),
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

// Immediately resolve the Shift mod-taps to "hold" when another key is pressed,
// so fast rolls like Shift+I don't emit the tap symbol ("=i" / "-i").
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LSFT, KC_EQUAL):
        case MT(MOD_RSFT, KC_MINUS):
            return true;
        default:
            return false;
    }
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
