/*
 * keyboard.c
 *
 *  Created on: Apr 18, 2020
 *      Author: stor
 */

#include "keyboard.h"

uint8_t isSpecialKey[KB_COLUMN * KB_ROW] = {
    [lShift] = 1,
    [lCtrl] = 1,
    [lAlt] = 1,
    [rShift] = 1,
    [rCtrl] = 1,
    [rAlt] = 1,
    [rWin] = 1,
    [lCorner] = 1,
    [lFn] = 1,
    [rFn] = 1
};


uint8_t keyUID0[KB_COLUMN * KB_ROW] = {
[keyA] =	UID_A	    	,
[keyB] =	UID_B	    	,
[keyC] =	UID_C	    	,
[keyD] =	UID_D	    	,
[keyE] =	UID_E	    	,
[keyF] =	UID_F	    	,
[keyG] =	UID_G	    	,
[keyH] =	UID_H	    	,
[keyI] =	UID_I	    	,
[keyJ] =	UID_J	    	,
[keyK] =	UID_K	    	,
[keyL] =	UID_L	    	,
[keyM] =	UID_M	    	,
[keyN] =	UID_N	    	,
[keyO] =	UID_O	    	,
[keyP] =	UID_P	    	,
[keyQ] =	UID_Q	    	,
[keyR] =	UID_R	    	,
[keyS] =	UID_S	    	,
[keyT] =	UID_T	    	,
[keyU] =	UID_U	    	,
[keyV] =	UID_V	    	,
[keyW] =	UID_W	    	,
[keyX] =	UID_X	    	,
[keyY] =	UID_Y	    	,
[keyZ] =	UID_Z	    	,
[num1] =	UID_num1    	,
[num2] =	UID_num2    	,
[num3] =	UID_num3    	,
[num4] =	UID_num4    	,
[num5] =	UID_num5    	,
[num6] =	UID_num6    	,
[num7] =	UID_num7    	,
[num8] =	UID_num8    	,
[num9] =	UID_num9    	,
[num0] =	UID_num0    	,
[KeyEnter] =	UID_enter	,
[esc] =	        UID_esc		,
[backspace] =	UID_backspace	,
[tab] =	        UID_tab		,
[space] =	UID_space	,
[charMin] =	UID_minus	,
[charPlus] =	UID_equal	,
[LeftMBrace] =	UID_lMBrace	,
[rightMBrace] =	UID_rMBrace	,
[keyOr] =	UID_or		,
[keyColon] =	UID_colon	,
[keyQuot] =	UID_quota	,
[keyComma] =	UID_comma	,
[keyPoint] =	UID_point	,
[keyQues] =     UID_question	,
};

uint8_t keyUID1[KB_COLUMN * KB_ROW] = {
[keyA] =	UID_A	    	,
[keyB] =	UID_B	    	,
[keyC] =	UID_C	    	,
[keyD] =	UID_D	    	,
[keyE] =	UID_E	    	,
[keyF] =	UID_F	    	,
[keyG] =	UID_G	    	,
[keyH] =	UID_H	    	,
[keyI] =	UID_printScreen	,
[keyJ] =	UID_J	    	,
[keyK] =	UID_home    	,
[keyL] =	UID_pageUp    	,
[keyM] =	UID_M	    	,
[keyN] =	UID_N	    	,
[keyO] =	UID_scrollLock	,
[keyP] =	UID_pause    	,
[keyQ] =	UID_Q	    	,
[keyR] =	UID_R	    	,
[keyS] =	UID_S	    	,
[keyT] =	UID_T	    	,
[keyU] =	UID_U	    	,
[keyV] =	UID_V	    	,
[keyW] =	UID_W	    	,
[keyX] =	UID_X	    	,
[keyY] =	UID_Y	    	,
[keyZ] =	UID_Z	    	,
[num1] =	UID_f1    	,
[num2] =	UID_f2    	,
[num3] =	UID_f3    	,
[num4] =	UID_f4    	,
[num5] =	UID_f5    	,
[num6] =	UID_f6    	,
[num7] =	UID_f7    	,
[num8] =	UID_f8    	,
[num9] =	UID_f9    	,
[num0] =	UID_f10    	,
[KeyEnter] =	UID_enter	,
[esc] =	        UID_esc		,
[backspace] =	UID_delete	,
[tab] =	        UID_cap	,
[space] =	UID_space	,
[charMin] =	UID_f11	,
[charPlus] =	UID_f12	,
[LeftMBrace] =	UID_up		,
[rightMBrace] =	UID_rMBrace	,
[keyOr] =	UID_tilde	,
[keyColon] =	UID_left	,
[keyQuot] =	UID_right	,
[keyComma] =	UID_end		,
[keyPoint] =	UID_pageDown	,
[keyQues] =     UID_down	,
};

