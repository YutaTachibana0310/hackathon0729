//=============================================================================
//
// ���͏��� [input.cpp]
// Author : 
//
//=============================================================================
#include "input.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECTINPUT8			g_pDInput = NULL;					// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^

//=============================================================================
// ���͏����̏�����
//=============================================================================
HRESULT InitInput(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	if(!g_pDInput)
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
									IID_IDirectInput8, (void**)&g_pDInput, NULL);
	}

	// �L�[�{�[�h�̏�����
	InitKeyboard(hInst, hWnd, g_pDInput);

	//�}�E�X������
	InitializeMouse(hInst, hWnd, g_pDInput);

	//�p�b�h����������
	InitializePad(g_pDInput);

	return S_OK;
}

//=============================================================================
// ���͏����̏I������
//=============================================================================
void UninitInput(void)
{
	// �L�[�{�[�h�̏I������
	UninitKeyboard();

	//�}�E�X�I������
	UninitMouse();

	//�p�b�h�I������
	UninitPad();

	if(g_pDInput)
	{// DirectInput�I�u�W�F�N�g�̊J��
		g_pDInput->Release();
		g_pDInput = NULL;
	}
}

//=============================================================================
// ���͏����̍X�V����
//=============================================================================
void UpdateInput(void)
{
	// �L�[�{�[�h�̍X�V
	UpdateKeyboard();

	//�}�E�X�X�V����
	UpdateMouse();

	//�Q�[���p�b�h�X�V����
	UpdatePad();
}

//=============================================================================
// ���������ւ̓���
//=============================================================================
float GetHorizontalInputPress()
{

	if (IsButtonPressed(0, BUTTON_LEFT))
		return -1.0f;

	if (IsButtonPressed(0, BUTTON_RIGHT))
		return 1.0f;

	if (GetKeyboardPress(DIK_LEFT))
		return -1.0f;

	if (GetKeyboardPress(DIK_RIGHT))
		return 1.0f;

	return 0.0f;
}

//=============================================================================
// ���������ւ̓���
//=============================================================================
float GetVerticalInputPress()
{
	if (IsButtonPressed(0, BUTTON_UP))
		return 1.0f;

	if (IsButtonPressed(0, BUTTON_DOWN))
		return -1.0f;

	if (GetKeyboardPress(DIK_UP))
		return 1.0f;

	if (GetKeyboardPress(DIK_DOWN))
		return -1.0f;

	return 0.0f;
}