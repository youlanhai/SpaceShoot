// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// 阵营类型
UENUM()
enum class ESPCamp : uint8
{
    // 中立。不参与任何战斗。
    Peace,

    // 攻击方
    Attack,

    // 防守方
    Defence,

    // 野怪方
    Enemy,

    // 自由阵营
    Free,
};

// 阵营关系
UENUM()
enum class ESPRelation : uint8
{
    None,
    Good,
    Bad,
};

// 获得两个阵营的关系
ESPRelation GetRelation(ESPCamp a, ESPCamp b);

// 两个阵营是否是敌对关系
bool IsRelationBad(ESPCamp a, ESPCamp b);

// 两个阵营是否是友好关系
bool IsRelationGood(ESPCamp a, ESPCamp b);
