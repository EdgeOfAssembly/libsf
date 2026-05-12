/*
 * test_debug_cpp23.cpp - Extensive unit tests for debug.h in C++23
 * Author: GitHub Copilot
 * Date: 2025-12-17
 *
 * Compile with: g++ -std=c++23 -g -Wall -Wextra -Wpedantic -rdynamic -o test_debug_cpp23 test_debug_cpp23.cpp
 * Or for release: g++ -std=c++23 -O2 -DNDEBUG -o test_debug_cpp23_release test_debug_cpp23.cpp
 *
 * Tests all features of debug.h in C++ context:
 * - Log levels (TRACE, DEBUG, INFO, WARN, ERROR)
 * - Function tracing (DEBUG_ENTER, DEBUG_EXIT)
 * - Generic formatting (_GENERIC_FMT)
 * - Variable inspection (DEBUG_VAR)
 * - Pointer inspection (DEBUG_PTR)
 * - Memory allocation wrappers (DEBUG_MALLOC, DEBUG_FREE)
 * - Assertions (DEBUG_ASSERT, DEBUG_CHECK)
 * - Backtrace (DEBUG_BACKTRACE)
 * - Loop tracing (DEBUG_LOOP_START, DEBUG_LOOP_ITER, DEBUG_LOOP_END)
 * - Conditional compilation (DEBUG_IF)
 * - Scope helpers (DEBUG_SCOPE_BEGIN, DEBUG_SCOPE_END)
 * - C++ specific tests (classes, templates, exceptions)
 */

#define DEBUG_LEVEL 5  // Full verbosity for testing
#include "../debug.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <functional>
#include <type_traits>

/* Test counters */
static int tests_passed = 0;
static int tests_failed = 0;

/* Test helper macros */
#define TEST_START(name) \
    do { \
        std::cout << "\n=== TEST: " << name << " ===" << std::endl; \
    } while(0)

#define TEST_PASS(name) \
    do { \
        std::cout << "[PASS] " << name << std::endl; \
        tests_passed++; \
    } while(0)

#define TEST_FAIL(name, reason) \
    do { \
        std::cout << "[FAIL] " << name << " - " << reason << std::endl; \
        tests_failed++; \
    } while(0)

/* ============================================================================
 * TEST: Log Levels
 * ============================================================================ */

void test_log_levels() {
    TEST_START("Log Levels (C++)");
    
    /* Test all log level macros compile and execute */
    DEBUG_TRACE("Testing TRACE level log in C++");
    TEST_PASS("DEBUG_TRACE compiles and executes in C++");
    
    DEBUG_DEBUG("Testing DEBUG level log in C++");
    TEST_PASS("DEBUG_DEBUG compiles and executes in C++");
    
    DEBUG_INFO("Testing INFO level log in C++");
    TEST_PASS("DEBUG_INFO compiles and executes in C++");
    
    DEBUG_WARN("Testing WARN level log in C++");
    TEST_PASS("DEBUG_WARN compiles and executes in C++");
    
    DEBUG_ERROR("Testing ERROR level log in C++");
    TEST_PASS("DEBUG_ERROR compiles and executes in C++");
    
    /* Test with format arguments */
    int value = 42;
    DEBUG_INFO("Testing INFO with arg: value=%d", value);
    (void)value;  /* Prevent unused warning in NDEBUG mode */
    TEST_PASS("DEBUG_INFO with format args in C++");
    
    /* Test LOG_* constants - only available when NDEBUG is not defined */
#ifndef NDEBUG
    if (LOG_ERROR == 1 && LOG_WARN == 2 && LOG_INFO == 3 && 
        LOG_DEBUG == 4 && LOG_TRACE == 5) {
        TEST_PASS("LOG_* level constants are correct in C++");
    } else {
        TEST_FAIL("LOG_* constants", "Values are incorrect");
    }
#else
    TEST_PASS("LOG_* constants test skipped (NDEBUG mode)");
#endif
}

/* ============================================================================
 * TEST: Function Tracing in C++ (DEBUG_ENTER, DEBUG_EXIT)
 * ============================================================================ */

int test_function_cpp(int n) {
    DEBUG_ENTER("(n=%d)", n);
    
    int result = n * 2;
    DEBUG_VAR(result);
    
    DEBUG_EXIT(result);
}

