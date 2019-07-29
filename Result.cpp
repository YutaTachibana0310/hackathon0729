//=============================================================================
//
// ���U���g��ʏ��� [result.cpp]
// Author : ���a �ɑ��N
//
//=============================================================================
#include "Result.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RESULT		("data/TEXTURE/result001.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_POS_X			(0)									// �^�C�g���̕\���ʒu
#define	RESULT_POS_Y			(0)									// �^�C�g���̕\���ʒu
#define	RESULT_SIZE_X			(SCREEN_WIDTH)						// �^�C�g���̕�
#define	RESULT_SIZE_Y			(SCREEN_HEIGHT)						// �^�C�g���̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexResult(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureResult = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				vertexWkResult[NUM_VERTEX];			// ���_���i�[���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RESULT,				// �t�@�C���̖��O
		&D3DTextureResult);		// �ǂݍ��ރ������[

// ���_���̍쐬
	MakeVertexResult();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{
	if (D3DTextureResult != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureResult->Release();
		D3DTextureResult = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTextureResult);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkResult, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexResult(void)
{
	// ���_���W�̐ݒ�
	vertexWkResult[0].vtx = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	vertexWkResult[1].vtx = D3DXVECTOR3(RESULT_POS_X + RESULT_SIZE_X, RESULT_POS_Y, 0.0f);
	vertexWkResult[2].vtx = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y + RESULT_SIZE_Y, 0.0f);
	vertexWkResult[3].vtx = D3DXVECTOR3(RESULT_POS_X + RESULT_SIZE_X, RESULT_POS_Y + RESULT_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWkResult[0].rhw =
	vertexWkResult[1].rhw =
	vertexWkResult[2].rhw =
	vertexWkResult[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkResult[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkResult[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkResult[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkResult[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWkResult[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkResult[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkResult[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkResult[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}

