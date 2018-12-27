#include <CSphere.h>


bool CSphere::Hit(const CRay& aRay, float t_min, float t_max, THitRecord& aHit) const
{
    const CVec3 OC = aRay.Origin() - mCenter;
        
    const float a = dot(aRay.Direction(), aRay.Direction());
    const float b = dot(OC, aRay.Direction());
    const float c = dot(OC, OC) - (mRadius * mRadius);
      
    const float lDiscriminant = b*b - a*c;

    if(lDiscriminant > 0.f)
    {
        float temp = (-b - sqrt(lDiscriminant))/a;
        if (temp < t_max && temp > t_min)
        {
            aHit.t       = temp;
            aHit.mPoint  = aRay.PointAtParameter(aHit.t);
            aHit.mNormal = (aHit.mPoint - mCenter) / mRadius;
            return true;
        }
        temp = (-b + sqrt(lDiscriminant))/a;
        if (temp < t_max && temp > t_min)
        {
            aHit.t       = temp;
            aHit.mPoint  = aRay.PointAtParameter(aHit.t);
            aHit.mNormal = (aHit.mPoint - mCenter) / mRadius;
            return true;
        }
    }

    return false;
}