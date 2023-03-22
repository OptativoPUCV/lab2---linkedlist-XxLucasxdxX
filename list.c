#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
     List * newList = (List *) malloc(sizeof(List));
     newList->head = NULL;
     newList->tail = NULL;
     newList->current = NULL;
     return newList;
}

void * firstList(List * list) {
    if (list->head == NULL) {
        return NULL;
    }
    list->current = list->head;
    return list->head->data;
}

void * nextList(List * list) {
    if (list->current == NULL || list->current->next == NULL) {
        return NULL;
    }
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if (list->tail == NULL) {
        return NULL;
    }
    list->current = list->tail;
    return list->tail->data;
}

void * prevList(List * list) {
    if (list->current == NULL || list->current->prev == NULL) {
        return NULL;
    }
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node * new = createNode(data);
    new->next = list->head;
    if (list->head != NULL) {
        list->head->prev = new;
    }
    list->head = new;
    if (list->tail == NULL) {
        list->tail = new;
    }
}
void pushBack(List * list, void * data) {
    Node * newNode = createNode(data);
    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
}
void pushCurrent(List * list, void * data) {
    if (list->current == NULL) {
        pushFront(list, data);
        return;
    }
    if (list->current == list->tail) {
        pushBack(list, data);
        return;
    }
    Node * new = createNode(data);
    new->prev = list->current;
    new->next = list->current->next;
    list->current->next->prev = new;
    list->current->next = new;
}

void * popCurrent(List * list) {
    if (list->current == NULL) {
        return NULL;
    }
    Node * nodeToRemove = list->current;
    void * data = nodeToRemove->data;
    if (nodeToRemove == list->head) {
        list->head = nodeToRemove->next;
    } else {
        nodeToRemove->prev->next = nodeToRemove->next;
    }
    if (nodeToRemove == list->tail) {
        list->tail = nodeToRemove->prev;
    } else {
        nodeToRemove->next->prev = nodeToRemove->prev;
    }
    list->current = nodeToRemove->prev;
    free(nodeToRemove);
    return data;
}