/* * Notes */
/* ** If anyone else should ever read this... */
/* - watch out - I use a german local, so german keycodes are all over the place
   - sorry for those ugly comment headings... I use emacs' outshine minor mode for folding, so what might look incredibly messy for you
   is actually what keeps this file readable
*/

/* ** for me */
/* if i forget how to keep my branch (fork? whatever) up to date with
   zsa's repo:
   https://stackoverflow.com/questions/41283955/github-keeps-saying-this-branch-is-x-commits-ahead-y-commits-behind */
/* *** todo
   - understand git... arrgh.
   - implement macro to get rid of windows footer (or find software/ahk solution)
   - implement unicode "⇒" as single key
   - or make L1 and L2 combined act as L5 or something like in neo2 (nice to hold)
*/




/* * Includes and defines */
#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_german.h"


/* ** Aliases / handles */
#define ent_KENT LT(0,KC_ENTER)
#define m_MENU LT(0,KC_M)
#define x_CUT LT(0,KC_X)
#define v_PASTE LT(0,KC_V)
#define c_COPY LT(0,KC_C)
#define f_SEARCH LT(0,KC_F)
#define hyph_ENDASH LT(0,DE_MINS)

#define TSKMGR LCTL(LSFT(KC_ESC))



/* * Macros: the enum part  */
enum custom_keycodes {
 // RGB_SLD,
  ID_mark_par,
  ST_MACRO_1,
  M_Id_Quer,
  M_ALT_TAB = SAFE_RANGE, // for super alt tab
 // Refocus
};

/* ** Super Alt Tab */
// needs about 120 bytes
bool is_alt_tab_active = false;    // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;        // we will be using them soon.

void matrix_scan_user(void) {     // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}






/* * Combos */
// don't forget to update the combo counter in .config every time you add a combo!!!

const uint16_t PROGMEM test_combo1[] = {KC_K, KC_H, KC_G, COMBO_END}; // Caps Lock
const uint16_t PROGMEM test_combo2[] = {KC_V, KC_L, COMBO_END};
const uint16_t PROGMEM test_combo3[] = {DE_EQL, DE_RABK, COMBO_END};
// TODO: make "⇒" from those to: DE_RPRN,        DE_MINS,

combo_t key_combos[COMBO_COUNT] = {
    COMBO(test_combo1, KC_CAPSLOCK),
    COMBO(test_combo2, KC_1),             // this is stupid. i should do something more interesting with this ;-)
    //    COMBO(test_combo3, X(DRAR)),
    COMBO(test_combo3, KC_INSERT)        // really what i  want is to send Unicode ⇒, but it doesn't work with "X(DRAR)". will have to try sendstring in custom code
    //    COMBO(test_combo2, LCTL(KC_Z)), // keycodes with modifiers are possible too!

};


/* ** Combo configurations */
/* see https://beta.docs.qmk.fm/using-qmk/software-features/feature_combo for details */

/* *** not needed (yet) */
/* if I should enable this later: remember to set the config flag in config.h */



/* uint16_t get_combo_term(uint16_t index, combo_t *combo) { */
/*     // decide by combo->keycode */
/*     switch (combo->keycode) { */
/*         case KC_X: */
/*             return 50; */
/*     } */

/*     // or with combo index, i.e. its name from enum. */
/*     switch (index) { */
/*         case COMBO_NAME_HERE: */
/*             return 9001; */
/*     } */

/*     // And if you're feeling adventurous, you can even decide by the keys in the chord, */
/*     // i.e. the exact array of keys you defined for the combo. */
/*     // This can be useful if your combos have a common key and you want to apply the */
/*     // same combo term for all of them. */
/*     if (combo->keys[0] == KC_ENTER) { // if first key in the array is KC_ENTER */
/*         return 150; */
/*     } */

/*     return COMBO_TERM; */
/* } */



/* bool get_combo_must_hold(uint16_t index, combo_t *combo) { */
/*     // Same as above, decide by keycode, the combo index, or by the keys in the chord. */

/*     if (KEYCODE_IS_MOD(combo->keycode) ||  */
/*         (combo->keycode >= QK_MOMENTARY && combo->keycode <= QK_MOMENTARY_MAX) // MO(kc) keycodes */
/*         ) { */
/*         return true; */
/*     } */

/*     switch (index) { */
/*         case COMBO_NAME_HERE: */
/*             return true; */
/*     } */

/*     return false; */
/* } */



/* *** tap-only combos for use with Mod-Tap keys */
bool get_combo_must_tap(uint16_t index, combo_t *combo) {
    // If you want all combos to be tap-only, just uncomment the next line
    // return true

    // If you want *all* combos, that have Mod-Tap/Layer-Tap/Momentary keys in its chord, to be tap-only, this is for you:
    uint16_t key;
    uint8_t idx = 0;
    while ((key = pgm_read_word(&combo->keys[idx])) != COMBO_END) {
        switch (key) {
            case QK_MOD_TAP...QK_MOD_TAP_MAX:
            case QK_LAYER_TAP...QK_LAYER_TAP_MAX:
            case QK_MOMENTARY...QK_MOMENTARY_MAX:
                return true;
        }
        idx += 1;
    }
    return false;

}



/* * Unicode */

// this is the unicode table, requires UNICODEMAP_ENABLE = yes in rules.mk (and, in my case, UNICODE_ENABLE = no or so, due to ergodox' presets)
enum unicode_names {
    BANG,
    SNEK,
    AACU,
    DQ1,
    DQ2,
    DQ3,
    SQ1,
    SQ2,
    SQ3,
    DRAR,
};

const uint32_t PROGMEM unicode_map[] = {
    [BANG] = 0x203D,       // interrobang
    [SNEK] = 0x1F40D,	   // well, a snake
    [AACU] = 0x00E1,	   // a mit Akut
    [DQ1] = 0x201E,	   // „
    [DQ2] = 0x201C,	   // “
    [DQ3] = 0x201D,	   // ”
    [SQ1] = 0x201A,	   // ‚
    [SQ2] = 0x2018,	   // ‘
    [SQ3] = 0x2019,	   // ’
    [DRAR] = 0x21D2,      // ⇒
    //    [] = 0x,   //
    //    [] = 0x,   //
    //    [] = 0x,   //
    //    [] = 0x,   //

};


/* * Tap Dance Part I */
// based on the code from DanielGGordon


// definitions for states
typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;


// define possible states
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD
};



// enumerate tap dances
enum {
    CVXA,
    CTL_ALT,
    ESC_WTAB
};


// not sure what this does
uint8_t cur_dance(qk_tap_dance_state_t *state);


/* ** _finished and _reset definitions for all TDs */

// Those have to be put it here so they can be used in any keymap


void cvxa_finished(qk_tap_dance_state_t *state, void *user_data);
void cvxa_reset(qk_tap_dance_state_t *state, void *user_data);




