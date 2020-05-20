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
    void check_vector_type_matches_type_name();
    
    bool is_empty();
    
    bool has_one_element();
    
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
    static bool both_are_spaces(char lhs, char rhs);

public:
// ------------------------------------ public methods declaration ------------------------------------
    explicit Stack(std::string type_name);
    
    explicit Stack(std::string calculation_input, const std::string& type_name);
    
    void set_calculation(std::string calculation_input);
    
    std::string get_calculation();
    
    void process_calculation();
    
    T get_result();
};




// ------------------------------------ private methods definition ------------------------------------

/**
 * Prüft, ob der übergebene String _type_name zum Datentyp des Stacks passt.
 * @tparam T (typename)
 * @throws TypesNotMatchingException
 */
template <typename T>
void Stack<T>::check_vector_type_matches_type_name() {
    bool type_correct;
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

/**
 * Gibt an, ob der Stack leer ist.
 * @tparam T (typename)
 * @return is_empty (bool)
 */
template <typename T>
bool Stack<T>::is_empty() {
    return _values.size() == 0;
}

/**
 * Gibt an, ob exakt ein Element im Stack ist
 * @tparam T (typename)
 * @return has_one_element (bool)
 */
template <typename T>
bool Stack<T>::has_one_element() {
    return _values.size() == 1;
}

/**
 * Entfernt jeglichen überflüssigenen Leerraum aus _calculation
 * @tparam T (typename)
 */
template <typename T>
void Stack<T>::remove_unnecessary_whitespace() {
    if (!_calculation.empty()) {
        size_t position = 0;
        // npos is the largest possible size_t. It's the return value of find_first_of() if no occurrence is found
        while (position != std::string::npos) {
            position = _calculation.find_first_of("\n\t\r");
            if (position != std::string::npos) {
                _calculation.replace(position, 1, " "); // first, replaces all non-space whitespace by spaces
            }
        }
        // removes all non-single spaces
        std::string::iterator new_end = std::unique(_calculation.begin(), _calculation.end(), both_are_spaces);
        _calculation.erase(new_end, _calculation.end()); // shortens the string
        _calculation.erase(_calculation.find_last_not_of(' ') + 1); // crops whitespace at the end of _calculation
        if (_calculation.find_first_not_of(' ') - 1 != std::string::npos) {
            // finally crops whitespace at the beginning if necessary
            _calculation.erase(_calculation.find_first_not_of(' ') - 1, 1);
        }
    }
}

/**
 * Extrahiert einen einzelnen Operanden oder Operator aus _calculation
 * und kürzt _calculation dementsprechend.
 * @tparam T (typename)
 * @return single_op (std::string)
 */
template <typename T>
std::string Stack<T>::extract_single_op() {
    std::string single_op;
    if (!_calculation.empty()) {
        size_t pos = _calculation.find_first_of(' ');
        if (pos == std::string::npos) {
            single_op = _calculation;
            _calculation.clear();
        } else {
            single_op = _calculation.substr(0, pos);
            _calculation.erase(0, pos + 1);
        }
    }
    return single_op;
}

/**
 * Prüft, ob der übergebene String ein korrekter Operand
 * (also eine valide Zahl vom angegebenen Datentypen) ist.
 * @tparam T (typename)
 * @param s (std::string&)
 * @return correct_operand (bool)
 */
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

/**
 * Prüft, ob der übergebene String ein korrekter Operator (+ - / *) ist.
 * @tparam T (typename)
 * @param s (std::string&)
 * @return correct_operator (bool)
 */
template <typename T>
bool Stack<T>::is_correct_operator(std::string& s) {
    return s == "/" || s == "*" || s == "-" || s == "+";
}

/**
 * Legt einen als String vorliegenden Operanden auf den Stack
 * @tparam T (typename)
 * @param single_op (std::string&)
 * @throws InvalidNumberException
 */
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

/**
 * Legt einen als Wert vorliegenden Operanden auf den Stack
 * @tparam T (typename)
 * @param val (T)
 */
template <typename T>
void Stack<T>::push(T val) {
    _values.push_back(val);
}

/**
 * Liefert das oberste Element des Stapels zurück
 * @tparam T (typename)
 * @throws EmptyStackException
 * @return top_element (T)
 */
template <typename T>
T Stack<T>::top() {
    if (!is_empty()) {
        return _values.back();
    }
    throw EmptyStackException();
}

/**
 * Entfernt das oberste Element aus dem Stack und liefert es zurück
 * @tparam T (typename)
 * @throws EmptyStackException
 * @return top_element (T)
 */
template <typename T>
T Stack<T>::pop() {
    if (!is_empty()) {
        T top_element = top();
        _values.pop_back();
        return top_element;
    }
    throw EmptyStackException();
}

/**
 * Führt eine einzelne Operation (Addition, Subtraktion, ...) aus.
 * Hierzu entfernt die Funktion die obersten zwei Werte aus dem Stack
 * und legt das Ergebnis auf den Stack.
 * @tparam T (typename)
 * @throws TooFewOperandsException
 * @throws DivisionByZeroException
 * @param op (const std::string&)
 */
template <typename T>
void Stack<T>::execute_operation(const std::string& op) {
    if (is_empty() || has_one_element()) {
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

/**
 * Hilfsfunktion für remove_unnecessary_whitespace. Gibt an, ob
 * beide Parameter Leerzeichen sind.
 * (lhs = left hand side, rhs = right hand side)
 * @tparam T (typename)
 * @param lhs (char)
 * @param rhs (char)
 * @return both_are_spaces (bool)
 */
template <typename T>
bool Stack<T>::both_are_spaces(char lhs, char rhs) {
    return (lhs == rhs) && (lhs == ' ');
}

// ------------------------------------ public methods definition -------------------------------------

/**
 * Konstruktor: erstellt ein Objekt ohne _calculation zu füllen.
 * Dies muss dann manuell über set_calculation() nachgeholt werden.
 * @tparam T (typename)
 * @param type_name (std::string)
 * @throws InvalidDataTypeException
 */
template <typename T>
Stack<T>::Stack(std::string type_name) {
    if (type_name == "int" || type_name == "unsigned" || type_name == "float" || type_name == "double") {
        _type_name = std::move(type_name);
    } else {
        throw InvalidDataTypeException();
    }
    check_vector_type_matches_type_name();
}

/**
 * Überladener Konstruktor: erstellt ein Objekt und füllt den String _calculation
 * @tparam T (typename)
 * @param calculation_input (std::string)
 * @param type_name (const std::string&)
 */
template <typename T>
Stack<T>::Stack(std::string calculation_input, const std::string& type_name) : Stack(type_name) {
    _calculation = std::move(calculation_input);
    remove_unnecessary_whitespace();
}

/**
 * Füllt das private Attribut _calculation mit dem übergebenen String
 * @tparam T (typename)
 * @param calculation_input (std::string)
 */
template <typename T>
void Stack<T>::set_calculation(std::string calculation_input) {
    check_vector_type_matches_type_name();
    _calculation = std::move(calculation_input);
    remove_unnecessary_whitespace();
}

/**
 * Gibt den Inhalt von _calculation zurück.
 * @tparam T (typename)
 * @return _calculation (std::string)
 */
template <typename T>
std::string Stack<T>::get_calculation() {
    return _calculation;
}

/**
 * Führt die Berechnung aus. Hierfür kürzt es Stück für Stück
 * den String _calculation bis er leer ist und benutzt den Stack
 * für die Berechnung.
 * @tparam T (typename)
 * @throws InvalidSyntaxException
 * @throws InvalidResultException
 */
template <typename T>
void Stack<T>::process_calculation() {
    _values.clear();
    check_vector_type_matches_type_name();
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
    if (!has_one_element()) {
        // if there are two or more numbers left on the stack
        throw InvalidResultException();
    }
}

/**
 * Gibt das Ergebnis zurück, falls nur noch ein Element auf dem Stack liegt.
 * Sollten noch mehrere Elemente vorhanden sein, gibt die Methode 0 zurück.
 * @tparam T (typename)
 * @throws InvalidResultException
 * @return result (T)
 */
template <typename T>
T Stack<T>::get_result() {
    if (has_one_element()) {
        return _values[0];
    }
    throw InvalidResultException();
}

#endif //UMGEKEHRTER_POLE_CPP_STACK_HPP