#ifndef __KEYCODE_H__
#define __KEYCODE_H__

#include "hid_keycode.h"

#define EVENT_VALUE_KEYCODE 0x00010000
#define EVENT_VALUE_KEYMOD	0x00020000
#define EVENT_VALUE_LAYER	0x00030000
#define EVENT_VALUE_MASK	0x00FF0000


#define LAYER_0 EVENT_VALUE_LAYER | 0x00
#define LAYER_1 EVENT_VALUE_LAYER | 0x01
#define LAYER_2 EVENT_VALUE_LAYER | 0x02
#define LAYER_3 EVENT_VALUE_LAYER | 0x03
#define LAYER_4 EVENT_VALUE_LAYER | 0x04
#define LAYER_5 EVENT_VALUE_LAYER | 0x05
#define LAYER_6 EVENT_VALUE_LAYER | 0x06
#define KB_TRAN ;//TODO



#define KB_LCTL	EVENT_VALUE_KEYMOD | KEYCODE_MOD_LCTRL
#define KB_LSFT	EVENT_VALUE_KEYMOD | KEYCODE_MOD_LSHIFT
#define KB_LALT	EVENT_VALUE_KEYMOD | KEYCODE_MOD_LALT
#define KB_LMET	EVENT_VALUE_KEYMOD | KEYCODE_MOD_LMETA
#define KB_RCTL	EVENT_VALUE_KEYMOD | KEYCODE_MOD_RCTRL
#define KB_RSFT	EVENT_VALUE_KEYMOD | KEYCODE_MOD_RSHIFT
#define KB_RALT	EVENT_VALUE_KEYMOD | KEYCODE_MOD_RALT
#define KB_RMET	EVENT_VALUE_KEYMOD | KEYCODE_MOD_RMETA

#define KB_A___ EVENT_VALUE_KEYCODE|KEYCODE_A
#define KB_B___ EVENT_VALUE_KEYCODE|KEYCODE_B
#define KB_C___ EVENT_VALUE_KEYCODE|KEYCODE_C
#define KB_D___ EVENT_VALUE_KEYCODE|KEYCODE_D
#define KB_E___ EVENT_VALUE_KEYCODE|KEYCODE_E
#define KB_F___ EVENT_VALUE_KEYCODE|KEYCODE_F
#define KB_G___ EVENT_VALUE_KEYCODE|KEYCODE_G
#define KB_H___ EVENT_VALUE_KEYCODE|KEYCODE_H
#define KB_I___ EVENT_VALUE_KEYCODE|KEYCODE_I
#define KB_J___ EVENT_VALUE_KEYCODE|KEYCODE_J
#define KB_K___ EVENT_VALUE_KEYCODE|KEYCODE_K
#define KB_L___ EVENT_VALUE_KEYCODE|KEYCODE_L
#define KB_M___ EVENT_VALUE_KEYCODE|KEYCODE_M
#define KB_N___ EVENT_VALUE_KEYCODE|KEYCODE_N
#define KB_O___ EVENT_VALUE_KEYCODE|KEYCODE_O
#define KB_P___ EVENT_VALUE_KEYCODE|KEYCODE_P
#define KB_Q___ EVENT_VALUE_KEYCODE|KEYCODE_Q
#define KB_R___ EVENT_VALUE_KEYCODE|KEYCODE_R
#define KB_S___ EVENT_VALUE_KEYCODE|KEYCODE_S
#define KB_T___ EVENT_VALUE_KEYCODE|KEYCODE_T
#define KB_U___ EVENT_VALUE_KEYCODE|KEYCODE_U
#define KB_V___ EVENT_VALUE_KEYCODE|KEYCODE_V
#define KB_W___ EVENT_VALUE_KEYCODE|KEYCODE_W
#define KB_X___ EVENT_VALUE_KEYCODE|KEYCODE_X
#define KB_Y___ EVENT_VALUE_KEYCODE|KEYCODE_Y
#define KB_Z___ EVENT_VALUE_KEYCODE|KEYCODE_Z

#define KB_1___ EVENT_VALUE_KEYCODE|KEYCODE_1
#define KB_2___ EVENT_VALUE_KEYCODE|KEYCODE_2
#define KB_3___ EVENT_VALUE_KEYCODE|KEYCODE_3
#define KB_4___ EVENT_VALUE_KEYCODE|KEYCODE_4
#define KB_5___ EVENT_VALUE_KEYCODE|KEYCODE_5
#define KB_6___ EVENT_VALUE_KEYCODE|KEYCODE_6
#define KB_7___ EVENT_VALUE_KEYCODE|KEYCODE_7
#define KB_8___ EVENT_VALUE_KEYCODE|KEYCODE_8
#define KB_9___ EVENT_VALUE_KEYCODE|KEYCODE_9
#define KB_0___ EVENT_VALUE_KEYCODE|KEYCODE_0

