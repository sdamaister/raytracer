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
    CMetal(const CVec3& aAlbedo, float aFuzz)
        : mAlbedo(aAlbedo)
    {
        if (aFuzz < 1.0f)
        {
            mFuzz = aFuzz;
        }
        else
        {
            mFuzz = 1.f;
        }
    }

    virtual bool Scatter(const CRay& aInRay, const THitRecord& aHit, CVec3& aAttenuation, CRay& aScattered) const
    {
        const CVec3 lReflected = Reflect(UnitVector(aInRay.Direction()), aHit.mNormal);
        aScattered = CRay(aHit.mPoint, lReflected + mFuzz * RandomInUnitSphere());
        aAttenuation = mAlbedo;

        return (dot(aScattered.Direction(), aHit.mNormal) > 0.f);
    }

    CVec3 mAlbedo;
    float mFuzz;
};

#endif // _METAL_H_ 
