# Modern C++ (C++11/14) — Quick Reference

Modern C++ (C++11 and C++14) introduced many features that simplify coding, improve safety, enhance performance, and enable more expressive code. This document summarizes key language improvements with brief explanations and examples.

---

## 1️⃣ Language Improvements

### General Features

#### `constexpr`

* Allows functions and variables to be evaluated at compile time.

```cpp
constexpr int square(int x) { return x * x; }
```

#### `auto` Type Deduction

* The compiler automatically deduces the variable type.

```cpp
auto x = 42; // int
auto name = "Hafiz"; // const char*
```

#### `decltype`

* Deduce the type of an expression.

```cpp
int a = 5;
decltype(a) b = 10; // b is int
```

#### Range-based `for` Loop

* Simplifies iteration over containers.

```cpp
for (auto& num : numbers) {
    std::cout << num << std::endl;
}
```

#### `static_assert`

* Compile-time assertion for constant expressions.

```cpp
static_assert(sizeof(int) == 4, "int size is not 4 bytes");
```

#### `nullptr`

* A type-safe null pointer literal.

```cpp
int* ptr = nullptr;
```

#### Scoped / Strongly-Typed Enums (`enum class`)

* Avoids name clashes; safer than old enums.

```cpp
enum class Color { Red, Green, Blue };
Color c = Color::Red;
```

#### Uniform Initialization (`{}`)

* Consistent initialization syntax for variables, structs, classes.

```cpp
int arr[3] {1, 2, 3};
std::vector<int> v {1, 2, 3, 4};
```

#### `using` Keyword for Type Aliasing

* Cleaner alternative to `typedef`.

```cpp
using IntVec = std::vector<int>;
```

#### User-Defined Literals

* Define custom literal suffixes.

```cpp
constexpr long double operator"" _cm(long double val) { return val / 100; }
auto length = 50.0_cm;
```

#### Binary Literals (`0b`)

* Binary representation of numbers.

```cpp
int mask = 0b10101010;
```

#### Digit Separators (`'`)

* Improve readability of large numbers.

```cpp
int big = 1'000'000;
```

#### Raw String Literals (`R"(...)"`)

* Avoid escaping in strings.

```cpp
std::string path = R"(C:\Program Files\MyApp)";
```

---

## 2️⃣ Class & Object Improvements

#### Defaulted and Deleted Special Member Functions

* Request compiler-generated default or forbid certain operations.

```cpp
class MyClass {
public:
    MyClass() = default;
    MyClass(const MyClass&) = delete;  // No copy constructor
};
```

#### Delegating Constructors

* One constructor calls another within the same class.

```cpp
class MyClass {
public:
    MyClass(int x) { /*...*/ }
    MyClass() : MyClass(0) { }
};
```

#### In-Class Member Initializers

* Initialize member variables directly in class definition.

```cpp
class MyClass {
    int count = 0;
};
```

#### Uniform Initialization

* See earlier uniform `{}` initialization example.

#### `std::initializer_list`

* Allows initializer-list constructors.

```cpp
class MyClass {
public:
    MyClass(std::initializer_list<int> vals) { /*...*/ }
};
MyClass obj {1, 2, 3, 4};
```

#### Explicit Conversion Operators

* Prevent implicit conversions.

```cpp
class MyClass {
public:
    explicit operator bool() const { return true; }
};
```

#### Read-Only Objects (`const` Member Functions)

* Prevent modification of object state.

```cpp
class MyClass {
    int value;
public:
    int get() const { return value; }
};
```

#### Explicit Type Conversion

* Require explicit casting when converting.

```cpp
explicit MyClass(int val) { /*...*/ }
```

#### Type Traits (`<type_traits>`)

* Metaprogramming utilities for type introspection.

```cpp
static_assert(std::is_integral<int>::value, "int is not integral");
```

---

## 3️⃣ Inheritance Improvements

#### `final` and `override` Keywords

* Ensure correct overriding; prevent further overriding.

```cpp
class Base {
public:
    virtual void foo() final;
    virtual void bar() {}
};

class Derived : public Base {
public:
    void bar() override { /* correct override */ }
};
```

