#ifndef _METAL_H_
#define _METAL_H_

#include <CMaterial.h>
#include <CVec3.h>
#include <CRay.h>

namespace
{
    CVec3 Reflect(const CVec3& v, const CVec3& n)
    {
        return v - 2.0f * dot(v, n) * n;
    }    
}

class CMetal : public CMaterial
{
public:
    CMetal(const CVec3& aAlbedo)
        : mAlbedo(aAlbedo)
    {}

    virtual bool Scatter(const CRay& aInRay, const THitRecord& aHit, CVec3& aAttenuation, CRay& aScattered) const
    {
        const CVec3 lReflected = Reflect( UnitVector(aInRay.Direction()), aHit.mNormal);
        aScattered          = CRay(aHit.mPoint, lReflected);
        aAttenuation        = mAlbedo;
        
        return (dot(aScattered.Direction(), aHit.mNormal) > 0.f);
    }

    CVec3 mAlbedo;
};

#endif // _METAL_H_