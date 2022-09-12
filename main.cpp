#include <string>
#include <iostream>
#include "CalcList.hpp"
// #include <cmath>

/**
 * Jonathan Koch U25381998
 * Krish Veera U87325929
 */

int main(void) {
    CalcList calc;
    std::cout << "Total: " << calc.total() << std::endl;
    calc.newOperation(SUBTRACTION, 10);
     std::cout << "Total: " << calc.total() << std::endl;

    calc.removeLastOperation();
     std::cout << "Total: " << calc.total() << std::endl;
    try {
        calc.removeLastOperation();
    }catch (std::exception& e) {
        std::cout<< e.what() << endl;
    }

    calc.newOperation(ADDITION, 50);
    std::cout << "Total: " << calc.total() << std::endl;
    calc.newOperation(MULTIPLICATION, 0);
    std::cout << "Total: " << calc.total() << std::endl;

    calc.removeLastOperation();
    std::cout << "Total: " << calc.total() << std::endl;

    try {
        calc.newOperation(DIVISION, 0);
        std::cout << "Total: " << calc.total() << std::endl;
    } catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    try {
        calc.newOperation(SUBTRACTION, 10);
        std::cout << "Total: " << calc.total() << std::endl;
    } catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    try {
        calc.newOperation(DIVISION, 0);
        std::cout << "Total: " << calc.total() << std::endl;  
    } catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    calc.newOperation(ADDITION, 10);
    calc.newOperation(ADDITION, 20);
    calc.newOperation(SUBTRACTION, 20.2);
    // calc.removeLastOperation();
    calc.newOperation(MULTIPLICATION, 1.782);
    std::cout << "O/\n";
    std::string output = calc.toString(3);
    std::cout << output << std::endl;

    std::cout << "Total: " << calc.total() << std::endl;  

    CalcList copy = CalcList(calc);

}