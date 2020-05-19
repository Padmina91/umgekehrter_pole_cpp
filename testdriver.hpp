//
// Created by Mina (Marina Inokuchi) on 19.05.2020.
// Padmina91 (GitHub)
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
    void test09(const std::string& type_name);
    
    template <typename T>
    void test10(const std::string& type_name);
    
    template <typename T>
    void test11(const std::string& type_name);
    
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
    std::string calculation06_1 = "5 -";
    Stack<T> test_stack06_1(calculation06_1, type_name);
    try {
        test_stack06_1.process_calculation();
    } catch (TooFewOperandsException&) {
        test_successful = true;
    }
    if (test_successful) {
        test_successful = false;
        std::string calculation06_2 = "/ 5 7";
        Stack<T> test_stack06_2(type_name);
        test_stack06_2.set_calculation(calculation06_2);
        try {
            test_stack06_2.process_calculation();
        } catch (TooFewOperandsException&) {
            test_successful = true;
        }
    }
    
    if (test_successful) {
        std::cout << "Test 6 erfolgreich." << std::endl;
    } else {
        std::cout << "Test 6 fehlgeschlagen." << std::endl;
    }
}

template <typename T>
void Testdriver::test07(const std::string& type_name) {
    bool test_successful = false;
    if (type_name == "int" || type_name == "unsigned") {
        Stack<T> test_stack07_1(type_name);
        test_stack07_1.set_calculation("5.48 7.78 *");
        try {
            test_stack07_1.process_calculation();
        } catch (InvalidSyntaxException&) {
            test_successful = true;
        }
        if (test_successful) {
            test_successful = false;
            Stack<T> test_stack07_2("8 4*78/", type_name);
            try {
                test_stack07_2.process_calculation();
            } catch (InvalidSyntaxException&) {
                test_successful = true;
            }
        }
    } else {
        Stack<T> test_stack07_3(type_name);
        test_stack07_3.set_calculation("5.48.74 87.15 -");
        try {
            test_stack07_3.process_calculation();
        } catch (InvalidSyntaxException&) {
            test_successful = true;
        }
        if (test_successful) {
            test_successful = false;
            Stack<T> test_stack07_4("5.74/   *-*/", type_name);
            try {
                test_stack07_4.process_calculation();
            } catch (InvalidSyntaxException&) {
                test_successful = true;
            }
        }
    }
    
    if (test_successful) {
        std::cout << "Test 7 erfolgreich." << std::endl;
    } else {
        std::cout << "Test 7 fehlgeschlagen." << std::endl;
    }
}

template <typename T>
void Testdriver::test08(const std::string& type_name) {
    bool test_successful = false;
    if (type_name == "int" || type_name == "unsigned") {
        Stack<T> test_stack08_1("7954849815648796215515464854684 7 -", type_name);
        try {
            test_stack08_1.process_calculation();
        } catch (InvalidNumberException&) {
            test_successful = true;
        }
    } else if (type_name == "float") {
        Stack<T> test_stack08_2(
                "7954849815648795186548484457621551546846887896435125152485854545464854684.7878515858484312518254848543458 7 -",
                type_name);
        try {
            test_stack08_2.process_calculation();
        } catch (InvalidNumberException&) {
            test_successful = true;
        }
    } else {
        test_successful = true; // there is no real overflow in double, it will just lose precision
    }
    
    if (test_successful) {
        std::cout << "Test 8 erfolgreich." << std::endl;
    } else {
        std::cout << "Test 8 fehlgeschlagen." << std::endl;
    }
}

template <typename T>
void Testdriver::test09(const std::string& type_name) {
    bool test_successful = false;
    Stack<T> test_stack09(type_name);
    if (type_name == "int") {
        int expected_result = (-8 + 9 - 1) * 45 / 3;
        std::string calculation = "-8 9 + 1 - 45 * 3 /";
        test_stack09.set_calculation(calculation);
        test_stack09.process_calculation();
        T result = test_stack09.get_result();
        if (result == expected_result) {
            test_successful = true;
        }
    } else if (type_name == "unsigned") {
        unsigned expected_result = (851 - 87 / 2) * 9 + 5;
        std::string calculation = "851 87 2 / - 9 * 5 +";
        test_stack09.set_calculation(calculation);
        test_stack09.process_calculation();
        T result = test_stack09.get_result();
        if (result == expected_result) {
            test_successful = true;
        }
    } else if (type_name == "float") {
        float expected_result = (5.4f - 1.0348f) * 78.74f / 4.4f + 100.7f;
        std::string calculation = "5.4 1.0348 - 78.74 * 4.4 / 100.7 +";
        test_stack09.set_calculation(calculation);
        test_stack09.process_calculation();
        T result = test_stack09.get_result();
        if (result == expected_result) {
            test_successful = true;
        }
    } else {
        double expected_result = (53.1612676456 * 45.48789 + 7.78954) / 485.89851 - (-74.4136925);
        std::string calculation = "53.1612676456 45.48789 * 7.78954 + 485.89851 / -74.4136925 -";
        test_stack09.set_calculation(calculation);
        test_stack09.process_calculation();
        T result = test_stack09.get_result();
        if (result == expected_result) {
            test_successful = true;
        }
    }
    
    if (test_successful) {
        std::cout << "Test 9 erfolgreich." << std::endl;
    } else {
        std::cout << "Test 9 fehlgeschlagen." << std::endl;
    }
}

template <typename T>
void Testdriver::test10(const std::string& type_name) {
    bool test_successful = false;
    if (type_name == "int" || type_name == "unsigned") {
        Stack<T> test_stack10_1("4 0 /", type_name);
        try {
            test_stack10_1.process_calculation();
        } catch (DivisionByZeroException&) {
            test_successful = true;
        }
    } else {
        Stack<T> test_stack10_2("4.0 0.0 /", type_name);
        try {
            test_stack10_2.process_calculation();
        } catch (DivisionByZeroException&) {
            test_successful = true;
        }
    }

    if (test_successful) {
        std::cout << "Test 10 erfolgreich." << std::endl;
    } else {
        std::cout << "Test 10 fehlgeschlagen." << std::endl;
    }
}

template <typename T>
void Testdriver::test11(const std::string& type_name) {
    bool test_successful = false;
    Stack<T> test_stack11("6", type_name);
    test_stack11.process_calculation();
    if (test_stack11.get_result() == (T) 6) {
        test_successful = true;
    }
    
    if (test_successful) {
        std::cout << "Test 11 erfolgreich." << std::endl;
    } else {
        std::cout << "Test 11 fehlgeschlagen." << std::endl;
    }
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
    test09<T>(type_name);
    test10<T>(type_name);
    test11<T>(type_name);
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
