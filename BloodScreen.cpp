#include "main.h"
#include "BloodScreen.h"

#define TEXTURE_BLOODSCREEN ("data/TEXTURE/blood.png")
#define PLUS_ALPHA			(25)						// �A���t�@�̉��Z�l

int BloodScreen::alpha = 0;

BloodScreen::BloodScreen()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	size = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	use = true;
	alpha = 0;

	D3DXCreateTextureFromFile(Device,	// �f�o�C�X�̃|�C���^
		TEXTURE_BLOODSCREEN,			// �t�@�C���̖��O
		&D3DTexture);					// �ǂݍ��ރ������̃|�C���^

	MakeVertex();
}


BloodScreen::~BloodScreen()
{
	if (D3DTexture != NULL)
	{	// �e�N�X�`���̊J��
		D3DTexture->Release();
		D3DTexture = NULL;
	}
}

void BloodScreen::Update()
{
	SetColor();
}

void BloodScreen::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, D3DTexture);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
}

void BloodScreen::MakeVertex()
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
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(0.5f, 1.0f);

}

void BloodScreen::SetColor()
{
	// ���ˌ��̐ݒ�
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);
}
void BloodScreen::SetAlpha()
{
	alpha += PLUS_ALPHA;
	alpha = min(alpha, 255);
}
