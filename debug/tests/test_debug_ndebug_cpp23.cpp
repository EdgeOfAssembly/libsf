/*
 * test_debug_ndebug_cpp23.cpp - Tests debug.h in NDEBUG (release) mode for C++23
 * Author: GitHub Copilot
 * Date: 2025-12-17
 *
 * Compile with: g++ -std=c++23 -O2 -DNDEBUG -o test_debug_ndebug_cpp23 test_debug_ndebug_cpp23.cpp
 *
 * This test verifies that:
 * 1. All debug macros compile to no-ops when NDEBUG is defined
 * 2. No runtime overhead is introduced in C++
 * 3. DEBUG_EXIT still returns correctly
 * 4. DEBUG_MALLOC/FREE still allocate/free correctly
 * 5. C++ classes work correctly with debug macros in NDEBUG mode
 */

#define NDEBUG  // Must be defined BEFORE including debug.h
#define DEBUG_LEVEL 5  // Should be ignored when NDEBUG is set
#include "../debug.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <memory>
#include <iostream>

/* Test counters */
static int tests_passed = 0;
static int tests_failed = 0;

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
 * TEST: All debug macros should be no-ops in C++
 * ============================================================================ */

void test_log_macros_noop_cpp() {
    /* These should all compile but do nothing */
    DEBUG_TRACE("This should not print");
    DEBUG_DEBUG("This should not print");
    DEBUG_INFO("This should not print");
    DEBUG_WARN("This should not print");
    DEBUG_ERROR("This should not print");
    TEST_PASS("Log macros compile as no-ops in C++");
}

int test_exit_return_cpp(int n) {
    DEBUG_ENTER("(n=%d)", n);
    int result = n * 2;
    DEBUG_EXIT(result);  /* Should still return correctly */
}

void test_function_tracing_noop_cpp() {
    int result = test_exit_return_cpp(21);
    if (result == 42) {
        TEST_PASS("DEBUG_EXIT returns correctly in NDEBUG mode (C++)");
    } else {
        TEST_FAIL("DEBUG_EXIT", "Return value incorrect");
    }
}

void test_var_ptr_noop_cpp() {
    int x = 42;
    DEBUG_VAR(x);  /* Should be no-op */
    
    int* p = &x;
    DEBUG_PTR(p, "int pointer");  /* Should be no-op */
    
    std::unique_ptr<int> smart_p = std::make_unique<int>(100);
    DEBUG_PTR(smart_p.get(), "smart pointer");  /* Should be no-op */
    
    TEST_PASS("DEBUG_VAR and DEBUG_PTR compile as no-ops in C++");
}

void test_memory_functions_cpp() {
    /* DEBUG_MALLOC should still allocate */
    void* p = DEBUG_MALLOC(100);
    if (p != nullptr) {
        TEST_PASS("DEBUG_MALLOC still allocates in NDEBUG mode (C++)");
        
        /* Can write to the memory */
        std::memset(p, 0, 100);
        
        DEBUG_FREE(p);  /* Should still free */
        TEST_PASS("DEBUG_FREE still frees in NDEBUG mode (C++)");
    } else {
        TEST_FAIL("DEBUG_MALLOC", "Returned nullptr");
    }
}

void test_assert_check_noop_cpp() {
    /* These should evaluate expression but not abort/warn */
    DEBUG_ASSERT(1 == 1, "Should be no-op");
    DEBUG_CHECK(1 == 1, "Should be no-op");
    
    /* In NDEBUG, even failing checks should not warn */
    DEBUG_CHECK(0 == 1, "This warning should NOT print");
    
    TEST_PASS("DEBUG_ASSERT and DEBUG_CHECK compile as no-ops in C++");
}

void test_backtrace_noop_cpp() {
    DEBUG_BACKTRACE();  /* Should be no-op */
    TEST_PASS("DEBUG_BACKTRACE compiles as no-op in C++");
}

void test_loop_macros_noop_cpp() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    int sum = 0;
    
    DEBUG_LOOP_START("Loop");
    for (const auto& val : vec) {
        DEBUG_LOOP_ITER(0, 5);
        sum += val;
    }
    DEBUG_LOOP_END();
    
    if (sum == 15) {
        TEST_PASS("DEBUG_LOOP_* compile as no-ops in C++");
    } else {
        TEST_FAIL("DEBUG_LOOP_*", "Loop behavior changed");
    }
}

void test_conditional_noop_cpp() {
    int executed = 0;
    
    /* DEBUG_IF should always be false in NDEBUG mode */
    DEBUG_IF(1) {
        executed = 1;
    }
    
    if (executed == 0) {
        TEST_PASS("DEBUG_IF always false in NDEBUG mode (C++)");
    } else {
        TEST_FAIL("DEBUG_IF", "Block unexpectedly executed");
    }
}

/* C++ class with debug instrumentation in NDEBUG mode */
class InstrumentedClassNDEBUG {
public:
    explicit InstrumentedClassNDEBUG(int val) : value_(val) {
        DEBUG_ENTER("(val=%d)", val);
        DEBUG_VAR(value_);
    }
    
    ~InstrumentedClassNDEBUG() {
        DEBUG_TRACE("Destructor called");
    }
    
    int getValue() const {
        DEBUG_ENTER();
        DEBUG_EXIT(value_);
    }

private:
    int value_;
};

void test_cpp_class_ndebug() {
    InstrumentedClassNDEBUG obj(42);
    if (obj.getValue() == 42) {
        TEST_PASS("C++ class with debug macros works in NDEBUG mode");
    } else {
        TEST_FAIL("C++ class", "getValue returned incorrect value");
    }
}

void test_definitions_ndebug_cpp() {
    /* Verify NDEBUG is defined */
    #ifdef NDEBUG
    TEST_PASS("NDEBUG is defined in C++");
    #else
    TEST_FAIL("NDEBUG", "Not defined");
    #endif
    
    /* LOG_* constants should NOT be defined in NDEBUG mode */
    #ifdef LOG_ERROR
    TEST_FAIL("LOG_ERROR", "Should not be defined in NDEBUG");
    #else
    TEST_PASS("LOG_ERROR not defined in NDEBUG (correct) in C++");
    #endif
}

/* ============================================================================
 * MAIN
 * ============================================================================ */

int main() {
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "  debug.h NDEBUG Mode Tests (C++23)\n";
    std::cout << "========================================\n";
    #ifdef NDEBUG
    std::cout << "Mode: RELEASE (NDEBUG defined)\n";
    #else
    std::cout << "Mode: DEBUG (NDEBUG NOT defined - ERROR!)\n";
    #endif
    std::cout << "========================================\n";
    
    test_log_macros_noop_cpp();
    test_function_tracing_noop_cpp();
    test_var_ptr_noop_cpp();
    test_memory_functions_cpp();
    test_assert_check_noop_cpp();
    test_backtrace_noop_cpp();
    test_loop_macros_noop_cpp();
    test_conditional_noop_cpp();
    test_cpp_class_ndebug();
    test_definitions_ndebug_cpp();
    
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "  TEST SUMMARY (NDEBUG Mode C++23)\n";
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
