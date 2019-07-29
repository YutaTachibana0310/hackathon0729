//=============================================================================
//
// �X�R�A���� [score.h]
// Author : ����@�W��
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_
//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_GAME_SCORE	"data/TEXTURE/number.png"			// �X�R�A�p�摜
#define TEXTURE_GAME_ROGO	"data/TEXTURE/rogo.png"				// �X�R�A���S�p�摜

#define TEXTURE_SCORE_SIZE_X			(100)					// �X�R�A�e�N�X�`���T�C�Y
#define TEXTURE_SCORE_SIZE_Y			(100)					// ����
#define TEXTURE_SCORE_ROGO_SIZE_X		(100)					// �X�R�A�e�N�X�`���T�C�Y
#define TEXTURE_SCORE_ROGO_SIZE_Y		(100)					// ����

#define SCORE_POS_X						(1400)					// �X�R�A�̏����ʒuX
#define SCORE_POS_Y						(10)					// ����
#define SCORE_ROGO_POS_X				(1100)					// �X�R�A���S�̏����ʒuY
#define SCORE_ROGO_POS_Y				(10)					// ����

#define SCORE_WIDE				(50)                            //�����̕�
#define SCORE_MAX				(99999)							// �X�R�A�̍ő�l
#define SCORE_DIGIT				(5)								// ����


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int num);

#endif
