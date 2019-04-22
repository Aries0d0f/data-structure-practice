#include <stdio.h>
#define DATA_TYPE int

class Node {
  public:
    Node();
    Node(DATA_TYPE);

    void print();
    void push(DATA_TYPE);
    DATA_TYPE pop();
    DATA_TYPE del(DATA_TYPE);
  
  private:
    DATA_TYPE data;
    Node *next;
};

Node::Node() {
  data = NULL;
  next = NULL;
}

Node::Node(DATA_TYPE value) {
  data = value;
  next = NULL;
}

void Node::print() {
  Node *current = this;

  while(current != NULL) {
    printf("[%08x] %10d -> [%08x]\n", current, current->data, current->next);
    current = current->next;
  }
}

void Node::push(DATA_TYPE value) {
  Node *newNode = new Node(value);
  Node *current = this;
  
  while (current->next != NULL)
    current = current->next;

  current->next = newNode;
}

DATA_TYPE Node::pop() {
  Node *nextNode = NULL;
  DATA_TYPE _ret = -1;

  if (this == NULL)
    return -1;

  _ret = this->data;
  nextNode = this->next;
  delete this;
  this->data = nextNode->data;
  this->next = nextNode->next;
}

DATA_TYPE Node::del(DATA_TYPE value) {
  Node *_tmpNode = NULL,
       *current = this;
  DATA_TYPE _del = -1;

  while(current->next->data != value)
    current = current->next;
  
  _del = current->data;
  _tmpNode = current->next;
  delete _tmpNode;
  current->next = _tmpNode->next;

  return _del;
}

int main () {
  Node *list = new Node(99);

  list->push(110);
  list->push(1);
  list->push(102384);
  list->del(1);

  list->print();

  return 0;
}