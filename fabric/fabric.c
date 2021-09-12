#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "new.h"
#include "fabric.h"
#include "point.h"
#include "circle.h"
#include "line.h"
#include "rect.h"

enum shape {
    POINT = 0,
    CIRCLE,
    LINE,
    RECTANGLE,
    SHAPES_AMOUNT,
    NAMELESS = -1
};

static void *identify_point_params(parameters *point_params){
    char* end;
    point_params->fragments = calloc(2, sizeof(int));
    point_params->fragments[0] = (void *) strtol(strtok(NULL, " "), &end, 0); //x1
    point_params->fragments[1] = (void *) strtol(strtok(NULL, " "), &end, 0); //y1
    return point_params;
}

static void *identify_circle_params(parameters *circle_params){
    char* end;
    circle_params->fragments = calloc(3, sizeof(int));
    circle_params->fragments[0] = (void *) strtol(strtok(NULL, " "), &end, 0); //x1
    circle_params->fragments[1] = (void *) strtol(strtok(NULL, " "), &end, 0); //y1
    circle_params->fragments[2] = (void *) strtol(strtok(NULL, " "), &end, 0); //rad
    return circle_params;
}

static void *identify_line_params(parameters *line_params){
    char* end;
    line_params->fragments = calloc(4, sizeof(int));
    line_params->fragments[0] = (void *) strtol(strtok(NULL, " "), &end, 0); //x1
    line_params->fragments[1] = (void *) strtol(strtok(NULL, " "), &end, 0); //y1
    line_params->fragments[2] = (void *) strtol(strtok(NULL, " "), &end, 0); //x2
    line_params->fragments[3] = (void *) strtol(strtok(NULL, " "), &end, 0); //y2
    return line_params;
}

static void *identify_rect_params(parameters *rect_params){
    char* end;
    rect_params->fragments = calloc(4, sizeof(int));
    rect_params->fragments[0] = (void *) strtol(strtok(NULL, " "), &end, 0); //x1
    rect_params->fragments[1] = (void *) strtol(strtok(NULL, " "), &end, 0); //y1
    rect_params->fragments[2] = (void *) strtol(strtok(NULL, " "), &end, 0); //x2
    rect_params->fragments[3] = (void *) strtol(strtok(NULL, " "), &end, 0); //y2
    return rect_params;
}

static void *(*table[SHAPES_AMOUNT])(parameters*) = {identify_point_params, identify_circle_params, identify_line_params, identify_rect_params};

void param_dtor(parameters *shape_params) {
    free(shape_params->fragments);
    shape_params->product_type = NAMELESS;
    free(shape_params);
}

int products_checking(const char *obj_name) {
    if (obj_name != NULL) {
        if (strcmp(obj_name, "point") == 0)
            return POINT;
        if (strcmp(obj_name, "circle") == 0)
            return CIRCLE;
        if (strcmp(obj_name, "line") == 0)
            return LINE;
        if (strcmp(obj_name, "rect") == 0)
            return RECTANGLE;
    }
    return NAMELESS;
}

parameters *line_parser(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    parameters *shape_params = malloc(sizeof(struct parameters));
    char str_copied[1024] = "";
    strcpy_s(str_copied, 1024, str);
    char *prod_name = strtok(str_copied, " ");
    shape_params->product_type = products_checking(prod_name);
    if (POINT <= shape_params->product_type && shape_params->product_type < SHAPES_AMOUNT) {
        table[shape_params->product_type](shape_params);
    } else {
        free(shape_params);
        return NULL;
    }
    return shape_params;
}

void *product_creator(const parameters *shape_params) {
    if (!shape_params)
        return NULL;
    if (POINT <= shape_params->product_type && shape_params->product_type < SHAPES_AMOUNT) {
        void *product;
        switch (shape_params->product_type) {
            case POINT:
                product = new(Point, shape_params->fragments[0], shape_params->fragments[1]);
                break;
            case CIRCLE:
                product = new(Circle, shape_params->fragments[0], shape_params->fragments[1],
                              shape_params->fragments[2]);
                break;
            case LINE:
                product = new(Line, shape_params->fragments[0], shape_params->fragments[1],
                              shape_params->fragments[2], shape_params->fragments[3]);
                break;
            case RECTANGLE:
                product = new(Rect, shape_params->fragments[0], shape_params->fragments[1],
                              shape_params->fragments[2], shape_params->fragments[3]);
                break;
            default:
                return NULL;
        }
        return product;
    }
    return NULL;
}

bool draw_shape(const void *object) {
    if (object == NULL)
        return false;
    draw(object);
    return true;
}