#ifndef _UIOBJECT_H_
#define _UIOBJECT_H_

// UI�p���N���X
class UIObject
{
protected:
	LPDIRECT3DTEXTURE9	D3DTexture;					// �e�N�X�`���̃|�C���^
	VERTEX_2D			vertexWk[NUM_VERTEX];		// ���_���i�[�\����
	D3DXVECTOR3			pos;						// ���W
	D3DXVECTOR3			size;						// �T�C�Y
	bool				use;						// �g�p�t���O

public:
	UIObject();
	~UIObject();

	virtual void Update() = 0;
	virtual void Draw() = 0;
};

#endif
