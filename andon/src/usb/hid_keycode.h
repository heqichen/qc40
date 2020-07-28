#ifndef __HID_KEYCODE_H__
#define __HID_KEYCODE_H__


#define KEYCODE_MOD_LCTRL  0x01
#define KEYCODE_MOD_LSHIFT 0x02
#define KEYCODE_MOD_LALT   0x04
#define KEYCODE_MOD_LMETA  0x08
#define KEYCODE_MOD_RCTRL  0x10
#define KEYCODE_MOD_RSHIFT 0x20
#define KEYCODE_MOD_RALT   0x40
#define KEYCODE_MOD_RMETA  0x80


#define KEYCODE_NONE 0x00 // No key pressed
#define KEYCODE_ERR_OVF 0x01 //  Keyboard Error Roll Over - used for all slots if too many keys are pressed ("Phantom key")
#define KEYCODE_POST_FAIL	0x02 // Keyboard POST Fail
#define KEYCODE_ERROR	0x03 // Keyboard Error Undefined
#define KEYCODE_A 0x04 // Keyboard a and A
#define KEYCODE_B 0x05 // Keyboard b and B
#define KEYCODE_C 0x06 // Keyboard c and C
#define KEYCODE_D 0x07 // Keyboard d and D
#define KEYCODE_E 0x08 // Keyboard e and E
#define KEYCODE_F 0x09 // Keyboard f and F
#define KEYCODE_G 0x0a // Keyboard g and G
#define KEYCODE_H 0x0b // Keyboard h and H
#define KEYCODE_I 0x0c // Keyboard i and I
#define KEYCODE_J 0x0d // Keyboard j and J
#define KEYCODE_K 0x0e // Keyboard k and K
#define KEYCODE_L 0x0f // Keyboard l and L
#define KEYCODE_M 0x10 // Keyboard m and M
#define KEYCODE_N 0x11 // Keyboard n and N
#define KEYCODE_O 0x12 // Keyboard o and O
#define KEYCODE_P 0x13 // Keyboard p and P
#define KEYCODE_Q 0x14 // Keyboard q and Q
#define KEYCODE_R 0x15 // Keyboard r and R
#define KEYCODE_S 0x16 // Keyboard s and S
#define KEYCODE_T 0x17 // Keyboard t and T
#define KEYCODE_U 0x18 // Keyboard u and U
#define KEYCODE_V 0x19 // Keyboard v and V
#define KEYCODE_W 0x1a // Keyboard w and W
#define KEYCODE_X 0x1b // Keyboard x and X
#define KEYCODE_Y 0x1c // Keyboard y and Y
#define KEYCODE_Z 0x1d // Keyboard z and Z

#define KEYCODE_1 0x1e // Keyboard 1 and !
#define KEYCODE_2 0x1f // Keyboard 2 and @
#define KEYCODE_3 0x20 // Keyboard 3 and #
#define KEYCODE_4 0x21 // Keyboard 4 and $
#define KEYCODE_5 0x22 // Keyboard 5 and %
#define KEYCODE_6 0x23 // Keyboard 6 and ^
#define KEYCODE_7 0x24 // Keyboard 7 and &
#define KEYCODE_8 0x25 // Keyboard 8 and *
#define KEYCODE_9 0x26 // Keyboard 9 and (
#define KEYCODE_0 0x27 // Keyboard 0 and )

#define KEYCODE_ENTER 0x28 // Keyboard Return (ENTER)
#define KEYCODE_ESC 0x29 // Keyboard ESCAPE
#define KEYCODE_BACKSPACE 0x2a // Keyboard DELETE (Backspace)
#define KEYCODE_TAB 0x2b // Keyboard Tab
#define KEYCODE_SPACE 0x2c // Keyboard Spacebar
#define KEYCODE_MINUS 0x2d // Keyboard - and _
#define KEYCODE_EQUAL 0x2e // Keyboard = and +
#define KEYCODE_LEFTBRACE 0x2f // Keyboard [ and {
#define KEYCODE_RIGHTBRACE 0x30 // Keyboard ] and }
#define KEYCODE_BACKSLASH 0x31 // Keyboard \ and |
#define KEYCODE_HASHTILDE 0x32 // Keyboard Non-US # and ~
#define KEYCODE_SEMICOLON 0x33 // Keyboard ; and :
#define KEYCODE_APOSTROPHE 0x34 // Keyboard ' and "
#define KEYCODE_GRAVE 0x35 // Keyboard ` and ~
#define KEYCODE_COMMA 0x36 // Keyboard , and <
#define KEYCODE_DOT 0x37 // Keyboard . and >
#define KEYCODE_SLASH 0x38 // Keyboard / and ?
#define KEYCODE_CAPSLOCK 0x39 // Keyboard Caps Lock

