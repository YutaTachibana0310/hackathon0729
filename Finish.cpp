#include "main.h"
#include "Finish.h"

#define FINISH_TEXTURE	("data/TEXTURE/finish.png")
#define FINISH_SIZE	D3DXVECTOR3(400.0f, 400.0f, 0.0f)

Finish::Finish()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	use = true;
	pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	size = FINISH_SIZE;

	D3DXCreateTextureFromFile(Device,	// �f�o�C�X�̃|�C���^
		FINISH_TEXTURE,					// �t�@�C���̖��O
		&D3DTexture);					// �ǂݍ��ރ������̃|�C���^

	MakeVertex();
}


Finish::~Finish()
{
	if (D3DTexture != NULL)
	{	// �e�N�X�`���̊J��
		D3DTexture->Release();
		D3DTexture = NULL;
	}

}

void Finish::Update()
{
}

void Finish::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	if (use == true)
	{
		// �e�N�X�`���̐ݒ�(�|���S���̕`��O�ɓǂݍ��񂾃e�N�X�`���̃Z�b�g���s��)
		// �e�N�X�`���̃Z�b�g�����Ȃ��ƑO�ɃZ�b�g���ꂽ�e�N�X�`�����\���遨�����͂�Ȃ����Ƃ��w�肷��pDevide->SetTexture(0, NULL);
		Device->SetTexture(0, D3DTexture);

		// �|���S���̕`��
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
	}
}

void Finish::MakeVertex()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, 0.0f);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0.0f);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0.0f);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);

	// rhw�̐ݒ�
	vertexWk[0].rhw = 1.0f;
	vertexWk[1].rhw = 1.0f;
	vertexWk[2].rhw = 1.0f;
	vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	SetTexture();
}

void Finish::SetTexture()
{
	int x = 1;
	int y = 1;
	float sizeX = 1.0f;
	float sizeY = 1.0f;

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}
