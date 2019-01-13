#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <CHitable.h>

class CMaterial;

class CSphere : public CHitable
{
public:
    CSphere() {}
    CSphere(CVec3 aCenter, float aRadius, const CMaterial* aMaterial)
        : mCenter(aCenter), mRadius(aRadius), mMaterial(aMaterial)
    {}

    virtual bool Hit(const CRay& aRay, float t_min, float t_max, THitRecord& aHit) const;

    CVec3            mCenter;
    float            mRadius;
    const CMaterial* mMaterial;
};

#endif //_SPHERE_H_