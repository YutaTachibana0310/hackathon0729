//*****************************************************************************
// �R���{����[combo.cpp]
// Author:����@�W��
//*****************************************************************************
#include "main.h"
#include "combo.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexCombo(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureCombo = NULL;					// �R���{�e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		D3DTextureComboRogo = NULL;				// ���S�e�N�X�`���ւ̃|���S��
VERTEX_2D				VertexWkCombo[COMBO_DIGIT][NUM_VERTEX];	// �R���{���_���i�[���[�N
VERTEX_2D				VertexWkComboRogo[NUM_VERTEX];			// ���S���_���i�[���[�N
D3DXVECTOR3				PosCombo;								// �R���{�̈ʒu
D3DXVECTOR3				PosComboRogo;							// �R���{���S�̈ʒu

//=============================================================================
// ����������
//=============================================================================
HRESULT InitCombo()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_COMBO,				// �t�@�C���̖��O
			&D3DTextureCombo);				// �ǂݍ��ރ������̃|�C���^
	
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		TEXTURE_GAME_COMBO_ROGO,				// �t�@�C���̖��O
		&D3DTextureComboRogo);				// �ǂݍ��ރ������̃|�C���^

	PosCombo = D3DXVECTOR3((float)COMBO_POS_X, (float)COMBO_POS_Y, 0.0f);
	PosComboRogo = D3DXVECTOR3((float)COMBO_ROGO_POS_X, (float)COMBO_ROGO_POS_Y, 0.0f);

	// ���_���̍쐬
	MakeVertexCombo();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCombo(void)
{
	if (D3DTextureCombo != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureCombo->Release();
		D3DTextureCombo = NULL;
	}

	if (D3DTextureComboRogo != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureComboRogo->Release();
		D3DTextureComboRogo = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCombo(void)
{
	SetCombo(1); //������
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCombo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTextureCombo);

	// �X�R�A
	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, VertexWkCombo[i], sizeof(VERTEX_2D));
	}

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTextureComboRogo);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, VertexWkComboRogo, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexCombo(void)
{

	// ��������������
	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		VertexWkCombo[i][0].vtx.x = -COMBO_WIDE * i + PosCombo.x;
		VertexWkCombo[i][0].vtx.y = PosCombo.y;
		VertexWkCombo[i][0].vtx.z = 0.0f;
		VertexWkCombo[i][1].vtx.x = -COMBO_WIDE * i + PosCombo.x + TEXTURE_COMBO_SIZE_X;
		VertexWkCombo[i][1].vtx.y = PosCombo.y;
		VertexWkCombo[i][1].vtx.z = 0.0f;
		VertexWkCombo[i][2].vtx.x = -COMBO_WIDE * i + PosCombo.x;
		VertexWkCombo[i][2].vtx.y = PosCombo.y + TEXTURE_COMBO_SIZE_Y;
		VertexWkCombo[i][2].vtx.z = 0.0f;
		VertexWkCombo[i][3].vtx.x = -COMBO_WIDE * i + PosCombo.x + TEXTURE_COMBO_SIZE_X;
		VertexWkCombo[i][3].vtx.y = PosCombo.y + TEXTURE_COMBO_SIZE_Y;
		VertexWkCombo[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		VertexWkCombo[i][0].rhw =
		VertexWkCombo[i][1].rhw =
		VertexWkCombo[i][2].rhw =
		VertexWkCombo[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		VertexWkCombo[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkCombo[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkCombo[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkCombo[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		VertexWkCombo[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		VertexWkCombo[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		VertexWkCombo[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		VertexWkCombo[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���S�̒��_���W�̐ݒ�
	VertexWkComboRogo[0].vtx = D3DXVECTOR3(COMBO_ROGO_POS_X, COMBO_ROGO_POS_Y, 0);
	VertexWkComboRogo[1].vtx = D3DXVECTOR3(COMBO_ROGO_POS_X + TEXTURE_COMBO_ROGO_SIZE_X, COMBO_ROGO_POS_Y, 0);
	VertexWkComboRogo[2].vtx = D3DXVECTOR3(COMBO_ROGO_POS_X, COMBO_ROGO_POS_Y + TEXTURE_COMBO_ROGO_SIZE_Y, 0);
	VertexWkComboRogo[3].vtx = D3DXVECTOR3(COMBO_ROGO_POS_X + TEXTURE_COMBO_ROGO_SIZE_X, COMBO_ROGO_POS_Y + TEXTURE_COMBO_ROGO_SIZE_Y, 0);

	// rhw�̐ݒ�
	VertexWkComboRogo[0].rhw =
	VertexWkComboRogo[1].rhw =
	VertexWkComboRogo[2].rhw =
	VertexWkComboRogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	VertexWkComboRogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	VertexWkComboRogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	VertexWkComboRogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	VertexWkComboRogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	VertexWkComboRogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	VertexWkComboRogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	VertexWkComboRogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	VertexWkComboRogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	return S_OK;
}

//=============================================================================
// �X�R�A���Z�b�g����
// ����:num :�`�悷��_���B
//=============================================================================
void SetCombo(int num)
{

	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(num % 10);
		VertexWkCombo[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		VertexWkCombo[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		VertexWkCombo[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		VertexWkCombo[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		num /= 10;
	}

}