#define KEYCODE_F1 0x3a // Keyboard F1
#define KEYCODE_F2 0x3b // Keyboard F2
#define KEYCODE_F3 0x3c // Keyboard F3
#define KEYCODE_F4 0x3d // Keyboard F4
#define KEYCODE_F5 0x3e // Keyboard F5
#define KEYCODE_F6 0x3f // Keyboard F6
#define KEYCODE_F7 0x40 // Keyboard F7
#define KEYCODE_F8 0x41 // Keyboard F8
#define KEYCODE_F9 0x42 // Keyboard F9
#define KEYCODE_F10 0x43 // Keyboard F10
#define KEYCODE_F11 0x44 // Keyboard F11
#define KEYCODE_F12 0x45 // Keyboard F12

#define KEYCODE_PRINTSCREEN 0x46 // Keyboard Print Screen
#define KEYCODE_SCROLLLOCK 0x47 // Keyboard Scroll Lock
#define KEYCODE_PAUSE 0x48 // Keyboard Pause
#define KEYCODE_INSERT 0x49 // Keyboard Insert
#define KEYCODE_HOME 0x4a // Keyboard Home
#define KEYCODE_PAGEUP 0x4b // Keyboard Page Up
#define KEYCODE_DELETE 0x4c // Keyboard Delete Forward
#define KEYCODE_END 0x4d // Keyboard End
#define KEYCODE_PAGEDOWN 0x4e // Keyboard Page Down
#define KEYCODE_RIGHT 0x4f // Keyboard Right Arrow
#define KEYCODE_LEFT 0x50 // Keyboard Left Arrow
#define KEYCODE_DOWN 0x51 // Keyboard Down Arrow
#define KEYCODE_UP 0x52 // Keyboard Up Arrow

#define KEYCODE_PAD_NUMLOCK 0x53 // Keyboard Num Lock and Clear
#define KEYCODE_PAD_SLASH 0x54 // Keypad /
#define KEYCODE_PAD_ASTERISK 0x55 // Keypad *
#define KEYCODE_PAD_MINUS 0x56 // Keypad -
#define KEYCODE_PAD_PLUS 0x57 // Keypad +
#define KEYCODE_PAD_ENTER 0x58 // Keypad ENTER
#define KEYCODE_PAD_1 0x59 // Keypad 1 and End
#define KEYCODE_PAD_2 0x5a // Keypad 2 and Down Arrow
#define KEYCODE_PAD_3 0x5b // Keypad 3 and PageDn
#define KEYCODE_PAD_4 0x5c // Keypad 4 and Left Arrow
#define KEYCODE_PAD_5 0x5d // Keypad 5
#define KEYCODE_PAD_6 0x5e // Keypad 6 and Right Arrow
#define KEYCODE_PAD_7 0x5f // Keypad 7 and Home
#define KEYCODE_PAD_8 0x60 // Keypad 8 and Up Arrow
#define KEYCODE_PAD_9 0x61 // Keypad 9 and Page Up
#define KEYCODE_PAD_0 0x62 // Keypad 0 and Insert
#define KEYCODE_PAD_DOT 0x63 // Keypad . and Delete

#define KEYCODE_102ND 0x64 // Keyboard Non-US \ and |
#define KEYCODE_APPLICATION 0x65 // Keyboard Application
#define KEYCODE_POWER 0x66 // Keyboard Power
#define KEYCODE_PAD_EQUAL 0x67 // Keypad =

#define KEYCODE_F13 0x68 // Keyboard F13
#define KEYCODE_F14 0x69 // Keyboard F14
#define KEYCODE_F15 0x6a // Keyboard F15
#define KEYCODE_F16 0x6b // Keyboard F16
#define KEYCODE_F17 0x6c // Keyboard F17
#define KEYCODE_F18 0x6d // Keyboard F18
#define KEYCODE_F19 0x6e // Keyboard F19
#define KEYCODE_F20 0x6f // Keyboard F20
#define KEYCODE_F21 0x70 // Keyboard F21
#define KEYCODE_F22 0x71 // Keyboard F22
#define KEYCODE_F23 0x72 // Keyboard F23
#define KEYCODE_F24 0x73 // Keyboard F24

