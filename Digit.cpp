#include "main.h"
#include "Digit.h"

#define DIGIT_TEXTURE	("data/TEXTURE/Digit.png")
#define DIGIT_SIZE	D3DXVECTOR3(50.0f, 100.0f, 0.0f)
#define DIGIT_POS	D3DXVECTOR3(SCREEN_CENTER_X + DIGIT_SIZE.x, DIGIT_SIZE.y, 0.0f)	// �E�̌����
#define DIGIT_SPACE	(DIGIT_SIZE.x * 2)
#define DIGIT_DIVIDE_X	(10)
#define DIGIT_DIVIDE_Y	(1)

LPDIRECT3DTEXTURE9	Digit::D3DTexture = NULL; // �e�N�X�`���̃|�C���^

Digit::Digit(int digit, DWORD time)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	use = true;
	this->time = time;
	pos = DIGIT_POS;
	pos.x -= digit * DIGIT_SPACE;
	size = DIGIT_SIZE;

	if (D3DTexture == NULL)
	{
		D3DXCreateTextureFromFile(Device,	// �f�o�C�X�̃|�C���^
			DIGIT_TEXTURE,					// �t�@�C���̖��O
			&D3DTexture);					// �ǂݍ��ރ������̃|�C���^
	}

	MakeVertex();
}


Digit::~Digit()
{
	SAFE_RELEASE(Digit::D3DTexture);
}

void Digit::Update()
{
}

void Digit::Update(DWORD time)
{
	this->time = time;
	SetTexture();
}

void Digit::Draw()
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

void Digit::SetTexture()
{
	int x = time % DIGIT_DIVIDE_X;
	int y = time / DIGIT_DIVIDE_X;
	float sizeX = 1.0f / DIGIT_DIVIDE_X;
	float sizeY = 1.0f / DIGIT_DIVIDE_Y;

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

void Digit::MakeVertex()
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