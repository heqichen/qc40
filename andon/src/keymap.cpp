#include "keymap.h"
#include "keycode.h"

uint32_t myLayout[][48] = {
	{H4K_LAYOUT(	//default layer 0
		KB_ESC_, KB_Q___, KB_W___, KB_E___, KB_R___, KB_T___, KB_Y___, KB_U___, KB_I___, KB_O___, KB_P___, KB_BKSP, KB_DEL_,
		KB_TAB_, KB_A___, KB_S___, KB_D___, KB_F___, KB_G___, KB_H___, KB_J___, KB_K___, KB_L___, KB_SEMI, KB_ENT_,
		KB_LSFT, KB_Z___, KB_X___, KB_C___, KB_V___, KB_B___, KB_N___, KB_M___, KB_COMA, KB_DOT_, KB_RSFT, LAYER_2,
		KB_LCTL, LAYER_1, KB_LALT, LAYER_3, KB_SP__, KB_RMET, KB_RALT, KB_0___, KB_RCTL,
		KB_0___, KB_D___)
	},
	{H4K_LAYOUT(	//Layer #1
		KB_GRAV, MS_WHUP, MS_MOVU, MS_WHDN, KB_____, KB_____, KB_____, KB_HOME, KB_END_, KB_PGUP, KB_PGDN, KB_MINU, KB_EQ__, 
		KB_____, MS_MOVL, MS_MOVD, MS_MOVR, KB_VODN, KB_VOUP, KB_LEFT, KB_DOWN, KB_UP__, KB_RIGH, KB_____, KB_____,
		KB_____, MS_LB__, MS_MB__, MS_RB__, KB_____, KB_____, KB_LBRA, KB_RBRA, KB_BKSP, KB_DEL_, KB_____, KB_____,
		KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____,
		KB_____, KB_____)
	},
	{H4K_LAYOUT(	//Layer #2
		KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, 
		KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____,
		KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_UP__, KB_____,
		KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_LEFT, KB_DOWN, KB_RIGH,
		KB_____, KB_____)
	},
	{H4K_LAYOUT(	//Layer #3
		KB_____, KB_F1__, KB_F2__, KB_F3__, KB_F4__, KB_F5__, KB_F6__, KB_F7__, KB_F8__, KB_F9__, KB_F10_, KB_F11_, KB_F12_,  
		KB_CAPS, KB_1___, KB_2___, KB_3___, KB_4___, KB_5___, KB_6___, KB_7___, KB_8___, KB_9___, KB_0___, KB_BKSL,
		KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_SL__, KB_QUOT, KB_____, KB_____,
		KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____, KB_____,
		KB_____, KB_____)
	},
};



