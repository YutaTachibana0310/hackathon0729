#include "main.h"
#include "Start.h"
#include "GameScene.h"

#define START_TEXTURE	("data/TEXTURE/readygo.png")
#define START_DIVIDE_X	(1)
#define START_DIVIDE_Y	(2)
#define START_SIZE		D3DXVECTOR3(400.0f, 100.0f, 0.0f)

Start::Start()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	cnt = 0;
	anim = 0;
	use = true;
	pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	size = START_SIZE;

	D3DXCreateTextureFromFile(Device,	// デバイスのポインタ
		START_TEXTURE,					// ファイルの名前
		&D3DTexture);					// 読み込むメモリのポインタ

	MakeVertex();
}

Start::~Start()
{
	if (D3DTexture != NULL)
	{	// テクスチャの開放
		D3DTexture->Release();
		D3DTexture = NULL;
	}
}


void Start::Update()
{
	if (use)
	{
		cnt++;

		//60フレームに一度テクスチャを切り替え
		if ((cnt % 60) == 0)
		{
			anim++;
		}

		if (cnt == START_TIME)
		{
			use = false;
		}

		SetTexture();
	}
}

void Start::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	if (use == true)
	{
		// テクスチャの設定(ポリゴンの描画前に読み込んだテクスチャのセットを行う)
		// テクスチャのセットをしないと前にセットされたテクスチャが貼られる→何もはらないことを指定するpDevide->SetTexture(0, NULL);
		Device->SetTexture(0, D3DTexture);

		// ポリゴンの描画
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
	}
}

void Start::MakeVertex()
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
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(0.5f, 1.0f);

}

void Start::SetTexture()
{
	int x = anim % START_DIVIDE_X;
	int y = anim / START_DIVIDE_X;
	float sizeX = 1.0f / START_DIVIDE_X;
	float sizeY = 1.0f / START_DIVIDE_Y;

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

int Start::Check()
{
	return cnt;
}
