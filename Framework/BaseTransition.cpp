//=====================================
//
//ベーストランジション処理[BaseTransition.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BaseTransition.h"

/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
BaseTransition::BaseTransition()
{
	//パラメータ初期化
	transform.pos = D3DXVECTOR3((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, 0.0f);
	radius = D3DXVec2Length(&D3DXVECTOR2((float)SCREEN_WIDTH, (float)SCREEN_WIDTH));
	angle = atan2f((float)SCREEN_WIDTH, (float)SCREEN_WIDTH);

	//マスク用頂点ワーク初期化
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		vtxMask[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vtxMask[i].rhw = 1.0f;
	}

	vtxMask[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxMask[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxMask[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxMask[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	SetVertexMask();

	//トランジション用頂点ワーク初期化
	vtxTransition[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vtxTransition[1].vtx = D3DXVECTOR3((float)SCREEN_WIDTH, 0.0f, 0.0f);
	vtxTransition[2].vtx = D3DXVECTOR3(0.0f, (float)SCREEN_HEIGHT, 0.0f);
	vtxTransition[3].vtx = D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f);

	vtxTransition[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxTransition[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxTransition[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxTransition[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		vtxTransition[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vtxTransition[i].rhw = 1.0f;
	}

	//コールバック初期化
	callback = NULL;
	
	//フラグ初期化
	enableMask = false;
	enableTransition = false;
}

/**************************************
デストラクタ
***************************************/
BaseTransition::~BaseTransition()
{
	SAFE_RELEASE(maskTexture);
	SAFE_RELEASE(transitionTexture);
}

/**************************************
マスク開始処理
***************************************/
void BaseTransition::BeginMask()
{
	if (!enableMask)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, true);
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
}

/**************************************
マスク描画処理
***************************************/
void BaseTransition::DrawMask()
{
	if (!enableMask)
		return;

	if (transform.scale == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		return;

	BeginMask();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, maskTexture);
	
	pDevice->SetFVF(FVF_VERTEX_2D);

	SetVertexMask();

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxMask, sizeof(VERTEX_2D));

	EndMask();
}

/**************************************
マスク終了処理
***************************************/
void BaseTransition::EndMask()
{
	if (!enableMask)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,
		D3DCOLORWRITEENABLE_RED |
		D3DCOLORWRITEENABLE_GREEN |
		D3DCOLORWRITEENABLE_BLUE |
		D3DCOLORWRITEENABLE_ALPHA);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

/**************************************
トランジション描画処理
***************************************/
void BaseTransition::DrawTransition()
{
	if (!enableTransition)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//マスクが書き込まれていないピクセルにトランジション画像を描画する
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x00);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

	pDevice->SetTexture(0, transitionTexture);

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxTransition, sizeof(VERTEX_2D));

	pDevice->SetRenderState(D3DRS_STENCILENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

/**************************************
マスクテクスチャ読み込み処理
***************************************/
void BaseTransition::LoadMaskTexture(const char* path)
{
	D3DXCreateTextureFromFile(GetDevice(), path, &maskTexture);
}

/**************************************
トランジションテクスチャ読み込み処理
***************************************/
void BaseTransition::LoadTransitionTexture(const char* path)
{
	D3DXCreateTextureFromFile(GetDevice(), path, &transitionTexture);
}

/**************************************
頂点ワークセット処理
***************************************/
void BaseTransition::SetVertexMask()
{
	vtxMask[0].vtx.x = transform.pos.x - cosf(angle + transform.rot.z) * radius * transform.scale.x;
	vtxMask[0].vtx.y = transform.pos.y - sinf(angle + transform.rot.z) * radius * transform.scale.y;
	vtxMask[1].vtx.x = transform.pos.x + cosf(angle - transform.rot.z) * radius * transform.scale.x;
	vtxMask[1].vtx.y = transform.pos.y - sinf(angle - transform.rot.z) * radius * transform.scale.y;
	vtxMask[2].vtx.x = transform.pos.x - cosf(angle - transform.rot.z) * radius * transform.scale.x;
	vtxMask[2].vtx.y = transform.pos.y + sinf(angle - transform.rot.z) * radius * transform.scale.y;
	vtxMask[3].vtx.x = transform.pos.x + cosf(angle + transform.rot.z) * radius * transform.scale.x;
	vtxMask[3].vtx.y = transform.pos.y + sinf(angle + transform.rot.z) * radius * transform.scale.y;
}