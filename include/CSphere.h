#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <CHitable.h>

class CSphere : public CHitable
{
public:
    CSphere() {}
    CSphere(CVec3 aCenter, float aRadius)
        : mCenter(aCenter), mRadius(aRadius)
    {}

    virtual bool Hit(const CRay& aRay, float t_min, float t_max, THitRecord& aHit) const;

    CVec3 mCenter;
    float mRadius;
};

#endif //_SPHERE_H_