#define KB_F1__ EVENT_VALUE_KEYCODE|KEYCODE_F1
#define KB_F2__ EVENT_VALUE_KEYCODE|KEYCODE_F2
#define KB_F3__ EVENT_VALUE_KEYCODE|KEYCODE_F3
#define KB_F4__ EVENT_VALUE_KEYCODE|KEYCODE_F4
#define KB_F5__ EVENT_VALUE_KEYCODE|KEYCODE_F5
#define KB_F6__ EVENT_VALUE_KEYCODE|KEYCODE_F6
#define KB_F7__ EVENT_VALUE_KEYCODE|KEYCODE_F7
#define KB_F8__ EVENT_VALUE_KEYCODE|KEYCODE_F8
#define KB_F9__ EVENT_VALUE_KEYCODE|KEYCODE_F9
#define KB_F10_ EVENT_VALUE_KEYCODE|KEYCODE_F10
#define KB_F11_ EVENT_VALUE_KEYCODE|KEYCODE_F11
#define KB_F12_ EVENT_VALUE_KEYCODE|KEYCODE_F12


#define KB_ENT_	EVENT_VALUE_KEYCODE | KEYCODE_ENTER
#define KB_ESC_	EVENT_VALUE_KEYCODE | KEYCODE_ESC
#define KB_BKSP	EVENT_VALUE_KEYCODE | KEYCODE_BACKSPACE
#define KB_TAB_ EVENT_VALUE_KEYCODE | KEYCODE_TAB
#define KB_SP__	EVENT_VALUE_KEYCODE | KEYCODE_SPACE
#define KB_MINU	EVENT_VALUE_KEYCODE | KEYCODE_MINUS
#define KB_EQ__	EVENT_VALUE_KEYCODE | KEYCODE_EQUAL
#define KB_LBRA	EVENT_VALUE_KEYCODE | KEYCODE_LEFTBRACE
#define KB_RBRA	EVENT_VALUE_KEYCODE | KEYCODE_RIGHTBRACE
#define KB_BKSL	EVENT_VALUE_KEYCODE | KEYCODE_BACKSLASH
#define KB_HASH	EVENT_VALUE_KEYCODE | KEYCODE_HASHTILDE
#define KB_SEMI	EVENT_VALUE_KEYCODE | KEYCODE_SEMICOLON
#define KB_QUOT	EVENT_VALUE_KEYCODE | KEYCODE_APOSTROPHE
#define KB_GRAV	EVENT_VALUE_KEYCODE | KEYCODE_GRAVE
#define KB_COMA	EVENT_VALUE_KEYCODE | KEYCODE_COMMA
#define KB_DOT_	EVENT_VALUE_KEYCODE | KEYCODE_DOT
#define KB_SL__	EVENT_VALUE_KEYCODE | KEYCODE_SLASH
#define KB_CAPS	EVENT_VALUE_KEYCODE | KEYCODE_CAPSLOCK

#define KB_PTSC	 EVENT_VALUE_KEYCODE | KEYCODE_PRINTSCREEN
#define KB_SCRL	 EVENT_VALUE_KEYCODE | KEYCODE_SCROLLLOCK
#define KB_PAUS	 EVENT_VALUE_KEYCODE | KEYCODE_PAUSE
#define KB_INS_	 EVENT_VALUE_KEYCODE | KEYCODE_INSERT
#define KB_HOME	 EVENT_VALUE_KEYCODE | KEYCODE_HOME
#define KB_PGUP	 EVENT_VALUE_KEYCODE | KEYCODE_PAGEUP
#define KB_DEL_	 EVENT_VALUE_KEYCODE | KEYCODE_DELETE
#define KB_END_	 EVENT_VALUE_KEYCODE | KEYCODE_END
#define KB_PGDW	 EVENT_VALUE_KEYCODE | KEYCODE_PAGEDOWN
#define KB_RIGH	 EVENT_VALUE_KEYCODE | KEYCODE_RIGHT
#define KB_LEFT	 EVENT_VALUE_KEYCODE | KEYCODE_LEFT
#define KB_DOWN	 EVENT_VALUE_KEYCODE | KEYCODE_DOWN
#define KB_UP__	 EVENT_VALUE_KEYCODE | KEYCODE_UP

#endif