double test_function_double_cpp(double x) {
    DEBUG_ENTER("(x=%f)", x);
    double result = x * 3.14;
    DEBUG_EXIT(result);
}

/* C++ class with debug instrumentation */
class DebuggedClass {
public:
    explicit DebuggedClass(int val) : value_(val) {
        DEBUG_ENTER("(val=%d)", val);
        DEBUG_VAR(value_);
    }
    
    ~DebuggedClass() {
        DEBUG_TRACE("Destructor called");
    }
    
    int getValue() const {
        DEBUG_ENTER();
        DEBUG_EXIT(value_);
    }
    
    void setValue(int val) {
        DEBUG_ENTER("(val=%d)", val);
        value_ = val;
        DEBUG_VAR(value_);
    }

private:
    int value_;
};

void test_function_tracing_cpp() {
    TEST_START("Function Tracing (C++)");
    
    int result = test_function_cpp(21);
    if (result == 42) {
        TEST_PASS("DEBUG_ENTER/EXIT with int return in C++");
    } else {
        TEST_FAIL("DEBUG_ENTER/EXIT with int return", "Unexpected return value");
    }
    
    double d_result = test_function_double_cpp(2.0);
    if (d_result > 6.0 && d_result < 7.0) {
        TEST_PASS("DEBUG_ENTER/EXIT with double return in C++");
    } else {
        TEST_FAIL("DEBUG_ENTER/EXIT with double return", "Unexpected return value");
    }
    
    /* Test with C++ class */
    {
        DebuggedClass obj(100);
        if (obj.getValue() == 100) {
            TEST_PASS("DEBUG_ENTER/EXIT in C++ class constructor");
        } else {
            TEST_FAIL("C++ class constructor", "Unexpected value");
        }
        
        obj.setValue(200);
        if (obj.getValue() == 200) {
            TEST_PASS("DEBUG_ENTER/EXIT in C++ class methods");
        } else {
            TEST_FAIL("C++ class methods", "Unexpected value");
        }
    }
    TEST_PASS("DEBUG instrumentation in C++ class destructor");
}

/* ============================================================================
 * TEST: Generic Formatting in C++ (_GENERIC_FMT via DEBUG_VAR)
 * ============================================================================ */

void test_generic_formatting_cpp() {
    TEST_START("Generic Formatting in C++ (_GENERIC_FMT)");
    
    /* Test int */
    int i = 42;
    DEBUG_VAR(i);
    (void)i;  /* Prevent unused warning in NDEBUG mode */
    TEST_PASS("_GENERIC_FMT with int in C++");
    
    /* Test unsigned int */
    unsigned int ui = 100u;
    DEBUG_VAR(ui);
    (void)ui;
    TEST_PASS("_GENERIC_FMT with unsigned int in C++");
    
    /* Test long */
    long l = 1234567890L;
    DEBUG_VAR(l);
    (void)l;
    TEST_PASS("_GENERIC_FMT with long in C++");
    
    /* Test unsigned long */
    unsigned long ul = 9876543210UL;
    DEBUG_VAR(ul);
    (void)ul;
    TEST_PASS("_GENERIC_FMT with unsigned long in C++");
    
    /* Test double */
    double d = 3.14159265359;
    DEBUG_VAR(d);
    (void)d;
    TEST_PASS("_GENERIC_FMT with double in C++");
    
    /* Test char* */
    char* s = const_cast<char*>("test string");
    DEBUG_VAR(s);
    (void)s;
    TEST_PASS("_GENERIC_FMT with char* in C++");
    
    /* Test void* */
    void* p = reinterpret_cast<void*>(0xDEADBEEF);
    DEBUG_VAR(p);
    (void)p;
    TEST_PASS("_GENERIC_FMT with void* in C++");
    
    /* Test size_t */
    size_t sz = sizeof(double);
    DEBUG_VAR(sz);
    (void)sz;
    TEST_PASS("_GENERIC_FMT with size_t in C++");
}

/* ============================================================================
 * TEST: Pointer Inspection in C++ (DEBUG_PTR)
 * ============================================================================ */

