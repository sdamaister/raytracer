#ifndef _MATH_UTILS_H_
#define _MATH_UTILS_H_

CVec3 Reflect(const CVec3& v, const CVec3& n)
{
    return v - 2.0f * dot(v, n) * n;
}

bool Refract(const CVec3& aVec, const CVec3& aNormal, float aNiOverNt, CVec3& aRefracted)
{
    CVec3 lUv = UnitVector(aVec);

    const float lDt = dot(lUv, aNormal);
    const float lDiscriminant = 1.f - (aNiOverNt * aNiOverNt) * (1.f - (lDt*lDt));
    if (lDiscriminant > 0.f)
    {
        aRefracted = (aNiOverNt * (lUv - (aNormal * lDt))) - (aNormal * sqrt(lDiscriminant));
        return true;
    }

    return false;
}

#endif // _MATH_UTILS_H_
