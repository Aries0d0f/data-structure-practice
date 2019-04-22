#include <stdio.h>
#include <stdlib.h>
#define DATA_TYPE int

typedef struct Node Node;

struct Node {
  DATA_TYPE data;
  Node *prev;
  Node *next;

  void (*print) (Node *head);
  void (*push) (Node *head, DATA_TYPE value);
  DATA_TYPE (*pop) (Node *head);
  DATA_TYPE (*del) (Node *head, DATA_TYPE value);
};

void print(Node *head) {
  Node *current = head;

  while(current != NULL) {
    printf("[%08x] <- [%08x] %10d -> [%08x]\n", current->prev, current, current->data, current->next);
    current = current->next;
  }
}

void push(Node *head, DATA_TYPE value) {
  Node *current = head;

  while (current->next != NULL)
    current = current->next;
  
  current->next = malloc(sizeof(Node));
  current->next->data = value;
  current->next->next = NULL;
  current->next->prev = current;
}

DATA_TYPE pop(Node *head) {
  DATA_TYPE _ret = -1;
  Node *nextNode = NULL;

  if (head == NULL)
    return -1;
  
  _ret = head->data;
  nextNode = head->next;
  free(head);
  head->data = nextNode->data;
  head->next = nextNode->next;
  head->prev = NULL;

  return _ret;
}

DATA_TYPE del(Node *head, DATA_TYPE value) {
  DATA_TYPE _del = -1;
  Node *current = head,
       *_tmpNode = NULL;

  while(current->next->data != value)
    current = current->next;

  _del = current->data;
  _tmpNode = current->next;
  free(_tmpNode);
  current->next = _tmpNode->next;
  current->prev = _tmpNode->prev->prev;
  current->next->prev = _tmpNode->prev;
  
  return _del;
}

int main () {
  Node *list;
  list = malloc(sizeof(Node));
  list->data = 99;
  list->prev = NULL;
  list->next = NULL;

  push(list, 110);
  push(list, 1);
  push(list, 102384);
  del(list, 1);

  print(list);

  return 0;
}