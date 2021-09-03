#pragma once
// 敵他ファイル共有ヘッダー

// 敵の種類
enum class EnemyType
{
	Circle,		// 円形の敵
	Pentagon,	// 五角形の敵
	Square,		// 四角形の敵
	Triangle,	// 三角形の敵
};
// ルートの向き
enum class RootDir
{
	UP,		// ↑
	DOWN,	// ↓
	RIGHT,	// →
	LEFT,	// ←
	MAX
};
// 敵のデータ
struct EnemyData
{
	EnemyType type;
	float spawnTime;
	int rootID;
	EnemyData() :type(EnemyType::Circle), spawnTime(0.0f), rootID(0) {};
	EnemyData(EnemyType t, float st, int id, int w = 1) :type(t), spawnTime(st), rootID(id) {};
};