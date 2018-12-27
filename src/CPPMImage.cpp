#include <CPPMImage.h>
#include <CVec3.h>
#include <CHitable.h>
#include <CHitableList.h>
#include <CSphere.h>
#include <CRay.h>
#include <math.h>
#include <iostream>

namespace
{
    static const unsigned int kSizeX = 200;
    static const unsigned int kSizeY = 100;

    static const CVec3 kLowerLeftCorner = CVec3(-2.0f, -1.0f, -1.0f);
    static const CVec3 kHorizontal      = CVec3(4.0f, 0.0f, 0.0f);
    static const CVec3 kVertical        = CVec3(0.0f, 2.0f, 0.0f);
    static const CVec3 kOrigin          = CVec3(0.0f, 0.0f, 0.0f);

    static const CVec3 kSphereCenter    = CVec3(0.f, 0.f, -1.f);

    static const int   kWorldSize       = 2;

    CVec3 Color(const CRay& aRay, CHitable *aWorld)
    {
        THitRecord lHit;
        // todo. cehck MAXFLOAT problem
        if (aWorld->Hit(aRay, 0.0, 999999.9f, lHit))
        {
            const CVec3 N = lHit.mNormal; 
            return 0.5f * CVec3(N.x() + 1.0f, N.y() + 1.0f, N.z() + 1.0f);
        }
        
        const CVec3 lUnitDirection = UnitVector(aRay.Direction());
        const float t = 0.5f * (lUnitDirection.y() + 1.0f);
        return (1.0f - t) * CVec3(1.0f, 1.0f, 1.0f) + t * CVec3(0.5f, 0.7f, 1.0f);
    }
}

void CPPMImage::PrintRGBImage() const
{
    const int lNx = kSizeX;
    const int lNy = kSizeY;
    std::cout << "P3\n" << lNx << ' ' << lNy << "\n255\n";

    CHitable *lList[kWorldSize];
    lList[0] = new CSphere(CVec3(kSphereCenter), 0.5f);
    lList[1] = new CSphere(CVec3(0.f, -100.5f, -1.f), 100);

    CHitable *lWorld = new CHitableList(lList, kWorldSize);

    for (int j = lNy - 1; j >= 0; j--)
    {
        for (int i = 0; i < lNx; ++i)
        {
            const float u = float(i) / float(lNx);
            const float v = float(j) / float(lNy);

            const CRay  lRay(kOrigin, kLowerLeftCorner + (u * kHorizontal) + (v * kVertical));
            const CVec3 lColor = Color(lRay, lWorld);

            const int iR = int(255.99 * lColor[0]);
            const int iG = int(255.99 * lColor[1]);
            const int iB = int(255.99 * lColor[2]);
            std::cout << iR << ' ' << iG << ' ' << iB << "\n"; 
        } 
    }

    // todo: delete news
}
