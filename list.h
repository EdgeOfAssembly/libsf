#ifndef __LIST_H__
#define __LIST_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    TYPE_CHAR,
    TYPE_SHORT,
    TYPE_INT,
    TYPE_LONG,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_USER_DEFINED
} type_t;

typedef struct _node
{
    struct _node* prev;
    void* data;
    size_t size;
    type_t type;
    struct _node* next;
} node_t;

typedef struct _list
{
    node_t* head;
    node_t* tail;
    size_t size;
} list_t;




node_t*		list_back(list_t* list);
node_t*		list_begin(list_t* list);
void		list_clear(list_t* list);
node_t*		list_erase(list_t* list, int position);
bool 		list_empty(list_t* list);
node_t* 	list_end(list_t* list);
void 		list_insert(list_t* list, void* element, size_t n, type_t type, int position);
void 		list_merge(list_t* one, list_t* two);
node_t* 	list_pop_back(list_t* list);
node_t* 	list_pop_front(list_t* list);
node_t* 	list_front(list_t* list);
void 		list_push_back(list_t* list, void* element, size_t n, type_t type);
void 		list_push_front(list_t* list, void* element, size_t n, type_t type);
void 		list_reverse(list_t* list);
size_t 		list_size(list_t* list);
void 		list_sort(list_t* list);
void 		list_unique(list_t* list);









/* Helper function to create a new node */
static node_t* create_node(void* element, size_t n, type_t type)
{
    node_t* node = (node_t*)malloc(sizeof(node_t));
    if (node == NULL) return NULL;
    
    node->data = malloc(n);
    if (node->data == NULL) {
        free(node);
        return NULL;
    }
    
    memcpy(node->data, element, n);
    node->size = n;
    node->type = type;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

/* Helper function to free a node */
static void free_node(node_t* node)
{
    if (node) {
        free(node->data);
        free(node);
    }
}

// Function to register a new user-defined type
static inline void list_register_user_type(type_t* type, size_t size)
{
    *type = TYPE_USER_DEFINED; // Assuming we only use TYPE_USER_DEFINED for new types
}


/* List Construction and Management */
void list_clear(list_t* list)
{
    node_t* current = list->head;
    while (current != NULL) {
        node_t* next = current->next;
        free_node(current);
        current = next;
    }
    memset(list, 0, sizeof(list_t));
}

/* Element Access */
node_t* list_back(list_t* list)
{
    return list->tail;
}

node_t* list_front(list_t* list)
{
    return list->head;
}

/* Element Insertion */
void list_insert(list_t* list, void* element, size_t n, type_t type, int position)
{
    if (position < 0 || (size_t)position > list->size) return;

    node_t* new_node = create_node(element, n, type);
    if (new_node == NULL) return;

    if (list->size == 0) {
        list->head = list->tail = new_node;
    } else if (position == 0) {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    } else if ((size_t)position == list->size) {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    } else {
        node_t* current = list->head;
        for (int i = 0; i < position; ++i) {
            current = current->next;
        }
        new_node->next = current;
        new_node->prev = current->prev;
        current->prev->next = new_node;
        current->prev = new_node;
    }
    list->size++;
}

void list_push_back(list_t* list, void* element, size_t n, type_t type)
{
    list_insert(list, element, n, type, list->size);
}

void list_push_front(list_t* list, void* element, size_t n, type_t type)
{
    list_insert(list, element, n, type, 0);
}

/* Element Removal */
node_t* list_erase(list_t* list, int position)
{
    if (position < 0 || (size_t)position >= list->size) return NULL;

    node_t* current = list->head;
    for (int i = 0; i < position; ++i) {
        current = current->next;
    }

    if (current == list->head) {
        list->head = current->next;
        if (list->head) list->head->prev = NULL;
    } else {
        current->prev->next = current->next;
    }
    
    if (current == list->tail) {
        list->tail = current->prev;
        if (list->tail) list->tail->next = NULL;
    } else {
        current->next->prev = current->prev;
    }

    list->size--;
    node_t* ret = current;
    current = NULL;  // Prevent double free
    return ret;
}

node_t* list_pop_back(list_t* list)
{
    if (list_empty(list)) return NULL;
    return list_erase(list, list->size - 1);
}

node_t* list_pop_front(list_t* list)
{
    if (list_empty(list)) return NULL;
    return list_erase(list, 0);
}

/* Query and Inspection */
size_t list_size(list_t* list)
{
    return list->size;
}

bool list_empty(list_t* list)
{
    return list->size == 0;
}

/* Iteration and Navigation */
node_t* list_begin(list_t* list)
{
    return list->head;
}

node_t* list_end(list_t* list)
{
    return list->tail;  // Updated for doubly-linked list
}

/* List Modification */
void list_merge(list_t* one, list_t* two)
{
    if (list_empty(two)) return;

    if (list_empty(one)) {
        *one = *two;
        memset(two, 0, sizeof(list_t));
    } else {
        one->tail->next = two->head;
        two->head->prev = one->tail;
        one->tail = two->tail;
        one->size += two->size;
        memset(two, 0, sizeof(list_t));
    }
}

void list_reverse(list_t* list)
{
    node_t* current = list->head;
    node_t* temp;
    
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    
    if (list->head != NULL) {
        temp = list->head;
        list->head = list->tail;
        list->tail = temp;
    }
}

void list_sort(list_t* list)
{
    // Note: This is a placeholder for sorting. A proper implementation would require defining comparison logic.
    // Here, we're assuming all elements are of the same type and size for simplicity.
    if (list->size <= 1) return;
    
    node_t* nodes[list->size];
    node_t* current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        nodes[i] = current;
        current = current->next;
    }
    
    // Quick sort for simplicity
    for (size_t i = 0; i < list->size - 1; i++) {
        for (size_t j = 0; j < list->size - i - 1; j++) {
            if (memcmp(nodes[j]->data, nodes[j + 1]->data, nodes[j]->size) > 0) {
                node_t* t = nodes[j];
                nodes[j] = nodes[j + 1];
                nodes[j + 1] = t;
            }
        }
    }
    
    list->head = nodes[0];
    list->tail = nodes[list->size - 1];
    for (size_t i = 0; i < list->size - 1; ++i) {
        nodes[i]->next = nodes[i + 1];
        nodes[i + 1]->prev = nodes[i];
    }
    nodes[list->size - 1]->next = NULL;
    nodes[0]->prev = NULL;
}

void list_unique(list_t* list)
{
    if (list->size <= 1) return;

    node_t* current = list->head;
    while (current != NULL && current->next != NULL) {
        if (memcmp(current->data, current->next->data, current->size) == 0) {
            node_t* to_remove = current->next;
            current->next = to_remove->next;
            if (to_remove->next) to_remove->next->prev = current;
            if (to_remove == list->tail) list->tail = current;
            free_node(to_remove);
            list->size--;
        } else {
            current = current->next;
        }
    }
}

#endif // __LIST_H__

