#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef struct parameters {
    enum shape product_type;
    void **fragments;
} parameters;

parameters *line_parser(const char *str);

void *product_creator(const parameters *shape_params);

void param_dtor(parameters *shape_params);

bool draw_shape(const void *object);