/* * Tap-Hold configuration */
/* ** Per key tapping terms */
// requires #define TAPPING_TERM_PER_KEY in config.h

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  /* case SFT_T(KC_SPC): */
  /*   return TAPPING_TERM + 1250; */
  /* case LT(1, KC_GRV): */
  /*   return 130; */
  case f_SEARCH:
    return TAPPING_TERM + 100;
  case TD(CVXA):
    return TAPPING_TERM + 100;
  case TD(CTL_ALT):
    return TAPPING_TERM + 100;    // hitting another key directly after pressing and holding the CTL_ALT key results in it only applying to that first key
                                  // but setting this to 10 ms breaks the one-shot functionality (or maybe the other thing did...)
                                  // or else hold on other keypress could work...

    // longer for German ü on left pinky
    // AARRRGH Im so stupid!!! doesn't work because the key ist not DE_UDIA but LT(1,DE_UDIA), so...
    // probably first have to implement a TD here, then set a tapping term for it
  case LT(1,DE_UDIA):
    return TAPPING_TERM + 100;
  case LT(4,DE_Z):
    return TAPPING_TERM + 100;



    /*   ** Mod-Tap terms */

    // home row base layer
  case CTL_T(KC_E):
    return TAPPING_TERM + 100;
  case SFT_T(KC_A):
    return TAPPING_TERM;   // less harm in accidentally choosing hold action and most time sensitive
  case ALT_T(KC_I):
    return TAPPING_TERM + 100;
  case GUI_T(KC_U):
    return TAPPING_TERM + 100;


  case CTL_T(KC_N):
    return TAPPING_TERM + 100;
  case SFT_T(KC_R):
    return TAPPING_TERM;   // less harm in accidentally choosing hold action and most time sensitive
  case ALT_T(KC_T):
    return TAPPING_TERM + 100;
  case GUI_T(KC_D):
    return TAPPING_TERM + 100;


    // home row layer 1 (number / navigation)
  case CTL_T(KC_RIGHT):
    return TAPPING_TERM + 100;
  case SFT_T(KC_DOWN):
    return TAPPING_TERM + 100;
  case ALT_T(KC_LEFT):
    return TAPPING_TERM + 100;
  case GUI_T(KC_PMNS):
    return TAPPING_TERM + 100;



  case CTL_T(KC_P4):
    return TAPPING_TERM + 100;
  case SFT_T(KC_P5):
    return TAPPING_TERM + 100;
  case ALT_T(KC_P6):
    return TAPPING_TERM + 100;
  case GUI_T(KC_HOME):
    return TAPPING_TERM + 100;




  case LSFT_T(KC_ENTER): // should not apply because of ON_OTHER_KEYPRESS... but that didn't work. so.
    return 100;
  case RSFT_T(KC_ENTER):
    return 100;
    // all other cases: default from 'config.h' (currently 115)
  default:
    return TAPPING_TERM;

  }
}

/*   ** Hold on other keypress */
// currently only for Enter/Shift
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LSFT_T(KC_ENTER):
    // Immediately Select The Hold Action When Another Key Is Pressed.
    return true;

    case RSFT_T(KC_ENTER):
    return true;

    case TD(CTL_ALT):   // seems to have no effect... perhaps because it's custom code?
    return true;

  default:
    // Do not immediately select the hold action when another key is pressed.
    return false;
  }
}


/*   ** per-key tapping force hold (select hold function on second keydown after rapidly tapping - essentially like DOUBLE_HOLD case in TDs) */
// do i even need this?
// i had tapping force hold for all keys, now it should be restricted to the ones below
// had to do this because home row modifiers on navigation layer killed repeating arrow keys (very bad)
// now let's see where it breaks and fix it here

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Space/L1 must have this to type numbers or move about after typing a space
  case LT(1, KC_SPC):
    return true;

  default:
    return false;
  }
}



/* * THE LAYERS */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/* ** Layer 0: base layer (neo2) */
   /*  * Layer 0: Basic layer (neo2)
 * (watch out - german keycodes everywhere!)
 *
 *    ,-----------------------------------------------------------------------------------.               ,--------------------------------------------------------------------------------.
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |    Esc          |    1     |    2     |    3     |    4     |    5     |  RESET   |               |  TG(6)   |    6     |    7     |    8     |    9     |    0     |  Backspace   |
 *    |    Overview     |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |-----------------+----------+----------+----------+----------+----------+----------|               | ---------+----------+----------+----------+----------+----------+--------------|
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |  Tab            |    X     |    V     |    L     |    C     |    W     |  TG(3)   |               |  OSL(7)  |    K     |    H     |    G     |  f / C-f |    Q     |    ß         |
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |   (TD)   |          |              |
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |-----------------+----------+----------+----------+----------+----------|          |               |          | ---------+----------+----------+----------+----------+--------------|
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |  Ralt / L2      |   u / W- |  i / A-  |   a / S- |   e / C- |    O     | ---------|               | ---------|    S     |  N/Ctrl  |  R/Shft  |   T/Alt  |   D/Win  |   Y / L2     |
 *    |  (=Comp)        |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |-----------------+----------+----------+----------+----------+----------|  Undo    |               |  Save    | ---------+----------+----------+----------+----------+--------------|
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |  Ent / Shft     |  Ü / L1  |    Ö     |    Ä     |    P     |   Z / L4 |          |               |          |    B     |    M     |    ,     |    .     |     J    |  Ent / Shft  |
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    `-----------------+----------+----------+----------+----------+----------+----------'                `---------+----------+----------+----------+----------+----------+--------------'
 *           |          |          |          |          |          |                                                          |          |          |          |          |              |
 *           |          |  Ctrl    |  Win     |  Alt     |  Spc/L1  |                                                          |  Spc/L1  |  Alt     |  RAlt    |  Ctrl    |  TT(7)       |
 *           |          |          |          |          |          |                                                          |          |          |  (=Comp) |          |              |
 *           |          |          |          |          |          |                                                          |          |          |          |          |              |
 *           `------------------------------------------------------'                                                          `----------------------------------------------------------'
 *
 *
 *                                                                   ,---------------------.            ,----------------------.
 *                                                                   |          |          |            |          |           |
 *                                                                   |  S-F10   |   C-f    |            |  C-V-X-A |  M-Tab    |
 *                                                                   |          |          |            |          |           |
 *                                                        ,----------|----------| ---------|            | ---------+-----------+----------.
 *                                                        |          |          |          |            |          |           |          |
 *                                                        |          |          |   W+-Tab |            |  Ctl/Alt |           |          |
 *                                                        |          |          |          |            |          |           |          |
 *                                                        |  Shift   |  TT(5)   | ---------|            | ---------|  Mouse    |   Ctrl   |
 *                                                        |          |          |  Macro 1 |            |          |  Layer    |          |
 *                                                        |          |          |  Play    |            | M-Alt-Tab|           |          |
 *                                                        |          |          |          |            |          |           |          |
 *                                                        `--------------------------------'            `---------------------------------'
*/

