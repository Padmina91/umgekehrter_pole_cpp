#include <iostream>
#include "stack.hpp"


int main() {
    using namespace std;
    
    Stack<float> stack("5.0 6.0 - 5.0 + 0.0 /", "float");
    cout << "|" << stack.get_calculation() << "|" << endl;
    stack.process_calculation();
    cout << "|" << stack.get_result() << "|" << endl;

}