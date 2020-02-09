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
     * 左右を間違えて作ったので左側を右手のキーマップ用に設定
     * なぜかmacOSでAltとMCDが逆に認識される
     * ,-------------------------------------------------------.                 ,-------------------------------------------------------.
     * |  F1  |  F2  |   `  |   1  |   2  |   3  |   4  |   5  |                 | Del  |   =  |   -  |   0  |   9  |   8  |   7  |   6  |
     * |------+------+------+------+------+------+------+------|                 |------+------+------+------+------+------+------+------|
     * |  F3  |  F4  | Tab  |   Q  |   W  |   E  |   R  |   T  |                 |   \  |   ]  |   [  |   P  |   O  |   I  |   U  |   Y  |
     * |------+------+------+------+------+------+------+------|                 |------+------+------+------+------+------+------+------|
     * |  F5  |  F6  | Esc  |   A  |   S  |   D  |   F  |   G  |                 | Enter| Enter|   "  |   ;  |   L  |   K  |   J  |   H  |
     * |------+------+------+------+------+------+------+------|                 |------+------+------+------+------+------+------+------|
     * |  F7  |  F8  | Shift|   Z  |   X  |   C  |   V  |   B  |                 |Adjust| Shift| Shift|   /  |   .  |   ,  |   M  |   N  |
     * |------+------+------+------+------+------+------+------|                 |------+------+------+------+------+------+------+------|
     * |  F9  |  F10 | Ctrl | GUI  | Alt  | EISU |  Del | Space|                 | Right|  Up  | Down | Left | Alt  | Cmd  | Space| Space|
     * `-------------------------------------------------------'                 `-------------------------------------------------------'
     */
  [_QWERTY] = LAYOUT(
      KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_DEL,      KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_DEL,  
      KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,     KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS, 
      KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,  KC_ENT,  KC_ENT,      KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,  KC_ENT,  KC_ENT,  
      KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,  KC_RSFT, ADJUST,      KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,  KC_RSFT, ADJUST,  
      KC_SPC,  KC_SPC, KC_LALT, KC_RCMD, KC_LEFT, KC_DOWN,  KC_UP,   KC_RGHT,     KC_SPC,  KC_SPC, KC_LALT, KC_RCMD, KC_LEFT, KC_DOWN,  KC_UP,   KC_RGHT
      ),

    /* Adjust
      ,-------------------------------------------------------.                  ,-------------------------------------------------------.
     * |   F6 |   F7 |   F8 |   F9 |  F10 |  F11 |  F12 |      |                 |      |  F12 |  F11 |  F10 |   F9 |   F8 |   F7 |   F6 |
     * |------+------+------+------+------+------+------+------|                 |------+------+------+------+------+------+------+------|
     * |   6  |   7  |   8  |   9  |   0  |   -  |   =  | Del  |                 |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------|                 |------+------+------+------+------+------+------+------|
     * |      |      |      |  TOG |  HUI |  SAI |  VAI |      |                 |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------|                 |------+------+------+------+------+------+------+------|
     * |      |      |      |  MOD |  HUD |  SAD |  VAD |      |                 |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------|                 |------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |                 |      |      |      |      |      |      |      |      |
     * `-------------------------------------------------------'                 `-------------------------------------------------------'
     */
  [_ADJUST] =  LAYOUT(
      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,    _______, KC_F12,  KC_F11,  KC_F10,  KC_F9,   KC_F8,   KC_F7,   KC_F6,
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