#### Inheriting Base Class Constructors

* Simplify constructor inheritance.

```cpp
class Base {
public:
    Base(int) { }
};

class Derived : public Base {
    using Base::Base;
};
```

---

## 4️⃣ Move Semantics

#### Move Constructor & Move Assignment Operator

* Efficient resource transfer, avoid unnecessary copies.

```cpp
class MyClass {
public:
    MyClass(MyClass&& other) noexcept { /* move resources */ }
    MyClass& operator=(MyClass&& other) noexcept { /* move assign */ return *this; }
};
```

#### `std::move()`

* Cast object to rvalue reference to enable move semantics.

```cpp
MyClass obj1;
MyClass obj2 = std::move(obj1);  // obj1 moved
```

### Key Reasons to Use `new` Over `malloc`

| Feature | `new` Operator | `malloc()` Function |
| :--- | :--- | :--- |
| **Object Construction** | Automatically calls the constructor to initialize the object. | Only allocates raw memory; the object remains uninitialized. |
| **Type Safety** | Returns the exact data type pointer (e.g., `int*`), avoiding dangerous casts. | Returns a `void*` which must be manually cast to the correct type. |
| **Error Handling** | Throws a `std::bad_alloc` exception if memory allocation fails. | Returns `NULL`, requiring manual checks after every call. |
| **Size Calculation** | The compiler automatically calculates the required size based on the type. | You must manually calculate the size in bytes using `sizeof()`. |
| **Customization** | Can be overloaded for specific classes to customize how memory is handled. | Cannot be overloaded; its behavior is fixed by the standard library. |

# C++ Lambdas (Introduced in C++11)

A **lambda function** (or lambda expression) is an anonymous, inline function. Instead of formally defining a function with a name, you create it on the fly, exactly where you need it. They are primarily used for short, throwaway operations or passing functions as arguments to other functions.

In C++, lambdas are incredibly powerful because they allow you to "capture" variables from the surrounding scope.

**Basic Syntax:**
```cpp
[capture_clause](parameters) -> return_type { body }
```
*(Note: `-> return_type` is optional; the compiler can usually deduce it).*

## Example A: The Basic Lambda
```cpp
#include <iostream>

int main() {
    // Defining a lambda and assigning it to a variable 'add'
    auto add = [](int a, int b) { 
        return a + b; 
    };

    std::cout << add(5, 3); // Outputs: 8
    return 0;
}
```

## Example B: Capturing Variables (The Capture Clause)
The `[]` brackets dictate what external variables the lambda can access.

```cpp
#include <iostream>

int main() {
    int multiplier = 5;
    int counter = 0;

    // [multiplier] captures by VALUE (read-only copy)
    // [&counter] captures by REFERENCE (can modify the original)
    auto doMath = [multiplier, &counter](int x) {
        counter++; // We can change this because of '&'
        return x * multiplier;
    };

    std::cout << doMath(10) << "\n"; // Outputs: 50
    std::cout << "Function called " << counter << " times."; // Outputs: 1 times.
    return 0;
}
```
*   `[=]` captures *all* external variables by value.
*   `[&]` captures *all* external variables by reference.

## Example C: Using Lambdas with Standard Algorithms
This is where lambdas shine in C++—passing them into functions like `std::sort` or `std::for_each`.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {5, 2, 8, 1, 9};

    // Sort descending using a lambda
    std::sort(numbers.begin(), numbers.end(), [](int a, int b) {
        return a > b; 
    });

    // Print using a lambda
    std::for_each(numbers.begin(), numbers.end(), [](int n) {
        std::cout << n << " ";
    });
    // Outputs: 9 8 5 2 1
    return 0;
}
```
---
A **variadic template** in C++ is a template that can accept an arbitrary number of template arguments. Introduced in C++11, it allows you to write functions and classes that can handle any number of parameters of any type in a type-safe way.

Before C++11, if you wanted a function to take a variable number of arguments, you had to use C-style variadic functions (like `printf`), which are not type-safe, or write dozens of overloaded templates. Variadic templates solve both problems.

Here is a breakdown of how they work, the syntax, and how to use them.

### 1. The Syntax: Parameter Packs and the Ellipsis (`...`)

The magic of variadic templates lies in the ellipsis (`...`). It is used to declare a **parameter pack**, which represents zero or more parameters.

* **Template Parameter Pack:** `template <typename... Args>`
*(Represents a list of types)*
* **Function Parameter Pack:** `void myFunction(Args... args)`
*(Represents a list of values of those types)*
* **Pack Expansion:** `args...`
*(Unpacks the parameters so they can be used)*

### 2. The Traditional Way: Recursion (C++11 / C++14)

Because you cannot simply loop through a parameter pack using a standard `for` loop, the traditional way to unpack them is through **compile-time recursion**. You process the first argument, and then recursively pass the rest of the arguments to the function.

To do this, you need two things:

1. A **Base Case**: To stop the recursion when the pack is empty.
2. A **Recursive Case**: To process one argument and pass the rest forward.

Here is the classic example of a variadic `print` function:

```cpp
#include <iostream>

