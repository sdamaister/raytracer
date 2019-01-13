#ifndef _LAMBERTIAN_H_
#define _LAMBERTIAN_H_

#include <CMaterial.h>
#include <CVec3.h>
#include <CRay.h>

namespace
{
    CVec3 RandomInUnitSphere()
    {
        CVec3 p;
        do
        {
            p = 2.0f *CVec3(drand48(), drand48(), drand48()) - CVec3(1.f, 1.f, 1.f);
        } while (p.SquaredLength() >= 1.0f);

        return p;
    }    
}

class CLambertian : public CMaterial
{
public:
    CLambertian(const CVec3& aAlbedo)
        : mAlbedo(aAlbedo)
    {}

    virtual bool Scatter(const CRay& aInRay, const THitRecord& aHit, CVec3& aAttenuation, CRay& aScattered) const
    {
        aInRay;
        const CVec3 lTarget = aHit.mPoint + aHit.mNormal + RandomInUnitSphere();
        aScattered          = CRay(aHit.mPoint, lTarget - aHit.mPoint);
        aAttenuation        = mAlbedo;

        return true;
    }

    CVec3 mAlbedo;
};

#endif // _LAMBERTIAN_H_