#define KEYCODE_EXECUTE 0x74 // Keyboard Execute
#define KEYCODE_HELP 0x75 // Keyboard Help
#define KEYCODE_PROPS 0x76 // Keyboard Menu
#define KEYCODE_FRONT 0x77 // Keyboard Select
#define KEYCODE_STOP 0x78 // Keyboard Stop
#define KEYCODE_AGAIN 0x79 // Keyboard Again
#define KEYCODE_UNDO 0x7a // Keyboard Undo
#define KEYCODE_CUT 0x7b // Keyboard Cut
#define KEYCODE_COPY 0x7c // Keyboard Copy
#define KEYCODE_PASTE 0x7d // Keyboard Paste
#define KEYCODE_FIND 0x7e // Keyboard Find
#define KEYCODE_MUTE 0x7f // Keyboard Mute
#define KEYCODE_VOLUMEUP 0x80 // Keyboard Volume Up
#define KEYCODE_VOLUMEDOWN 0x81 // Keyboard Volume Down
#define KEYCODE_LOCKING_CAPSLOCK	0x82 //  Keyboard Locking Caps Lock
#define KEYCODE_LOCKING_NUMLOCK		0x83 //  Keyboard Locking Num Lock
#define KEYCODE_LOCKING_SCROLLLOCK	0x84 //  Keyboard Locking Scroll Lock
#define KEYCODE_PAD_KPCOMMA 0x85 // Keypad Comma
#define KEYCODE_PAD_EQUAL_AS400	0x86 //  Keypad Equal Sign
#define KEYCODE_RO 0x87 // Keyboard International1
#define KEYCODE_KATAKANAHIRAGANA 0x88 // Keyboard International2
#define KEYCODE_YEN 0x89 // Keyboard International3
#define KEYCODE_HENKAN 0x8a // Keyboard International4
#define KEYCODE_MUHENKAN 0x8b // Keyboard International5
#define KEYCODE_KPJPCOMMA 0x8c // Keyboard International6
#define KEYCODE_INTERNATIONAL7	0x8d //  Keyboard International7
#define KEYCODE_INTERNATIONAL8	0x8e //  Keyboard International8
#define KEYCODE_INTERNATIONAL9	0x8f //  Keyboard International9
#define KEYCODE_HANGEUL 0x90 // Keyboard LANG1
#define KEYCODE_HANJA 0x91 // Keyboard LANG2
#define KEYCODE_KATAKANA 0x92 // Keyboard LANG3
#define KEYCODE_HIRAGANA 0x93 // Keyboard LANG4
#define KEYCODE_ZENKAKUHANKAKU 0x94 // Keyboard LANG5
#define KEYCODE_LANG6		0x95 //  Keyboard LANG6
#define KEYCODE_LANG7		0x96 //  Keyboard LANG7
#define KEYCODE_LANG8		0x97 //  Keyboard LANG8
#define KEYCODE_LANG9		0x98 //  Keyboard LANG9
#define KEYCODE_ERASE		0x99 //  Keyboard Alternate Erase
#define KEYCODE_SYSREQ		0x9a //  Keyboard SysReq/Attention
#define KEYCODE_CANCEL		0x9b //  Keyboard Cancel
#define KEYCODE_CLEAR		0x9c //  Keyboard Clear
#define KEYCODE_PRIOR		0x9d //  Keyboard Prior
#define KEYCODE_RETURN		0x9e //  Keyboard Return
#define KEYCODE_SEPARATOR	0x9f //  Keyboard Separator
#define KEYCODE_OUT			0xa0 //  Keyboard Out
#define KEYCODE_OPER 		0xa1 //  Keyboard Oper
#define KEYCODE_CLEARAGAIN		0xa2 //  Keyboard Clear/Again
#define KEYCODE_CRSEL		0xa3 //  Keyboard CrSel/Props
#define KEYCODE_EXSEL		0xa4 //  Keyboard ExSel

