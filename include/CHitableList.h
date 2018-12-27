#ifndef _HITABLE_LIST_H_
#define _HITABLE_LIST_H_

#include <CHitable.h>

class CHitableList : public CHitable
{
public:
    CHitableList() {}
    CHitableList(CHitable **aList, int aSize) { mList = aList; mSize = aSize; }

    virtual bool Hit(const CRay& aRay, float t_min, float t_max, THitRecord& aHit) const;

    CHitable **mList;
    int        mSize;
};

#endif // _HITABLE_LIST_H_