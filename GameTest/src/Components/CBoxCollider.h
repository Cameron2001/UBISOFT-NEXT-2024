//------------------------------------------------------------------------
// CBoxCollider.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../Util/Vectors.h"

//------------------------------------------------------------------------
struct CBoxCollider
{
    vec2 extents;
    vec2 offset;

    CBoxCollider(
        const vec2 extents,
        const vec2 offset = {0.0f, 0.0f}
    ):
        extents(extents),
        offset(offset)
    {
    }
};
