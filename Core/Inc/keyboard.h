/*
 * keyboard.h
 *
 *  Created on: Apr 18, 2020
 *      Author: stor
 */

#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_

#define UID_A		4
#define UID_B		5
#define UID_C		6
#define UID_D		7
#define UID_E		8
#define UID_F		9
#define UID_G		10
#define UID_H		11
#define UID_I		12
#define UID_J		13
#define UID_K		14
#define UID_L		15
#define UID_M		16
#define UID_N		17
#define UID_O		18
#define UID_P		19
#define UID_Q		20
#define UID_R		21
#define UID_S		22
#define UID_T		23
#define UID_U		24
#define UID_V		25
#define UID_W		26
#define UID_X		27
#define UID_Y		28
#define UID_Z		29
#define UID_num1	30
#define UID_num2	31
#define UID_num3	32
#define UID_num4	33
#define UID_num5	34
#define UID_num6	35
#define UID_num7	36
#define UID_num8	37
#define UID_num9	38
#define UID_num0	39
#define UID_enter	40
#define UID_esc		41
#define UID_backspace	42
#define UID_tab		43
#define UID_space	44
#define UID_minus	45
#define UID_equal	46
#define UID_lMBrace	47
#define UID_rMBrace	48
#define UID_or		49
#define UID_colon	51
#define UID_quota	52
#define UID_tilde	53
#define UID_comma	54
#define UID_point	55
#define UID_question	56
#define UID_cap		57
#define UID_f1		58
#define UID_f2		59
#define UID_f3		60
#define UID_f4		61
#define UID_f5		62
#define UID_f6		63
#define UID_f7		64
#define UID_f8		65
#define UID_f9		66
#define UID_f10		67
#define UID_f11		68
#define UID_f12		69
#define UID_printScreen	70
#define UID_scrollLock	71
#define UID_pause	72
#define UID_insert	73
#define UID_home	74
#define UID_pageUp	75
#define UID_delete	76
#define UID_end		77
#define UID_pageDown	78
#define UID_right	79
#define UID_left	80
#define UID_down	81
#define UID_up		82

#include <stdbool.h>
#include "main.h"

#define COLUMN0 GPIO_PIN_0
#define COLUMN1 GPIO_PIN_1
#define COLUMN2 GPIO_PIN_2
#define COLUMN3 GPIO_PIN_3
#define COLUMN4 GPIO_PIN_4
#define COLUMN5 GPIO_PIN_5
#define COLUMN6 GPIO_PIN_6
#define COLUMN7 GPIO_PIN_7

#define ROW0    GPIO_PIN_8
#define ROW1    GPIO_PIN_9
#define ROW2    GPIO_PIN_10
#define ROW3    GPIO_PIN_11
#define ROW4    GPIO_PIN_12
#define ROW5    GPIO_PIN_13
#define ROW6    GPIO_PIN_14
#define ROW7    GPIO_PIN_15

#define COLUMN(n) (COLUMN0 << (n))
#define ROW(n) (ROW0 << (n))

#define COLUMN_OFFSET	0
#define COLUMN_PIN 		(COLUMN0|COLUMN1|COLUMN2|COLUMN3|COLUMN4|COLUMN5|COLUMN6|COLUMN7)
#define COLUMN_PORT		GPIOA
#define ROW_OFFSET     	8
#define ROW_PIN    		(ROW0|ROW1|ROW2|ROW3|ROW4|ROW5|ROW6|ROW7)
#define ROW_PORT   		GPIOB

#define KB_COLUMN 		8
#define KB_ROW    		8
#define KB_LEVEL 	    2

#define STATE_PRESS 	0
#define KEYS_PRESS_MAX 	6

#define KEY_LEVEL_INVAILD -1
enum
{
 esc,      num1,         num2,           num3,       num4,       num5,       num6,       num7,
 num8,     num9,         num0,           charMin,    charPlus,   keyOr,      tab,        keyQ,
 keyW,     keyE,         keyR,           keyT,       keyY,       keyU,       keyI,       keyO,
 keyP,     LeftMBrace,   rightMBrace,    backspace,  lCtrl,      keyA,       keyS,       keyD,
 keyF,     keyG,         keyH,           keyJ,       keyK,       keyL,       keyColon,   keyQuot,
 KeyEnter, lShift,       keyZ,           keyX,       keyC,       keyV,       keyB,       keyN,
 keyM,     keyComma,     keyPoint,       keyQues,    rShift,     lCorner,      lFn,        lAlt,
 space,    rAlt,         rWin,           rCtrl,      rFn
};

typedef struct {
	uint8_t matrix[KB_COLUMN * KB_ROW];
	uint8_t keylist[KEYS_PRESS_MAX];
	int8_t keylevel[KEYS_PRESS_MAX];
	uint8_t keycnt;
	uint8_t keylastlist[KEYS_PRESS_MAX];
	int8_t keylastlevel[KEYS_PRESS_MAX];
	uint8_t keylastcnt;
	uint8_t vaild;
} KeyState;

void ScanKeyState(KeyState * keystate);
void GenReport(KeyState * keystate, uint8_t * reportBuf);

#endif /* INC_KEYBOARD_H_ */
