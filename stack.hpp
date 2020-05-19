//
// Created by Mina (Marina Inokuchi) on 18.05.2020.
// Padmina91 (GitHub)
//

#ifndef UMGEKEHRTER_POLE_CPP_STACK_HPP
#define UMGEKEHRTER_POLE_CPP_STACK_HPP

//#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include "exception.hpp"

template <typename T>
class Stack {
private:
// ---------------------------------------- private attributes ----------------------------------------
    std::vector<T> _values;
    
    std::string _calculation;
    
    std::string _type_name;

// ----------------------------------- private methods declaration ------------------------------------
    void check_vector_type_equals_type_name();

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

// ------------------------------- private static methods declaration ---------------------------------
    static bool both_are_spaces(char left, char right);

public:
// ------------------------------------ public methods declaration ------------------------------------
    explicit Stack(std::string type_name);
    
    explicit Stack(std::string calculation_input, const std::string& type_name);
    
    void set_calculation(std::string calculation_input);
    
    std::string get_calculation();
    
    void print_current_stack();
    
    void process_calculation();
    
    T get_result();
};

// ------------------------------------ private methods definition ------------------------------------

template <typename T>
void Stack<T>::check_vector_type_equals_type_name() {
    bool type_correct = false;
    if (_type_name == "int") {
        type_correct = sizeof(T) == sizeof(int); // rules out everything but unsigned, int, float
        if (type_correct) {
            T compare_test_lhs = 6.5;
            int compare_test_rhs = 6;
            type_correct = (float) compare_test_lhs == (float) compare_test_rhs; // rules out float
        }
        if (type_correct) {
            T negative_test = -5;
            type_correct = negative_test < 0; // rules out unsigned
        }
    } else if (_type_name == "unsigned") {
        T negative_test = -5;
        type_correct = negative_test > 0; // T must be unsigned if this is true
    } else if (_type_name == "float") {
        type_correct = sizeof(T) == sizeof(float); // rules out double
        if (type_correct) {
            T float_test_lhs = 6.5f;
            float float_test_rhs = 6.5f;
            type_correct = (float) float_test_lhs == float_test_rhs; // rules out all int types
        }
    } else { // _type_name = "double"
        type_correct = sizeof(T) == sizeof(double); // leaves only double, long long int and unsigned long long int
        if (type_correct) {
            T double_test_lhs = 6.5;
            double double_test_rhs = 6.5;
            type_correct = (double) double_test_lhs == double_test_rhs; // rules out all int types
        }
    }
    if (!type_correct) {
        _values.clear();
        _calculation.clear();
        throw TypesNotMatchingException();
    }
}


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
    while (position !=
           std::string::npos) { // npos is the largest possible size_t. It's the return value of find_first_of() if no occurrence is found
        position = _calculation.find_first_of("\n\t\r");
        if (position != std::string::npos) {
            _calculation.replace(position, 1, " "); // first, replaces all non-space whitespace by spaces
        }
    }
    std::string::iterator new_end = std::unique(_calculation.begin(), _calculation.end(),
                                                both_are_spaces); // removes all non-single spaces
    _calculation.erase(new_end, _calculation.end()); // shortens the string
    _calculation.erase(_calculation.find_last_not_of(' ') + 1); // crops whitespace at the end of _calculation
    if (_calculation.find_first_not_of(' ') - 1 != std::string::npos) {
        _calculation.erase(_calculation.find_first_not_of(' ') - 1,
                           1); // finally crops whitespace at the beginning if necessary
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
        } else {
            s = _calculation.substr(0, position);
            _calculation.erase(0, position + 1);
        }
    }
    return s;
}

template <typename T>
bool Stack<T>::is_correct_operand(std::string& s) {
    bool correct_operand = true;
    int num_of_decimal_points = 0;
    if (_type_name == "int" || _type_name == "unsigned") {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] > '9' || s[i] < '0') {
                correct_operand = false;
            }
            if (i == 0 && s[i] == '-' && _type_name == "int" && s.size() > 1) {
                correct_operand = true;
            }
        }
    } else {
        for (int i = 0; i < s.size(); i++) {
            if ((s[i] > '9' || s[i] < '0') && s[i] != '.') {
                correct_operand = false;
            }
            if (i == 0 && s[i] == '-' && s.size() > 1) {
                correct_operand = true;
            }
            if (s[i] == '.') {
                num_of_decimal_points++;
            }
        }
        if (num_of_decimal_points > 1) {
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
void Stack<T>::execute_operation(const std::string& op) {
    if (is_empty() || only_one_element_left()) {
        _calculation.clear();
        _values.clear();
        throw TooFewOperandsException();
    }
    T op2 = pop();
    T op1 = pop();
    if (op == "/") {
        if (op2 == (T) 0) {
            throw DivisionByZeroException();
        } else {
            T result = op1 / op2;
            push(result);
        }
    }
    if (op == "*") {
        T result = op1 * op2;
        push(result);
    }
    if (op == "-") {
        T result = op1 - op2;
        push(result);
    }
    if (op == "+") {
        T result = op1 + op2;
        push(result);
    }
}

// -------------------------------- private static methods definition ---------------------------------

template <typename T>
bool Stack<T>::both_are_spaces(char left, char right) {
    return (left == right) && (left == ' ');
}

// ------------------------------------ public methods definition -------------------------------------

template <typename T>
Stack<T>::Stack(std::string type_name) {
    if (type_name == "int" || type_name == "unsigned" || type_name == "float" || type_name == "double") {
        _type_name = std::move(type_name);
    } else {
        throw InvalidDataTypeException();
    }
    check_vector_type_equals_type_name();
}

template <typename T>
Stack<T>::Stack(std::string calculation_input, const std::string& type_name) : Stack(type_name) {
    _calculation = std::move(calculation_input);
    remove_unnecessary_whitespace();
}

template <typename T>
void Stack<T>::set_calculation(std::string calculation_input) {
    check_vector_type_equals_type_name();
    _calculation = std::move(calculation_input);
    remove_unnecessary_whitespace();
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

template <typename T>
void Stack<T>::process_calculation() {
    check_vector_type_equals_type_name();
    while (!_calculation.empty()) {
        std::string single_op = extract_single_op(); // op = either operand or operator
        if (is_correct_operand(single_op)) {
            push(single_op);
        } else if (is_correct_operator(single_op)) {
            execute_operation(single_op);
        } else {
            throw InvalidSyntaxException();
        }
    }
    if (!only_one_element_left()) {
        // if there are two or more numbers left on the stack
        throw InvalidSyntaxException();
    }
}

template <typename T>
T Stack<T>::get_result() {
    if (only_one_element_left()) {
        return _values[0];
    }
    return 0;
}

#endif //UMGEKEHRTER_POLE_CPP_STACK_HPP