#include QMK_KEYBOARD_H

// ** LAYER & VARIABLE ** //
enum layers {
    _BASE = 0,
    _SYM,
    _NAV,
    _FUNC,
    _FUNC2,
    _SETTINGS,
    _MAC_OVERLAY
};

bool is_mac_mode = false;

enum custom_keycodes {
    OS_TOGGLE = SAFE_RANGE,

    // VSCode > FOCUS > ...
    VSC_FOCUS_L, // Left
    VSC_FOCUS_D, // Down
    VSC_FOCUS_R, // Right
    VSC_FOCUS_U, // Up
    
    // VSCode > MOVE > ...
    VSC_MOVE_L, // Left
    VSC_MOVE_D, // Down
    VSC_MOVE_R, // Right
    VSC_MOVE_U  // Up
};

// ** CHORDAL HOLD HAND DEFINE ** //
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
    'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R',
    '*', '*', '*',                        '*', '*', '*'
);

#define CHORDAL_TERM 35

bool get_chordal_hold(
    uint16_t tap_hold_keycode, 
    keyrecord_t* tap_hold_record,
    uint16_t other_keycode,
    keyrecord_t* other_record
) {
    uint16_t elapsed = TIMER_DIFF_16(other_record->event.time, tap_hold_record->event.time);

    if (elapsed < CHORDAL_TERM) {
        return get_chordal_hold_default(tap_hold_record, other_record);
    }
    return true;
}

// ** KEYMAP ** //
#define KC_L_THM LGUI_T(KC_ESC) 
#define KC_R_THM KC_DEL

#define KC_KOR KC_F18

#define SYM_T(kc) LT(_SYM, kc)
#define FUNC_T(kc) LT(_FUNC, kc)
#define NAV_T(kc) LT(_NAV, kc)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* #0: BASE (Windows Default) */
    [_BASE] = LAYOUT(
        KC_Q,           KC_W,           KC_E,           KC_R,          KC_T,            /**/    KC_Y,           KC_U,           KC_I,           KC_O,           KC_SLSH,            
        KC_A,           KC_S,           KC_D,           KC_F,          KC_G,            /**/    KC_H,           KC_J,           KC_K,           KC_L,           KC_P,               
        LSFT_T(KC_Z),   LALT_T(KC_X),   KC_C,           KC_V,          KC_B,            /**/    KC_B,           KC_N,           KC_M,           RALT_T(KC_COMM),RSFT_T(KC_DOT),     
        /**/                            KC_L_THM,       SYM_T(KC_SPC), LCTL_T(KC_TAB),  /**/    FUNC_T(KC_KOR), NAV_T(KC_BSPC), KC_R_THM
    ),

    /* #1: SYMBOL */
    [_SYM] = LAYOUT(
        KC_TILD,        KC_MINS,        KC_EQL,         KC_SCLN,        KC_DQUO,        /**/    KC_PIPE,        KC_LCBR,        KC_LBRC,        KC_RBRC,        KC_RCBR,
        KC_GRV,         KC_UNDS,        KC_PLUS,        KC_COLN,        KC_QUOT,        /**/    KC_BSLS,        KC_LT,          KC_LPRN,        KC_RPRN,        KC_GT,
        KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         CW_TOGG,        /**/    KC_RCTL,        KC_PERC,        KC_CIRC,        KC_AMPR,        KC_ASTR,
        /**/                            _______,        _______,        _______,        /**/    _______,        _______,        _______
    ),

    /* #2: NAVIGATION & NUMBER */
    [_NAV] = LAYOUT(
        KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           /**/    KC_TAB,         KC_HOME,        KC_UP,          KC_BSPC,        XXX,
        KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           /**/    KC_SPC,         KC_LEFT,        KC_DOWN,        KC_RGHT,        LCTL_T(KC_ENT),
        KC_LSFT,        KC_LALT,        KC_COMM,        KC_DOT,         CW_TOGG,        /**/    KC_PSCR,        KC_END,         KC_PGUP,        KC_PGDN,        XXX,
        /**/                            _______,        _______,        _______,        /**/    _______,        _______,        _______
    ),

    /* #3: FUNCTION */
    [_FUNC] = LAYOUT(
        LCTL(KC_W),     LCTL(KC_PGUP),  VSC_FOCUS_U,    LCTL(KC_PGDN),  XXX,            /**/    XXX,            KC_F9,          KC_F10,         KC_F11,         KC_F12,
        MO(_FUNC2),     VSC_FOCUS_L,    VSC_FOCUS_D,    VSC_FOCUS_R,    XXX,            /**/    XXX,            KC_F5,          KC_F6,          KC_F7,          KC_F8,
        XXX,            LCTL(KC_T),     LCTL(KC_N),     LCTL(S(KC_N)),  XXX,            /**/    XXX,            KC_F1,          KC_F2,          KC_F3,          KC_F4,
        /**/                            _______,        _______,        _______,        /**/    _______,        _______,        _______
    ),

    /* #4: FUNCTION, DEEPER */
    [_FUNC2] = LAYOUT(
        XXX,            _______,        VSC_MOVE_U,     _______,        XXX,            /**/    XXX,            XXX,            XXX,            XXX,            XXX,
        XXX,            VSC_MOVE_L,     VSC_MOVE_D,     VSC_MOVE_R,     XXX,            /**/    XXX,            XXX,            XXX,            XXX,            XXX,
        XXX,            XXX,            XXX,            XXX,            XXX,            /**/    XXX,            XXX,            XXX,            XXX,            XXX,
        /**/                            _______,        _______,        _______,        /**/    _______,        _______,        _______
    ),

    /* #5: SETTINGS */
    [_SETTINGS] = LAYOUT(
        QK_BOOT,        XXX,            XXX,            XXX,            XXX,            /**/    XXX,            XXX,            XXX,            OS_TOGGLE,      QK_BOOT,
        XXX,            XXX,            XXX,            XXX,            XXX,            /**/    XXX,            XXX,            XXX,            NK_TOGG,        XXX,
        XXX,            XXX,            XXX,            XXX,            XXX,            /**/    XXX,            XXX,            XXX,            XXX,            XXX,
        /**/                            XXX,            XXX,            XXX,            /**/    XXX,            XXX,            XXX
    ),

    /* #6: MAC_OVERLAY */
    [_MAC_OVERLAY] = LAYOUT(
        _______,        _______,        _______,        _______,        _______,        /**/    _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        /**/    _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        /**/    _______,        _______,        _______,        _______,        _______,
        /**/                            _______,        _______,        LGUI_T(KC_TAB), /**/    _______,        _______,        _______ 
    ),
};


