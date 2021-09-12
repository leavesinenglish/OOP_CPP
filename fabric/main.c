#define _CRTDBG_MAP_ALLOC

#include "fabric.h"
#include "new.h"
#include <stdio.h>
#include <crtdbg.h>

int main(int argc, char *argv[]) {
    argv[1] = "INPUT.txt";
    FILE *file = fopen(argv[1], "r");
    char buff[1024];
    char *str;
    if (file == NULL) {
        printf("FILE ERROR");
        return 1;
    }
    void *object;
    while (!feof(file)) {
        str = fgets(buff, 1024, file);
        parameters *shape_params = line_parser(str);
        object = product_creator(shape_params);
        draw_shape(object);
        param_dtor(shape_params);
        delete(object);
    }
    fclose(file);

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

    _CrtDumpMemoryLeaks();
    return 0;
}
