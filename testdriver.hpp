//
// Created by Mina on 19.05.2020.
//

#ifndef UMGEKEHRTER_POLE_CPP_TESTDRIVER_HPP
#define UMGEKEHRTER_POLE_CPP_TESTDRIVER_HPP

#include "stack.hpp"

class Testdriver {
private:
// ----------------------------------- private methods declaration ------------------------------------
    template <typename T>
    void test01();
    
    template <typename T>
    void test02(const std::string& type_name);
    
    template <typename T>
    void test03(const std::string& type_name);
    
    template <typename T>
    void test04(const std::string& type_name);
    
    template <typename T>
    void test05(const std::string& type_name);
    
    template <typename T>
    void test06(const std::string& type_name);
    
    template <typename T>
    void test07(const std::string& type_name);
    
    template <typename T>
    void test08(const std::string& type_name);
    
    template <typename T>
    void execute_all_tests(const std::string& type_name);

public:
// -------------------------------- public static methods declaration ---------------------------------
    static void execute_tests();
};

// ------------------------------------ private methods definition ------------------------------------

template <typename T>
void Testdriver::test01() {
    bool test_successful = false;
    try {
        Stack<T> test_stack01_1("8 7 +", "int aaaaaaaaa 235 14  55");
    } catch (InvalidDataTypeException&) {
        test_successful = true;
    }
    if (test_successful) {
        try {
            test_successful = false;
            Stack<int> test_stack01_2("asdfasdf float");
        } catch (InvalidDataTypeException&) {
            test_successful = true;
        }
    }
    if (test_successful) {
        std::cout << "Test 1 erfolgreich." << std::endl;
    } else {
        std::cout << "Test 1 fehlgeschlagen." << std::endl;
    }
}

template <typename T>
void Testdriver::test02(const std::string& type_name) {
    bool test_successful = false;
    Stack<T> test_stack02(type_name);
    std::string calculation = "    \r   + \r * / \t   5.4\n 7 \t8 - \r    \t\n\n\n       ";
    test_stack02.set_calculation(calculation);
    if (test_stack02.get_calculation().size() == 15) { // "+ * / 5.4 7 8 -" = 15 Zeichen im String
        test_successful = true;
    }
    if (test_successful) {
        std::cout << "Test 2 erfolgreich." << std::endl;
    } else {
        std::cout << "Test 2 fehlgeschlagen." << std::endl;
    }
}

template <typename T>
void Testdriver::test03(const std::string& type_name) {
    bool test_successful = false;
    std::string calculation = "    \r   l \r * / \t   5.4\n 7 \t8 - \r    \t\n\n\n       ";
    Stack<T> test_stack03_1(calculation, type_name);
    try {
        test_stack03_1.process_calculation();
    } catch (InvalidSyntaxException&) {
        test_successful = true;
    }
    if (test_successful) {
        Stack<T> test_stack03_2(type_name);
        test_stack03_2.set_calculation(calculation);
        try {
            test_successful = false;
            test_stack03_2.process_calculation();
        } catch (InvalidSyntaxException&) {
            test_successful = true;
        }
    }
    if (test_successful) {
        std::cout << "Test 3 erfolgreich." << std::endl;
    } else {
        std::cout << "Test 3 fehlgeschlagen." << std::endl;
    }
}

template <typename T>
void Testdriver::test04(const std::string& type_name) {
    bool test_successful = false;
    Stack<T> test_stack04(type_name);
    std::string calculation;
    
    if (type_name == "int" || type_name == "unsigned") {
        calculation = "5 4 7 6 -";
    } else {
        calculation = "5 4.7 7 6.5 -";
    }
    
    try {
        test_stack04.set_calculation(calculation);
        test_stack04.process_calculation();
    } catch (InvalidSyntaxException&) {
        test_successful = true;
    }
    
    if (test_successful) {
        std::cout << "Test 4 erfolgreich." << std::endl;
    } else {
        std::cout << "Test 4 fehlgeschlagen." << std::endl;
    }
}

template <typename T>
void Testdriver::test05(const std::string& type_name) {
    bool test_successful = false;
    
    if (type_name == "int") {
        try {
            Stack<double> test_stack05_01(type_name);
        } catch (TypesNotMatchingException&) {
            test_successful = true;
        }
        if (test_successful) {
            try {
                Stack<float> test_stack05_02(type_name);
            } catch (TypesNotMatchingException&) {
                test_successful = true;
            }
        }
        if (test_successful) {
            try {
                Stack<unsigned> test_stack05_03(type_name);
            } catch (TypesNotMatchingException&) {
                test_successful = true;
            }
        }
    }
    
    if (type_name == "unsigned") {
        try {
            Stack<double> test_stack05_04(type_name);
        } catch (TypesNotMatchingException&) {
            test_successful = true;
        }
        if (test_successful) {
            try {
                Stack<int> test_stack05_05(type_name);
            } catch (TypesNotMatchingException&) {
                test_successful = true;
            }
        }
        if (test_successful) {
            try {
                Stack<float> test_stack05_06(type_name);
            } catch (TypesNotMatchingException&) {
                test_successful = true;
            }
        }
    }
    
    if (type_name == "float") {
        try {
            Stack<double> test_stack05_07(type_name);
        } catch (TypesNotMatchingException&) {
            test_successful = true;
        }
        if (test_successful) {
            try {
                Stack<int> test_stack05_08(type_name);
            } catch (TypesNotMatchingException&) {
                test_successful = true;
            }
        }
        if (test_successful) {
            try {
                Stack<unsigned> test_stack05_09(type_name);
            } catch (TypesNotMatchingException&) {
                test_successful = true;
            }
        }
    }
    
    if (type_name == "double") {
        try {
            Stack<float> test_stack05_10(type_name);
        } catch (TypesNotMatchingException&) {
            test_successful = true;
        }
        if (test_successful) {
            try {
                Stack<int> test_stack05_11(type_name);
            } catch (TypesNotMatchingException&) {
                test_successful = true;
            }
        }
        if (test_successful) {
            try {
                Stack<unsigned> test_stack05_12(type_name);
            } catch (TypesNotMatchingException&) {
                test_successful = true;
            }
        }
    }
    
    if (test_successful) {
        std::cout << "Test 5 erfolgreich." << std::endl;
    } else {
        std::cout << "Test 5 fehlgeschlagen." << std::endl;
    }
}

template <typename T>
void Testdriver::test06(const std::string& type_name) {
    bool test_successful = false;
    
    
    
    if (test_successful) {
        std::cout << "Test 6 erfolgreich." << std::endl;
    } else {
        std::cout << "Test 6 fehlgeschlagen." << std::endl;
    }
}

template <typename T>
void Testdriver::test07(const std::string& type_name) {
    std::cout << "Test 7..." << std::endl;
}

template <typename T>
void Testdriver::test08(const std::string& type_name) {
    std::cout << "Test 8..." << std::endl;
}

template <typename T>
void Testdriver::execute_all_tests(const std::string& type_name) {
    test01<T>();
    test02<T>(type_name);
    test03<T>(type_name);
    test04<T>(type_name);
    test05<T>(type_name);
    test06<T>(type_name);
    test07<T>(type_name);
    test08<T>(type_name);
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