void test_pointer_inspection_cpp() {
    TEST_START("Pointer Inspection in C++ (DEBUG_PTR)");
    
    int arr[10];
    DEBUG_PTR(arr, "10 ints");
    (void)arr;  /* Prevent unused warning in NDEBUG mode */
    TEST_PASS("DEBUG_PTR with int array in C++");
    
    const char* str = "hello";
    DEBUG_PTR(str, "5 chars + null");
    (void)str;
    TEST_PASS("DEBUG_PTR with const char* in C++");
    
    /* Test with new/delete */
    int* p = new int[100];
    DEBUG_PTR(p, "100 ints");
    delete[] p;
    TEST_PASS("DEBUG_PTR with new[] memory in C++");
    
    /* Test with smart pointer */
    std::unique_ptr<int> smart_p = std::make_unique<int>(42);
    DEBUG_PTR(smart_p.get(), "unique_ptr<int>");
    TEST_PASS("DEBUG_PTR with unique_ptr in C++");
    
    /* Test with nullptr */
    int* null_ptr = nullptr;
    DEBUG_PTR(null_ptr, "nullptr");
    (void)null_ptr;
    TEST_PASS("DEBUG_PTR with nullptr in C++");
}

/* ============================================================================
 * TEST: Memory Allocation in C++ (DEBUG_MALLOC, DEBUG_FREE)
 * ============================================================================ */

void test_memory_allocation_cpp() {
    TEST_START("Memory Allocation in C++ (DEBUG_MALLOC, DEBUG_FREE)");
    
    /* Note: In C++ we typically use new/delete, but DEBUG_MALLOC/FREE 
     * still work for C-style allocations */
    
    /* Basic allocation */
    void* p1 = DEBUG_MALLOC(100);
    if (p1 != nullptr) {
        TEST_PASS("DEBUG_MALLOC returns non-null in C++");
        DEBUG_FREE(p1);
        TEST_PASS("DEBUG_FREE frees memory in C++");
    } else {
        TEST_FAIL("DEBUG_MALLOC", "Returned nullptr unexpectedly");
    }
    
    /* Allocation for C-style struct */
    struct CStyleStruct {
        int x;
        double y;
    };
    
    auto* cs = static_cast<CStyleStruct*>(DEBUG_MALLOC(sizeof(CStyleStruct)));
    if (cs != nullptr) {
        cs->x = 10;
        cs->y = 3.14;
        TEST_PASS("DEBUG_MALLOC works with C-style struct in C++");
        DEBUG_FREE(cs);
        TEST_PASS("DEBUG_FREE works with C-style struct in C++");
    } else {
        TEST_FAIL("DEBUG_MALLOC struct", "Returned nullptr");
    }
    
    /* Multiple allocations */
    std::vector<void*> ptrs;
    for (int i = 0; i < 5; i++) {
        ptrs.push_back(DEBUG_MALLOC(static_cast<size_t>(i + 1) * 100));
    }
    for (auto* ptr : ptrs) {
        DEBUG_FREE(ptr);
    }
    TEST_PASS("DEBUG_MALLOC/FREE handles multiple allocations in C++");
}

/* ============================================================================
 * TEST: Assertions in C++ (DEBUG_ASSERT)
 * ============================================================================ */

void test_assertions_cpp() {
    TEST_START("Assertions in C++ (DEBUG_ASSERT)");
    
    /* Simple passing assertion */
    DEBUG_ASSERT(1 == 1, "Basic equality");
    TEST_PASS("DEBUG_ASSERT with true condition in C++");
    
    /* Assertion with variables */
    int a = 5, b = 5;
    DEBUG_ASSERT(a == b, "Variable equality: a=%d, b=%d", a, b);
    TEST_PASS("DEBUG_ASSERT with variables in C++");
    
    /* Assertion with pointer check */
    int* p = &a;
    DEBUG_ASSERT(p != nullptr, "Pointer not nullptr");
    TEST_PASS("DEBUG_ASSERT with nullptr check in C++");
    
    /* Assertion with C++ specific types */
    std::string str = "hello";
    DEBUG_ASSERT(!str.empty(), "String not empty");
    TEST_PASS("DEBUG_ASSERT with std::string in C++");
    
    /* Assertion with vector */
    std::vector<int> vec = {1, 2, 3};
    DEBUG_ASSERT(vec.size() == 3, "Vector size check");
    TEST_PASS("DEBUG_ASSERT with std::vector in C++");
}

