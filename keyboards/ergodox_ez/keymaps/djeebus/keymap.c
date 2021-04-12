#include QMK_KEYBOARD_H
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define WIN  3 // win arrows
#define FN   4 // function style keys

enum custom_keycodes {
  EPRM = SAFE_RANGE,
  VRSN,
  RGB_SLD
};

/*
DF(layer) - switches the default layer. The default layer is the always-active base layer that other layers stack on top of. See below for more about the default layer. This might be used to switch from QWERTY to Dvorak layout. (Note that this is a temporary switch that only persists until the keyboard loses power. To modify the default layer in a persistent way requires deeper customization, such as calling the set_single_persistent_default_layer function inside of process_record_user.)

MO(layer) - momentarily activates layer. As soon as you let go of the key, the layer is deactivated.

LM(layer, mod) - Momentarily activates layer (like MO), but with modifier(s) mod active. Only supports layers 0-15 and the left modifiers: MOD_LCTL, MOD_LSFT, MOD_LALT, MOD_LGUI (note the use of MOD_ constants instead of KC_). These modifiers can be combined using bitwise OR, e.g. LM(_RAISE, MOD_LCTL | MOD_LALT).

LT(layer, kc) - momentarily activates layer when held, and sends kc when tapped. Only supports layers 0-15.

OSL(layer) - momentarily activates layer until the next key is pressed. See One Shot Keys for details and additional functionality.

TG(layer) - toggles layer, activating it if it's inactive and vice versa

TO(layer) - activates layer and de-activates all other layers (except your default layer). This function is special, because instead of just adding/removing one layer to your active layer stack, it will completely replace your current active layers, uniquely allowing you to replace higher layers with a lower one. This is activated on keydown (as soon as the key is pressed).

TT(layer) - Layer Tap-Toggle. If you hold the key down, layer is activated, and then is de-activated when you let go (like MO). If you repeatedly tap it, the layer will be toggled on or off (like TG). It needs 5 taps by default, but you can change this by defining TAPPING_TOGGLE -- for example, #define TAPPING_TOGGLE 2 to toggle on just two taps.

MT(mod, kc) - The Mod-Tap key MT(mod, kc) acts like a modifier when held, and a regular keycode when tapped. In other words, you can have a key that sends Escape when you tap it, but functions as a Control or Shift key when you hold it down.

*/

#define MAGIC_TAB MT(MOD_LCTL|MOD_LSFT,KC_CAPSLOCK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_ergodox_pretty(
        KC_ESCAPE,      KC_1,       KC_2,       KC_3,    KC_4,    KC_5,    KC_6,            KC_6,       KC_7,       KC_8,     KC_9,    KC_0,    KC_MINUS,         KC_EQUAL,
        KC_TAB,         KC_Q,       KC_W,       KC_E,    KC_R,    KC_T,    KC_PGUP,         KC_PGUP,    KC_Y,       KC_U,     KC_I,    KC_O,    KC_P,             KC_BSLASH,
        MAGIC_TAB,      KC_A,       KC_S,       KC_D,    KC_F,    KC_G,                                 KC_H,       KC_J,     KC_K,    KC_L,    LT(MDIA,KC_SCLN), KC_QUOT,
        KC_LSFT,        KC_Z,       KC_X,       KC_C,    KC_V,    KC_B,    KC_PGDOWN,         KC_PGDOWN,  KC_N,       KC_M,     KC_COMM, KC_DOT,  KC_SLASH,         KC_RSFT,
        KC_LCTRL,       MO(MDIA),   MO(SYMB),   KC_LALT, KC_SPACE,                                                  KC_SPACE, KC_TRNS, KC_RALT, KC_RCTRL,         MO(SYMB),
                                                            KC_MPRV,    KC_MNXT,            KC_TRNS,    KC_TRNS,
                                                                        KC_VOLU,            KC_TRNS,
                                                KC_BSPACE, KC_DELETE,  KC_VOLD,           MO(MDIA),   KC_LGUI,    KC_ENTER
    ),

    [SYMB] = LAYOUT_ergodox_pretty(
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                    KC_F7,      KC_F8,   KC_F9, KC_F10,  KC_F11,  KC_F12,  KC_HOME,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS,                  KC_TRNS,    KC_TRNS, KC_7,  KC_8,    KC_9,    KC_ASTR, KC_END,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_LPRN, KC_RPRN, KC_GRV,                                        KC_TRNS, KC_4,  KC_5,    KC_6,    KC_PLUS, KC_PGUP,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS,                  KC_TRNS,    KC_TRNS, KC_1,  KC_2,    KC_3,    KC_BSLS, KC_PGDOWN,
        RESET,   EPRM,    KC_TRNS, KC_TRNS, KC_TRNS,                                                         KC_0,  KC_TRNS, KC_DOT,  KC_EQL,  KC_TRNS,
                                                    RGB_MOD, KC_TRNS,                   RGB_TOG,    RGB_SLD,
                                                                KC_F3,                  KC_TRNS,
                                            RGB_VAD, RGB_VAI, KC_TRNS,                  KC_RCTRL, RGB_HUD, RGB_HUI
    ),

    [MDIA] = LAYOUT_ergodox_pretty(
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,     KC_F7, KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_PGUP, KC_UP, KC_HOME, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ENTER,                       KC_TRNS, KC_RCTRL, KC_RSHIFT, KC_RALT, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_PGDOWN, KC_TRNS, KC_END, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                                                    KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,
                                                                KC_TRNS,     KC_TRNS,
                                            KC_WWW_BACK, KC_TRNS, KC_WWW_FORWARD,     KC_TRNS, KC_RGUI, KC_WBAK
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case EPRM:
        eeconfig_init();
        return false;
      case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
      #ifdef RGBLIGHT_ENABLE
      case RGB_SLD:
        rgblight_mode(1);
        return false;
      #endif
    }
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
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
