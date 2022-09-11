#include "CalcListInterface.hpp"

using namespace std;

#ifndef Node_h
#define Node_h

template <class T>
class Node {
  private:
    T *data;

  public:
    Node<T> *prev;
    Node<T> *next;
  Node(){
    this->prev = nullptr;
    this->next = nullptr;
  }

  ~Node() {
    delete data; //delete prev; delete next;
  }

  Node(T *data, Node<T> *p, Node<T> *n) {
    this->data = data;
    this->prev = p;
    this->next = n;
}

  Node(T *data) {
    this->prev = nullptr;
    this->next = nullptr;
    this->data = data;
}

  Node* getNext() { return  this->next; }

  Node* getPrev() { return  this->prev; }

  bool hasPrev() { return !(this->prev == nullptr); }

  bool hasNext(){ return  !(this->next == nullptr); }

  void setPrev(Node<T> *p) {
    this->prev = p;
}
  void setNext(Node<T> *n) {
    this->next = n;
}

  void setData(T* data) {
    this->data = data;
}
  T *getData() { return this->data; }
  
};
#endif

/**
 * @brief Structure to hold information corresponding to the Operation
 *  in place.
 */

struct Operation {
    FUNCTIONS function;
    double operand;/* Might Have to Be consistent */
    Operation() {}
    Operation(FUNCTIONS func, double op) {
        this->function = func;
        this->operand = op;
    }
};

#ifndef CALCLIST_H
#define CALCLIST_H



class CalcList : public CalcListInterface {  
    
    protected:
    /* Variables Which Will Be avialable to Subclasses etc.. */
        double pTotal;
        Node<Operation>* head,* tail;

                                                                                                         
    /* Protected Functions */
    void updateTotal();


    private:
        size_t l;
        void link(Node<Operation>* a, Node<Operation>* b);

    public:
    /* Public Contstructors & Destructors */
    CalcList();
    ~CalcList();
    CalcList(CalcList* const copy);
    CalcList(CalcList& copy);
    
    /* Public Variables */

    /* Public Functions */
    double total();
    void newOperation(FUNCTIONS func, double operand);
    void removeLastOperation();
    std::string toString(unsigned short precision);
    size_t length();

  
};

#endif




template <class T>
class NodeStack {
 protected:
    
    Node<T>* top;
    unsigned int length;

 public:
    /* Initialize Stack */
    NodeStack() {
      this->top = nullptr;
      this->length = 0;
    }
    /* Removes Node Stack */
    ~NodeStack() { 
      Node<T>* stackPtr = this->top;
      Node<T>* above;
      while (nullptr != stackPtr) {
        above = stackPtr;
        stackPtr = stackPtr->prev;
        if (nullptr!= above) delete above;
      }
    }

    void push(T data) {
        T* dataPtr = new T(data);
        Node<T>* node = new Node<T>(dataPtr);
        if (!this->isEmpty()) {
          this->top->next = node;
          node->prev = this->top;
        }
        if (node) {
            this->top = node;
            this->length++;
        }
    }
    
    Node<T>* peek() {
        return this->top;
    }

    Node<T>* pop() {
        Node<T> * returnNode = this->top;
        this->top = this->top->prev;
        length--;
        return returnNode;
    }
    
    bool isEmpty() {
        return nullptr == this->top;
    }

};
