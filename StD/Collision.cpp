#include <numeric>
#include "Collision.h"

Collision::~Collision()
{
}

const bool Collision::CvC(Vec2Float pos, float r, Vec2Float pos2, float r2)
{
    //ŽO•½•û‚Ì’è—‚ðŽg—p‚µ‚½“–‚½‚è”»’è(‰~‚Æ‰~)
    auto h = (pos.y - pos2.y);
    auto g = (pos.x - pos2.x);
    auto hypot = std::sqrtf(h * h + g * g);
    if (r+r2 >= hypot)
    {
        return true;
    }
    return false;
}

const bool Collision::CvB(Vec2Float pos,float r, Vec2Float pos2,Vec2Float sizeHalf)
{
    if ((pos.x > pos2.x -r - sizeHalf.x) && (pos.y > pos2.y) 
        && (pos.x < pos2.x + r + sizeHalf.x) && (pos.y < pos2.y+r+sizeHalf.y))
    {
        return true;
    }
    return false;
}

Collision::Collision()
{
}
