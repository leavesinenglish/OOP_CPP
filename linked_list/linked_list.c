#include "linked_list.h"
#include <stdlib.h>
#include <assert.h>

typedef struct ListNode {
    void *data;
    struct ListNode *next;
} ListNode;

typedef struct List {
    size_t itemSize;
    ListNode *head;
    size_t listSize;
} List;

///slist_create -- Создать новый пустой односвязный список. Размер элемента -- itemSize байт.
void *slist_create(size_t itemSize) {
    if (itemSize == 0)
        return NULL;
    List *pList = malloc(sizeof(List));
    if (pList == NULL)
        return NULL;
    pList->head = NULL;
    pList->listSize = 0;
    pList->itemSize = itemSize;
    return pList;
}

static ListNode *list_node_create(size_t itemSize) {
    ListNode *node = malloc(sizeof(ListNode));
    if (node == NULL)
        return NULL;
    node->data = calloc(1, itemSize);
    if (node->data == NULL) {
        return NULL;
    }
    node->next = NULL;
    return node;
}

static void list_nodes_delete(void *slist, void(*destroy)(void *)) {
    List *pList = slist;
    ListNode *curnode = pList->head;
    ListNode *next;
    if (pList->listSize != 0) {
        for (int i = 0; i < pList->listSize; i++) {
            if (destroy != NULL) {
                destroy(curnode->data);
            }
            next = curnode->next;
            free(curnode->data);
            free(curnode);
            curnode = next;
        }
    }
    pList->head = NULL;
}

///slist_destroy -- Удалить существующий односвязный список.
///Если указана функция destroy, то вызвать её для каждого удаляемого элемента.
void slist_destroy(void *slist, void(*destroy)(void *)) {
    if (slist == NULL)
        return;
    List *pList = slist;
    list_nodes_delete(pList, destroy);
    if (pList == NULL)
        return;
    pList->head = NULL;
    free(pList);
}

///slist_init -- Инициализировать односвязный список новыми параметрами. Если slist содержит элементы, то сначала удалить
///все элементы, потом инициализировать односвязный список с учетом новых параметров. Размер элемента -- itemSize байт.
///Если указана функция destroy, то вызвать её для каждого удаляемого элемента.
void *slist_init(void *slist, size_t itemSize, void(*destroy)(void *)) {
    if (slist == NULL || itemSize == 0)
        return NULL;
    List *pList = slist;
    if (pList->listSize == 0) {
        pList->itemSize = itemSize;
        return pList;
    }
    list_nodes_delete(pList, destroy);
    free(pList);
    pList = slist_create(itemSize);
    return pList;
}

///slist_clear -- Удалить все элементы из односвязного списка. Если указана функция destroy, то вызвать её для каждого удаляемого элемента.
void slist_clear(void *slist, void(*destroy)(void *)) {
    if (slist == NULL)
        return;
    List *pList = slist;
    list_nodes_delete(pList, destroy);
    pList->listSize = 0;
}

///slist_count -- Количество элементов в списке. В случае, если slist равен NULL, возвращает INVALID константу.
size_t slist_count(const void *slist) {
    if (slist == NULL)
        return INVALID;
    List const *pList = slist;
    return pList->listSize;
}

///slist_item -- Получить элемент по индексу в списке.
void *slist_item(void *slist, size_t i) {
    List const *pList = slist;
    if (slist == NULL || pList->listSize <= i)
        return NULL;
    ListNode *curnode = pList->head;
    for (int j = 0; j < i; j++) {
        if (curnode == NULL)
            return NULL;
        curnode = curnode->next;
    }
    return curnode->data;
}

///slist_prepend -- Добавить элемент в голову односвязного списка.
///В случае успеха, функция возвращает указатель на добавленный элемент, иначе -- NULL.
void *slist_prepend(void *slist) {
    if (slist == NULL)
        return NULL;
    List *pList = slist;
    ListNode *new_head = list_node_create(pList->itemSize);
    if (new_head == NULL)
        return NULL;
    if (pList->listSize == 0) {
        pList->head = new_head;
    } else {
        new_head->next = pList->head;
        pList->head = new_head;
        assert(pList->head == new_head);
    }
    pList->listSize++;
    return pList->head->data;
}

