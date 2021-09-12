#include <string.h>
#include <assert.h>
#include <math.h>

#include "linked_list.h"

typedef struct {
    int array[8];
    float d_variable;
} Value;

int main(int argc, char* argv[])
{
    //Создаем односвязный список с элементами типа Value;
    void* slist = slist_create(sizeof(Value));

    assert(0 == slist_count(slist));
    assert(slist_stop(slist) == slist_first(slist));

    //Создаем объект для односвязного списка
    Value value = { {1, 2, 3, 4, 5, 6, 7, 8}, 0.f };

    //Добавляем новый элемент в односвязный список
    Value* insertedValue = (Value*)slist_prepend(slist);

    //Инициализируем добавленный элемент
    *insertedValue = value;

    Value* item = (Value*)slist_item(slist, 0);

    for (size_t i = 0; 8 > i; ++i) {
        assert(item->array[i] == value.array[i]);
    }

    assert(fabsf(item->d_variable - value.d_variable) < 1e-10f);
    assert(NULL == slist_item(slist, 1));

    assert(slist_next(slist, slist_first(slist)) == slist_stop(slist));

    slist_destroy(slist, NULL);

    return 0;
}