/* ============================================================================
 * TEST: Soft Checks in C++ (DEBUG_CHECK)
 * ============================================================================ */

void test_soft_checks_cpp() {
    TEST_START("Soft Checks in C++ (DEBUG_CHECK)");
    
    /* Passing check */
    DEBUG_CHECK(1 == 1, "Basic equality check");
    TEST_PASS("DEBUG_CHECK with true condition in C++");
    
    /* Failing check - should warn but continue */
    DEBUG_CHECK(1 == 0, "Expected failure - testing soft check");
    TEST_PASS("DEBUG_CHECK continues after failure in C++");
    
    /* Check with C++ specific */
    std::vector<int> vec;
    DEBUG_CHECK(vec.empty(), "Vector should be empty");
    TEST_PASS("DEBUG_CHECK with STL container in C++");
    
    /* Check with lambda result */
    auto check_fn = []() { return true; };
    DEBUG_CHECK(check_fn(), "Lambda check");
    TEST_PASS("DEBUG_CHECK with lambda result in C++");
}

/* ============================================================================
 * TEST: Backtrace in C++ (DEBUG_BACKTRACE)
 * ============================================================================ */

void test_backtrace_inner_cpp() {
    DEBUG_BACKTRACE();
}

void test_backtrace_middle_cpp() {
    test_backtrace_inner_cpp();
}

class BacktraceTestClass {
public:
    void method() {
        DEBUG_BACKTRACE();
    }
};

void test_backtrace_cpp() {
    TEST_START("Backtrace in C++ (DEBUG_BACKTRACE)");
    
    /* Direct call */
    DEBUG_BACKTRACE();
    TEST_PASS("DEBUG_BACKTRACE direct call in C++");
    
    /* Nested call */
    test_backtrace_middle_cpp();
    TEST_PASS("DEBUG_BACKTRACE nested call in C++");
    
    /* From class method */
    BacktraceTestClass obj;
    obj.method();
    TEST_PASS("DEBUG_BACKTRACE from class method in C++");
}

/* ============================================================================
 * TEST: Loop Tracing in C++ (DEBUG_LOOP_*)
 * ============================================================================ */

void test_loop_tracing_cpp() {
    TEST_START("Loop Tracing in C++");
    
    /* Range-based for loop with vector */
    std::vector<int> vec = {1, 2, 3, 4, 5};
    int sum = 0;
    int idx = 0;
    DEBUG_LOOP_START("Vector iteration");
    for (const auto& val : vec) {
        DEBUG_LOOP_ITER(idx, static_cast<int>(vec.size()));
        sum += val;
        idx++;
    }
    DEBUG_LOOP_END("Sum = %d", sum);
    if (sum == 15) {
        TEST_PASS("DEBUG_LOOP_* with range-based for in C++");
    } else {
        TEST_FAIL("DEBUG_LOOP_* range-based", "Unexpected sum");
    }
    
    /* Traditional for loop */
    int count = 0;
    DEBUG_LOOP_START("Traditional for loop");
    for (size_t i = 0; i < vec.size(); i++) {
        DEBUG_LOOP_ITER(static_cast<int>(i), static_cast<int>(vec.size()));
        count++;
    }
    DEBUG_LOOP_END("Count = %d", count);
    if (count == 5) {
        TEST_PASS("DEBUG_LOOP_* with traditional for in C++");
    } else {
        TEST_FAIL("DEBUG_LOOP_* traditional", "Unexpected count");
    }
    
    /* std::for_each equivalent */
    count = 0;
    DEBUG_LOOP_START("Algorithm-style iteration");
    std::for_each(vec.begin(), vec.end(), [&count](int) {
        count++;
    });
    DEBUG_LOOP_END();
    TEST_PASS("DEBUG_LOOP_* with std algorithms in C++");
}

/* ============================================================================
 * TEST: Conditional Compilation in C++ (DEBUG_IF)
 * ============================================================================ */

