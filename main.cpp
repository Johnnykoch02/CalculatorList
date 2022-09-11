#include <string>
#include <iostream>
#include "CalcList.hpp"
// #include <cmath>

int main(void) {
    CalcList calc;
    std::cout << "Total: " << calc.total() << std::endl;
    calc.newOperation(SUBTRACTION, 10);
     std::cout << "Total: " << calc.total() << std::endl;

    calc.removeLastOperation();
     std::cout << "Total: " << calc.total() << std::endl;

}