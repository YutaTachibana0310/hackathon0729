//=============================================================================
// �R���{���� [combo.h]
// Author : ����@�W��
//=============================================================================
#ifndef _COMBO_H_
#define _COMBO_H_
//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_GAME_COMBO	"data/TEXTURE/number.png"			    // �R���{�p�摜
#define TEXTURE_GAME_COMBO_ROGO	"data/TEXTURE/comborogo.png"		// �R���{���S�p�摜

#define TEXTURE_COMBO_SIZE_X		(100)							// �R���{�e�N�X�`���T�C�Y
#define TEXTURE_COMBO_SIZE_Y		(100)							// ����
#define TEXTURE_COMBO_ROGO_SIZE_X	(100)							// �R���{���S�e�N�X�`���T�C�Y
#define TEXTURE_COMBO_ROGO_SIZE_Y	(100)							// ����

#define COMBO_POS_X					(1700)							// �R���{�̏����ʒuX
#define COMBO_POS_Y					(10)							// ����
#define COMBO_ROGO_POS_X			(1500)							// �R���{�̏����ʒuX
#define COMBO_ROGO_POS_Y			(10)							// ����

#define COMBO_WIDE					(50)                            //�����̕�
#define COMBO_MAX					(999)							// �R���{�̍ő�l
#define COMBO_DIGIT					(3)								// ����


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCombo();
void UninitCombo(void);
void UpdateCombo(void);
void DrawCombo(void);
void SetCombo(int num);

#endif

