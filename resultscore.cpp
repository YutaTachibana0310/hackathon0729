//*****************************************************************************
// �X�R�A����[score.cpp]
// Author: ����@�W��
//*****************************************************************************
#include "main.h"
#include "resultscore.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexResultScore(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureResultScore = NULL;							// �X�R�A�e�N�X�`���ւ̃|���S��
VERTEX_2D				VertexWkResultScore[RESULT_SCORE_DIGIT][NUM_VERTEX];	// �X�R�A�̒��_���i�[���[�N
D3DXVECTOR3				PosResultScore;										// �X�R�A�̈ʒu

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResultScore()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		TEXTURE_GAME_RESULT_SCORE,				// �t�@�C���̖��O
		&D3DTextureResultScore);				// �ǂݍ��ރ������̃|�C���^

										// �e�N�X�`���̓ǂݍ���
	

	PosResultScore = D3DXVECTOR3((float)RESULT_SCORE_POS_X, (float)RESULT_SCORE_POS_Y, 0.0f);
	
	// ���_���̍쐬
	MakeVertexResultScore();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResultScore(void)
{
	if (D3DTextureResultScore != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureResultScore->Release();
		D3DTextureResultScore = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResultScore(void)
{
	SetResultScore(1000); //������
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResultScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTextureResultScore);

	// �X�R�A
	for (int i = 0; i < RESULT_SCORE_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, VertexWkResultScore[i], sizeof(VERTEX_2D));
	}

	
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexResultScore(void)
{

	// ��������������
	for (int i = 0; i < RESULT_SCORE_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		VertexWkResultScore[i][0].vtx.x = -RESULT_SCORE_WIDE * i + PosResultScore.x;
		VertexWkResultScore[i][0].vtx.y = PosResultScore.y;
		VertexWkResultScore[i][0].vtx.z = 0.0f;
		VertexWkResultScore[i][1].vtx.x = -RESULT_SCORE_WIDE * i + PosResultScore.x + TEXTURE_RESULT_SCORE_SIZE_X;
		VertexWkResultScore[i][1].vtx.y = PosResultScore.y;
		VertexWkResultScore[i][1].vtx.z = 0.0f;
		VertexWkResultScore[i][2].vtx.x = -RESULT_SCORE_WIDE * i + PosResultScore.x;
		VertexWkResultScore[i][2].vtx.y = PosResultScore.y + TEXTURE_RESULT_SCORE_SIZE_Y;
		VertexWkResultScore[i][2].vtx.z = 0.0f;
		VertexWkResultScore[i][3].vtx.x = -RESULT_SCORE_WIDE * i + PosResultScore.x + TEXTURE_RESULT_SCORE_SIZE_X;
		VertexWkResultScore[i][3].vtx.y = PosResultScore.y + TEXTURE_RESULT_SCORE_SIZE_Y;
		VertexWkResultScore[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		VertexWkResultScore[i][0].rhw =
		VertexWkResultScore[i][1].rhw =
		VertexWkResultScore[i][2].rhw =
		VertexWkResultScore[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		VertexWkResultScore[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkResultScore[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkResultScore[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkResultScore[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		VertexWkResultScore[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		VertexWkResultScore[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		VertexWkResultScore[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		VertexWkResultScore[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	
	return S_OK;
}

//=============================================================================
// �X�R�A���Z�b�g����
// ����:num :�`�悷��_���B
//=============================================================================
void SetResultScore(int num)
{

	for (int i = 0; i < RESULT_SCORE_DIGIT; i++)
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(num % 10);
		VertexWkResultScore[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		VertexWkResultScore[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		VertexWkResultScore[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		VertexWkResultScore[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		num /= 10;
	}

}