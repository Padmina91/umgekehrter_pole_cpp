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

// ----------------------------------------------------------------------------------------------------
// ----------------------------------- private methods declaration ------------------------------------
// ----------------------------------------------------------------------------------------------------
    bool is_empty();
    
    bool only_one_element_left();
    
    void remove_unnecessary_whitespace();

// ----------------------------------------------------------------------------------------------------
// ------------------------------- private static methods declaration ---------------------------------
// ----------------------------------------------------------------------------------------------------
    static bool both_are_spaces(char left, char right);

public:
// ----------------------------------------------------------------------------------------------------
// ------------------------------------ public methods declaration ------------------------------------
// ----------------------------------------------------------------------------------------------------
    explicit Stack(std::string s);
    
    ~Stack();
    
    void set_calculation(std::string s);
    
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
    std::string::iterator new_end = std::unique(_calculation.begin(), _calculation.end(), both_are_spaces);
    _calculation.erase(new_end, _calculation.end());
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
Stack<T>::Stack(std::string s) {
    _calculation = std::move(s);
    remove_unnecessary_whitespace();
}

template <typename T>
Stack<T>::~Stack() {
    _values.clear();
}

template <typename T>
void Stack<T>::set_calculation(std::string s) {
    _calculation = std::move(s);
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