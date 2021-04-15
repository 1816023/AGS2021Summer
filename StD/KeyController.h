#pragma once
#include <memory>
#include <array>

enum class KEY_TYPE
{
	NOW,		// 押した瞬間
	OLD,		// 押した後
	MAX
};

#define lpKeyController KeyController::GetInstance()

typedef std::array<char, 256> KEY_ARRAY;

class KeyController
{
public:
	static KeyController& GetInstance()
	{
		return (*s_Instans);
	}

	const KEY_ARRAY& GetCtl(KEY_TYPE type) const;	// キータイプの取得
	bool Update();		// アップデート関数
private:
	struct KeyDelete
	{
		void operator()(KeyController* keyController) const
		{
			delete keyController;
		}
	};

	KeyController();
	~KeyController();

	static std::unique_ptr<KeyController, KeyDelete> s_Instans;

	KEY_ARRAY data;			// 押した瞬間の処理
	KEY_ARRAY dataOld;		// 押した後の処理
};