[0] = LAYOUT_ergodox_pretty( // base layer
			      /* base layer (neo2) */
    TD(ESC_WTAB)    , KC_1         ,  KC_2       , KC_3         , KC_4       ,   KC_5       ,        QK_BOOT ,                                         TG(6)  ,     KC_6 ,   KC_7       ,    KC_8,           KC_9,           KC_0,           KC_BSPACE,
    KC_TAB          , x_CUT        ,  v_PASTE    , KC_L         , c_COPY     ,   KC_W       ,        TG(3)   ,                                         OSL(7) ,     KC_K ,   KC_H       ,    KC_G,           f_SEARCH,       KC_Q,           DE_SS,
    LT(2,KC_RALT)   , GUI_T(KC_U)  ,  ALT_T(KC_I), SFT_T(KC_A)  , CTL_T(KC_E),   KC_O       ,                                                                       KC_S ,   CTL_T(KC_N),    SFT_T(KC_R),    ALT_T(KC_T),    GUI_T(KC_D),           LT(2,DE_Y),
    LSFT_T(KC_ENTER), LT(1,DE_UDIA),  DE_ODIA    , DE_ADIA      , KC_P       ,   LT(4,DE_Z) ,        C(DE_Z) ,                                         C(KC_S),     KC_B ,   m_MENU     ,    KC_COMMA,       KC_DOT,         KC_J,           RSFT_T(KC_ENTER),
    _______         , OSM(MOD_LCTL),  KC_LGUI    , OSM(MOD_LALT), LT(1,KC_SPACE),                                                                                           LT(1,KC_SPACE),  OSM(MOD_LALT),  KC_RALT,        OSM(MOD_LCTL),  TT(7),
                                                                                                                                /* thumbs */
    /*                                                                     2     */                 LSFT(KC_F10),   LCTL(KC_F),        /* */     TD(CVXA)   ,   A(KC_TAB),
    /*                                                                     1     */                                 LGUI(KC_TAB),      /* */     TD(CTL_ALT),
    /*                                                                     3     */ OSM(MOD_LSFT) , TT(5)      ,   DYN_MACRO_PLAY1,    /* */     M_ALT_TAB  ,   MO(3)    ,  TD(CTL_ALT)
  ),




/* ** Layer 1: movement and numbers */
/*
 *
 *    ,------------------------------------------------------------------------.              ,-------------------------------------------------------------------------.
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |   Esc      |   f1    |  f2     |  f3     |  f4     |  f5     | M-f4    |              |         |  f6     |  f7     |  f8     |  f9     |  f10    |   f11       |
 *    |   Overview |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |------------+---------+---------+---------+---------+-------------------|              |---------+---------+---------+---------+---------+---------+-------------|
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    | Tab        |  Undo   | Bcksp   |    ↑    |  Del    |  PgUp   |         |              | OSL(7)  | Bcksp   |   P7    |   P8    |   P9    |   +     |   f12       |
 *    |            |         |         |         |         |         |  PgUp   |              |         |         |         |         |         |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |------------+---------+---------+---------+---------+---------|         |              |         |---------+---------+---------+---------+---------+-------------|
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    | Ralt / L2  | Home/W- | ← / A-  |  ↓ / S- |  → / C- |  End    |---------|              |---------|   :     | P4/Ctl  | P5/Shft |  P6/Alt | - / Win |  Y / L2     |
 *    | (=Comp)    |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |------------+---------+---------+---------+---------+---------| PgUp    |              | Save    |---------+---------+---------+---------+---------+-------------|
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    | Ent / Shft |   Esc   |   Tab   |  W-Tab  | Enter/  |  PgDn   |         |              |         |   P0    |   P1    |   P2    |    P3   |    ,    | Ent / Shft  |
 *    |            |         |         |         | KP_Ent  |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    `------------+---------+---------+---------+---------+-------------------'              `-------------------+---------+---------+---------+---------+-------------'
 *     |           |         |         |         |         |                                                      |         |         |         |         |             |
 *     | Swap Hands| Ctrl    | Win     | Alt     | Spc/L1  |                                                      | Spc/L1  | Alt     | RAlt    | Ctrl    | TT(7)       |
 *     |(OS)(disab)|         |         |         |         |                                                      |         |         | (=Comp) |         |             |
 *     |           |         |         |         |         |                                                      |         |         |         |         |             |
 *     `---------------------------------------------------'                                                      `-----------------------------------------------------'
 *
 *
 *                                                ,-------------------.           ,--------------------.
 *                                                |         |         |           |         |          |
 *                                                | S-F10   |  C-f    |           |  Prev   |  Next    |
 *                                                |         |         |           |  Track  |  Track   |
 *                                      ,---------|---------|---------|           |---------+----------+---------.
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |  W+Tab  |           |  Vol +  |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      | Shift   | TT(5)   |---------|           |---------|          |   P0    |
 *                                      |         |         | Macro 1 |           |         |          |         |
 *                                      |         |         | Play    |           |  Vol -  |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      `-----------------------------'           `------------------------------'
 */

[1] = LAYOUT_ergodox_pretty( // nav, numpad, f-keys
			    /* movement and numpad */
			    _______ ,   KC_F1        ,  KC_F2         ,  KC_F3         ,  KC_F4          ,  KC_F5         ,      A(KC_F4)   ,                                    _______,   KC_F6      ,    KC_F7        ,  KC_F8        ,  KC_F9        ,  KC_F10         ,   KC_F11   ,
			    _______ ,   C(DE_Z)      ,  KC_BSPACE     ,  KC_UP         ,  KC_DELETE      ,  KC_PGUP       ,      KC_PGUP    ,                                    _______,   KC_BSPACE  ,    KC_P7        ,  KC_P8        ,  KC_P9        ,  KC_KP_PLUS     ,   KC_F12   ,
			    _______ , GUI_T(KC_HOME) ,  ALT_T(KC_LEFT),  SFT_T(KC_DOWN),  CTL_T(KC_RIGHT),  KC_END        ,                                                                 DE_COLN    ,    CTL_T(KC_P4) ,  SFT_T(KC_P5) ,  ALT_T(KC_P6) ,  GUI_T(KC_PMNS) ,   _______  ,
			    _______ ,   KC_ESCAPE    ,  KC_TAB        ,  LGUI(KC_TAB)  ,  ent_KENT       ,  KC_PGDOWN     ,      KC_PGDOWN  ,                                    _______,   KC_P0      ,    KC_P1        ,  KC_P2        ,  KC_P3        ,  KC_COMMA       ,   _______  ,
			    _______ ,      _______   ,  _______       ,  _______       , _______         ,                                                                                                  _______      ,  _______      ,  _______      ,  _______        ,   _______  ,
			    /* thumbs */
			    /*                                                                     2     */                 _______,        _______,           KC_MEDIA_PREV_TRACK,  KC_MEDIA_NEXT_TRACK,
			    /*                                                                     1     */                                 _______,           KC_AUDIO_VOL_UP,
			    /*                                                                     3     */  _______,       _______,        _______,           KC_AUDIO_VOL_DOWN,   _______ , KC_P0
			    ),


