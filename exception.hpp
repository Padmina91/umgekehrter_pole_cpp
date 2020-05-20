//
// Created by Mina (Marina Inokuchi) on 18.05.2020.
// Padmina91 (GitHub)
//

#ifndef UMGEKEHRTER_POLE_CPP_EXCEPTION_HPP
#define UMGEKEHRTER_POLE_CPP_EXCEPTION_HPP

#include <exception>

class TypesNotMatchingException : public std::exception {};

class InvalidSyntaxException : public std::exception {};

class InvalidResultException : public std::exception {};

class InvalidNumberException : public std::exception {};

class DivisionByZeroException : public std::exception {};

class TooFewOperandsException : public std::exception {};

class EmptyStackException : public std::exception {};

class InvalidDataTypeException : public std::exception {};

#endif //UMGEKEHRTER_POLE_CPP_EXCEPTION_HPP