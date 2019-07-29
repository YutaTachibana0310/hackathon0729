#include "main.h"
#include "BloodScreen.h"

#define TEXTURE_BLOODSCREEN ("data/TEXTURE/blood.png")
#define PLUS_ALPHA			(25)						// アルファの加算値

int BloodScreen::alpha = 0;

BloodScreen::BloodScreen()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	size = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	use = true;
	alpha = 0;

	D3DXCreateTextureFromFile(Device,	// デバイスのポインタ
		TEXTURE_BLOODSCREEN,			// ファイルの名前
		&D3DTexture);					// 読み込むメモリのポインタ

	MakeVertex();
}


BloodScreen::~BloodScreen()
{
	if (D3DTexture != NULL)
	{	// テクスチャの開放
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

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, D3DTexture);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
}

void BloodScreen::MakeVertex()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, 0.0f);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0.0f);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0.0f);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);

	// rhwの設定
	vertexWk[0].rhw = 1.0f;
	vertexWk[1].rhw = 1.0f;
	vertexWk[2].rhw = 1.0f;
	vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(0.5f, 1.0f);

}

void BloodScreen::SetColor()
{
	// 反射光の設定
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
