#include <iostream>


// defines Interface {
//  void method1();
//  int method2();
// }
#include "interface.h"


// a class that implicitly implements Interface
// but does not have to derive from it
class GoodClass {
public:
    void method1() {
        std::cout << "called GoodClass::method1\n";
    }
    int method2() {
        std::cout << "called GoodClass::method2\n";
        return 42;
    }
};

// another one to demonstrate polymorphism
class EvilClass {
public:
    void method1() {
        std::cout << "called EvilClass::method1\n";
    }
    int method2() {
        std::cout << "called EvilClass::method2\n";
        return 666;
    }
};


// a nontemplate function that can be called with any of the above types
void use_interface(Interface i) {
    i.method1();
    int val = i.method2();
    std::cout << "returned " << val << "\n";
}


int main() {
    GoodClass good;
    EvilClass evil;

    use_interface(good);
    // prints:
    // called GoodClass::method1
    // called GoodClass::method2
    // returned 42

    use_interface(evil);
    // prints:
    // called EvilClass::method1
    // called EvilClass::method2
    // returned 666
}
