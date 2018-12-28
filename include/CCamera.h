#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <CRay.h>

namespace
{
    static const CVec3 kLowerLeftCorner = CVec3(-2.0f, -1.0f, -1.0f);
    static const CVec3 kHorizontal      = CVec3(4.0f, 0.0f, 0.0f);
    static const CVec3 kVertical        = CVec3(0.0f, 2.0f, 0.0f);
    static const CVec3 kOrigin          = CVec3(0.0f, 0.0f, 0.0f);
}

class CCamera
{
public:
    CCamera()
        : mOrigin(kOrigin)
        , mLowerLeftCorner(kLowerLeftCorner)
        , mHorizontal(kHorizontal)
        , mVertical(kVertical)
    {}

    CRay GetRay(float u, float v) const { return CRay( mOrigin, mLowerLeftCorner + (u * mHorizontal) + (v * mVertical)); }

    CVec3 mOrigin;
    CVec3 mLowerLeftCorner;
    CVec3 mHorizontal;
    CVec3 mVertical;
};

#endif // _CAMERA_H_