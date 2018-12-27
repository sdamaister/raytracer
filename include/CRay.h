#ifndef _RAY_H_
#define _RAY_H_

#include <CVec3.h>

class CRay
{
public:
    CRay() {}
    CRay(const CVec3& aOrigin, const CVec3& aDirection) { mOrigin = aOrigin; mDirection = aDirection; }
    
    CVec3 Origin    () const { return mOrigin;    }
    CVec3 Direction () const { return mDirection; } 
    
    CVec3 PointAtParameter(float t) const { return mOrigin + (t * mDirection); }

    CVec3 mOrigin;
    CVec3 mDirection;
};

#endif // _RAY_H_