/* ** Layer 2: special characters */
 /* Layer 2: Symbols
 *
 *
 *    ,------------------------------------------------------------------------.              ,-------------------------------------------------------------------------.
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |   (0)      |   ß     |    á    |   xxx   |   xxx   |  xxx    |         |              |         |   xxx   |         |    „    |    “    |    ”    |    xxx      |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |------------+---------+---------+---------+---------+-------------------|              |---------+---------+---------+---------+---------+---------+-------------|
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |   xxx      |  Euro   |   _     |    [    |    ]    |    ^    |         |              |  ???    |    !    |   <     |    >    |    =    |    &    |    @        |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |------------+---------+---------+---------+---------+---------|         |              |         |---------+---------+---------+---------+---------+-------------|
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |    \    |    /    |    {    |    }    |    *    |---------|              |---------|    ?    |    (    |    )    |    -    |    :    |    @        |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |------------+---------+---------+---------+---------+---------|         |              |         |---------+---------+---------+---------+---------+-------------|
 *    |            |         |         |         |         |         |         |              | ???     |         |         |         |         |         |             |
 *    |            |    #    |    $    |     |   |    ~    |    `    |         |              |         |    +    |    %    |    "    |    '    |    ;    |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *     ------------+---------+---------+---------+---------+-------------------'               -----------------+---------+---------+---------+---------+---------------'
 *     |           |         |         |         |         |                                              |         |         |         |         |             |
 *     |   xxx     |         |         |         |         |                                              |         |         |         |  xxx    |   xxx       |
 *     |           |         |         |         |         |                                              |         |         |         |         |             |
 *      ---------------------------------------------------'                                               -----------------------------------------------------'
 *
 *
 *                                                ,-------------------.           ,--------------------.
 *                                                |         |         |           |         |          |
 *                                                |         |         |           |         |          |
 *                                                |         |         |           |         |          |
 *                                      ,---------|---------|---------|           |---------+----------+---------.
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |---------|           |---------|          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                       -----------------------------'            ------------------------------'
 */
[2] = LAYOUT_ergodox_pretty( // symbols
			      /* symbols, brackets, etc. */
			    TO(0)   ,    DE_SS    ,      X(AACU),        KC_NO,          KC_NO,          KC_NO,             _______,                                        _______,    XXXXXXX,   XP(DQ1, SQ1),   XP(DQ2, SQ2),   XP(DQ3, SQ3),        _______,        XXXXXXX,
			    XXXXXXX ,    DE_EURO  ,      DE_UNDS,        DE_LBRC,        DE_RBRC,        DE_CIRC,           _______,                                        DE_ACUT ,   DE_EXLM,        DE_LABK,        DE_RABK,        DE_EQL,         DE_AMPR,        DE_AT,
			    _______ ,    DE_BSLS  ,      DE_SLSH,        DE_LCBR,        DE_RCBR,        DE_ASTR,                                                                       DE_QUES ,       DE_LPRN,        DE_RPRN,        hyph_ENDASH,    DE_COLN,        DE_AT,
			    _______ ,    DE_HASH  ,      DE_DLR,         DE_PIPE,        DE_TILD,        DE_GRV,            _______,                                        DE_CIRC ,   DE_PLUS,        DE_PERC,        DE_DQUO,        DE_QUOT,        DE_SCLN,        _______,
			    XXXXXXX ,    _______  ,      _______,        _______,        _______,                                                                                                       _______,        _______,        _______,        XXXXXXX,        XXXXXXX,
                                                                                                                                /* thumbs */
                                                                                                           _______,        _______,        _______,        _______,

                                                                                                                           _______,        _______,
                                                                                           _______,        _______,        _______,        _______,        _______,        _______
  ),

/* ** Layer 3: Mouse movement */
 /*
 *    ,------------------------------------------------------------------------.              ,-------------------------------------------------------------------------.
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |    TO(0)   |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |------------+---------+---------+---------+---------+-------------------|              |---------+---------+---------+---------+---------+---------+-------------|
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |         | L-Click | MoveUp  | R-Click |         |         |              |         |         | Btn4    |  Btn5   |         |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |------------+---------+---------+---------+---------+---------|         |              |         |---------+---------+---------+---------+---------+-------------|
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |         | MoveL   | MoveDn  | MoveR   |         |---------|              |---------|         | Speed0  | Speed1  | Speed2  |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |------------+---------+---------+---------+---------+---------|         |              |         |---------+---------+---------+---------+---------+-------------|
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |  Cut    |  Copy   |  Paste  |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *     ------------+---------+---------+---------+---------+-------------------'               -------------------+---------+---------+---------+---------+-------------'
 *     |           |         |         |         |         |                                              |         |         |         |         |             |
 *     |           |         |         |         |         |                                              |         |         |         |         |             |
 *     |           |         |         |         |         |                                              |         |         |         |         |             |
 *      ---------------------------------------------------'                                               -----------------------------------------------------'
 *
 *
 *                                                ,-------------------.           ,--------------------.
 *                                                |         |         |           |         |          |
 *                                                |         |         |           |         |          |
 *                                                |         |         |           |         |          |
 *                                      ,---------|---------|---------|           |---------+----------+---------.
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      | L-Click | M-Click |---------|           |---------|          | R-Click |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                       -----------------------------'            ------------------------------'
*/

[3] = LAYOUT_ergodox_pretty( // mouse movement + clicks
    TO(0), 	           _______,        _______,        _______,        _______,          _______,        _______,                                        _______,        _______,        _______,        _______,        _______,        _______,        _______,
           _______,        _______,     KC_MS_BTN1,       KC_MS_UP,     KC_MS_BTN2,          _______,        _______,                                        _______,        _______,     KC_MS_BTN4,     KC_MS_BTN5,        _______,        _______,        _______,
           _______,        MO(4)  ,     KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,         _______,                                                                        _______,   KC_MS_ACCEL0,   KC_MS_ACCEL1,   KC_MS_ACCEL2,        _______,        _______,
           _______,        _______,        C(KC_X),        C(KC_V),         C(KC_C),         _______,        _______,                                        _______,        _______,        _______,        _______,        _______,        _______,        _______,
           _______,        _______,        _______,        _______,        _______,                                                                                                          _______,        _______,        _______,        _______,        _______,
                                                                                                                                /* thumbs */
                                                                                                           _______,        _______,        _______,        _______,
                                                                                                                           _______,        _______,
                                                                                    KC_MS_BTN1,     KC_MS_BTN3,            _______,        _______,        _______, KC_MS_BTN2
  ),



