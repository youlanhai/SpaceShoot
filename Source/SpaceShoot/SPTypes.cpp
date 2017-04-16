// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShoot.h"
#include "SPTypes.h"

ESPRelation GetRelation(ESPCamp a, ESPCamp b)
{
    if (a == ESPCamp::Peace || b == ESPCamp::Peace)
        return ESPRelation::None;

    if (a == ESPCamp::Free || b == ESPCamp::Free)
        return ESPRelation::Bad;

    if (a != b)
        return ESPRelation::Bad;

    return ESPRelation::Good;
}

bool IsRelationBad(ESPCamp a, ESPCamp b)
{
    return GetRelation(a, b) == ESPRelation::Bad;
}

bool IsRelationGood(ESPCamp a, ESPCamp b)
{
    return GetRelation(a, b) == ESPRelation::Good;
}
