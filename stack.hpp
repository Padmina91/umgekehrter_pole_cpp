//
// Created by Mina on 18.05.2020.
//

#ifndef UMGEKEHRTER_POLE_CPP_STACK_HPP
#define UMGEKEHRTER_POLE_CPP_STACK_HPP

#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include "exception.hpp"

template <typename T>
class Stack {
private:
// ----------------------------------------------------------------------------------------------------
// ---------------------------------------- private attributes ----------------------------------------
// ----------------------------------------------------------------------------------------------------
    std::vector<T> _values;
    
    std::string _calculation;
    
    std::string _type_name;

// ----------------------------------------------------------------------------------------------------
// ----------------------------------- private methods declaration ------------------------------------
// ----------------------------------------------------------------------------------------------------
    bool is_empty();
    
    bool only_one_element_left();
    
    void remove_unnecessary_whitespace();
    
    std::string extract_single_op(); // op = operator or operand
    
    bool is_correct_operand(std::string& s);
    
    bool is_correct_operator(std::string& s);
    

// ----------------------------------------------------------------------------------------------------
// ------------------------------- private static methods declaration ---------------------------------
// ----------------------------------------------------------------------------------------------------
    static bool both_are_spaces(char left, char right);

public:
    void process_calculation(); //TODO: return back to private methods when debugging is done
// ----------------------------------------------------------------------------------------------------
// ------------------------------------ public methods declaration ------------------------------------
// ----------------------------------------------------------------------------------------------------
    explicit Stack(std::string calculation_input, std::string type_name);
    
    ~Stack();
    
    void set_calculation(std::string calculation_input, std::string type_name);
    
    std::string get_calculation();
    
    void push(T val);
    
    T top();
    
    T pop();
    
    void print_current_stack();

// ----------------------------------------------------------------------------------------------------
// -------------------------------- public static methods declaration ---------------------------------
// ----------------------------------------------------------------------------------------------------
};
// ----------------------------------------------------------------------------------------------------
// ------------------------------------ private methods definition ------------------------------------
// ----------------------------------------------------------------------------------------------------

template <typename T>
bool Stack<T>::is_empty() {
    return _values.size() == 0;
}

template <typename T>
bool Stack<T>::only_one_element_left() {
    return _values.size() == 1;
}

template <typename T>
void Stack<T>::remove_unnecessary_whitespace() {
    size_t position = 0;
    while (position != std::string::npos) { // npos is the largest possible size_t. It's the return value of find_first_of() if no occurrence is found
        position = _calculation.find_first_of("\n\t\r");
        if (position != std::string::npos) {
            _calculation.replace(position, 1, " "); // first, replaces all non-space whitespace by spaces
        }
    }
    std::string::iterator new_end = std::unique(_calculation.begin(), _calculation.end(), both_are_spaces); // removes all non-single spaces
    _calculation.erase(new_end, _calculation.end()); // shortens the string
    _calculation.erase(_calculation.find_last_not_of(' ') + 1); // crops whitespace at the end of _calculation
    if (_calculation.find_first_not_of(' ') - 1 != std::string::npos) {
        _calculation.erase(_calculation.find_first_not_of(' ') - 1, 1); // finally crops whitespace at the beginning if necessary
    }
}


template <typename T>
std::string Stack<T>::extract_single_op() {
    using namespace std;
    string s;
    if (!_calculation.empty()) {
        size_t position = _calculation.find_first_of(' ');
        if (position == string::npos) {
            s = _calculation;
            _calculation.clear();
        }
        s = _calculation.substr(0, position);
        _calculation.erase(0, position + 1);
    }
    return s;
}

template <typename T>
bool Stack<T>::is_correct_operand(std::string& s) {
    bool correct_operand = true;
    using namespace std;
    if (_type_name == "int") {
        try {
            stoi(s);
        } catch (invalid_argument&) {
            correct_operand = false;
        } catch (out_of_range&) {
            correct_operand = false;
        }
    } else if (_type_name == "float") {
        try {
            stof(s);
        } catch (invalid_argument&) {
            correct_operand = false;
        } catch (out_of_range&) {
            correct_operand = false;
        }
    } else if (_type_name == "double") {
        try {
            stod(s);
        } catch (invalid_argument&) {
            correct_operand = false;
        } catch (out_of_range&) {
            correct_operand = false;
        }
    }
    return correct_operand;
}

template <typename T>
bool Stack<T>::is_correct_operator(std::string& s) {
    return s == "/" || s == "*" || s == "-" || s == "+";
}

template <typename T>
void Stack<T>::process_calculation() {
    using namespace std;
    string single_op = extract_single_op();
    if (is_correct_operand(single_op)) {
        cout << "|" << single_op << "| ist ein korrekter Operand! Jippie ja jeiii!" << endl;
        // push_shit_to_stack
    } else {
        cout << "|" << single_op << "| ist leider kein korrekter Operand..." << endl;
    }
    if (is_correct_operator(single_op)) {
        cout << "Korrekter Operator! Jippie ja jeiii!" << endl;
        // TRY TO execute_operation... catch TooFewOperandsException&
    } else {
        cout << "Leider kein korrekter Operator..." << endl;
    }
}

// ----------------------------------------------------------------------------------------------------
// -------------------------------- private static methods definition ---------------------------------
// ----------------------------------------------------------------------------------------------------

template <typename T>
bool Stack<T>::both_are_spaces(char left, char right) {
    return (left == right) && (left == ' ');
}

// ----------------------------------------------------------------------------------------------------
// ------------------------------------ public methods definition -------------------------------------
// ----------------------------------------------------------------------------------------------------

template <typename T>
Stack<T>::Stack(std::string calculation_input, std::string type_name) {
    _calculation = std::move(calculation_input);
    remove_unnecessary_whitespace();
    _type_name = std::move(type_name);
}

template <typename T>
Stack<T>::~Stack() {
    _values.clear();
}

template <typename T>
void Stack<T>::set_calculation(std::string calculation_input, std::string type_name) {
    _calculation = std::move(calculation_input);
    _type_name = std::move(type_name);
}

template <typename T>
std::string Stack<T>::get_calculation() {
    return _calculation;
}

template <typename T>
void Stack<T>::push(T val) {
    _values.push_back(val);
}

template <typename T>
T Stack<T>::top() {
    if (!is_empty()) {
        return _values.back();
    }
    throw EmptyStackException();
}

template <typename T>
T Stack<T>::pop() {
    if (!is_empty()) {
        T last_val = top();
        _values.pop_back();
        return last_val;
    }
    throw EmptyStackException();
}

template <typename T>
void Stack<T>::print_current_stack() {
    for (T& val : _values) {
        std::cout << val << ", ";
    }
}

// ----------------------------------------------------------------------------------------------------
// --------------------------------- public static methods definition ---------------------------------
// ----------------------------------------------------------------------------------------------------


#endif //UMGEKEHRTER_POLE_CPP_STACK_HPP