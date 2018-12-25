#include <CPPMImage.h>
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
            const float r = float(i) / float(lNx);
            const float g = float(j) / float(lNy);
            const float b = 0.2;
            const int iR = int(255.99 * r);
            const int iG = int(255.99* g);
            const int iB = int(255.99 * b);
            std::cout << iR << ' ' << iG << ' ' << iB << "\n"; 
        } 
    }
}