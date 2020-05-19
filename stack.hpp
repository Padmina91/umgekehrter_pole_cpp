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
    
    void push(const std::string& single_op);
    
    void push(T val);
    
    T top();
    
    T pop();
    
    void execute_operation(const std::string& op);
    
    void process_calculation();

// ----------------------------------------------------------------------------------------------------
// ------------------------------- private static methods declaration ---------------------------------
// ----------------------------------------------------------------------------------------------------
    static bool both_are_spaces(char left, char right);

public:
// ----------------------------------------------------------------------------------------------------
// ------------------------------------ public methods declaration ------------------------------------
// ----------------------------------------------------------------------------------------------------
    explicit Stack(std::string calculation_input, std::string type_name);
    
    void set_calculation(std::string calculation_input, std::string type_name);
    
    std::string get_calculation();
    
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
    std::string s;
    if (!_calculation.empty()) {
        size_t position = _calculation.find_first_of(' ');
        if (position == std::string::npos) {
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
    if (_type_name == "int" || _type_name == "unsigned") {
        for (int i = 0; i <s.size(); i++) {
            if (s[i] > '9' || s[i] < '0') {
                correct_operand = false;
            }
            if (i == 0 && s[i] == '-' && _type_name == "int" && s.size() > 1) {
                correct_operand = true;
            }
        }
    } else {
        for (int i = 0; i <s.size(); i++) {
            if ((s[i] > '9' || s[i] < '0') && s[i] != '.') {
                correct_operand = false;
            }
            if (i == 0 && s[i] == '-' && s.size() > 1) {
                correct_operand = true;
            }
        }
    }
    return correct_operand;
}

template <typename T>
bool Stack<T>::is_correct_operator(std::string& s) {
    return s == "/" || s == "*" || s == "-" || s == "+";
}

template <typename T>
void Stack<T>::push(const std::string& single_op) {
    if (_type_name == "int") {
        try {
            _values.push_back(stoi(single_op));
        } catch (std::invalid_argument&) {
            _calculation.clear();
            _values.clear();
            throw InvalidNumberException();
        } catch (std::out_of_range&) {
            _calculation.clear();
            _values.clear();
            throw InvalidNumberException();
        }
    }
    if (_type_name == "unsigned") {
        try {
            _values.push_back(stoul(single_op));
        } catch (std::invalid_argument&) {
            _calculation.clear();
            _values.clear();
            throw InvalidNumberException();
        } catch (std::out_of_range&) {
            _calculation.clear();
            _values.clear();
            throw InvalidNumberException();
        }
    }
    if (_type_name == "float") {
        try {
            _values.push_back(stof(single_op));
        } catch (std::invalid_argument&) {
            _calculation.clear();
            _values.clear();
            throw InvalidNumberException();
        } catch (std::out_of_range&) {
            _calculation.clear();
            _values.clear();
            throw InvalidNumberException();
        }
    }
    if (_type_name == "double") {
        try {
            _values.push_back(stod(single_op));
        } catch (std::invalid_argument&) {
            _calculation.clear();
            _values.clear();
            throw InvalidNumberException();
        } catch (std::out_of_range&) {
            _calculation.clear();
            _values.clear();
            throw InvalidNumberException();
        }
    }
}

template <typename T>
void Stack<T>::push(T val) {

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
void Stack<T>::execute_operation(const std::string& op) {
    if (op == "/") {
        T op2 = pop();
        T op1 = pop();
        if (op2 == (T) 0) {
            throw DivisionByZeroException();
        } else {
        
        }
    }
    if (op == "*") {
    
    }
    if (op == "-") {
    
    }
    if (op == "+") {
    
    }
}

template <typename T>
void Stack<T>::process_calculation() {
    std::string single_op = extract_single_op(); // TODO: check if single_op is empty!
    if (is_correct_operand(single_op)) {
        try {
            push(single_op);
        } catch(InvalidNumberException&) {
            throw InvalidNumberException();
        }
    }
    if (is_correct_operator(single_op)) {
        // TRY TO execute_operation... catch TooFewOperandsException&
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
    if (type_name == "int" || type_name == "unsigned" || type_name == "float" || type_name == "double") {
        _type_name = std::move(type_name);
    } else {
        throw InvalidDataTypeException();
    }
}

template <typename T>
void Stack<T>::set_calculation(std::string calculation_input, std::string type_name) {
    _calculation = std::move(calculation_input);
    if (type_name == "int" || type_name == "unsigned" || type_name == "float" || type_name == "double") {
        _type_name = std::move(type_name);
    } else {
        throw InvalidDataTypeException();
    }
}

template <typename T>
std::string Stack<T>::get_calculation() {
    return _calculation;
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