///slist_remove -- Удалить элемент из головы односвязного списка.
///Если указана функция destroy, то вызвать её для удаляемого элемента.
void slist_remove(void *slist, void(*destroy)(void *)) {
    List *pList = slist;
    if (slist == NULL || pList->listSize == 0 || pList->head == NULL)
        return;
    if (destroy)
        destroy(pList->head->data);
    free(pList->head->data);
    if (pList->head->next) {
        ListNode *new_head = pList->head->next;
        free(pList->head);
        pList->head = new_head;
    } else {
        free(pList->head);
        pList->head = NULL;
    }
    pList->listSize--;
}

///slist_first -- Идентификатор для первого элемента из односвязного списка. Идентификатор может стать невалидным при модификации списка.
///идентификатор - адрес.
size_t slist_first(const void *slist) {
    List const *pList = slist;
    if (pList == NULL || pList->listSize == 0)
        return slist_stop(slist);
    return (size_t) pList->head;
}

///slist_next -- По идентификатору текущего элемента получить идентификатор следующего элемента списка.
size_t slist_next(const void *slist, size_t item_id) {
    List const *pList = slist;
    ListNode *cur = (ListNode *) (item_id);
    if (item_id == INVALID || item_id == slist_stop(slist) ||
        pList == NULL || cur == NULL || cur->next == NULL || pList->listSize == 0)
        return slist_stop(slist);
    return (size_t) cur->next;
}

///slist_stop -- Идентификатор, получаемый при попытке обратиться к элементу за пределами списка.
size_t slist_stop(const void *slist) {
    return INVALID - 1;
}

///slist_current -- Получить указатель на элемент списка по его идентификатору.
void *slist_current(const void *slist, size_t item_id) {
    List const *pList = slist;
    if (slist == NULL || item_id == INVALID || item_id == slist_stop(slist) || pList->listSize == 0)
        return NULL;
    ListNode *cur = (ListNode *) (item_id);
    return cur->data;
}

///slist_insert -- Вставка нового элемента списка после указанного по идентификатору.
///Когда список пустой, для успешной вставки элемента в качестве item_id должен указываться идентификатор,
///возвращаемый функцией slist_stop. В остальных случаях, item_id должен однозначно соответствовать элементу списка.
///В случае успеха, функция возвращает указатель на вставленный элемент, иначе -- NULL.
void *slist_insert(void *slist, size_t item_id) {
    if (slist == NULL || item_id == INVALID)
        return NULL;
    List *pList = slist;
    if (pList->listSize == 0 && item_id == slist_stop(slist))
        return slist_prepend(slist);
    if (item_id == slist_stop(slist))
        return NULL;
    ListNode *cur = (ListNode *) (item_id);
    ListNode *new_node = list_node_create(pList->itemSize);
    if (new_node == NULL)
        return NULL;
    if (cur->next != NULL) {
        new_node->next = cur->next;
    }
    cur->next = new_node;
    pList->listSize++;
    return new_node->data;
}

///slist_erase -- Удаление элемента по его идентификатору. Если указана функция destroy, то вызвать её для удаляемого
///элемента. После удаления элемента из списка, идентификаторы любых элементов из этого массива могут стать невалидным.
void slist_erase(void *slist, size_t item_id, void(*destroy)(void *)) {
    if (slist != NULL && item_id != slist_stop(slist)) {
        List *pList = slist;
        ListNode *removing = (ListNode *) (item_id);
        if (removing == pList->head) {
            slist_remove(slist, destroy);
            return;
        }else {
            ListNode *curnode = (ListNode *)slist_first(pList);
            size_t item;
            for (item = slist_first(slist); item != item_id; item = slist_next(slist, item)) {
                if (curnode == removing)
                    break;
                curnode = (ListNode *) (item);
            }
            assert(slist_next(slist, item) == item_id);
            curnode->next = removing->next;
            destroy(removing->data);
            free(removing);
        }
        pList->listSize--;
    }
}