uint8_t * keyUID[KB_LEVEL] = {
		keyUID0,
		keyUID1
};

void InitRow()
{
	HAL_GPIO_WritePin(ROW_PORT, ROW_PIN, GPIO_PIN_SET);
}

void CheckRow(uint8_t row)
{
	HAL_GPIO_WritePin(ROW_PORT, ROW(row), GPIO_PIN_RESET);
}

uint8_t CheckColumn()
{
	uint8_t column =  (COLUMN_PORT->IDR & COLUMN_PIN ) >> COLUMN_OFFSET;
	return column;
}

bool IsSpecialKey(uint8_t keyId)
{
	return isSpecialKey[keyId];
}

void BackupLastKeyList(KeyState * keystate)
{
	for (int i=0; i<keystate->keycnt; i++){
		keystate->keylastlist[i] = keystate->keylist[i];
		keystate->keylastlevel[i] = keystate->keylevel[i];
	}
	keystate->keylastcnt = keystate->keycnt;
}

int lastPress(KeyState * keystate, uint8_t keyId)
{
	for (int i=0; i<keystate->keylastcnt; i++){
		if (keystate->keylastlist[i] == keyId){
			return i;
		}
	}
	return -1;
}

void UpdateKeyLevel(KeyState * keystate)
{
	uint8_t * m = keystate->matrix;
	uint8_t curlevel = m[lFn] | m[rFn]| m[lCorner];
	for (int i=0; i<keystate->keycnt; i++){
		if (keystate->keylevel[i] == KEY_LEVEL_INVAILD){
			keystate->keylevel[i] = curlevel;
		}
	}
}

void UpdateKeyState(int row, int col, int stat, KeyState * keystate)
{
	uint8_t keyId = row * KB_COLUMN + col;
	keystate->matrix[keyId] = (stat == STATE_PRESS);
	int lastIdx = lastPress(keystate,keyId);
	if (stat == STATE_PRESS){
		if (IsSpecialKey(keyId)) {
			return ;
		} else if (lastIdx != -1){
			keystate->keylist[keystate->keycnt] = keyId;
			keystate->keylevel[keystate->keycnt] = keystate->keylastlevel[lastIdx];
			keystate->keycnt ++;
		} else if (keystate->keycnt == KEYS_PRESS_MAX) {
			keystate->vaild = false;
		} else {
			keystate->keylist[keystate->keycnt] = keyId;
			keystate->keylevel[keystate->keycnt] = KEY_LEVEL_INVAILD;
			keystate->keycnt ++;
		}
	}
}

void ScanKeyState(KeyState * keystate)
{
	int i,j;
	uint8_t stat;
	uint8_t column;
	keystate->keycnt = 0;
	keystate->vaild = true;
	for (i=0; i<KB_COLUMN; i++){
		InitRow();
		CheckRow(i);
		HAL_Delay(1); // to wait io stable
		column = CheckColumn();
		for(j=0; j<KB_COLUMN; j++){
			stat =  column & 1;
			column >>= 1;
			UpdateKeyState(i, j, stat, keystate);
		}
	}
	UpdateKeyLevel(keystate);
	BackupLastKeyList(keystate);
}

uint8_t KeyIdToUID(uint8_t keyId, uint8_t level)
{
	return keyUID[level][keyId];
}

/*
Report Format:
0____________1___________2____________________________________7___________
special key |     0     |   key0  	| key1      | ......     | key5      |

Special Key:
 rWin rAlt rShift rCtrl lWin lAlt lShift lCtrl
*/
void GenReport(KeyState * keystate, uint8_t * reportBuf)
{
	int i;
	uint8_t * m = keystate->matrix;
	uint8_t specialKey = 	m[lCtrl]  << 0 |
							m[lShift] << 1 |
							m[lAlt]   << 2 |
							0         << 3 |
							m[rCtrl]  << 4 |
							m[rShift] << 5 |
							m[rAlt]   << 6 |
							m[rWin]   << 7;
	reportBuf[0] = specialKey;
	reportBuf[1] = 0;
	reportBuf[2] = 0;
	reportBuf[3] = 0;
	reportBuf[4] = 0;
	reportBuf[5] = 0;
	reportBuf[6] = 0;
	reportBuf[7] = 0;
	for (i=0; i<keystate->keycnt; i++){
		if (keystate->vaild){
			reportBuf[i+2] = KeyIdToUID(keystate->keylist[i], keystate->keylevel[i]);
		} else {
			reportBuf[i+2] = 0xff;
		}
	}
}

