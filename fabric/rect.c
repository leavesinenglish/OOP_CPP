#include <stdio.h>
#include "rect.h"
#include "new.h"

static void *Rect_ctor(void *_self, va_list *app) {
    struct Rect *self = (struct Rect*) _self;
    int x = va_arg(*app, int);
    int y = va_arg(*app, int);
    self->left_up_coord = new(Point, x, y);
    x = va_arg(*app, int);
    y = va_arg(*app, int);
    self->right_down_coord = new(Point, x, y);
    return self;
}

static void *Rect_dtor(void* _self){
    struct Rect *self = (struct Rect*) _self;
    delete(self->right_down_coord);
    delete(self->left_up_coord);
    return self;
}

static void Rect_draw(const void * _self){
    const struct Rect *self = _self;
    if (self->left_up_coord->x == self->right_down_coord->x && self->left_up_coord->y == self->right_down_coord->y)
        return;
    printf("rectangle at (%d, %d) and (%d, %d)\n", self->left_up_coord->x, self->left_up_coord->y,
                                                            self->right_down_coord->x, self->right_down_coord->y);
}


static const struct Class _Rect = {
    sizeof(struct Rect),
    Rect_ctor,
    Rect_dtor,
    Rect_draw
};


const void *Rect = &_Rect;