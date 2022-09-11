#include "CalcList.hpp"

/* Constructors */

CalcList::CalcList() {
    this->pTotal=0;
    this->l=0;
    this->head = nullptr;
    this->tail = nullptr;
}

CalcList::CalcList(CalcList* const copy) : CalcList::CalcList() {
    this->l = copy->length();
    /* Copy In all Data from the Nodes */
    Node<Operation>* our_prev = nullptr;
    Node<Operation>* our_curr = this->head;
    Node<Operation>* copy_curr = copy->head;
    while (copy_curr) {
        our_curr = new Node<Operation>;
        our_curr->setData(copy_curr->getData());
        link(our_prev, our_curr);
        our_prev = our_curr;
        copy_curr = copy_curr->next;
    /* Back Propagation */
    this->tail = our_curr;
    while (our_curr->prev) our_curr= our_curr->prev;
    this->head = our_curr;
    updateTotal();
    }
}

CalcList::CalcList(CalcList& copy) {
    this->l = copy.length();
    /* Copy In all Data from the Nodes */
    Node<Operation>* our_prev = nullptr;
    Node<Operation>* our_curr;
    Node<Operation>* copy_curr = copy.head;
    while (copy_curr) {
        our_curr = new Node<Operation>;
        our_curr->setData(copy_curr->getData());
        link(our_prev, our_curr);
        our_prev = our_curr;
        copy_curr = copy_curr->next;
    }
    /* Back Propagation */
    this->tail = our_curr;
    while (our_curr->prev) our_curr= our_curr->prev;
    this->head = our_curr;
    updateTotal();
}

/* Public Functions */
double CalcList::total() {
    return this->pTotal;
}

void CalcList::newOperation(FUNCTIONS func,double operand) {
    /* This logic adds in a new data point into the right position in the list and updates our total. */
    struct Operation* new_data = new Operation(func, operand);//;new_data->function=func;new_data->operand=operand;
    if (nullptr == this->head) { /* n < 1 */
        this->head = new Node<Operation>;
        this->head->setData(new_data);
    }
    else if(nullptr == this->tail) { /* n < 2*/
        this->tail = new Node<Operation>;
        this->tail->setData(new_data);
        link(this->head, this->tail);
    }
    else { /* n > 2 */
        Node<Operation>* old_tail = this->tail;
        this->tail = new Node<Operation>;
        this->tail->setData(new_data);
        link(old_tail, this->tail);
    }
    /* Now Reflect the Changes */
    this->l++;
    this->updateTotal();
}

void CalcList::removeLastOperation() {
    /* Change the Tail, and free the old Tails memory. Reflect this change in the total. */
    Node<Operation>* old_tail = this->tail;
    this->tail = old_tail->prev;
    link(this->tail, nullptr);
    this->updateTotal();
    delete old_tail;
}

std::string CalcList::toString(unsigned short precision) {
    /* Initialize Variables */
    std::string returnString = "";
    Node<Operation>* curr = this->head;
    unsigned int opNumber = 1;
    /* A very simple utilization of a stack would work very well here. */
    NodeStack<std::string> reverser = NodeStack<std::string>();
    double total_temp = 0;
    
    while (nullptr != curr) { 
        /* Create new Calc String Steam */
        std::stringstream s;
        /* Append Current Total */
        s << opNumber++ << ": ";
        s<< std::fixed << std::setprecision(precision);
        s << total_temp;

        /* Determine which function to apply the operand by */
        Operation* curr_op = curr->getData();
        curr = curr->next;
        switch (curr_op->function) {
            case ADDITION:
                s << "+" << curr_op->operand<<"=";
                total_temp+=curr_op->operand;
                s<<total_temp<<"\n";
                break;
           
            case SUBTRACTION:
                s << "-" << curr_op->operand<<"=";
                total_temp-=curr_op->operand;
                s<<total_temp<<"\n";
                break;
          

            case MULTIPLICATION:
                s << "*" << curr_op->operand<<"=";
                total_temp*=curr_op->operand;
                s<<total_temp<<"\n";                
                break;

           
            case DIVISION:
                s << "*/*" << curr_op->operand<<"=";
                total_temp/=curr_op->operand;
                s<<total_temp<<"\n";                
                break;

            default:
                return "OPERAND ERROR";
        }
        /* Push the new stream data to the stack */

        reverser.push(s.str());
        curr=curr->next;
    }
    while( !(reverser.isEmpty()) ) {
        std::string* popString = reverser.pop()->getData();
        returnString+= *popString;
    }

    return returnString;

}

size_t CalcList::length() {
    return this->l;
}



void CalcList::link(Node<Operation>* a, Node<Operation>* b) {
    /*This process puts node a's next to b, and b's prev to a*/
    if(nullptr != a)/*Cannot dereference null...*/
        a->next = b;
    if(nullptr != b)
        b->prev = a;
}


void CalcList::updateTotal() {
    Node<Operation>* curr = this->head;
    while (nullptr != curr) { 

        /* Determine which function to apply the operand by */
        Operation* curr_op = curr->getData();
        curr=curr->next;
        switch (curr_op->function) {
            
            case ADDITION:
                this->pTotal+=curr_op->operand;
                break;
           
            case SUBTRACTION:
                this->pTotal-=curr_op->operand;
                break;

            case MULTIPLICATION:
                this->pTotal*=curr_op->operand;
                break;

            case DIVISION:
                this->pTotal/=curr_op->operand;
                break;

            default:
                break; /* Maybe exception shtuff*/
        }

    }
}