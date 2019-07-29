#ifndef _UIOBJECT_H_
#define _UIOBJECT_H_

// UI用基底クラス
class UIObject
{
protected:
	LPDIRECT3DTEXTURE9	D3DTexture;					// テクスチャのポインタ
	VERTEX_2D			vertexWk[NUM_VERTEX];		// 頂点情報格納構造体
	D3DXVECTOR3			pos;						// 座標
	D3DXVECTOR3			size;						// サイズ
	bool				use;						// 使用フラグ

public:
	UIObject();
	~UIObject();

	virtual void Update() = 0;
	virtual void Draw() = 0;
};

#endif
