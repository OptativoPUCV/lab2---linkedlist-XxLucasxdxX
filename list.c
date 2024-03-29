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
  List *L= (List*) malloc(sizeof(List));
  L->head=NULL;
  L->tail=NULL;
  L->current=NULL;
     return L;
}

void * firstList(List * list) {
  
  if((list->head)==NULL)return NULL; 
  list->current=list->head;
  
  return list->head->data;
}

void * nextList(List * list) {
  if(list->current==NULL || list->current->next == NULL) return NULL;
  list->current=list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if((list->tail)==NULL)return NULL; 
  list->current=list->tail;
    return list->current->data;
}

void * prevList(List * list) {
  if(list->current==NULL || list->current->prev==NULL) return NULL;
  list->current=list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
  Node * NuevoNodo = createNode(data);
  if(list->head==NULL)
  {
    list->head=NuevoNodo;
    list->tail=NuevoNodo;
  } else {
    NuevoNodo->next=list->head;
    list->head->prev=NuevoNodo->next;
    list->head=NuevoNodo;
  }
  
}

void pushBack(List * list, void * data) {
    Node * NuevoNodo = createNode(data);
  if(list->tail==NULL){
    list->head=NuevoNodo;
    list->tail=NuevoNodo;
  } else {
    NuevoNodo->prev=list->tail;
    list->tail->next=NuevoNodo;
    list->tail=NuevoNodo;
  }

}

void pushCurrent(List * list, void * data) {
  Node * NuevoNodo = createNode(data);
  if(list->current==NULL) return;
  
  NuevoNodo->prev=list->current;
  
  if(list->current==list->tail) {
    list->tail=NuevoNodo;
    list->current->next=NuevoNodo;
  } else {
    NuevoNodo->next = list->current->next;
    list->current->next=NuevoNodo;
  }    
}

void * popFront(List * list) {
  if(list->head==NULL) return NULL;
  Node  * NodoElimiar = list->head;
  void * data =  NodoElimiar->data;
  if(list->head==list->tail)
  {
    list->head=NULL;
    list->tail=NULL;
  } else {
    list->head=NodoElimiar->next;
    list->head->prev=NULL;
  }
  return data;
  
}

void * popBack(List * list) {
  if(list->tail==NULL) return NULL;
  Node  * NodoElimiar = list->tail;
  void * data =  NodoElimiar->data;
  if(list->head==list->tail)
  {
    list->head=NULL;
    list->tail=NULL;
  } else {
    list->tail=NodoElimiar->prev;
    list->tail->next=NULL;
  }
  return  data;
}

void * popCurrent(List * list) {
  
  if(list->current==NULL) return NULL;
  Node  * NodoElimiar = list->current;
  void * data =  NodoElimiar->data;
  if(list->current==list->head)
  {
    list->head=NodoElimiar->next;
    if(list->head!=NULL) list->head->prev=NULL;
  } else if(list->current==list->tail){
      list->tail=NodoElimiar->prev;
      if(list->tail!=NULL) list->tail->next=NULL;
    } else {
  NodoElimiar->prev->next=NodoElimiar->next;
  NodoElimiar->next->prev=NodoElimiar->prev; 
  }
  

  
  return data;
}

void cleanList(List * list) {
  Node * NodoEliminar = list->head;
  
  while(NodoEliminar!=NULL) {
    Node * next = NodoEliminar->next;
    free(NodoEliminar);
    NodoEliminar=next;
  }
  
  list->head=NULL;
  list->tail=NULL;
  list->current=NULL;
}