//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : ���a �ɑ��N
//
//=============================================================================
#include "Title.h"
#include "input.h"
#include "Game.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TITLE		"data/TEXTURE/title001.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TITLE_LOGO	"data/TEXTURE/logo001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_LOGO_START	"data/TEXTURE/start.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define	TITLE_LOGO_POS_X		(450)		// �^�C�g�����S�̈ʒu(X���W)
#define	TITLE_LOGO_POS_Y		(200)		// �^�C�g�����S�̈ʒu(Y���W)
#define	TITLE_LOGO_WIDTH		(1000)		// �^�C�g�����S�̕�
#define	TITLE_LOGO_HEIGHT		(250)		// �^�C�g�����S�̍���

#define	START_POS_X				(800)		// �X�^�[�g�{�^���̈ʒu(X���W)
#define	START_POS_Y				(700)		// �X�^�[�g�{�^���̈ʒu(Y���W)
#define	START_WIDTH				(280)		// �X�^�[�g�{�^���̕�
#define	START_HEIGHT			(100)		// �X�^�[�g�{�^���̍���

#define	COUNT_APPERA_START		(60)		// �X�^�[�g�{�^���o���܂ł̎���
#define	INTERVAL_DISP_START		(60)		// �X�^�[�g�{�^���_�ł̎���

#define	COUNT_WAIT_DEMO			(60 * 5)	// �f���܂ł̑҂�����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTitle(LPDIRECT3DDEVICE9 Device);
void SetColorTitleLogo(void);
void SetColorTitleLogoStart(void);

void FillVertexTitle();
void FillVertexTitleLogo();
void FillVertexStart();

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureTitle = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffTitle = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9		D3DTextureTitleLogo = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffTitleLogo = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9		D3DTextureStart = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffStart = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
int						CountAppearStart = 0;		
float					AlphaLogo = 0.0f;		
float					AlphaLogoStart = 0.0f;		
int						CountDisp = 0;			
bool					DispStart = false;		

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	CountAppearStart = 0;
	AlphaLogo = 0.0f;
	CountDisp = 0;
	DispStart = false;

	// ���_���̍쐬
	MakeVertexTitle(Device);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_TITLE,				// �t�@�C���̖��O
								&D3DTextureTitle);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(Device,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE_LOGO,			// �t�@�C���̖��O
		&D3DTextureTitleLogo);	// �ǂݍ��ރ������[


	D3DXCreateTextureFromFile(Device,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_LOGO_START,			// �t�@�C���̖��O
		&D3DTextureStart);		// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	if(D3DTextureTitle != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureTitle->Release();
		D3DTextureTitle = NULL;
	}

	if(D3DVtxBuffTitle != NULL)
	{// ���_�o�b�t�@�̊J��
		D3DVtxBuffTitle->Release();
		D3DVtxBuffTitle = NULL;
	}

	if (D3DTextureTitleLogo != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureTitleLogo->Release();
		D3DTextureTitleLogo = NULL;
	}

	if (D3DVtxBuffTitleLogo != NULL)
	{// ���_�o�b�t�@�̊J��
		D3DVtxBuffTitleLogo->Release();
		D3DVtxBuffTitleLogo = NULL;
	}

	if (D3DTextureStart != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureStart->Release();
		D3DTextureStart = NULL;
	}

	if (D3DVtxBuffStart != NULL)
	{// ���_�o�b�t�@�̊J��
		D3DVtxBuffStart->Release();
		D3DVtxBuffStart = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{

	if (AlphaLogo < 1.0f)
	{
		AlphaLogo += 0.005f;
		if (AlphaLogo >= 1.0f)
		{
			AlphaLogo = 1.0f;
		}
		SetColorTitleLogo();
	}
	else
	{
		CountAppearStart++;
		if (CountAppearStart > COUNT_APPERA_START)
		{
			CountDisp = (CountDisp + 1) % 80;
			if (CountDisp > INTERVAL_DISP_START)
			{
				DispStart = false;
			}
			else
			{
				DispStart = true;
			}
		}
	}

	if (AlphaLogoStart < 1.0f)
	{
		AlphaLogoStart += 0.010f;
		if (AlphaLogoStart >= 1.0f)
		{
			AlphaLogoStart--;
		}
		SetColorTitleLogoStart();
	}

#if 0

	if (GetKeyboardTrigger(DIK_SPACE))
	{
		ChangeScene(SceneResult);

	}

#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, D3DVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTextureTitle);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);


	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, D3DVtxBuffTitleLogo, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTextureTitleLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//if(DispStart == true)
	//{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, D3DVtxBuffStart, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTextureStart);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	//}


}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice)
{

	// �^�C�g��
	//// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&D3DVtxBuffTitle,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))						// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	//���_�o�b�t�@�̒��g�𖄂߂�
	FillVertexTitle();

	// �^�C�g�����S
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DVtxBuffTitleLogo,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̒��g�𖄂߂�
	FillVertexTitleLogo();


	// �X�^�[�g�A�C�R��
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DVtxBuffStart,			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̒��g�𖄂߂�
	FillVertexStart();


	return S_OK;
}

//=============================================================================
//	TitleLogo�̐F�Z�b�g
//=============================================================================
void SetColorTitleLogo(void)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffTitleLogo->Unlock();
	}

}

void SetColorTitleLogoStart(void)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffStart->Lock(0, 0, (void**)&pVtx, 0);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogoStart);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogoStart);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogoStart);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogoStart);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffStart->Unlock();
	}

}

//=============================================================================
// ���_�o�b�t�@�̒��g�𖄂߂�
//=============================================================================
// �^�C�g��
void FillVertexTitle()
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffTitle->Unlock();
	}

}

// �^�C�g�����S
void FillVertexTitleLogo()
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(TITLE_LOGO_POS_X, TITLE_LOGO_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(TITLE_LOGO_POS_X + TITLE_LOGO_WIDTH, TITLE_LOGO_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(TITLE_LOGO_POS_X, TITLE_LOGO_POS_Y + TITLE_LOGO_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(TITLE_LOGO_POS_X + TITLE_LOGO_WIDTH, TITLE_LOGO_POS_Y + TITLE_LOGO_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffTitleLogo->Unlock();
	}


}

// �X�^�[�g
void FillVertexStart()
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffStart->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(START_POS_X, START_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(START_POS_X + START_WIDTH, START_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(START_POS_X, START_POS_Y + START_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(START_POS_X + START_WIDTH, START_POS_Y + START_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogoStart);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogoStart);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogoStart);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogoStart);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffStart->Unlock();
	}


}