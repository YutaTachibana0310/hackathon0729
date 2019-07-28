//=====================================
//
//ベーストランジションヘッダ[BaseTransition.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASETRANSITION_H_
#define _BASETRANSITION_H_

#include "../main.h"
#include <functional>

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class BaseTransition
{
public:
	BaseTransition();
	virtual ~BaseTransition();

	virtual void Update() = 0;

	virtual void DrawMask();

	virtual void DrawTransition();

	virtual void SetTransition(bool isStart, std::function<void(void)> func = NULL) = 0;

	void LoadMaskTexture(const char* path);
	void LoadTransitionTexture(const char* path);

protected:
	bool enableMask;
	bool enableTransition;

	bool isTransitionOut;

	LPDIRECT3DTEXTURE9 maskTexture, transitionTexture;
	VERTEX_2D vtxMask[NUM_VERTEX], vtxTransition[NUM_VERTEX];
	Transform transform;

	float radius, angle;

	void SetVertexMask();

	std::function<void(void)> callback;

	virtual void BeginMask();
	virtual void EndMask();
};

#endif