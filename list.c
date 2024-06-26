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

List * createList()
{
  List *lista = (List *)malloc(sizeof(List));
  lista->head = NULL;
  lista->tail = NULL;
  lista->current = NULL;

  return lista;
}

void * firstList(List * list)
{
  if (list->head == NULL) return NULL;

  list->current = list->head;
  return list->head->data;
}

void * nextList(List * list)
{
  if (list->current == NULL || list->current->next == NULL) return NULL;
  list->current = list->current->next;

  return list->current->data;
}

void * lastList(List * list)
{
  if (list->head == NULL) return NULL;
  list->current = list->tail;
  
  return list->current->data;
}

void * prevList(List * list)
{
  if (list->current == NULL || list->current->prev == NULL) return NULL;
  list->current = list->current->prev;
  
  return list->current->data;
}

void pushFront(List * list, void * data)
{
  Node *newNode = createNode(data);

  if (list->head == NULL)
  {
    list->head = newNode;
    list->tail = newNode;
  }
  else
  {
    newNode->next = list->head;
    list->head->prev = newNode;
    list->head = newNode;
  }
}

void pushBack(List * list, void * data)
{
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data)
{
  Node *newNode = createNode(data);
  if (list->current == NULL)
  {
    list->head = newNode;
    list->tail = newNode;
  }
  else
  {
    newNode->prev = list->current;
    newNode->next = list->current->next;
    list->current->next = newNode;

    if (newNode->next == NULL) list->tail = newNode;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popCurrent(List * list)
{
  if (list->current == NULL) return NULL;

  Node *aux = list->current;
  if (aux->prev != NULL)
  {
    list->current = list->current->prev;
    list->current->next = aux->next;
  }
  else
  {
    list->head = aux->next;
    list->head->prev = NULL;
  }
  
  if (aux->next != NULL)
  {
    list->current = list->current->next;
    list->current->prev = aux->prev;
  }
  else
  {
    list->tail = aux->prev;
    list->tail->next = NULL;
  }

  list->current = aux->next;

  return aux->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}