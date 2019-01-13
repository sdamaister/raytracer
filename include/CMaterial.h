#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <CRay.h>
#include <CHitable.h>

class CMaterial
{
public:
    virtual bool Scatter(const CRay& aInRay, const THitRecord& aHit, CVec3& aAttenuation, CRay& aScattered) const = 0;
};


#endif // _MATERIAL_H_ 