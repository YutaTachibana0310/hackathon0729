//=====================================
//
//ボックスコライダー3Dヘッダ[BoxCollider3D.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOXCOLLIDER3D_H_
#define _BOXCOLLIDER3D_H_

#include "../main.h"
#include "ObserveSubject.h"

#include <map>
#include <list>

#define BOXCOLLIDER3D_USE_DEBUG

/**************************************
BoxCollider3DTag列挙子
***************************************/
enum class BoxCollider3DTag
{
	Player,
	Enemy,
	PlayerAttack,
	Max
};

/**************************************
BoxCollider3Dクラス
***************************************/
class BoxCollider3D : public ObserveSubject
{
public:
	friend class BoxCollider3D;

	//コンストラクタ、デストラクタ
	BoxCollider3D(BoxCollider3DTag tag, D3DXVECTOR3 *pPos);
	BoxCollider3D(BoxCollider3DTag tag, D3DXVECTOR3 *pPos, D3DXVECTOR3 size);
	~BoxCollider3D();

	//衝突判定、サイズセット、座標アドレスセット
	bool CheckCollision(BoxCollider3D *other);
	void SetSize(D3DXVECTOR3 size);
	void SetPosAddress(D3DXVECTOR3 *pPos);

	//衝突判定
	static void UpdateCollision();
	void RegisterToCheckList();
	void RemoveFromCheckList();

	//アクティブ判定
	bool active;

	//ヒットしているかどうか（ハッカソン用に一時的に追加）
	bool isHit;

#ifdef BOXCOLLIDER3D_USE_DEBUG
	//デバッグ用描画処理
	static void DrawCollider(BoxCollider3D *collider);
#endif

private:
	BoxCollider3D() {}

	BoxCollider3DTag tag;	//タグ
	D3DXVECTOR3 *pPos;		//親の座標アドレス
	D3DXVECTOR3 size;		//サイズ
	D3DXVECTOR3 offset;		//オフセット

	static std::map<BoxCollider3DTag, std::list<BoxCollider3D*>> checkDictionary;


#ifdef BOXCOLLIDER3D_USE_DEBUG
	static UINT instanceCount;		//インスタンスカウント
	static D3DMATERIAL9 material;	//描画用マテリアル
	static LPD3DXMESH mesh;			//描画用メッシュ
#endif
};
#endif