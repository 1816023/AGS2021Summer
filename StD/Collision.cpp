#include "Collision.h"

Collision::~Collision()
{
}

const bool Collision::CvC(Vec2Float pos, float r, Vec2Float pos2, float r2)
{
    //�O�����̒藝���g�p���������蔻��(�~�Ɖ~)
    Vec2Float ab = Vec2Float(std::abs(pos.x - pos2.x), std::abs(pos.y - pos.y));
    float c = std::sqrt((ab.x * ab.x) + (ab.y * ab.y));
    if (c + (r2 * 2) <= (r + r2))
    {
        return true;
    }
    return false;
}

Collision::Collision()
{
}