// ** COMBO ** //
#define COMBO_LIST \
    COMBO_X(CB_ENTER,    KC_ENT,        KC_K, KC_L) \
    COMBO_X(CB_ESC,      KC_ESC,        KC_W, KC_E) \
    COMBO_X(CB_CAPSWORD, CW_TOGG,       LSFT_T(KC_Z), RSFT_T(KC_DOT)) \
    COMBO_X(CB_SETTINGS, MO(_SETTINGS), LCTL_T(KC_TAB), LT(_FUNC, KC_LNG1)) \
    COMBO_X(CB_BOOT_L,   QK_BOOT,       KC_Q, KC_A, LSFT_T(KC_Z)) \
    COMBO_X(CB_BOOT_R,   QK_BOOT,       KC_SLSH, KC_P, RSFT_T(KC_DOT)) \
    COMBO_X(CB_MAC_TOG,  OS_TOGGLE,     KC_Q, KC_W, KC_E)

// MACRO_ENGINE
enum combos {
    #define COMBO_X(name, result, ...) name,
    COMBO_LIST
    #undef COMBO_X
};

#define COMBO_X(name, result, ...) const uint16_t PROGMEM name##_combo[] = {__VA_ARGS__, COMBO_END};
COMBO_LIST
#undef COMBO_X

combo_t key_combos[] = {
    #define COMBO_X(name, result, ...) [name] = COMBO(name##_combo, result),
    COMBO_LIST
    #undef COMBO_X
};


// ** PER-KEY PERMISSIVE HOLD ** //
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_TAB):
            if (timer_elapsed(record->event.time) > 100) {
                return true; 
            }
            return false;

        default:
            return false; 
    }
}

// ** MACRO & LOGICS & SNATCH ** //
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case FUNC_T(KC_KOR):
            if (record->tap.count && record->event.pressed) {
                if (is_mac_mode) {
                    tap_code16(LCTL(KC_SPC));
                } else {
                    tap_code(KC_LNG1);
                }
                return false;
            }
            break;
    }

    if (record->event.pressed) {
        switch (keycode) {
            case OS_TOGGLE:
                is_mac_mode = !is_mac_mode; 
                if (is_mac_mode) {
                    layer_on(_MAC_OVERLAY);

                    if (keymap_config.nkro) {
                        keymap_config.nkro = 0;
                    }
                } else {
                    layer_off(_MAC_OVERLAY);

                    if (keymap_config.nkro) {
                        keymap_config.nkro = 1;
                    }

                }
                return false;
            
            case VSC_FOCUS_L:
                if (is_mac_mode) { tap_code16(LGUI(KC_K)); tap_code16(LGUI(KC_LEFT)); } 
                else             { tap_code16(LCTL(KC_K)); tap_code16(LCTL(KC_LEFT)); }
                return false;
            case VSC_FOCUS_D:
                if (is_mac_mode) { tap_code16(LGUI(KC_K)); tap_code16(LGUI(KC_DOWN)); } 
                else             { tap_code16(LCTL(KC_K)); tap_code16(LCTL(KC_DOWN)); }
                return false;
            case VSC_FOCUS_R: 
                if (is_mac_mode) { tap_code16(LGUI(KC_K)); tap_code16(LGUI(KC_RIGHT)); } 
                else             { tap_code16(LCTL(KC_K)); tap_code16(LCTL(KC_RIGHT)); }
                return false;
            case VSC_FOCUS_U: 
                if (is_mac_mode) { tap_code16(LGUI(KC_K)); tap_code16(LGUI(KC_UP)); } 
                else             { tap_code16(LCTL(KC_K)); tap_code16(LCTL(KC_UP)); }
                return false;

            case VSC_MOVE_L:
                if (is_mac_mode) tap_code16(LGUI(KC_K)); else tap_code16(LCTL(KC_K));
                tap_code(KC_LEFT); return false;
            case VSC_MOVE_D:
                if (is_mac_mode) tap_code16(LGUI(KC_K)); else tap_code16(LCTL(KC_K));
                tap_code(KC_DOWN); return false;
            case VSC_MOVE_R:
                if (is_mac_mode) tap_code16(LGUI(KC_K)); else tap_code16(LCTL(KC_K));
                tap_code(KC_RIGHT); return false;
            case VSC_MOVE_U:
                if (is_mac_mode) tap_code16(LGUI(KC_K)); else tap_code16(LCTL(KC_K));
                tap_code(KC_UP); return false;
        }
    }
    return true;
}