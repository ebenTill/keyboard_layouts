#include QMK_KEYBOARD_H

enum {
    CT_CLN, // one tap for colon, hold for semi-colon
    CT_DASH // one tap for dash, hold for tilde
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data);
void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data);

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
        [CT_CLN] = ACTION_TAP_DANCE_TAP_HOLD(KC_COLN, KC_SCLN),
        [CT_DASH] = ACTION_TAP_DANCE_TAP_HOLD(KC_MINS, KC_TILD),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case TD(CT_CLN):  // list all tap dance keycodes with tap-hold configurations
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(CT_DASH):  // list all tap dance keycodes with tap-hold configurations
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;
    }
    return true;
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
            #ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
                ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_split_3x6_3(
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,   KC_O,  KC_P,     TD(CT_DASH),
        LCTL_T(KC_ESC),  KC_A,    KC_S,  KC_D,    KC_F,    KC_G,                   KC_H,    KC_J,    KC_K, KC_L, TD(CT_CLN),  KC_QUOTE,
        SC_LSPO,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N, KC_M,  KC_COMMA, KC_DOT,  KC_SLASH,    SC_RCPC,
        C_S_T(KC_DEL),   MO(1),    LGUI_T(KC_SPC),  SC_SENT,   MO(2), RALT_T(KC_BSPC)
),
[1] = LAYOUT_split_3x6_3(
        KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
        KC_LCTL, KC_VOLU, KC_LEFT, KC_RIGHT, KC_UP, XXXXXXX,                      KC_LEFT, KC_4,    KC_5,    KC_6,    XXXXXXX, XXXXXXX,
        KC_LSFT, KC_VOLD, KC_MUTE, XXXXXXX, KC_DOWN, XXXXXXX,                      XXXXXXX, KC_1, KC_2, KC_3, XXXXXXX, XXXXXXX,
        KC_LGUI, _______,  KC_SPC,     KC_ENT,   MO(3), KC_RALT
),
[2] = LAYOUT_split_3x6_3(
        KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        KC_LCTL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
        KC_LSFT, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
        KC_LGUI,   MO(3),  KC_SPC,     KC_ENT, _______, KC_RALT
),
[3] = LAYOUT_split_3x6_3(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
)
};