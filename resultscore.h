//=============================================================================
//
// ���U���g�X�R�A���� [resultscore.h]
// Author : ����@�W��
//
//=============================================================================
#ifndef _RESULTSCORE_H_
#define _RESULTSCORE_H_
//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_GAME_RESULT_SCORE	"data/TEXTURE/number.png"			// �X�R�A�p�摜

#define TEXTURE_RESULT_SCORE_SIZE_X				(300)					// �X�R�A�e�N�X�`���T�C�Y
#define TEXTURE_RESULT_SCORE_SIZE_Y				(300)					// ����

#define RESULT_SCORE_POS_X						(1100)					// �X�R�A�̏����ʒuX
#define RESULT_SCORE_POS_Y						(300)					// ����

#define RESULT_SCORE_WIDE						(150)                    //�����̕�
#define RESULT_SCORE_MAX						(99999)					// �X�R�A�̍ő�l
#define RESULT_SCORE_DIGIT						(5)						// ����


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResultScore(void);
void UninitResultScore(void);
void UpdateResultScore(void);
void DrawResultScore(void);
void SetResultScore(int num);

#endif
