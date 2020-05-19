//
// Created by Mina on 19.05.2020.
//

#ifndef UMGEKEHRTER_POLE_CPP_TESTDRIVER_HPP
#define UMGEKEHRTER_POLE_CPP_TESTDRIVER_HPP

#include "stack.hpp"

class Testdriver {
private:
// ----------------------------------- private methods declaration ------------------------------------
    static void test1();
    
    template <typename T>
    void test2(const std::string& type_name);
    
    template <typename T>
    void test3(const std::string& type_name);
    
    template <typename T>
    void test4(const std::string& type_name);
    
    template <typename T>
    void test5(const std::string& type_name);
    
    template <typename T>
    void test6(const std::string& type_name);
    
    template <typename T>
    void test7(const std::string& type_name);
    
    template <typename T>
    void test8(const std::string& type_name);
    
    template <typename T>
    void execute_all_tests(const std::string& type_name);

public:
// -------------------------------- public static methods declaration ---------------------------------
    static void execute_tests();
};

// ------------------------------------ private methods definition ------------------------------------

void Testdriver::test1() {
    bool catch_activated = false;
    try {
        Stack<int> test_stack01("8 7 +", "int aaaaaaaaa 235 14  55");
    } catch (InvalidDataTypeException&) {
        catch_activated = true;
    }
    if (catch_activated) {
        try {
            catch_activated = false;
            Stack<int> test_stack02;
            test_stack02.set_calculation("2 -85 -", "asdf");
        } catch (InvalidDataTypeException&) {
            catch_activated = true;
            std::cout << "Test 1 erfolgreich." << std::endl;
        }
    }
    if (!catch_activated) {
        std::cout << "Test 1 fehlgeschlagen." << std::endl;
    }
}

template <typename T>
void Testdriver::test2(const std::string& type_name) {
    std::cout << "Test 2..." << std::endl;
}

template <typename T>
void Testdriver::test3(const std::string& type_name) {
    std::cout << "Test 3..." << std::endl;
}

template <typename T>
void Testdriver::test4(const std::string& type_name) {
    std::cout << "Test 4..." << std::endl;
}

template <typename T>
void Testdriver::test5(const std::string& type_name) {
    std::cout << "Test 5..." << std::endl;
}

template <typename T>
void Testdriver::test6(const std::string& type_name) {
    std::cout << "Test 6..." << std::endl;
}

template <typename T>
void Testdriver::test7(const std::string& type_name) {
    std::cout << "Test 7..." << std::endl;
}

template <typename T>
void Testdriver::test8(const std::string& type_name) {
    std::cout << "Test 8..." << std::endl;
}

template <typename T>
void Testdriver::execute_all_tests(const std::string& type_name) {
    test1();
    test2<T>(type_name);
    test3<T>(type_name);
    test4<T>(type_name);
    test5<T>(type_name);
    test6<T>(type_name);
    test7<T>(type_name);
    test8<T>(type_name);
    std::cout << std::endl;
}


// --------------------------------- public static methods definition ---------------------------------

void Testdriver::execute_tests() {
    Testdriver testdriver;
    testdriver.execute_all_tests<int>("int");
    testdriver.execute_all_tests<unsigned>("unsigned");
    testdriver.execute_all_tests<float>("float");
    testdriver.execute_all_tests<double>("double");
}

#endif //UMGEKEHRTER_POLE_CPP_TESTDRIVER_HPP
