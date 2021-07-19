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

using keyArray = std::array<char, 256>;

class KeyController
{
public:
	static KeyController& GetInstance()
	{
		return (*s_Instans);
	}

	const keyArray& GetCtl(KEY_TYPE type) const;	// キータイプの取得
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

	keyArray data;			// 押した瞬間の処理
	keyArray dataOld;		// 押した後の処理
};

