#pragma once
#include "../VECTOR2.h"
#include <string>
#include <vector>
#include <functional>

// UI整列位置enum
enum class Justified
{
	CENTER,
	CENTER_UP,
	CENTER_DOWN,
	CENTER_LEFT,
	LEFT_UP,
	LEFT_DOWN,
	CENTER_RIGHT,
	RIGHT_UP,
	RIGHT_DOWN
};
class UI;
struct UIStat;
class Canvas
{
public:
	Canvas(VECTOR2 pos, VECTOR2 size, int color = 0xffffff);
	Canvas(VECTOR2 pos, VECTOR2 size, std::wstring path);
	Canvas(VECTOR2 pos, VECTOR2 size, std::function<void(VECTOR2)> drawFunc);
	~Canvas();
	// ------- UIをキャンバスに追加する -------
	// IDから整列機能を使う
	void AddUIByID(UI* ui, Justified just, int id = -1);
	// IDから自分で座標設定をする
	void AddUIByID(UI* ui, VECTOR2& pos, int id = -1);
	// 名前から整列機能を使う
	void AddUIByName(UI* ui, Justified just, std::wstring name = L"");
	// 名前から自分で座標設定をする
	void AddUIByName(UI* ui, VECTOR2& pos, std::wstring name = L"");
	// ----------------------------------------
	// 名前からUIを取得
	UI* GetUIByName(std::wstring name);
	// IDからUIを取得
	UI* GetUIByName(int id);
	// キャンバスの色を設定
	void SetColor(int color);
	// 初期化
	void Init();
	// 描画
	void Draw();
	// キャンバス背景描画
	void BackDraw();
	// 更新
	void Update();
private:
	// UI位置の座標を返す
	VECTOR2 PosToJustified(const Justified& just, const VECTOR2& size);

	// -- UIのサイズを渡すと各並び揃えの座標を返す関数	--
	VECTOR2 Center(const VECTOR2& size);
	VECTOR2 Left(const VECTOR2& size);
	VECTOR2 Right(const VECTOR2& size);
	VECTOR2 Up(const VECTOR2& size);
	VECTOR2 Down(const VECTOR2& size);
	// ---------------------------------------------------

	VECTOR2 pos_;	// 左上座標
	VECTOR2 size_;	// 大きさ
	std::vector<UIStat>UIList_;	// UIのリスト
	int color_;		// 色
	int gHandle_;	// 画像ハンドル
	std::function<void(VECTOR2)> drawFunc_;	// 描画function #VECTOR2はoffset
};

