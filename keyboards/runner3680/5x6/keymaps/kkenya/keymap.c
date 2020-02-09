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
     * 左右を間違えて作ったのでキーマップを反転させる必要がある
     * ,-----------------------------------------.              ,-----------------------------------------.
     * |   5  |   4  |   3  |   2  |   1  | Esc  |              |   6  |   7  |   8  |   9  |   0  |   -  |
     * |------+------+------+------+------+------|              |------+------+------+------+------+------|
     * |   T  |   R  |   E  |   W  |   Q  | Tab  |              |   Y  |   U  |   I  |   O  |   P  |   [  |
     * |------+------+------+------+------+------|              |------+------+------+------+------+------|
     * |   G  |   F  |   D  |   S  |   A  | Ctrl |              |   H  |   J  |   K  |   L  |   ;  |   "  |
     * |------+------+------+------+------+------|              |------+------+------+------+------+------|
     * |   B  |   V  |   C  |   X  |   Z  | Shift|              |   N  |   M  |   ,  |   .  |   /  | Shift|
     * |------+------+------+------+------+------|              |------+------+------+------+------+------|
     * | Space| Space| Cmd  | Alt  |Adjust|   `  |              | Space| Space| Cmd  | Alt  | Left | Down |
     * `-----------------------------------------'              `-----------------------------------------'
     */

    /*
  *[_QWERTY] = LAYOUT(
  *    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        _______, _______, _______, _______, _______, _______, 
  *    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        _______, _______, _______, _______, _______, _______, 
  *    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        _______, _______, _______, _______, _______, _______, 
  *    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        _______, _______, _______, _______, _______, _______, 
  *    KC_GRV,  ADJUST,  KC_LALT, KC_RCMD, KC_SPC,  KC_SPC,      _______, _______, _______, _______, _______, _______
  *    ),
  *    */
  [_QWERTY] = LAYOUT(
      KC_5,   KC_4,    KC_3,    KC_2,    KC_1,    KC_ESC,       _______, _______, _______, _______, _______, _______, 
      KC_T,   KC_R,    KC_E,    KC_W,    KC_Q,    KC_TAB,       _______, _______, _______, _______, _______, _______, 
      KC_G,   KC_F,    KC_D,    KC_S,    KC_A,    KC_LCTL,      _______, _______, _______, _______, _______, _______, 
      KC_B,   KC_V,    KC_C,    KC_X,    KC_Z,    KC_LSFT,      _______, _______, _______, _______, _______, _______, 
      KC_SPC, KC_SPC,  KC_RCMD, KC_LALT, ADJUST,  KC_GRV,       _______, _______, _______, _______, _______, _______
      ),

    /* Adjust
     * ,-----------------------------------------.             ,-----------------------------------------.
     * |   F6 |   F7 |   F8 |   F9 |  F10 |  F11 |             |      |   F1 |   F2 |   F3 |   F4 |   F5 |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      |RGBRST| RESET|      |      |      |             |      |   1  |   2  |   3  |   4  |   5  |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      |  TOG |  HUI |  SAI |  VAI |      |             |      |      |      |      |      |      |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      |  MOD |  HUD |  SAD |  VAD |      |             |      |      |      |      |      |      |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      |      |      |      |      |      |             |      |      |      |      |      |      |
     * `-----------------------------------------'             `-----------------------------------------'
     */
  [_ADJUST] =  LAYOUT( \
      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,     _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
      _______, RGBRST,  RESET,   _______, _______, _______,    _______, _______, _______, _______, _______, _______,
      _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______,    _______, _______, _______, _______, _______, _______,
      _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______,    _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______
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
