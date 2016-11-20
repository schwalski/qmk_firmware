// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on OSX (But not on Windows).
#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

//Alias
#define C(kc) LCTL(kc)
#define A(kc) LALT(kc)
#define SC(kc) (S(C(kc)))
#define SA(kc) (S(A(kc)))
#define CA(kc) (C(A(kc)))
#define KC_M_WU KC_MS_WH_UP
#define KC_M_WD KC_MS_WH_DOWN

#define KC_M_WR KC_MS_WH_RIGHT
#define KC_M_U KC_MS_U
#define KC_M_D KC_MS_D
#define KC_M_L KC_MS_L
#define KC_M_R KC_MS_R
#define KC_M_A0 KC_MS_ACCEL0
#define KC_M_A1 KC_MS_ACCEL1
#define KC_M_A2 KC_MS_ACCEL2
#define KC_M_B1 KC_MS_BTN1
#define KC_M_B2 KC_MS_BTN2
#define KC_M_B3 KC_MS_BTN3
#define LANG_EN M(0)
#define LANG_JA M(1)

//Layers
enum {
  L_MAC = 0, // Mac Qwerty
  L_WIN, // Windows
  L_QKDW, // QKDW
  L_CUR, // mouse and cursor
  L_CONF // config
};

//Tap Dance Declarations
enum {
  TD_LANG = 0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | `~     |   1! |   2@ |   3# |   4$ |   5% | ESC  |           |CmdAES|   6^ |   7& |   8* |   9( |   0) |   =+   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  [{  |           |  ]}  |   Y  |   U  |   I  |   O  |   P  |   -_   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCtrl  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;:  |   '"   |
 * |--------+------+------+------+------+------|  (   |           |  )   |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |  ,<  |  .>  |  /?  |   \|   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      | LAlt |                                       | RAlt |  BS  |  DEL |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |Cmd sp|      |       |      | ctl F3 |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 | Space|LShift|------|       |------| RShift | Enter|
 *                                 |  Cmd |      | LCtrl|       | Hyper|        | ->L2 |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[L_MAC] = KEYMAP(  // layer 0 : default
    // left hand
    KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_ESC,
    KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_LBRC,
    KC_LCTL,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,
    KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       S(KC_9),
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_LALT,

    LGUI(KC_SPC),   KC_TRNS,
    KC_TRNS,
    GUI_T(KC_SPC),  KC_LSFT,    KC_LCTL,


    //righthand
    RGUI(A(KC_ESC)), KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_EQL,
    KC_RBRC,    KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_MINS,
                KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
    S(KC_0),    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_BSLS,
                            KC_RALT,    KC_BSPC,    KC_DEL,     KC_TRNS,    KC_TRNS,

    KC_TRNS,  C(KC_F3),
    KC_TRNS,
    KC_HYPR,  KC_RSFT,    LT(L_CUR,KC_ENT)
),


/* Keymap: Windows override
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |Alt F4|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | Space|      |------|       |------|      |      |
 *                                 | LCtrl|      | Win  |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_WIN] = KEYMAP(
    // left hand
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,

                KC_TRNS,    KC_TRNS,
                            KC_TRNS,
    CTL_T(KC_SPC),    KC_TRNS,    KC_LGUI,

    //righthand
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,

    KC_TRNS,    A(KC_F4),
    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS
),


/* Keymap: QKDW layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   K  |   D  |   W  |   F  |      |           |      |   P  |   B  |   Y  |   J  |  ;:  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   S  |   I  |   T  |   G  |------|           |------|   H  |   N  |   E  |   O  |   U  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   R  |   V  |      |           |      |   L  |   M  |  ,<  |  .>  |  /?  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_QKDW] = KEYMAP(
    // left hand
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_Q,       KC_K,       KC_D,       KC_W,       KC_F,       KC_TRNS,
    KC_TRNS,    KC_A,       KC_S,       KC_I,       KC_T,       KC_G,
    KC_TRNS,    SFT_T(KC_Z),       KC_X,       KC_C,       KC_R,       KC_V,       KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,

                KC_TRNS,    KC_TRNS,
                            KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,


    //righthand
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_P,       KC_B,       KC_Y,       KC_J,       KC_SCLN,    KC_TRNS,
                KC_H,       KC_N,       KC_E,       KC_O,       KC_U,       KC_TRNS,
    KC_TRNS,    KC_L,       KC_M,       KC_COMM,    ALT_T(KC_DOT),     SFT_T(KC_SLSH),    KC_TRNS,
                            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,

    KC_TRNS,    KC_TRNS,
    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS
),


/* Keymap: Cursor, Mouse Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F11 |           | F12  |  F6  |  F7  |  F8  |  F9  |  F10 | ->CNF  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | M_U  |      |      |   (  |           |  )   | Home | PgUp |  Up  | PgDn |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | M_L  | M_D  | M_R  |      |------|           |------| End  | Left | Down | Right|   :  |        |
 * |--------+------+------+------+------+------|SC Tab|           | C Tab|------+------+------+------+------+--------|
 * |        |   1! |   2@ |   3# |   4$ |   5% |      |           |      |   6^ |   7& |   8* |   9( |   0) |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | MBtn3| MBtn2|                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | MBtn1| 　　　|------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_CUR] = KEYMAP(
    // left hand
    KC_TRNS,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,            KC_F11,
    KC_TRNS,      KC_TRNS,        KC_TRNS,        KC_M_U,         KC_TRNS,        KC_TRNS,          KC_LPRN,
    KC_TRNS,      KC_TRNS,        KC_M_L,         KC_M_D,         KC_M_R,         KC_TRNS,
    KC_TRNS,      SFT_T(KC_1),           KC_2,           KC_3,           KC_4,           KC_5,             SC(KC_TAB),
    KC_TRNS,      KC_TRNS,        KC_TRNS,        KC_M_B3,        KC_M_B2,

                  KC_TRNS,        KC_TRNS,
                                  KC_TRNS,
    KC_M_B1,      KC_TRNS,        KC_TRNS,

    //righthand
    KC_F12,       KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,           MO(L_CONF),
    KC_RPRN,      KC_HOME,        KC_PGUP,        KC_UP,          KC_PGDN,        KC_TRNS,          KC_TRNS,
                  KC_END,         KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_COLN,          KC_TRNS,
    C(KC_TAB),    KC_6,           KC_7,           KC_8,           KC_9,           SFT_T(KC_0),      KC_TRNS,
                                  KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,          KC_TRNS,

    KC_TRNS,      KC_TRNS,
    KC_TRNS,
    KC_TRNS,      KC_TRNS,   KC_TRNS
),


/* Keymap: CONF
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  RESET | Mac  | Win  |      |      |      |      |           |      | QWRT |      |      |      | QKDW |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_CONF] = KEYMAP(
    // left hand
    RESET,      DF(L_MAC),  DF(L_WIN),  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,

                KC_TRNS,    KC_TRNS,
                            KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,

    //righthand
    KC_TRNS,    TO(L_MAC), KC_TRNS, KC_TRNS, KC_TRNS, TO(L_QKDW),    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,

    KC_TRNS,    KC_TRNS,
    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS
)
};

const uint16_t PROGMEM fn_actions[] = {
//    [1] = ACTION_LAYER_TAP_TOGGLE(L1)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
    if (record->event.pressed) {
        switch(id) {
            case 0:
                return MACRO( T(MHEN), T(LANG2), END);
                break;
            case 1:
                return MACRO( T(HENK), T(LANG1), END);
                break;
        }
    }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 0:
        case 3:
            break;
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 4:
            ergodox_right_led_3_on();
            break;
        default:
            ergodox_board_led_on();
            break;
    }

};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_LANG]  = ACTION_TAP_DANCE_DOUBLE(KC_LANG2, KC_LANG1)
// Other declarations would go here, separated by commas, if you have them
};
