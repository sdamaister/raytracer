#ifndef _HITABLE_H_
#define _HITABLE_H_

#include <CRay.h>

class CMaterial;

struct THitRecord
{
    THitRecord()
        : t(0)
        , mMaterial(0)
    {}

    float      t;
    CVec3      mPoint;
    CVec3      mNormal;
    CMaterial* mMaterial;
};

class CHitable
{
public:
    virtual bool Hit(const CRay& aRay, float t_min, float t_max, THitRecord& aHit) const = 0;

    // todo: virtual destructor
};

#endif // _HITABLE_H_