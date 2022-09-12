#ifndef CALCLISTINTERFACE_H
#define CALCLISTINTERFACE_H

#include <string>
#include <iomanip>
#include <sstream>

// Enum that contains all the arithmetic functions needed for newOperation
typedef enum { ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION } FUNCTIONS;



// Abstract class for inheritance
class CalcListInterface {
public:
    virtual double total() = 0;
    virtual void newOperation(FUNCTIONS func,double operand) = 0;
    virtual void removeLastOperation() = 0;
    virtual std::string toString(unsigned short precision) = 0;
};

#endif /* CALCLISTINTERFACE_H */