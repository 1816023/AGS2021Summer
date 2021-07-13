#include "Player.h"
#include "PlayerMng.h"

void Player::Init()
{
	statusOpen = false;
}

void Player::Update(float deltaTime)
{
	if (!executable)
	{
		coolTime_--;
	}
	else
	{
		coolTime_++;
	}
}

void Player::StatusDraw(Vec2Float pos)
{
	DrawFormatString(pos.x, pos.y, 0xffffff, L"ID:%s", unitData.name);
	DrawFormatString(pos.x, pos.y+16, 0xffffff, L"Lv:%d", unitData.lv);
	DrawFormatString(pos.x, pos.y+32, 0xffffff, L"HP:%d", unitData.stat.life);
	DrawFormatString(pos.x, pos.y+48, 0xffffff, L"çUåÇóÕ:%d", unitData.stat.power);
}

void Player::Draw()
{
}

void Player::LevelShift(int num)
{
	unitData.lv += num;
	auto mag = 1.0 + (0.1 * num);
	unitData.stat.power = (unitData.stat.power * mag) + 0.5;
}

void Player::SetExecutable(bool flag)
{
	executable = flag;
}

void Player::SetStatusOpen(bool flag)
{
	statusOpen = flag;
}

void Player::SetPosition(Vec2Float pos)
{
	unitData.stat.pos = pos;
}

void Player::SetHP(int power)
{
	unitData.stat.power = power;
}
