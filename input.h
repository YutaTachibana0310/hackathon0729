//=============================================================================
//
// ���͏��� [input.h]
// Author : 
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#include "Framework\Gamepad.h"
#include "Framework\Mouse.h"
#include "Framework\Keyboard.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

float GetHorizontalInputPress();		//���������̓��͏���
float GetVerticalInputPress();			//���������̓��͏���
#endif