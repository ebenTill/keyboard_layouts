/* Copyright 2015-2017 Jack Humbert
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

#include QMK_KEYBOARD_H


enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_ortho_4x12(
    KC_ESC, KC_Q, KC_W, KC_E  , KC_R    , KC_T   , KC_Y  , KC_U    , KC_I    , KC_O   , KC_P     , KC_BSPC ,
    KC_TAB, KC_A, KC_S, KC_D  , KC_F    , KC_G   , KC_H  , KC_J    , KC_K    , KC_L   , KC_SCLN  , KC_QUOT ,
    KC_LCTL, KC_Z, KC_X, KC_C  , KC_V    , KC_B   , KC_N  , KC_M    , KC_COMM , KC_DOT , KC_SLASH , KC_NO   ,
    KC_LSFT, KC_NO, KC_NO, KC_NO , MO(_LOWER), KC_SPC , KC_ENT, MO(_RAISE), KC_LEFT, KC_DOWN  , KC_UP    , KC_RGHT
  ),

  [_LOWER] = LAYOUT_ortho_4x12(
    KC_TILD , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_BSPC ,
    KC_DEL  , KC_LT   , KC_GT   , KC_DQT  , KC_QUES , KC_PIPE , KC_NO   , KC_UNDS , KC_PLUS , KC_LCBR , KC_RCBR , KC_NO   ,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
  ),

  [_RAISE] = LAYOUT_ortho_4x12(
    KC_TAB  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_BSPC ,
    KC_PIPE , KC_LT   , KC_GT   , KC_MINS , KC_UNDS , KC_QUOT , KC_DQT  , KC_EQL  , KC_PLUS , KC_LBRC , KC_RBRC , KC_BSLS ,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
  ),

  [_ADJUST] = LAYOUT_planck_mit(
    _______, QK_BOOT, DB_TOGG, _______, _______, _______, _______, _______, _______,  _______, _______, KC_DEL ,
    _______, _______, MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______,  _______, _______,  _______,
    _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,     _______,      _______, _______,  _______, _______, _______
  )

};

