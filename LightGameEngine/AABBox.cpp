/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#include "AABBox.h"

AABBox::AABBox(Vector3 min, Vector3 max)
{
    this->MinPos = min;
    this->MaxPos = max;
}
