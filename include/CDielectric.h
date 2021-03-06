#ifndef __DIELECTRIC_H__
#define __DIELECTRIC_H__

#include <CMaterial.h>
#include <MathUtils.h>

class CDielectric : public CMaterial
{
public:

    CDielectric(float aRefractIdx) : mRefractIdx(aRefractIdx) {}
    
    virtual bool Scatter(const CRay& aInRay, const THitRecord& aHit, CVec3& aAttenuation, CRay& aScattered) const
    {
        CVec3 lOutwardNormal;
        CVec3 lReflected = Reflect(aInRay.Direction(), aHit.mNormal);

        float lNiOverNt;
        aAttenuation = CVec3(1.f, 1.f, 1.f);
        CVec3 lRefracted;

        float lReflectedProb;
        float lCos;

        if (dot(aInRay.Direction(), aHit.mNormal) > 0.f)
        {
            lOutwardNormal = -aHit.mNormal;
            lNiOverNt      = mRefractIdx;
            lCos           = mRefractIdx * dot(aInRay.Direction(), aHit.mNormal) / aInRay.Direction().Length();
        }
        else
        {
            lOutwardNormal = aHit.mNormal;
            lNiOverNt      = 1.0f / mRefractIdx;
            lCos           = -dot(aInRay.Direction(), aHit.mNormal) / aInRay.Direction().Length();
        }

        if (Refract(aInRay.Direction(), lOutwardNormal, lNiOverNt, lRefracted))
        {
            lReflectedProb = Schlick(lCos, mRefractIdx);
        }
        else
        {
            lReflectedProb = 1.0f;
        }

        if (Rand() < lReflectedProb)
        {
            aScattered = CRay(aHit.mPoint, lReflected);
        }
        else
        {
            aScattered = CRay(aHit.mPoint, lRefracted);
        }

        return true;
    }

    float mRefractIdx;
};


#endif // ! __DIELECTRIC_H__
