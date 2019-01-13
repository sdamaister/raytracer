#include <CPPMImage.h>
#include <CVec3.h>
#include <CHitable.h>
#include <CHitableList.h>
#include <CSphere.h>
#include <CRay.h>
#include <CCamera.h>
#include <CMaterial.h>
#include <CLambertian.h>
#include <CMetal.h>
#include <math.h>
#include <fstream>
#include <RandUtils.h>

namespace
{
    static const unsigned int kSizeX   = 400;
    static const unsigned int kSizeY   = 200;
    static const unsigned int kSamples = 100;

    static const CVec3 kSphereCenter    = CVec3(0.f, 0.f, -1.f);

    static const int   kWorldSize       = 4;

    CVec3 Color(const CRay& aRay, CHitable *aWorld, int aDepth)
    {
        THitRecord lHit;
        // todo. cehck MAXFLOAT problem
        if (aWorld->Hit(aRay, 0.0001f, 999999.9f, lHit))
        {
            CRay lScattered;
            CVec3 lAttenuation;
            if (aDepth < 50 && lHit.mMaterial->Scatter(aRay, lHit, lAttenuation, lScattered))
            {
                return lAttenuation * Color(lScattered, aWorld, aDepth + 1);
            }
            else
            {
                return CVec3(0.f, 0.f, 0.f);
            }
        }
        
        const CVec3 lUnitDirection = UnitVector(aRay.Direction());
        const float t = 0.5f * (lUnitDirection.y() + 1.0f);
        return (1.0f - t) * CVec3(1.0f, 1.0f, 1.0f) + t * CVec3(0.5f, 0.7f, 1.0f);
    }
}

void CPPMImage::PrintRGBImage() const
{
    std::ofstream lOutputFile("image.ppm");
    if (lOutputFile)
    {
        const int lNx = kSizeX;
        const int lNy = kSizeY;
        const int lNs = kSamples;

        lOutputFile << "P3\n" << lNx << ' ' << lNy << "\n255\n";

        CHitable *lList[kWorldSize];
        CLambertian* lMaterial1 = new CLambertian(CVec3(0.8f, 0.3f, 0.3f));
        lList[0] = new CSphere(CVec3(kSphereCenter), 0.5f, lMaterial1);
        CLambertian* lMaterial2 = new CLambertian(CVec3(0.8f, 0.8f, 0.0f));
        lList[1] = new CSphere(CVec3(0.f, -100.5f, -1.f), 100.0f, lMaterial2);
        CMetal* lMaterial3 = new CMetal(CVec3(0.8f, 0.6f, 0.2f), 0.3f);
        lList[2] = new CSphere(CVec3(1.f, 0.f, -1.f), 0.5f, lMaterial3);
        CMetal* lMaterial4 = new CMetal(CVec3(0.8f, 0.8f, 0.8f), 1.0f);
        lList[3] = new CSphere(CVec3(-1.f, 0.f, -1.f), 0.5f, lMaterial4);

        CHitable *lWorld = new CHitableList(lList, kWorldSize);
        CCamera lCamera;

        for (int j = lNy - 1; j >= 0; j--)
        {
            for (int i = 0; i < lNx; ++i)
            {
                CVec3 lColor(0.f, 0.f, 0.f);
                for (int s = 0; s < lNs; ++s)
                {
                    const float u = float(i + Rand()) / float(lNx);
                    const float v = float(j + Rand()) / float(lNy);

                    const CRay  lRay = lCamera.GetRay(u, v);
                    lColor += Color(lRay, lWorld, 0);
                }

                lColor /= float(lNs);
                lColor = CVec3(sqrt(lColor[0]), sqrt(lColor[1]), sqrt(lColor[2]));

                const int iR = int(255.99 * lColor[0]);
                const int iG = int(255.99 * lColor[1]);
                const int iB = int(255.99 * lColor[2]);
                lOutputFile << iR << ' ' << iG << ' ' << iB << "\n";
            }
        }

        delete lMaterial1;
        delete lMaterial2;
        delete lMaterial3;
        delete lMaterial4;

        for (int i = 0; i < kWorldSize; ++i)
        {
            delete lList[i];
        }

        delete lWorld;
    }
    else
    {
        std::cerr << "Failure oppening 'image.ppm'" << '\n';
    }
}
