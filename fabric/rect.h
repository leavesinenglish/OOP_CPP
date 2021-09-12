#pragma once
#include "point.h"

struct Rect {
    const void *class;
    struct Point *left_up_coord;
    struct Point *right_down_coord;
};


extern const void *Rect;
