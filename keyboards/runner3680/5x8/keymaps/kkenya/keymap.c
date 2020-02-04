#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
rgblight_config_t RGB_current_config;
#endif

enum layer_number {
    _QWERTY = 0,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  ADJUST,
  RGBRST
};

// Fillers to make layering more clear
#define EISU LALT(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* QWERTY
     * ビルドを間違えたため左右反転
     * ,-------------------------------------------------------.                    ,--------------------------------------------------------.
     * |  F1  |  F2  |   5  |   4  |   3  |   2  |   1  | Esc  |                    | Bksp |   =  |   -  |   0  |   9  |   8  |   7  |   6  |
     * |------+------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------+------|
     * |  F3  |  F4  |   T  |   R  |   E  |   W  |   Q  | Tab  |                    |   \  |   ]  |   [  |   P  |   O  |   I  |   U  |   Y  |
     * |------+------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------+------|
     * |  F5  |  F6  |   G  |   F  |   D  |   S  |   A  | Ctrl |                    | Enter| Enter|   "  |   ;  |   L  |   K  |   J  |   H  |
     * |------+------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------+------|
     * |  F7  |  F8  |   B  |   V  |   C  |   X  |   Z  | Shift|                    | Shift|Adjust| Shift|   /  |   .  |   ,  |   M  |   N  |
     * |------+------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------+------|
     * |  F9  |  F10 | Space| Space| GUI  | Alt  | GUI  |   `  |                    | Right|  Up  | Down | Left | Alt  | GUI  | Space| Space|
     * `-------------------------------------------------------'                    `-------------------------------------------------------'
     */
  [_QWERTY] = LAYOUT(
      _______, _______, KC_5,   KC_4,   KC_3,    KC_2,       KC_1,     KC_ESC,      KC_BSPC,  KC_EQL,  KC_MINS, KC_0,     KC_9,    KC_8,    KC_7,    KC_6,  
      _______, _______, KC_T,   KC_R,   KC_E,    KC_W,       KC_Q,     KC_TAB,      KC_BSLS,  KC_RBRC, KC_LBRC, KC_P,     KC_O,    KC_I,    KC_U,    KC_Y,  
      _______, _______, KC_G,   KC_F,   KC_D,    KC_S,       KC_A,     KC_LCTL,     KC_ENT,   KC_ENT,  KC_QUOT, KC_SCLN,  KC_L,    KC_K,    KC_J,    KC_H,  
      _______, _______, KC_B,   KC_V,   KC_C,    KC_X,       KC_Z,     KC_LSFT,     KC_RSFT,  ADJUST,  KC_RSFT, KC_SLSH,  KC_DOT,  KC_COMM, KC_M,    KC_N,  
      _______, _______, KC_SPC, KC_SPC, KC_LGUI, KC_LALT,    KC_LGUI,  KC_GRV,      KC_RGHT,  KC_UP,   KC_DOWN, KC_LEFT,  KC_LALT, KC_LGUI, KC_SPC,  KC_SPC
      ),

    /* Adjust
     * ,-------------------------------------------------------.      ,--------------------------------------------------------.
     * |      |      |      |   F1 |   F2 |   F3 |   F4 |   F5 |      |   F6 |   F7 |   F8 |   F9 |  F10 |  F11 |  F12 |      |
     * |------+------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|
     * |      |      |      |RGBRST| RESET|      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|
     * |      |      |      |  TOG |  HUI |  SAI |  VAI |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|
     * |      |      |      |  MOD |  HUD |  SAD |  VAD |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-------------------------------------------------------'      `-------------------------------------------------------'
     */
  [_ADJUST] =  LAYOUT(
      _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
      _______, _______, _______, RGBRST,  RESET,   _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______
      )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case QWERTY:
        if (record->event.pressed) {
           print("mode just switched to qwerty and this is a huge string\n");
          set_single_persistent_default_layer(_QWERTY);
        }
        break;

      case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        break;

      case RGBRST:
        #ifdef RGBLIGHT_ENABLE
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_config = rgblight_config;
          }
        #endif
        break;
  }
  return true;
}
