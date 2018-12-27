#include <CHitableList.h>

bool CHitableList::Hit(const CRay& aRay, float t_min, float t_max, THitRecord& aHit) const
{
    THitRecord lHit;
    bool       lHitAnything = false;
    float      lClosestSoFar = t_max;
    
    for (int i = 0; i < mSize; ++i)
    {
        if (mList[i]->Hit(aRay, t_min, lClosestSoFar, lHit))
        {
            lHitAnything  = true;
            lClosestSoFar = lHit.t;
            aHit          = lHit;
        }
    }

    return lHitAnything;
}