/* ** Layer 4: Mouse scrolling */
/*
 *    ,------------------------------------------------------------------------.              ,-------------------------------------------------------------------------.
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |------------+---------+---------+---------+---------+-------------------|              |---------+---------+---------+---------+---------+---------+-------------|
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |------------+---------+---------+---------+---------+---------|         |              |         |---------+---------+---------+---------+---------+-------------|
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |         |         |         |         |---------|              |---------|         |         |         |         |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |------------+---------+---------+---------+---------+---------|         |              |         |---------+---------+---------+---------+---------+-------------|
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *     ------------+---------+---------+---------+---------+-------------------'               -------------------+---------+---------+---------+---------+-------------'
 *     |           |         |         |         |         |                                              |         |         |         |         |             |
 *     |           |         |         |         |         |                                              |         |         |         |         |             |
 *     |           |         |         |         |         |                                              |         |         |         |         |             |
 *      ---------------------------------------------------'                                               -----------------------------------------------------'
 *
 *
 *                                                ,-------------------.           ,--------------------.
 *                                                |         |         |           |         |          |
 *                                                |         |         |           |         |          |
 *                                                |         |         |           |         |          |
 *                                      ,---------|---------|---------|           |---------+----------+---------.
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |---------|           |---------|          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                       -----------------------------'            ------------------------------'
*/

  [4] = LAYOUT_ergodox_pretty( // mouse scrolling
    TO(0), 	           _______,        _______,         _______,         _______,        _______,        _______,                                        _______,        _______,        _______,        _______,        _______,        _______,        _______,
           _______,        _______,        _______,     KC_MS_WH_UP,         _______,        _______,        _______,                                        _______,        _______,        _______,        _______,        _______,        _______,        _______,
           _______,        _______,  KC_MS_WH_LEFT,   KC_MS_WH_DOWN,  KC_MS_WH_RIGHT,        _______,                                                                        _______,        _______,        _______,        _______,        _______,        _______,
           _______,        _______,        _______,         _______,         _______,        _______,        _______,                                        _______,        _______,        _______,        _______,        _______,        _______,        _______,
           _______,        _______,        _______,         _______,         _______,                                                                                                        _______,        _______,        _______,        _______,        _______,
                                                                                                                                /* thumbs */
                                                                                                           _______,        _______,        _______,        _______,
                                                                                                                           _______,        _______,
                                                                                           _______,        _______,        _______,        _______,        _______,        _______
  ),




/* ** Layer 5: Indesign */
// =============================================  LAYER 5 =======================   INDESIGN  ============
 /*
 *       TODO TODO TODO
 *
 *    ,-----------------------------------------------------------------------------------.               ,--------------------------------------------------------------------------------.
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |    TO(0)        |    1     |    2     |    3     |    4     |    5     |  RESET   |               |  TG(6)   |    6     |    7     |    8     |    9     |    0     |  Backspace   |
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |-----------------+----------+----------+----------+----------+----------+----------|               | ---------+----------+----------+----------+----------+----------+--------------|
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |  Tab            |    X     |    V     |    L     |    C     |    W     |  TG(3)   |               |  OSL(7)  |    K     |    H     |    G     |  f / C-f |    Q     |    ß         |
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |   (TD)   |          |              |
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |-----------------+----------+----------+----------+----------+----------|          |               |          | ---------+----------+----------+----------+----------+--------------|
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |  Ralt / L2      |   u / W- |  i / A-  |   a / S- |   e / C- |    O     | ---------|               | ---------|    S     |  N/Ctrl  |  R/Shft  |   T/Alt  |   D/Win  |   Y / L2     |
 *    |  (=Comp)        |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |-----------------+----------+----------+----------+----------+----------|  Undo    |               |  Save    | ---------+----------+----------+----------+----------+--------------|
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |  S-Enter        |  Ü / L1  |    Ö     |    Ä     |    P     |   Z / L4 |          |               |          |    B     |    M     |    ,     |    .     |     J    |  Ent / Shft  |
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    |                 |          |          |          |          |          |          |               |          |          |          |          |          |          |              |
 *    `-----------------+----------+----------+----------+----------+----------+----------'                `---------+----------+----------+----------+----------+----------+--------------'
 *           |          |          |          |          |          |                                                          |          |          |          |          |              |
 *           |          |  Ctrl    |  Win     |  Alt     |  Spc/L1  |                                                          |  Spc/L1  |  Alt     |  RAlt    |  Ctrl    |  TT(7)       |
 *           |          |          |          |          |          |                                                          |          |          |  (=Comp) |          |              |
 *           |          |          |          |          |          |                                                          |          |          |          |          |              |
 *           `------------------------------------------------------'                                                          `----------------------------------------------------------'
 *
 *
 *                                                                   ,---------------------.            ,----------------------.
 *                                                                   |          |          |            |          |           |
 *                                                                   |  S-F10   |   C-f    |            |  C-V-X-A |  M-Tab    |
 *                                                                   |          |          |            |          |           |
 *                                                        ,----------|----------| ---------|            | ---------+-----------+----------.
 *                                                        |          |          |          |            |          |           |          |
 *                                                        |          |          |   W+-Tab |            |  Ctl/Alt |           |          |
 *                                                        |          |          |          |            |          |           |          |
 *                                                        |  Shift   |  TT(5)   | ---------|            | ---------|  Mouse    |   Ctrl   |
 *                                                        |          |          |  Macro 1 |            |          |  Layer    |          |
 *                                                        |          |          |  Play    |            | M-Alt-Tab|           |          |
 *                                                        |          |          |          |            |          |           |          |
 *                                                        `--------------------------------'            `---------------------------------'
*/

/* LAYER 5: Indesign */
[5] = LAYOUT_ergodox_pretty // Indesgn layer
(
 TO(0)        ,  C(KC_1)          ,  C(KC_2)          ,  C(KC_3)     ,  C(KC_4)      ,  C(KC_5)      ,  A(C(KC_0))  ,        /* */       C(KC_0)        ,  C(KC_6)      ,  C(KC_7)     ,  C(KC_8)      ,  C(KC_9)     ,  C(KC_0)     ,  _______       ,
 _______      ,  _______          ,  S(KC_PGUP)       ,  KC_UP       ,  S(KC_PGDOWN) ,  C(KC_W)      ,  A(KC_PGUP)  ,        /* */       S(KC_PGUP)     ,  _______      ,  C(KC_KP_7)  ,  C(KC_KP_8)   ,  C(KC_KP_9)  ,  M_Id_Quer  ,  _______       ,
 _______      ,  C(S(KC_TAB))     ,  KC_LEFT          ,  KC_DOWN     ,  KC_RIGHT     ,  C(KC_TAB)    ,                       /* */                         C(KC_S)      ,  C(KC_KP_4)  ,  C(KC_KP_5)   ,  C(KC_KP_6)  ,  _______     ,  KC_MS_WH_UP   ,
 S(KC_ENTER)  ,  A(C(S(KC_LEFT))) ,  A(C(S(KC_RIGHT))),  C(S(KC_P))  ,  C(KC_P)      ,  C(S(KC_P))   ,  A(KC_PGDOWN),        /* */       S(KC_PGDOWN)   ,  _______      ,  C(KC_KP_1)  ,  C(KC_KP_2)   ,  C(KC_KP_3)  ,  C(KC_J)     ,  KC_MS_WH_DOWN ,
 _______      ,  _______          ,  _______          ,  _______     ,  _______      ,                                       /* */                                         _______     ,  _______      ,  _______     ,  _______     ,  _______       ,

 /* thumbs */
 /*                                                                     2     */               S(KC_PGUP)    , S(KC_PGDOWN)       ,               _______  ,  _______,
 /*                                                                     1     */                              C(S(KC_DOWN)) ,               _______  ,
 /*                                                                     3     */  ID_mark_par,  _______     , _______       ,               _______  ,  _______,    C(KC_KP_0)
 ),


