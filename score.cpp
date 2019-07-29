//*****************************************************************************
// �X�R�A����[score.cpp]
// Author: GA12A ����@�W��
//*****************************************************************************
#include "main.h"
#include "score.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexScore(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureScore = NULL;					// �X�R�A�e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		D3DTextureScoreRogo = NULL;				// �X�R�A���S�e�N�X�`���ւ̃|���S��

VERTEX_2D				VertexWkScore[SCORE_DIGIT][NUM_VERTEX];	// �X�R�A�̒��_���i�[���[�N
VERTEX_2D				VertexWkScoreRogo[NUM_VERTEX];			// �X�R�A�̒��_���i�[���[�N

D3DXVECTOR3				PosScore;								// �X�R�A�̈ʒu
D3DXVECTOR3				PosScoreRogo;							// �X�R�A���S�̈ʒu

//=============================================================================
// ����������
//=============================================================================
HRESULT InitScore()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_SCORE,				// �t�@�C���̖��O
			&D3DTextureScore);				// �ǂݍ��ރ������̃|�C���^

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		TEXTURE_GAME_ROGO,				// �t�@�C���̖��O
		&D3DTextureScoreRogo);				// �ǂݍ��ރ������̃|�C���^

	PosScore = D3DXVECTOR3((float)SCORE_POS_X, (float)SCORE_POS_Y, 0.0f);
	PosScoreRogo = D3DXVECTOR3((float)SCORE_ROGO_POS_X, (float)SCORE_ROGO_POS_Y, 0.0f);
	// ���_���̍쐬
	MakeVertexScore();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	if (D3DTextureScore != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureScore->Release();
		D3DTextureScore = NULL;
	}

	if (D3DTextureScoreRogo != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureScoreRogo->Release();
		D3DTextureScoreRogo = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
	SetScore(1000); //������
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTextureScore);

	// �X�R�A
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, VertexWkScore[i], sizeof(VERTEX_2D));
	}

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTextureScoreRogo);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, VertexWkScoreRogo, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexScore(void)
{
	
	// ��������������
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		VertexWkScore[i][0].vtx.x = -SCORE_WIDE * i + PosScore.x;
		VertexWkScore[i][0].vtx.y = PosScore.y;
		VertexWkScore[i][0].vtx.z = 0.0f;
		VertexWkScore[i][1].vtx.x = -SCORE_WIDE * i + PosScore.x + TEXTURE_SCORE_SIZE_X;
		VertexWkScore[i][1].vtx.y = PosScore.y;
		VertexWkScore[i][1].vtx.z = 0.0f;
		VertexWkScore[i][2].vtx.x = -SCORE_WIDE * i + PosScore.x;
		VertexWkScore[i][2].vtx.y = PosScore.y + TEXTURE_SCORE_SIZE_Y;
		VertexWkScore[i][2].vtx.z = 0.0f;
		VertexWkScore[i][3].vtx.x = -SCORE_WIDE * i + PosScore.x + TEXTURE_SCORE_SIZE_X;
		VertexWkScore[i][3].vtx.y = PosScore.y + TEXTURE_SCORE_SIZE_Y;
		VertexWkScore[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		VertexWkScore[i][0].rhw =
		VertexWkScore[i][1].rhw =
		VertexWkScore[i][2].rhw =
		VertexWkScore[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		VertexWkScore[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkScore[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkScore[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkScore[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		VertexWkScore[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		VertexWkScore[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		VertexWkScore[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		VertexWkScore[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���S�̒��_���W�̐ݒ�
	VertexWkScoreRogo[0].vtx = D3DXVECTOR3(SCORE_ROGO_POS_X, SCORE_ROGO_POS_Y, 0);
	VertexWkScoreRogo[1].vtx = D3DXVECTOR3(SCORE_ROGO_POS_X + TEXTURE_SCORE_ROGO_SIZE_X, SCORE_ROGO_POS_Y, 0);
	VertexWkScoreRogo[2].vtx = D3DXVECTOR3(SCORE_ROGO_POS_X, SCORE_ROGO_POS_Y + TEXTURE_SCORE_ROGO_SIZE_Y, 0);
	VertexWkScoreRogo[3].vtx = D3DXVECTOR3(SCORE_ROGO_POS_X + TEXTURE_SCORE_ROGO_SIZE_X, SCORE_ROGO_POS_Y + TEXTURE_SCORE_ROGO_SIZE_Y, 0);

	// rhw�̐ݒ�
	VertexWkScoreRogo[0].rhw =
	VertexWkScoreRogo[1].rhw =
	VertexWkScoreRogo[2].rhw =
	VertexWkScoreRogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	VertexWkScoreRogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	VertexWkScoreRogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	VertexWkScoreRogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	VertexWkScoreRogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	VertexWkScoreRogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	VertexWkScoreRogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	VertexWkScoreRogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	VertexWkScoreRogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	return S_OK;
}

//=============================================================================
// �X�R�A���Z�b�g����
// ����:num :�`�悷��_���B
//=============================================================================
void SetScore(int num)
{

	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(num % 10);
		VertexWkScore[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		VertexWkScore[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		VertexWkScore[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		VertexWkScore[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		num /= 10;
	}

}