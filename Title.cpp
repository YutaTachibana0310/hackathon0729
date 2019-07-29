//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 名和 遼汰朗
//
//=============================================================================
#include "Title.h"
#include "input.h"
#include "Game.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TITLE		"data/TEXTURE/title001.png"		// 読み込むテクスチャファイル名
#define	TEXTURE_TITLE_LOGO	"data/TEXTURE/logo001.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_LOGO_START	"data/TEXTURE/start.png"	// 読み込むテクスチャファイル名

#define	TITLE_LOGO_POS_X		(450)		// タイトルロゴの位置(X座標)
#define	TITLE_LOGO_POS_Y		(200)		// タイトルロゴの位置(Y座標)
#define	TITLE_LOGO_WIDTH		(1000)		// タイトルロゴの幅
#define	TITLE_LOGO_HEIGHT		(250)		// タイトルロゴの高さ

#define	START_POS_X				(800)		// スタートボタンの位置(X座標)
#define	START_POS_Y				(700)		// スタートボタンの位置(Y座標)
#define	START_WIDTH				(280)		// スタートボタンの幅
#define	START_HEIGHT			(100)		// スタートボタンの高さ

#define	COUNT_APPERA_START		(60)		// スタートボタン出現までの時間
#define	INTERVAL_DISP_START		(60)		// スタートボタン点滅の時間

#define	COUNT_WAIT_DEMO			(60 * 5)	// デモまでの待ち時間

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTitle(LPDIRECT3DDEVICE9 Device);
void SetColorTitleLogo(void);
void SetColorTitleLogoStart(void);

void FillVertexTitle();
void FillVertexTitleLogo();
void FillVertexStart();

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureTitle = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffTitle = NULL;		// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		D3DTextureTitleLogo = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffTitleLogo = NULL;		// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		D3DTextureStart = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffStart = NULL;		// 頂点バッファインターフェースへのポインタ
int						CountAppearStart = 0;		
float					AlphaLogo = 0.0f;		
float					AlphaLogoStart = 0.0f;		
int						CountDisp = 0;			
bool					DispStart = false;		

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	CountAppearStart = 0;
	AlphaLogo = 0.0f;
	CountDisp = 0;
	DispStart = false;

	// 頂点情報の作成
	MakeVertexTitle(Device);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,						// デバイスへのポインタ
								TEXTURE_TITLE,				// ファイルの名前
								&D3DTextureTitle);		// 読み込むメモリー

	D3DXCreateTextureFromFile(Device,						// デバイスへのポインタ
		TEXTURE_TITLE_LOGO,			// ファイルの名前
		&D3DTextureTitleLogo);	// 読み込むメモリー


	D3DXCreateTextureFromFile(Device,						// デバイスへのポインタ
		TEXTURE_LOGO_START,			// ファイルの名前
		&D3DTextureStart);		// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	if(D3DTextureTitle != NULL)
	{// テクスチャの開放
		D3DTextureTitle->Release();
		D3DTextureTitle = NULL;
	}

	if(D3DVtxBuffTitle != NULL)
	{// 頂点バッファの開放
		D3DVtxBuffTitle->Release();
		D3DVtxBuffTitle = NULL;
	}

	if (D3DTextureTitleLogo != NULL)
	{// テクスチャの開放
		D3DTextureTitleLogo->Release();
		D3DTextureTitleLogo = NULL;
	}

	if (D3DVtxBuffTitleLogo != NULL)
	{// 頂点バッファの開放
		D3DVtxBuffTitleLogo->Release();
		D3DVtxBuffTitleLogo = NULL;
	}

	if (D3DTextureStart != NULL)
	{// テクスチャの開放
		D3DTextureStart->Release();
		D3DTextureStart = NULL;
	}

	if (D3DVtxBuffStart != NULL)
	{// 頂点バッファの開放
		D3DVtxBuffStart->Release();
		D3DVtxBuffStart = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{

	if (AlphaLogo < 1.0f)
	{
		AlphaLogo += 0.005f;
		if (AlphaLogo >= 1.0f)
		{
			AlphaLogo = 1.0f;
		}
		SetColorTitleLogo();
	}
	else
	{
		CountAppearStart++;
		if (CountAppearStart > COUNT_APPERA_START)
		{
			CountDisp = (CountDisp + 1) % 80;
			if (CountDisp > INTERVAL_DISP_START)
			{
				DispStart = false;
			}
			else
			{
				DispStart = true;
			}
		}
	}

	if (AlphaLogoStart < 1.0f)
	{
		AlphaLogoStart += 0.010f;
		if (AlphaLogoStart >= 1.0f)
		{
			AlphaLogoStart--;
		}
		SetColorTitleLogoStart();
	}

#if 0

	if (GetKeyboardTrigger(DIK_SPACE))
	{
		ChangeScene(SceneResult);

	}

#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, D3DVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTextureTitle);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);


	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, D3DVtxBuffTitleLogo, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTextureTitleLogo);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//if(DispStart == true)
	//{
		// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, D3DVtxBuffStart, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTextureStart);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	//}


}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice)
{

	// タイトル
	//// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
												FVF_VERTEX_2D,				// 使用する頂点フォーマット
												D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
												&D3DVtxBuffTitle,		// 頂点バッファインターフェースへのポインタ
												NULL)))						// NULLに設定
	{
        return E_FAIL;
	}

	//頂点バッファの中身を埋める
	FillVertexTitle();

	// タイトルロゴ
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&D3DVtxBuffTitleLogo,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	//頂点バッファの中身を埋める
	FillVertexTitleLogo();


	// スタートアイコン
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&D3DVtxBuffStart,			// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	//頂点バッファの中身を埋める
	FillVertexStart();


	return S_OK;
}

//=============================================================================
//	TitleLogoの色セット
//=============================================================================
void SetColorTitleLogo(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);

		// 頂点データをアンロックする
		D3DVtxBuffTitleLogo->Unlock();
	}

}

void SetColorTitleLogoStart(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuffStart->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogoStart);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogoStart);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogoStart);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogoStart);

		// 頂点データをアンロックする
		D3DVtxBuffStart->Unlock();
	}

}

//=============================================================================
// 頂点バッファの中身を埋める
//=============================================================================
// タイトル
void FillVertexTitle()
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		D3DVtxBuffTitle->Unlock();
	}

}

// タイトルロゴ
void FillVertexTitleLogo()
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(TITLE_LOGO_POS_X, TITLE_LOGO_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(TITLE_LOGO_POS_X + TITLE_LOGO_WIDTH, TITLE_LOGO_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(TITLE_LOGO_POS_X, TITLE_LOGO_POS_Y + TITLE_LOGO_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(TITLE_LOGO_POS_X + TITLE_LOGO_WIDTH, TITLE_LOGO_POS_Y + TITLE_LOGO_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		D3DVtxBuffTitleLogo->Unlock();
	}


}

// スタート
void FillVertexStart()
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuffStart->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(START_POS_X, START_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(START_POS_X + START_WIDTH, START_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(START_POS_X, START_POS_Y + START_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(START_POS_X + START_WIDTH, START_POS_Y + START_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogoStart);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogoStart);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogoStart);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogoStart);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		D3DVtxBuffStart->Unlock();
	}


}