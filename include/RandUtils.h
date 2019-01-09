#ifndef _RAND_UTILS_H_
#define _RAND_UTILS_H_

#include <random>

namespace
{
    std::random_device                    kRandomDevice;
    std::mt19937                          kGenerator(kRandomDevice());
    std::uniform_real_distribution<float> kDistribution(0.f, 1.f);
}

float Rand()
{
    return kDistribution(kGenerator);
}

#endif // _RAND_UTILS_H_
