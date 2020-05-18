//
// Created by Mina on 18.05.2020.
//

#ifndef UMGEKEHRTER_POLE_CPP_EXCEPTION_HPP
#define UMGEKEHRTER_POLE_CPP_EXCEPTION_HPP

#include <exception>

class InvalidSyntaxException : public std::exception {};

class InvalidNumberException : public std::exception {};

class TooFewOperandsException : public std::exception{};

class EmptyStackException : public std::exception{};

#endif //UMGEKEHRTER_POLE_CPP_EXCEPTION_HPP