/* ** Layer 6: MemoQ */
/*
 * Layer :
 *
 *
 *    ,------------------------------------------------------------------------.              ,-------------------------------------------------------------------------.
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |    TO(0)   |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |------------+---------+---------+---------+---------+-------------------|              |---------+---------+---------+---------+---------+---------+-------------|
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |         |   Up    |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |------------+---------+---------+---------+---------+---------|         |              |         |---------+---------+---------+---------+---------+-------------|
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |  C-Left |   Down  | C-Right |         |---------|              |---------|         |         |         |         |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |------------+---------+---------+---------+---------+---------|         |              |         |---------+---------+---------+---------+---------+-------------|
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |         |         | C-p     |         |         |              |         |         |         |         |         |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *     ------------+---------+---------+---------+---------+-------------------'               -------------------+---------+---------+---------+---------+-------------'
 *     |           |         |         |         |         |                                            |         |         |         |         |             |
 *     |           |         | C-Up    | C-Down  | C-Space |                                            |         |         |         |         |             |
 *     |           |         |         |         |         |                                            |         |         |         |         |             |
 *      ---------------------------------------------------'                                             -----------------------------------------------------'
 *
 *
 *                                                ,-------------------.           ,--------------------.
 *                                                |         |         |           |         |          |
 *                                                |         |         |           |         |          |
 *                                                |         |         |           |         |          |
 *                                      ,---------|---------|---------|           |---------+----------+---------.
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |---------|           |---------|          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                       -----------------------------'            ------------------------------'
*/

  /* LAYER 6: MemoQ */
  [6] = LAYOUT_ergodox_pretty( // MemoQ layer
    TO(0),                 _______,        _______,        _______,        _______,        _______,        _______,                                        _______,        _______,        _______,        _______,        _______,        _______,        _______,
           _______,        _______,        _______, KC_UP,                 _______,        _______,        _______,                                        _______,        _______, LCTL(KC_7),     LCTL(KC_8),     LCTL(KC_9),            _______, LCTL(KC_N),
           _______,        _______, LCTL(KC_LEFT),  KC_DOWN,        LCTL(KC_RIGHT),        _______,                                                                        _______, LCTL(KC_4),     LCTL(KC_5),     LCTL(KC_6),            _______, LCTL(LSFT(KC_ENTER)),
           _______,        _______,        _______,        _______, LCTL(KC_P),            _______,        _______,                                        _______,        _______, LCTL(KC_1),     LCTL(KC_2),     LCTL(KC_3),            _______, LCTL(KC_ENTER),
           _______,        _______, LCTL(KC_UP),    LCTL(KC_DOWN),  LCTL(KC_SPACE),                                                                                                 LCTL(KC_UP),    LCTL(KC_DOWN),  LCTL(KC_SPACE), KC_DOWN,        KC_UP,
                                                                                                           _______,        _______,        _______,        _______,
                                                                                                                           _______,        _______,
                                                                                           _______,        _______,        _______,        _______,        _______,        _______
  ),



/* ** Layer 7: misc 1 */
/*
 *    ,------------------------------------------------------------------------.              ,-------------------------------------------------------------------------.
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |  DynRec     |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |  Stop       |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |------------+---------+---------+---------+---------+-------------------|              |---------+---------+---------+---------+---------+---------+-------------|
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         | DynRec  |  DynRec     |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         | Rec 2   |  Play 2     |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |------------+---------+---------+---------+---------+---------|         |              |         |---------+---------+---------+---------+---------+-------------|
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         | DynRec  | DynRec      |
 *    |            |         |         |         |         |         |---------|              |---------|         |         |         |         | Rec 1   | Play        |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *    |------------+---------+---------+---------+---------+---------|         |              |         |---------+---------+---------+---------+---------+-------------|
 *    |            |         |         |         |         |         |         |              |         |         | VirDesk |         | VirDesk |         |             |
 *    |            |         |         |         |         |         |         |              |         |         | left    |   up    | right   |         |             |
 *    |            |         |         |         |         |         |         |              |         |         |         |         |         |         |             |
 *     ------------+---------+---------+---------+---------+-------------------'               -------------------+---------+---------+---------+---------+-------------'
 *     |           |         |         |         |         |                                              |         |         |         |         |             |
 *     |           |         |         |         |         |                                              |         |  left   |  down   |  right  |             |
 *     |           |         |         |         |         |                                              |         |         |         |         |             |
 *      ---------------------------------------------------'                                               -----------------------------------------------------'
 *
 *
 *                                                ,-------------------.           ,--------------------.
 *                                                |         |         |           |         |          |
 *                                                |         |         |           |         |          |
 *                                                |         |         |           |         |          |
 *                                      ,---------|---------|---------|           |---------+----------+---------.
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |---------|           |---------|          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                      |         |         |         |           |         |          |         |
 *                                       -----------------------------'            ------------------------------'
*/

  [7] = LAYOUT_ergodox_pretty( /* right hand movement, dynamic macros, system-wide shortcuts via ahk, and unicode - for now */
    TO(0),          _______,        _______,        _______,        _______,        _______,        _______,                                        _______,        _______,        _______,        _______,        _______,         _______,     DYN_REC_STOP,
    _______,     HYPR(KC_X),        _______,        _______,        _______,        _______,        _______,                                        _______,        _______,        _______,        _______,     HYPR(KC_F),  DYN_REC_START2,  DYN_MACRO_PLAY2,
    _______,        _______,        _______,     HYPR(KC_A),     HYPR(KC_E),        _______,                                                                  XP(BANG, SNEK),       _______,     HYPR(KC_R),     HYPR(KC_T),  DYN_REC_START1,  DYN_MACRO_PLAY1,
    _______,        _______,        _______,        _______,         DE_GRV,        DE_ACUT,        _______,                                        _______,        _______,     HYPR(KC_M),  G(C(KC_LEFT)),          KC_UP,  G(C(KC_RIGHT)),          _______,
    _______,        _______,        _______,        _______,        _______,                                                                                                        _______,        KC_LEFT,        KC_DOWN,        KC_RIGHT,          _______,
                                                                                                           _______,        _______,        _______,        _______,
                                                                                                                           _______,        _______,
                                                                                           _______,        _______,        _______,        _______,        _______,        _______
  ),
};