// 1. Base case: called when the parameter pack is empty
void print() {
    std::cout << " (End of printing)\n";
}

// 2. Recursive case: takes at least one argument, plus a pack of remaining arguments
template <typename T, typename... Rest>
void print(T firstArg, Rest... remainingArgs) {
    std::cout << firstArg << " ";
    
    // Unpack the remaining arguments and call print() again
    print(remainingArgs...); 
}

int main() {
    print(1, "hello", 3.14, 'A'); 
    return 0;
}

```

**How the compiler expands this at compile-time:**

1. `print(1, "hello", 3.14, 'A')` -> prints `1`, calls `print("hello", 3.14, 'A')`
2. `print("hello", 3.14, 'A')` -> prints `"hello"`, calls `print(3.14, 'A')`
3. `print(3.14, 'A')` -> prints `3.14`, calls `print('A')`
4. `print('A')` -> prints `A`, calls `print()`
5. `print()` -> hits the base case, prints `" (End of printing)\n"`

### 3. The Modern Way: Fold Expressions (C++17)

In C++17, the language introduced **Fold Expressions**, which drastically simplifies variadic templates. You no longer need a base case or recursion to perform operations across a parameter pack.

You can "fold" the pack over an operator (like `+`, `<<`, `,`, etc.) directly.

Here is the exact same `print` function rewritten for C++17:

```cpp
#include <iostream>

template <typename... Args>
void print(Args... args) {
    // Fold expression using the comma operator and a lambda/stream
    (std::cout << ... << args) << '\n'; 
    
    // If you want spaces between them:
    // ((std::cout << args << " "), ...) << '\n';
}

int main() {
    print(1, "hello", 3.14, 'A'); // Prints: 1hello3.14A
    return 0;
}

```

### 4. Class Templates

Variadic templates aren't just for functions; they are heavily used in classes. The most famous example in the C++ Standard Library is `std::tuple`, which can hold an arbitrary number of differently typed values.

```cpp
#include <tuple>
#include <string>

// A tuple holding an int, a double, and a string
std::tuple<int, double, std::string> myData(42, 3.14, "C++ is great");

```

### Common Use Cases in Real Code

1. **Perfect Forwarding:** Passing an unknown number of arguments directly to a constructor or another function (e.g., `std::make_shared`, `std::make_unique`, or `std::vector::emplace_back`).
2. **Custom Loggers:** Writing logging systems that accept any number of variables and formats them cleanly.
3. **Type Traits & Metaprogramming:** Checking if a list of types meets certain conditions at compile time (e.g., checking if *all* provided types are arithmetic).


---

# Summary Table

| Feature                     | Purpose                       |
| --------------------------- | ----------------------------- |
| `auto` / `decltype`         | Type deduction                |
| `constexpr`                 | Compile-time evaluation       |
| `nullptr`                   | Safer null pointers           |
| `enum class`                | Scoped enums                  |
| `using`                     | Type alias                    |
| Uniform Initialization `{}` | Unified initialization syntax |
| `static_assert`             | Compile-time assertions       |
| Move Semantics              | Efficient resource handling   |
| `override` / `final`        | Safer inheritance             |
| `std::initializer_list`     | List initialization support   |

---