#define KEYCODE_PAD_00		0xb0 //  Keypad 00
#define KEYCODE_PAD_000		0xb1 //  Keypad 000
#define KEYCODE_THOUSAND_SEP	0xb2 //  Thousands Separator
#define KEYCODE_DECIMAL_SEP	0xb3 //  Decimal Separator
#define KEYCODE_CURRENCY_UNIT	0xb4 //  Currency Unit
#define KEYCODE_SUB_UNIT 	0xb5 //  Currency Sub-unit
#define KEYCODE_PAD_KPLEFTPAREN 0xb6 // Keypad (
#define KEYCODE_PAD_KPRIGHTPAREN 0xb7 // Keypad )
#define KEYCODE_PAD_LEFTBRACE	0xb8 //  Keypad {
#define KEYCODE_PAD_RIGHTBRACE	0xb9 //  Keypad }
#define KEYCODE_PAD_TAB 			0xba //  Keypad Tab
#define KEYCODE_PAD_BACKSPACE	0xbb //  Keypad Backspace
#define KEYCODE_PAD_A 			0xbc //  Keypad A
#define KEYCODE_PAD_B 			0xbd //  Keypad B
#define KEYCODE_PAD_C 			0xbe //  Keypad C
#define KEYCODE_PAD_D 			0xbf //  Keypad D
#define KEYCODE_PAD_E 			0xc0 //  Keypad E
#define KEYCODE_PAD_F 			0xc1 //  Keypad F
#define KEYCODE_PAD_XOR 			0xc2 //  Keypad XOR
#define KEYCODE_PAD_CARET		0xc3 //  Keypad ^
#define KEYCODE_PAD_PERCENT		0xc4 //  Keypad %
#define KEYCODE_PAD_LEFTANGLEBRACE 			0xc5 //  Keypad <
#define KEYCODE_PAD_RIGHTANGLEBRACE 			0xc6 //  Keypad >
#define KEYCODE_PAD_AND 			0xc7 //  Keypad &
#define KEYCODE_PAD_ANDAND		0xc8 //  Keypad &&
#define KEYCODE_PAD_OR 			0xc9 //  Keypad |
#define KEYCODE_PAD_OROR			0xca //  Keypad ||
#define KEYCODE_PAD_COLON		0xcb //  Keypad :
#define KEYCODE_PAD_HASH			0xcc //  Keypad #
#define KEYCODE_PAD_SPACE		0xcd //  Keypad Space
#define KEYCODE_PAD_AT 			0xce //  Keypad @
#define KEYCODE_PAD_EXCLAMATION  0xCF     // Keypad !
#define KEYCODE_PAD_MEM_STORE    0xD0     // Keypad Memory Store
#define KEYCODE_PAD_MEM_RECALL   0xD1     // Keypad Memory Recall
#define KEYCODE_PAD_MEM_CLEAR    0xD2     // Keypad Memory Clear
#define KEYCODE_PAD_MEM_ADD      0xD3     // Keypad Memory Add
#define KEYCODE_PAD_MEM_SUB      0xD4     // Keypad Memory Subtract
#define KEYCODE_PAD_MEM_MULTIPLY 0xD5     // Keypad Memory Multiply
#define KEYCODE_PAD_MEM_DIVIDE   0xD6     // Keypad Memory Divide
#define KEYCODE_PAD_PLUS_MINUS   0xD7     // Keypad +/-
#define KEYCODE_PAD_CLEAR             0xD8     // Keypad Clear
#define KEYCODE_PAD_CLEAR_ENTRY       0xD9     // Keypad Clear Entry
#define KEYCODE_PAD_BINARY            0xDA     // Keypad Binary
#define KEYCODE_PAD_OCTAL             0xDB     // Keypad Octal
#define KEYCODE_PAD_DECIMAL           0xDC     // Keypad Decimal
#define KEYCODE_PAD_HEXADECIMAL       0xDD     // Keypad Hexadecimal

#define KEYCODE_LEFTCTRL 0xe0 // Keyboard Left Control
#define KEYCODE_LEFTSHIFT 0xe1 // Keyboard Left Shift
#define KEYCODE_LEFTALT 0xe2 // Keyboard Left Alt
#define KEYCODE_LEFTMETA 0xe3 // Keyboard Left GUI
#define KEYCODE_RIGHTCTRL 0xe4 // Keyboard Right Control
#define KEYCODE_RIGHTSHIFT 0xe5 // Keyboard Right Shift
#define KEYCODE_RIGHTALT 0xe6 // Keyboard Right Alt
#define KEYCODE_RIGHTMETA 0xe7 // Keyboard Right GUI

#define KEYCODE_MEDIA_PLAYPAUSE 0xe8
#define KEYCODE_MEDIA_STOPCD 0xe9
#define KEYCODE_MEDIA_PREVIOUSSONG 0xea
#define KEYCODE_MEDIA_NEXTSONG 0xeb
#define KEYCODE_MEDIA_EJECTCD 0xec
#define KEYCODE_MEDIA_VOLUMEUP 0xed
#define KEYCODE_MEDIA_VOLUMEDOWN 0xee
#define KEYCODE_MEDIA_MUTE 0xef
#define KEYCODE_MEDIA_WWW 0xf0
#define KEYCODE_MEDIA_BACK 0xf1
#define KEYCODE_MEDIA_FORWARD 0xf2
#define KEYCODE_MEDIA_STOP 0xf3
#define KEYCODE_MEDIA_FIND 0xf4
#define KEYCODE_MEDIA_SCROLLUP 0xf5
#define KEYCODE_MEDIA_SCROLLDOWN 0xf6
#define KEYCODE_MEDIA_EDIT 0xf7
#define KEYCODE_MEDIA_SLEEP 0xf8
#define KEYCODE_MEDIA_COFFEE 0xf9
#define KEYCODE_MEDIA_REFRESH 0xfa
#define KEYCODE_MEDIA_CALC 0xfb

#endif