/* * RGB Stuff */

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
  [0] = { // base layer: mod keys
    // first the RIGHT hand, for whatever reason. going from inside towards outside
    {0,0,0},    {0,0,0},      {0,0,0},      {0,0,0},       {0,0,0},
    {0,0,0},    {0,0,0},      {0,0,0},      {0,0,0},       {0,0,0},
    {0,0,0},    {35,255,255}, {15,0,100},   {85,255,160},  {250,230,201},   // home-row mods
    {0,0,0},    {0,0,0},      {0,0,0},      {0,0,0},       {0,0,0},
    /*{ }*/     {15,0,150},   {85,255,158}, {169,200,243}, {35,255,255},    // red-orange, green, blue, yellow (slightly orange)

    // then the left hand, also going from inside out, so it's mirrored... what's on the left here is actually on the right
    {0,0,0},    {0,0,0},      {0,0,0},       {0,0,0},      {0,0,0},
    {0,0,0},    {0,0,0},      {0,0,0},       {0,0,0},      {0,0,0},
    {0,0,0},    {35,255,255}, {15,0,100},    {85,255,160}, {250,230,201},   // home-row mods
    {0,0,0},    {0,0,0},      {0,0,0},       {0,0,0},      {0,0,0},
    {15,0,150}, {85,255,158}, {250,230,201}, {35,255,255}  /*{ }*/          // red-orange, green, red, yellow (slightly orange)
  },

  [1] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {10,225,255}, {10,225,255}, {10,225,255}, {0,0,0}, {0,0,0}, {10,225,255}, {10,225,255}, {10,225,255}, {0,0,0}, {0,0,0}, {10,225,255}, {10,225,255}, {10,225,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {249,228,255}, {31,255,255}, {105,255,255}, {31,255,255}, {141,255,233}, {105,255,255}, {105,255,255}, {0,0,0}, {105,255,255}, {105,255,255}, {249,228,255}, {31,255,255}, {0,183,238}, {31,255,255}, {0,183,238}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

  [2] = { {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255} },

  [3] = { {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {134,255,213}, {134,255,213}, {40,129,243}, {40,129,243}, {40,129,243}, {105,255,255}, {105,255,255}, {105,255,255}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {134,255,213}, {105,255,255}, {134,255,213}, {40,129,243}, {40,129,243}, {105,255,255}, {105,255,255}, {105,255,255}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243}, {40,129,243} },

  [4] = { {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {105,255,255}, {42,128,249}, {42,128,249}, {42,128,249}, {105,255,255}, {105,255,255}, {105,255,255}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249}, {42,128,249} },

  [5] = { {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,183,238}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201}, {0,230,201} },

  [6] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {85,203,158}, {85,203,158}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (  // g_suspend_state ||       // commented out to avoid an error during linking I don't understand... this should work with ZSA's repo though
  // at some point I might look further into this... so:
  // the variable is set in led_matrix.c, rgb_matrix.c and rgb_matrix.h in ZSA's repo, but doesn't appear in regular qmk's codebase
  keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
    case 5:
      set_layer_color(5);
      break;
    case 6:
      set_layer_color(6);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}






/* * Custom code (function 'process_record_user' lives here) */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {


 /*   ** Macros: the definitions */

 // careful... we're inside process_record_user function here!


  case ID_mark_par:		// Indesign: mark the whole paragraph (including line break)
    if (record->event.pressed) {
      // move forward 1 char (to make sure we're inside the paragraph), move to beginning of paragraph, hold C and move to end of paragraph
      SEND_STRING(SS_TAP(X_RIGHT) SS_DELAY(100) SS_LCTL(SS_TAP(X_UP)) SS_DELAY(100) SS_LCTL(SS_LSFT(SS_TAP(X_DOWN))));
    }
    break;



  case M_Id_Quer:		// Indesign: Open quick access and type "Querver", wait for Indesign to complete, then hit Enter to open
    if (record->event.pressed) {
      SEND_STRING(SS_LCTL(SS_TAP(X_ENTER)) SS_DELAY(100) "Querverweis" SS_DELAY(1000) SS_TAP(X_ENTER));

    }
    break;



  case M_ALT_TAB:
    if (record->event.pressed) {
      if (!is_alt_tab_active) {
	is_alt_tab_active = true;
	register_code(KC_LALT);
      }
      alt_tab_timer = timer_read();
      register_code(KC_TAB);
    } else {
      unregister_code(KC_TAB);
    }
    break;


 /*  case Refocus:   // refocus windows if focus was lost by sending M-Tab twice
    if (record->event.pressed) {
      SEND_STRING(
		  SS_LALT(SS_TAP(X_TAB)) SS_DELAY(250) SS_LALT(SS_TAP(X_TAB)));
    }
    break; */


  /* case RGB_SLD:                // not sure what this one does, was included in my ORYX export
    if (record->event.pressed) {
      rgblight_mode(1);
    }
    return false; */







/*   ** Custom hold functions - kind of a dual role key without tap dance */

// careful - we're still inside the process_record_user function !


// following code comes from the section "Changing hold function" of the manual https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/mod_tap, plus my addings
// basic idea is a void Layer Toggle (to 0) which is intercepted and replaced by custom code
// this allows for easy doubling of the "normal" key


    // the case statements could also be written using the handles given as comments above each key
    // however, writing it like "LT(0,KC_ENTER)" etc. helps me remember how it works (roughly)


    //    x_CUT
  case LT(0,KC_X):
    if (record->tap.count && record->event.pressed) {
      return true;         // Return true for normal processing of tap keycode
      break;
    } else if (record->event.pressed) {
      tap_code16(C(KC_X)); // Intercept hold function to send Ctrl-X
      return false;
    }


    //    c_COPY
  case LT(0,KC_C):
    if (record->tap.count && record->event.pressed) {
      return true;         // Return true for normal processing of tap keycode
      break;
    } else if (record->event.pressed) {
      tap_code16(C(KC_C)); // Intercept hold function to send Ctrl-C
      return false;
    }


    //     v_PASTE
  case LT(0,KC_V):
    if (record->tap.count && record->event.pressed) {
      return true;         // Return true for normal processing of tap keycode
      break;
    } else if (record->event.pressed) {
      tap_code16(C(KC_V)); // Intercept hold function to send Ctrl-V
      return false;
    }


    //   m_MENU
  case LT(0,KC_M):         //sends m on tap and Shift+F10 (open context meu) --- this is my first own custom hold action :-)
			   // i might be using a handle "m_MENU" or similar in the keymap for this key
    if (record->tap.count && record->event.pressed) {
      return true;         // Return true for normal processing of tap keycode
      break;
    } else if (record->event.pressed) {
      register_code(KC_LSFT); tap_code16(KC_F10); unregister_code(KC_LSFT); // Intercept hold function to send Shift+F10
      return false;
    }


    // ent_KENT
  case LT(0,KC_ENTER):         // sends regular ENTER on tap and Numpad ENTER on hold (for use in Indesign)

    if (record->tap.count && record->event.pressed) {
      return true;         // Return true for normal processing of tap keycode
      break;
    } else if (record->event.pressed) {
      tap_code16(KC_KP_ENTER); // Intercept hold function to send numpad Enter
      return false;
    }



    // hyph_ENDASH
  case LT(0,DE_MINS):         // sends regular ENTER on tap and Numpad ENTER on hold (for use in Indesign)

    if (record->tap.count && record->event.pressed) {
      return true;         // Return true for normal processing of tap keycode
      break;
    } else if (record->event.pressed) {
      //tap_code16(KC_F24); tap_code16(DE_MINS); tap_code16(DE_MINS); tap_code16(KC_SPACE); tap_code16(KC_BSPACE); // Intercept hold function to send something that hopefully triggers WinCompose
      send_unicode_string("–");
      return false;
    }

    //   f_SEARCH
  case LT(0,KC_F):         //sends f on tap and Ctrl+f (search)
    if (record->tap.count && record->event.pressed) {
      return true;         // Return true for normal processing of tap keycode
      break;
    } else if (record->event.pressed) {
      register_code(KC_LCTL); tap_code16(KC_F); unregister_code(KC_LCTL); // Intercept hold function to send C-f
      return false;
    }



  }             // end of switch statement
  return true;  // process all other keys (all keys not handled by process_record_user) normally
}		// end of process_record_user function