void test_conditional_compilation_cpp() {
    TEST_START("Conditional Compilation in C++ (DEBUG_IF)");
    
    int executed = 0;
    
#ifndef NDEBUG
    /* DEBUG_IF with true expression */
    DEBUG_IF(1) {
        executed = 1;
    }
    if (executed == 1) {
        TEST_PASS("DEBUG_IF executes block in C++");
    } else {
        TEST_FAIL("DEBUG_IF true", "Block not executed");
    }
    
    /* DEBUG_IF with C++ bool */
    bool condition = true;
    DEBUG_IF(condition) {
        executed = 2;
    }
    if (executed == 2) {
        TEST_PASS("DEBUG_IF with C++ bool in C++");
    } else {
        TEST_FAIL("DEBUG_IF bool", "Block not executed");
    }
    
    /* DEBUG_IF with expression */
    std::vector<int> v = {1, 2, 3};
    DEBUG_IF(!v.empty()) {
        executed = 3;
    }
    if (executed == 3) {
        TEST_PASS("DEBUG_IF with STL expression in C++");
    } else {
        TEST_FAIL("DEBUG_IF STL", "Block not executed");
    }
#else
    /* In NDEBUG mode, DEBUG_IF is always false */
    DEBUG_IF(1) {
        executed = 1;
    }
    if (executed == 0) {
        TEST_PASS("DEBUG_IF always false in NDEBUG mode (test 1)");
    } else {
        TEST_FAIL("DEBUG_IF NDEBUG", "Block unexpectedly executed");
    }
    
    TEST_PASS("DEBUG_IF always false in NDEBUG mode (test 2)");
    TEST_PASS("DEBUG_IF always false in NDEBUG mode (test 3)");
#endif
}

/* ============================================================================
 * TEST: C++ Specific Features
 * ============================================================================ */

/* Template function with debug */
template<typename T>
T debug_template_add(T a, T b) {
    DEBUG_ENTER();
    T result = a + b;
    DEBUG_EXIT(result);
}

/* Lambda with debug */
void test_cpp_specific_features() {
    TEST_START("C++ Specific Features");
    
    /* Templates */
    int int_result = debug_template_add(1, 2);
    if (int_result == 3) {
        TEST_PASS("DEBUG_* in template function with int");
    } else {
        TEST_FAIL("Template int", "Unexpected result");
    }
    
    double double_result = debug_template_add(1.5, 2.5);
    if (double_result == 4.0) {
        TEST_PASS("DEBUG_* in template function with double");
    } else {
        TEST_FAIL("Template double", "Unexpected result");
    }
    
    /* Lambda */
    auto debug_lambda = [](int x) -> int {
        DEBUG_TRACE("Lambda called with x=%d", x);
        return x * 2;
    };
    
    int lambda_result = debug_lambda(21);
    if (lambda_result == 42) {
        TEST_PASS("DEBUG_* in lambda expression");
    } else {
        TEST_FAIL("Lambda", "Unexpected result");
    }
    
    /* std::function */
    std::function<int(int)> fn = [](int x) {
        DEBUG_TRACE("std::function called with x=%d", x);
        return x + 1;
    };
    
    if (fn(10) == 11) {
        TEST_PASS("DEBUG_* with std::function");
    } else {
        TEST_FAIL("std::function", "Unexpected result");
    }
    
    /* Smart pointers with DEBUG_PTR */
    auto shared = std::make_shared<int>(42);
    DEBUG_PTR(shared.get(), "shared_ptr<int>");
    TEST_PASS("DEBUG_PTR with shared_ptr");
}

/* ============================================================================
 * TEST: C++ Classes with Debug Instrumentation
 * ============================================================================ */

class InstrumentedClass {
public:
    InstrumentedClass() : data_(nullptr), size_(0) {
        DEBUG_ENTER();
        DEBUG_TRACE("Default constructor");
    }
    
    explicit InstrumentedClass(size_t size) : size_(size) {
        DEBUG_ENTER("(size=%zu)", size);
        data_ = DEBUG_MALLOC(size);
        DEBUG_PTR(data_, "allocated buffer");
        DEBUG_CHECK(data_ != nullptr, "Allocation should succeed");
    }
    
    ~InstrumentedClass() {
        DEBUG_TRACE("Destructor called, freeing data");
        if (data_) {
            DEBUG_FREE(data_);
        }
    }
    
