//=====================================
//
//�w�L�T�g�����W�V��������[HexaTransition.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "HexaTransition.h"

/**************************************
�}�N����`
***************************************/
#define HEXATRANSITION_DURATION		(45)

/**************************************
�X�V����
***************************************/
void HexaTransition::Update()
{
	if (!enableMask)
		return;

	cntFrame++;

	//�}�X�N�摜�̃X�P�[�����C�[�W���O����
	float t = 1.f * cntFrame / HEXATRANSITION_DURATION;
	transform.scale = Easing<D3DXVECTOR3>::GetEasingValue(t, &initScale, &goalScale, easeType);

	//��]������
	transform.Rotate(0.0f, 0.0f, 5.0f);

	//�g�����W�V�����̏I���m�F
	if (cntFrame == HEXATRANSITION_DURATION)
	{
		//�}�X�N���I�t��
		enableMask = false;

		//�J�ڌ�ł���΃g�����W�V�����摜���I�t��
		if (isTransitionOut)
			enableTransition = false;

		//�R�[���o�b�N�̌Ăяo��
		if(callback != NULL)
			callback();

		callback = NULL;
	}
}

/**************************************
�g�����W�V�����J�n����
***************************************/
void HexaTransition::SetTransition(bool isStart, std::function<void(void)> func)
{
	//���łɃ}�X�N���ł���ΊJ�n���Ȃ�
	if (enableMask)
		return;

	//�����J�ڏ�Ԃ͊J�n���Ȃ�
	if (isStart == enableTransition)
		return;

	//�C�[�W���O�p�̃p�����[�^������
	initScale = isStart ? D3DXVECTOR3(1.0f, 1.0f, 1.0f) : D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	goalScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f) - initScale;
	easeType = isStart ? OutExponential : InExponential;
	cntFrame = 0;

	//�R�[���o�b�N�o�^
	callback = func;

	//�t���O������
	enableMask = true;
	enableTransition = true;
	isTransitionOut = !isStart;
}

