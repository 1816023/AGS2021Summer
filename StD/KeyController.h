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

using keyArray = std::array<char, 256>;

class KeyController
{
public:
	static KeyController& GetInstance()
	{
		return (*s_Instans);
	}

	const keyArray& GetCtl(KEY_TYPE type) const;	// �L�[�^�C�v�̎擾
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

	keyArray data;			// �������u�Ԃ̏���
	keyArray dataOld;		// ��������̏���
};

