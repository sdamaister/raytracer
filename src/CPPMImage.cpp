#include <CPPMImage.h>
#include <CVec3.h>
#include <CHitable.h>
#include <CHitableList.h>
#include <CSphere.h>
#include <CRay.h>
#include <CCamera.h>
#include <math.h>
#include <iostream>

namespace
{
    static const unsigned int kSizeX   = 400;
    static const unsigned int kSizeY   = 200;
    static const unsigned int kSamples = 100;

    static const CVec3 kSphereCenter    = CVec3(0.f, 0.f, -1.f);

    static const int   kWorldSize       = 2;

    CVec3 RandomInUnitSphere()
    {
        CVec3 p;
        do
        {
            p = 2.0f *CVec3(drand48(), drand48(), drand48()) - CVec3(1.f, 1.f, 1.f);
        } while (p.SquaredLength() >= 1.0f);

        return p;
    }

    CVec3 Color(const CRay& aRay, CHitable *aWorld)
    {
        THitRecord lHit;
        // todo. cehck MAXFLOAT problem
        if (aWorld->Hit(aRay, 0.0001, 999999.9f, lHit))
        {
            CVec3 lTarget = lHit.mPoint + lHit.mNormal + RandomInUnitSphere();
            return 0.5f * Color( CRay(lHit.mPoint, lTarget - lHit.mPoint), aWorld );
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
    const int lNs = kSamples;

    std::cout << "P3\n" << lNx << ' ' << lNy << "\n255\n";

    CHitable *lList[kWorldSize];
    lList[0] = new CSphere(CVec3(kSphereCenter), 0.5f);
    lList[1] = new CSphere(CVec3(0.f, -100.5f, -1.f), 100);

    CHitable *lWorld = new CHitableList(lList, kWorldSize);
    CCamera lCamera;

    for (int j = lNy - 1; j >= 0; j--)
    {
        for (int i = 0; i < lNx; ++i)
        {
            CVec3 lColor(0.f, 0.f, 0.f);
            for(int s = 0; s < lNs; ++s)
            {
                const float u = float(i + drand48()) / float(lNx);
                const float v = float(j + drand48()) / float(lNy);

                const CRay  lRay = lCamera.GetRay(u, v);
                lColor          += Color(lRay, lWorld);
            }

            lColor /= float(lNs);
            lColor  = CVec3(sqrt(lColor[0]), sqrt(lColor[1]), sqrt(lColor[2]));

            const int iR = int(255.99 * lColor[0]);
            const int iG = int(255.99 * lColor[1]);
            const int iB = int(255.99 * lColor[2]);
            std::cout << iR << ' ' << iG << ' ' << iB << "\n"; 
        } 
    }

    // todo: delete news
}
