#pragma once
#include <memory>
#include <array>

enum class KEY_TYPE
{
	NOW,		// �������u��
	OLD,		// ��������
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

	const KEY_ARRAY& GetCtl(KEY_TYPE type) const;	// �L�[�^�C�v�̎擾
	bool Update();		// �A�b�v�f�[�g�֐�
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

	KEY_ARRAY data;			// �������u�Ԃ̏���
	KEY_ARRAY dataOld;		// ��������̏���
};

