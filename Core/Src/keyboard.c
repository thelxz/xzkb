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
    [lFn] = 1,
    [rFn] = 1
};


uint8_t keyUID0[KB_COLUMN * KB_ROW] = {
[keyA] =	    4,
[keyB] =	    5,
[keyC] =	    6,
[keyD] =	    7,
[keyE] =	    8,
[keyF] =	    9,
[keyG] =	    10,
[keyH] =	    11,
[keyI] =	    12,
[keyJ] =	    13,
[keyK] =	    14,
[keyL] =	    15,
[keyM] =	    16,
[keyN] =	    17,
[keyO] =	    18,
[keyP] =	    19,
[keyQ] =	    20,
[keyR] =	    21,
[keyS] =	    22,
[keyT] =	    23,
[keyU] =	    24,
[keyV] =	    25,
[keyW] =	    26,
[keyX] =	    27,
[keyY] =	    28,
[keyZ] =	    29,
[num1] =	    30,
[num2] =	    31,
[num3] =	    32,
[num4] =	    33,
[num5] =	    34,
[num6] =	    35,
[num7] =	    36,
[num8] =	    37,
[num9] =	    38,
[num0] =	    39,
[KeyEnter] =	40,
[esc] =	        41,
[backspace] =	42,
[tab] =	        43,
[space] =	    44,
[charMin] =	    45,
[charPlus] =	46,
[LeftMBrace] =	47,
[rightMBrace] =	48,
[keyOr] =	    49,
[keyColon] =	51,
[keyQuot] =	    52,
[keyComma] =	54,
[keyPoint] =	55,
[keyQues] =	    56,
[lCorner] =	        57
};

uint8_t keyUID1[KB_COLUMN * KB_ROW] = {
[keyA] =	    4,
[keyB] =	    5,
[keyC] =	    6,
[keyD] =	    7,
[keyE] =	    8,
[keyF] =	    9,
[keyG] =	    10,
[keyH] =	    11,
[keyI] =	    12,
[keyJ] =	    13,
[keyK] =	    74,//Home
[keyL] =	    75,//PgUp
[keyM] =	    16,
[keyN] =	    17,
[keyO] =	    18,
[keyP] =	    19,
[keyQ] =	    20,
[keyR] =	    21,
[keyS] =	    22,
[keyT] =	    23,
[keyU] =	    24,
[keyV] =	    25,
[keyW] =	    26,
[keyX] =	    27,
[keyY] =	    28,
[keyZ] =	    29,
[num1] =	    58, //F1
[num2] =	    59,
[num3] =	    60,
[num4] =	    61,
[num5] =	    62,
[num6] =	    63,
[num7] =	    64,
[num8] =	    65,
[num9] =	    66,
[num0] =	    67, //F10
[KeyEnter] =	40,
[esc] =	        41,
[backspace] =	76, //Delete
[tab] =	        43,
[space] =	    44,
[charMin] =	    68, //F11
[charPlus] =	69, //F12
[LeftMBrace] =	82, //Up
[rightMBrace] =	48,
[keyOr] =	    53,
[keyColon] =	80, //left
[keyQuot] =	    79, //right
[keyComma] =	77, //End
[keyPoint] =	78, //PgDn
[keyQues] =	    81, //down
[lCorner] =	    57
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
	uint8_t curlevel = m[lFn] | m[rFn];
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

