#include <stdio.h>
#include "line.h"
#include "new.h"

static void *Line_ctor(void *_self, va_list *app) {
    struct Line *self = (struct Line*) _self;
    int x = va_arg(*app, int);
    int y = va_arg(*app, int);
    self->first = new(Point, x, y);
    x = va_arg(*app, int);
    y = va_arg(*app, int);
    self->second = new(Point, x, y);
    return self;
}

static void *Line_dtor(void *_self){
    struct  Line *self = (struct Line*) _self;
    delete(self->first);
    delete(self->second);
    return self;
}

static void Line_draw(const void * _self){
    const struct Line *self = _self;
    if (self->first->x == self->second->x && self->first->y == self->second->y)
        return;
    printf("line through (%d,%d) and (%d, %d)\n", self->first->x, self->first->y,
           self->second->x, self->second->y);
}

// Описание класса Line
static const struct Class _Line = {
        sizeof(struct Line),
        Line_ctor,
        Line_dtor,
        Line_draw
};

// Объявление глобального указателя на _Line, который и будет представлять
// собой класс Line для пользователей (служить аргументом для функции new).
const void *Line = &_Line;