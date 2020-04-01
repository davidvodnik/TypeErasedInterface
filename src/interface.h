#include <stdint.h>

// defines Interface {
//  void method1();
//  int method2();
// }

// This is a Golang style interface (or a Swift Protocol, or Rust Trait Object)
// The idea is that types are not really polymorphic, only their usage is.
// So a dynamic dispatch mechanism is only generated when a type is used in
// a polymorphic setting, otherwise it does not need a vtable.
//
// Unfortunately C++ does not provide this kind of interface natively,
// so some boilerplate is required. The boilerplate looks horrible at
// at first but once familiar it is produced in a very mechanical way.
// With a dedicated tool this could be generated from a simple declaration:
// struct Interface {
//      void method1();
//      int method2();
// };

class Interface {
public:
    // Interface exposed to the users
    void method1() { method1_(val_); }
    int method2() { return method2_(val_); }

    // A templated constructor that generates functions for dynamic dispatch
    // for any type that is used with this interface
    template<typename T>
    Interface(T& t) {
        // save a pointer to passed object
        val_ = reinterpret_cast<uintptr_t>(&t);
        // lambdas without capture are implicitly converted to functions,
        // so this generates specialized functions for each type
        // each function just takes the saved pointer and any other parameters
        // and calls the types actual function
        method1_ = [](uintptr_t t) -> void { reinterpret_cast<T*>(t)->method1(); };
        method2_ = [](uintptr_t t) -> int { return reinterpret_cast<T*>(t)->method2(); };
    }


private:
    // This is a concrete type that just holds a pointer to the wrapped object,
    // and pointers to the functions the interface defines.
    // This could also be implemented with a single pointer to a "vtable class",
    // that would be generated in the constructor instead of the functions.
    void (*method1_)(uintptr_t t);
    int (*method2_)(uintptr_t t);
    uintptr_t val_;
};

