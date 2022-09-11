#include "CalcList.hpp"

/* Constructors */

/**
 * @brief Construct a new Calc List:: Calc List object
 * 
 */
CalcList::CalcList() {
    this->pTotal=0;
    this->l=0;
    this->head = nullptr;
    this->tail = nullptr;
}

CalcList::~CalcList() {
    Node<Operation>* listPtr = this->tail;
    Node<Operation>* above;
    while (nullptr != listPtr) {
        above = listPtr;
        listPtr = listPtr->prev;
        if (nullptr!= above) delete above;
    }
}


/**
 * @brief Construct a new Calc List:: Calc List object
 *  Copy constructor for the Calc List
 * @param copy ptr to the list to be copied
 */
CalcList::CalcList(CalcList* const copy) : CalcList::CalcList() {
    this->l = copy->l;
    /* Copy In all Data from the Nodes */
    Node<Operation>* our_prev = nullptr;
    Node<Operation>* our_curr = this->head;
    Node<Operation>* copy_curr = copy->head;
    while (nullptr != copy_curr) {
        our_curr = new Node<Operation>;
        our_curr->setData(copy_curr->getData());
        link(our_prev, our_curr);
        our_prev = our_curr;
        copy_curr = copy_curr->next;
    /* Back Propagation */
    this->tail = our_curr;
    while (nullptr != our_curr->prev) our_curr= our_curr->prev;
    this->head = our_curr;
    updateTotal();
    }
}

/**
 * @brief Construct a new Calc List:: Calc List object
 * Copy constructor for the Calc List
 * @param copy reference to the list to be copied
 */
CalcList::CalcList(const CalcList& copy): CalcList::CalcList() {
    this->l = copy.l;
    /* Copy In all Data from the Nodes */
    Node<Operation>* our_prev = nullptr;
    Node<Operation>* our_curr;
    Node<Operation>* copy_curr = copy.head;
    while (nullptr != copy_curr) {
        our_curr = new Node<Operation>;
        our_curr->setData(copy_curr->getData());
        link(our_prev, our_curr);
        our_prev = our_curr;
        copy_curr = copy_curr->next;
    }
    /* Back Propagation */
    this->tail = our_curr;
    while (nullptr != our_curr->prev) our_curr= our_curr->prev;
    this->head = our_curr;
    updateTotal();
}

/* Public Functions */
/**
 * @brief Gives back calculated total
 * 
 * @return double total
 */
double CalcList::total() {
    return this->pTotal;
}

/**
 * @brief Adds a new Operation into our List
 * 
 * @param func The function being applied
 * @param operand the Value of which to perform the function
 */
void CalcList::newOperation(FUNCTIONS func,double operand) {
    if(func == DIVISION && operand == 0) {
        throw std::runtime_error("Error: Cannot divde by Zero...");
        return;
    }
    /* This logic adds in a new data point into the right position in the list and updates our total. */
    struct Operation* new_data = new Operation(func, operand);//;new_data->function=func;new_data->operand=operand;
    if (nullptr == this->head) { /* n < 1 */
        this->head = new Node<Operation>;
        this->tail = this->head;
        this->head->setData(new_data);
    }
    else if(this->head == this->tail) { /* n < 2*/
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

/**
 * @brief 
 * @throw runtime error while removing an operation from an empty list.
 */
void CalcList::removeLastOperation() {
    /* Change the Tail, and free the old Tails memory. Reflect this change in the total. */
    if(this->l == 0) {
        throw std::runtime_error("Error: Cannot remove Operation from empty list...");
        return;
    }
    Node<Operation>* old_tail = this->tail;
    if ( nullptr != old_tail && old_tail->hasPrev() ) {
        this->tail = old_tail->prev;
        link(this->tail, nullptr);
        this->l--;
        this->updateTotal();
    }
    else { /* Single Node List */
        this->tail = nullptr; this->head = nullptr;
        this->l = 0;
        this->pTotal = 0;
    }
    delete old_tail;
}

/**
 * @brief Converts the list into a string and returns the reverse order of the operations
 * 
 * @param precision floating point rounding decimal places. 
 * @return std::string the reverse representation of the data.
 */
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
    }
    /* Pull the data from the stack into the return String */
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
    /* Start from Begginging of the List */
    Node<Operation>* curr = this->head;
    this->pTotal = 0;
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