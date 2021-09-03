#pragma once
// �G���t�@�C�����L�w�b�_�[

// �G�̎��
enum class EnemyType
{
	Circle,		// �~�`�̓G
	Pentagon,	// �܊p�`�̓G
	Square,		// �l�p�`�̓G
	Triangle,	// �O�p�`�̓G
};
// ���[�g�̌���
enum class RootDir
{
	UP,		// ��
	DOWN,	// ��
	RIGHT,	// ��
	LEFT,	// ��
	MAX
};
// �G�̃f�[�^
struct EnemyData
{
	EnemyType type;
	float spawnTime;
	int rootID;
	EnemyData() :type(EnemyType::Circle), spawnTime(0.0f), rootID(0) {};
	EnemyData(EnemyType t, float st, int id, int w = 1) :type(t), spawnTime(st), rootID(id) {};
};