/* * == Layer State LEDs == */
// this controls the three single color LEDs on the top of the right half
// disabling this saves about 200 bytes, so not much

layer_state_t layer_state_set_user(layer_state_t state) {

  uint8_t layer = biton32(state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case 1:
      ergodox_right_led_1_on();
      break;
    case 2:
      ergodox_right_led_2_on();
      break;
    case 3:
      ergodox_right_led_3_on();
      break;
    case 4:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      break;
    case 5:
      ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      break;
    case 6:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case 7:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    default:
      break;
  }
  return state;
};




/* * Tab Dance Part II */
// also based on QMK website (=> DangielGGordon)

/*   ** general explanation  */
/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */


/*   ** the engine - returns tap dance state (single tab/hold, double tab/hold, double single tab, triple tab/hold) */

uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return 8; // Magic number. At some point this method will expand to work for more presses
}


/*   ** CC_CV_CX_CA tap dance */

// Create an instance of 'tap' for the 'cvxa' tap dance.
static tap cvxa_state = {
    .is_press_action = true,
    .state = 0
};

void cvxa_finished(qk_tap_dance_state_t *state, void *user_data) {
  cvxa_state.state = cur_dance(state);
  switch (cvxa_state.state) {
  case SINGLE_TAP: register_code(KC_LCTL); tap_code(KC_C); break;
  case SINGLE_HOLD: register_code(KC_LCTL); tap_code(KC_V); break;
  case DOUBLE_TAP:  register_code(KC_LCTL); tap_code(KC_X); break;
  case DOUBLE_HOLD: register_code(KC_LCTL); tap_code(KC_A); break;
    // Last case is for fast typing. Assuming your key is `f`:
    // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  case DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X);
  }
}

// the whole thing could probably be written without a reset function... i guess
void cvxa_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (cvxa_state.state) {
  case SINGLE_TAP: unregister_code(KC_LCTL); break;
  case SINGLE_HOLD: unregister_code(KC_LCTL); break;
  case DOUBLE_TAP: unregister_code(KC_LCTL); break;
  case DOUBLE_HOLD: unregister_code(KC_LCTL); break;
  case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
  }
  cvxa_state.state = 0;
}



/*   ** ctl/alt tap dance */
// gives  _, CTL, _, ALT


static tap c_a_state = {
    .is_press_action = true,
    .state = 0
};

void c_a_finished(qk_tap_dance_state_t *state, void *user_data) {
  c_a_state.state = cur_dance(state);
  switch (c_a_state.state) {
  case SINGLE_TAP: set_oneshot_mods(MOD_BIT(KC_LCTL)); break;        // emulate OSM for Ctrl
  case SINGLE_HOLD: clear_oneshot_mods(); register_code(KC_LCTL); break;                // hold down Ctrl
  case DOUBLE_TAP: set_oneshot_mods(MOD_BIT(KC_LALT)); break;     // emulate OSM for Alt
  case DOUBLE_HOLD: clear_oneshot_mods(); register_code(KC_LALT); break;                // hold down Alt
    // Last case (below) is for fast typing. Will hardly apply here, so I make it do something else... soon(ish):
    // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  case DOUBLE_SINGLE_TAP: break;
    // to be expanded with Shift Added, or maybe Win+Tab (Overview) for triple tap...
  }
}

//
void c_a_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (c_a_state.state) {
  case SINGLE_TAP: break;             //  i just hope this doesn't break anything...
  case SINGLE_HOLD: clear_oneshot_mods(); unregister_code(KC_LCTL); break;   // have to clear the mods or it will break hold behaviour
  case DOUBLE_TAP: break;
  case DOUBLE_HOLD: clear_oneshot_mods(); unregister_code(KC_LALT); break;
  case DOUBLE_SINGLE_TAP: break;
  }
  c_a_state.state = 0;
}



/*   ** esc/W+Tab tap dance [ESC_WTAB]*/
// gives  esc, W+Tab (Overview), _, _,


static tap esc_ov_state = {
    .is_press_action = true,
    .state = 0
};

void esc_ov_finished(qk_tap_dance_state_t *state, void *user_data) {
  esc_ov_state.state = cur_dance(state);
  switch (esc_ov_state.state) {
  case SINGLE_TAP: tap_code(KC_ESC); break;                  // send ESC as normal
  case SINGLE_HOLD: register_code(KC_LGUI); tap_code(KC_TAB);; break;                // send Win+Tab to toggle Overview on Windows
  case DOUBLE_TAP: break;     // emulate OSM for Alt
  case DOUBLE_HOLD: break;                // hold down Alt
    // Last case (below) is for fast typing. Will hardly apply here, so I make it do something else... soon(ish):
    // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  case DOUBLE_SINGLE_TAP: break;
    // to be expanded with Shift Added, or maybe Win+Tab (Overview) for triple tap...
  }
}

//
void esc_ov_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (esc_ov_state.state) {
  case SINGLE_TAP: break;
  case SINGLE_HOLD: unregister_code(KC_LGUI); break;
  case DOUBLE_TAP: break;
  case DOUBLE_HOLD: break;
  case DOUBLE_SINGLE_TAP: break;
  }
  esc_ov_state.state = 0;
}



/*   ** list of tap dance actions */
qk_tap_dance_action_t tap_dance_actions[] = {
  [CVXA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cvxa_finished, cvxa_reset),         // 1st Arg: call on every tap, 2nd arg: call "with final tap count", 3rd arg: call "when tap dance action resets"
  [CTL_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, c_a_finished, c_a_reset),
  [ESC_WTAB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esc_ov_finished, esc_ov_reset),


};