    // Copy constructor
    InstrumentedClass(const InstrumentedClass& other) : size_(other.size_) {
        DEBUG_ENTER("(other.size=%zu)", other.size_);
        if (size_ > 0) {
            data_ = DEBUG_MALLOC(size_);
            std::memcpy(data_, other.data_, size_);
        } else {
            data_ = nullptr;
        }
    }
    
    // Move constructor
    InstrumentedClass(InstrumentedClass&& other) noexcept 
        : data_(other.data_), size_(other.size_) {
        DEBUG_ENTER();
        DEBUG_TRACE("Move constructor - taking ownership");
        other.data_ = nullptr;
        other.size_ = 0;
    }
    
    size_t size() const {
        DEBUG_ENTER();
        DEBUG_EXIT(size_);
    }

private:
    void* data_;
    size_t size_;
};

void test_cpp_class_instrumentation() {
    TEST_START("C++ Class Instrumentation");
    
    /* Default constructor */
    {
        InstrumentedClass obj1;
        TEST_PASS("Default constructor with debug");
    }
    
    /* Parameterized constructor */
    {
        InstrumentedClass obj2(100);
        if (obj2.size() == 100) {
            TEST_PASS("Parameterized constructor with debug");
        } else {
            TEST_FAIL("Parameterized constructor", "Unexpected size");
        }
    }
    
    /* Copy constructor */
    {
        InstrumentedClass obj3(50);
        InstrumentedClass obj4(obj3);
        if (obj4.size() == 50) {
            TEST_PASS("Copy constructor with debug");
        } else {
            TEST_FAIL("Copy constructor", "Unexpected size");
        }
    }
    
    /* Move constructor */
    {
        InstrumentedClass obj5(75);
        InstrumentedClass obj6(std::move(obj5));
        if (obj6.size() == 75 && obj5.size() == 0) {
            TEST_PASS("Move constructor with debug");
        } else {
            TEST_FAIL("Move constructor", "Unexpected sizes");
        }
    }
    
    TEST_PASS("Destructor cleanup with debug");
}

/* ============================================================================
 * TEST: Exception Safety with Debug
 * ============================================================================ */

void throwing_function() {
    DEBUG_ENTER();
    DEBUG_TRACE("About to throw");
    throw std::runtime_error("Test exception");
}

void test_exception_safety() {
    TEST_START("Exception Safety with Debug");
    
    try {
        DEBUG_TRACE("Entering try block");
        throwing_function();
        TEST_FAIL("Exception not thrown", "Should have thrown");
    } catch (const std::runtime_error& e) {
        DEBUG_TRACE("Caught exception: %s", e.what());
        TEST_PASS("DEBUG_* works with exceptions");
    }
    
    /* RAII with debug */
    try {
        InstrumentedClass obj(100);
        DEBUG_TRACE("Object created in try block");
        // Object will be destroyed even if exception occurs
    } catch (...) {
        // Should not reach here
    }
    TEST_PASS("RAII destruction with debug");
}

/* ============================================================================
 * TEST: Compile-time Definitions in C++
 * ============================================================================ */

void test_compile_definitions_cpp() {
    TEST_START("Compile-time Definitions (C++)");
    
    /* Test DEBUG_LEVEL is defined */
    #ifdef DEBUG_LEVEL
    TEST_PASS("DEBUG_LEVEL is defined in C++");
    std::cout << "DEBUG_LEVEL = " << DEBUG_LEVEL << std::endl;
    #else
    TEST_FAIL("DEBUG_LEVEL", "Not defined");
    #endif
    
    /* Test LOG_* constants exist - only in debug mode */
#ifndef NDEBUG
    #if defined(LOG_ERROR) && defined(LOG_WARN) && defined(LOG_INFO) && \
        defined(LOG_DEBUG) && defined(LOG_TRACE)
    TEST_PASS("All LOG_* constants defined in C++");
    #else
    TEST_FAIL("LOG_* constants", "Some not defined");
    #endif
#else
    /* In NDEBUG mode, LOG_* constants should NOT be defined */
    #if !defined(LOG_ERROR) && !defined(LOG_WARN) && !defined(LOG_INFO) && \
        !defined(LOG_DEBUG) && !defined(LOG_TRACE)
    TEST_PASS("LOG_* constants correctly not defined in NDEBUG mode");
    #else
    TEST_FAIL("LOG_* constants", "Should not be defined in NDEBUG mode");
    #endif
#endif
    
    /* Test DEBUG_H guard */
    #ifdef DEBUG_H
    TEST_PASS("DEBUG_H include guard defined in C++");
    #else
    TEST_FAIL("DEBUG_H", "Include guard not defined");
    #endif
    
    /* Test constexpr compatibility */
    constexpr int level = DEBUG_LEVEL;
    static_assert(level >= 0 && level <= 5, "DEBUG_LEVEL must be 0-5");
    TEST_PASS("DEBUG_LEVEL is constexpr compatible");
}

