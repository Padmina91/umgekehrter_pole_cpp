#include <iostream>
#include "stack.hpp"
#include <vector>
#include <algorithm>



int main() {
    using namespace std;
    
    Stack<int> stack("l  \n\n\n\t  werj\toi 2q3 r 23r 23 52 35 1  11 1 1 1  1    11   1\r\r\r\r11    \r\n     ", "int");
    cout << "|" << stack.get_calculation() << "|" << endl;
    stack.process_calculation();
    cout << "|" << stack.get_calculation() << "|" << endl;
    //vector<int> values;
    //for (int i = 1; i <= 5; i++)
    //    values.push_back(i);
    //
    //cout << *values.begin();
    //cout << *values.begin();
    //for (auto i = values.begin(); i != values.end(); ++i)
    //    cout << *i << endl;
    //cout << "*values.begin(): " << *values.begin() << endl;
    //cout << "*++values.begin(): " << *++values.begin() << endl;
    //cout << "*--values.end(): " << *--values.end() << endl;
    //cout << "*----values.end(): " << *----values.end() << endl;
    //cout << endl;
    //
    //cout << "*values.cbegin(): " << *values.cbegin() << endl;
    //cout << "*++values.cbegin(): " << *++values.cbegin() << endl;
    //cout << "*--values.cend(): " << *--values.cend() << endl;
    //cout << "*----values.cend(): " << *----values.cend() << endl;
    //cout << endl;
    //
    //cout << "*values.rbegin(): " << *values.rbegin() << endl;
    //cout << "*++values.rbegin(): " << *++values.rbegin() << endl;
    //cout << "*--values.rend(): " << *--values.rend() << endl;
    //cout << "*----values.rend(): " << *----values.rend() << endl;
    //cout << endl;
    //
    //cout << "*values.crbegin(): " << *values.crbegin() << endl;
    //cout << "*++values.crbegin(): " << *++values.crbegin() << endl;
    //cout << "*--values.crend(): " << *--values.crend() << endl;
    //cout << "*----values.crend(): " << *----values.crend() << endl;
    //cout << endl;
    //
    //cout << "values.front(): " << values.front() << endl;
    //cout << "values.back(): " << values.back() << endl;
    //values.pop_back();
    //cout << "values.back(): " << values.back() << endl;
    
}