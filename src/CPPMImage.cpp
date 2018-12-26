#include <CPPMImage.h>
#include <CVec3.h>
#include <iostream>

namespace
{
    static const unsigned int kSizeX = 256;
    static const unsigned int kSizeY = 256;
}

void CPPMImage::PrintRGBImage() const
{
    int lNx = kSizeX;
    int lNy = kSizeY;
    std::cout << "P3\n" << lNx << ' ' << lNy << "\n255\n";
    for (int j = lNy - 1; j >= 0; j--)
    {
        for (int i = 0; i < lNx; ++i)
        {
            const CVec3 lColor(float(i) / float(lNx), float(j) / float(lNy), 0.2f);
            const int iR = int(255.99 * lColor[0]);
            const int iG = int(255.99 * lColor[1]);
            const int iB = int(255.99 * lColor[2]);
            std::cout << iR << ' ' << iG << ' ' << iB << "\n"; 
        } 
    }
}