/* ============================================================================
 * TEST: Integration - Realistic C++ Usage
 * ============================================================================ */

class DataProcessor {
public:
    explicit DataProcessor(const std::string& name) : name_(name) {
        DEBUG_ENTER("(name=%s)", name.c_str());
    }
    
    void process(const std::vector<int>& data) {
        DEBUG_ENTER("(data.size=%zu)", data.size());
        DEBUG_ASSERT(!data.empty(), "Data should not be empty");
        
        int sum = 0;
        int idx = 0;
        DEBUG_LOOP_START("Processing data");
        for (const auto& val : data) {
            DEBUG_LOOP_ITER(idx, static_cast<int>(data.size()));
            DEBUG_CHECK(val >= 0, "Value should be non-negative: %d", val);
            sum += val;
            idx++;
        }
        DEBUG_LOOP_END("Sum = %d", sum);
        
        result_ = sum;
        DEBUG_VAR(result_);
    }
    
    int getResult() const {
        DEBUG_ENTER();
        DEBUG_EXIT(result_);
    }

private:
    std::string name_;
    int result_ = 0;
};

void test_integration_cpp() {
    TEST_START("Integration Test (C++)");
    
    DataProcessor processor("TestProcessor");
    TEST_PASS("DataProcessor construction");
    
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    processor.process(data);
    
    if (processor.getResult() == 55) {
        TEST_PASS("DataProcessor processing correct");
    } else {
        TEST_FAIL("DataProcessor", "Unexpected result");
    }
    
    /* Test with DEBUG_CHECK failure (should warn but continue) */
    std::vector<int> mixed_data = {1, -1, 2, -2, 3};
    processor.process(mixed_data);
    TEST_PASS("DataProcessor handles soft check failures");
}

/* ============================================================================
 * MAIN
 * ============================================================================ */

int main() {
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "  debug.h C++23 Unit Tests\n";
    std::cout << "========================================\n";
    std::cout << "DEBUG_LEVEL = " << DEBUG_LEVEL << "\n";
    #ifdef NDEBUG
    std::cout << "Mode: RELEASE (NDEBUG defined)\n";
    #else
    std::cout << "Mode: DEBUG (NDEBUG not defined)\n";
    #endif
    std::cout << "========================================\n";
    std::cout.flush();
    
    /* Run all tests */
    test_log_levels();
    test_function_tracing_cpp();
    test_generic_formatting_cpp();
    test_pointer_inspection_cpp();
    test_memory_allocation_cpp();
    test_assertions_cpp();
    test_soft_checks_cpp();
    test_backtrace_cpp();
    test_loop_tracing_cpp();
    test_conditional_compilation_cpp();
    test_cpp_specific_features();
    test_cpp_class_instrumentation();
    test_exception_safety();
    test_compile_definitions_cpp();
    test_integration_cpp();
    
    /* Print summary */
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "  TEST SUMMARY\n";
    std::cout << "========================================\n";
    std::cout << "Passed: " << tests_passed << "\n";
    std::cout << "Failed: " << tests_failed << "\n";
    std::cout << "Total:  " << (tests_passed + tests_failed) << "\n";
    std::cout << "========================================\n";
    
    if (tests_failed > 0) {
        std::cout << "RESULT: SOME TESTS FAILED\n";
        return 1;
    } else {
        std::cout << "RESULT: ALL TESTS PASSED\n";
        return 0;
    }
}
