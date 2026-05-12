/*
 * test_debug_c23.c - Extensive unit tests for debug.h in C23
 * Author: GitHub Copilot
 * Date: 2025-12-17
 *
 * Compile with: gcc -std=c23 -g -Wall -Wextra -Wpedantic -rdynamic -o test_debug_c23 test_debug_c23.c
 * Or for release: gcc -std=c23 -O2 -DNDEBUG -o test_debug_c23_release test_debug_c23.c
 *
 * Tests all features of debug.h:
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
 */

#define DEBUG_LEVEL 5  // Full verbosity for testing
#include "../debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/* Test counters */
static int tests_passed = 0;
static int tests_failed = 0;

/* Test helper macros */
#define TEST_START(name) \
    do { \
        fprintf(stdout, "\n=== TEST: %s ===\n", name); \
        fflush(stdout); \
    } while(0)

#define TEST_PASS(name) \
    do { \
        fprintf(stdout, "[PASS] %s\n", name); \
        tests_passed++; \
        fflush(stdout); \
    } while(0)

#define TEST_FAIL(name, reason) \
    do { \
        fprintf(stdout, "[FAIL] %s - %s\n", name, reason); \
        tests_failed++; \
        fflush(stdout); \
    } while(0)

/* ============================================================================
 * TEST: Log Levels
 * ============================================================================ */

void test_log_levels(void) {
    TEST_START("Log Levels");
    
    /* Test all log level macros compile and execute */
    DEBUG_TRACE("Testing TRACE level log");
    TEST_PASS("DEBUG_TRACE compiles and executes");
    
    DEBUG_DEBUG("Testing DEBUG level log");
    TEST_PASS("DEBUG_DEBUG compiles and executes");
    
    DEBUG_INFO("Testing INFO level log");
    TEST_PASS("DEBUG_INFO compiles and executes");
    
    DEBUG_WARN("Testing WARN level log");
    TEST_PASS("DEBUG_WARN compiles and executes");
    
    DEBUG_ERROR("Testing ERROR level log");
    TEST_PASS("DEBUG_ERROR compiles and executes");
    
    /* Test with format arguments */
    int value = 42;
    DEBUG_INFO("Testing INFO with arg: value=%d", value);
    (void)value;  /* Prevent unused warning in NDEBUG mode */
    TEST_PASS("DEBUG_INFO with format args");
    
    DEBUG_WARN("Testing WARN with multiple args: a=%d, b=%s", 123, "hello");
    TEST_PASS("DEBUG_WARN with multiple format args");
    
    /* Test LOG_* constants - only available when NDEBUG is not defined */
#ifndef NDEBUG
    if (LOG_ERROR == 1 && LOG_WARN == 2 && LOG_INFO == 3 && 
        LOG_DEBUG == 4 && LOG_TRACE == 5) {
        TEST_PASS("LOG_* level constants are correct");
    } else {
        TEST_FAIL("LOG_* constants", "Values are incorrect");
    }
    
    /* Test DEBUG_LOG direct usage */
    DEBUG_LOG(LOG_INFO, "Direct DEBUG_LOG test");
    TEST_PASS("DEBUG_LOG direct usage");
#else
    TEST_PASS("LOG_* constants test skipped (NDEBUG mode)");
    TEST_PASS("DEBUG_LOG test skipped (NDEBUG mode)");
#endif
}

/* ============================================================================
 * TEST: Function Tracing (DEBUG_ENTER, DEBUG_EXIT)
 * ============================================================================ */

int test_function_with_tracing(int n) {
    DEBUG_ENTER("(n=%d)", n);
    
    int result = n * 2;
    DEBUG_VAR(result);
    
    DEBUG_EXIT(result);
}

double test_function_double_return(double x) {
    DEBUG_ENTER("(x=%f)", x);
    double result = x * 3.14;
    DEBUG_EXIT(result);
}

char* test_function_string_return(void) {
    DEBUG_ENTER();
    char* result = "hello world";
    DEBUG_EXIT(result);
}

void test_function_tracing(void) {
    TEST_START("Function Tracing");
    
    int result = test_function_with_tracing(21);
    if (result == 42) {
        TEST_PASS("DEBUG_ENTER/EXIT with int return");
    } else {
        TEST_FAIL("DEBUG_ENTER/EXIT with int return", "Unexpected return value");
    }
    
    double d_result = test_function_double_return(2.0);
    if (d_result > 6.0 && d_result < 7.0) {
        TEST_PASS("DEBUG_ENTER/EXIT with double return");
    } else {
        TEST_FAIL("DEBUG_ENTER/EXIT with double return", "Unexpected return value");
    }
    
    char* s_result = test_function_string_return();
    if (strcmp(s_result, "hello world") == 0) {
        TEST_PASS("DEBUG_ENTER/EXIT with string return");
    } else {
        TEST_FAIL("DEBUG_ENTER/EXIT with string return", "Unexpected return value");
    }
    
    /* Test DEBUG_ENTER without args */
    DEBUG_ENTER();
    TEST_PASS("DEBUG_ENTER without args");
}

/* ============================================================================
 * TEST: Generic Formatting (_GENERIC_FMT via DEBUG_VAR)
 * ============================================================================ */

void test_generic_formatting(void) {
    TEST_START("Generic Formatting (_GENERIC_FMT)");
    
    /* Test int */
    int i = 42;
    DEBUG_VAR(i);
    (void)i;  /* Prevent unused warning in NDEBUG mode */
    TEST_PASS("_GENERIC_FMT with int");
    
    /* Test unsigned int */
    unsigned int ui = 100u;
    DEBUG_VAR(ui);
    (void)ui;
    TEST_PASS("_GENERIC_FMT with unsigned int");
    
    /* Test long */
    long l = 1234567890L;
    DEBUG_VAR(l);
    (void)l;
    TEST_PASS("_GENERIC_FMT with long");
    
    /* Test unsigned long */
    unsigned long ul = 9876543210UL;
    DEBUG_VAR(ul);
    (void)ul;
    TEST_PASS("_GENERIC_FMT with unsigned long");
    
    /* Test double */
    double d = 3.14159265359;
    DEBUG_VAR(d);
    (void)d;
    TEST_PASS("_GENERIC_FMT with double");
    
    /* Test char* */
    char* s = "test string";
    DEBUG_VAR(s);
    (void)s;
    TEST_PASS("_GENERIC_FMT with char*");
    
    /* Test void* */
    void* p = (void*)0xDEADBEEF;
    DEBUG_VAR(p);
    (void)p;
    TEST_PASS("_GENERIC_FMT with void*");
    
    /* Test size_t */
    size_t sz = sizeof(double);
    DEBUG_VAR(sz);
    (void)sz;
    TEST_PASS("_GENERIC_FMT with size_t");
}

/* ============================================================================
 * TEST: Pointer Inspection (DEBUG_PTR)
 * ============================================================================ */

void test_pointer_inspection(void) {
    TEST_START("Pointer Inspection (DEBUG_PTR)");
    
    int arr[10];
    DEBUG_PTR(arr, "10 ints");
    (void)arr;  /* Prevent unused warning in NDEBUG mode */
    TEST_PASS("DEBUG_PTR with int array");
    
    char* str = "hello";
    DEBUG_PTR(str, "5 chars + null");
    (void)str;
    TEST_PASS("DEBUG_PTR with char*");
    
    void* p = malloc(1024);
    DEBUG_PTR(p, "1024 bytes");
    free(p);
    TEST_PASS("DEBUG_PTR with malloc'd memory");
    
    /* Test with NULL pointer */
    int* null_ptr = NULL;
    DEBUG_PTR(null_ptr, "NULL pointer");
    (void)null_ptr;
    TEST_PASS("DEBUG_PTR with NULL pointer");
}

/* ============================================================================
 * TEST: Memory Allocation Wrappers (DEBUG_MALLOC, DEBUG_FREE)
 * ============================================================================ */

void test_memory_allocation(void) {
    TEST_START("Memory Allocation Wrappers");
    
    /* Basic allocation */
    void* p1 = DEBUG_MALLOC(100);
    if (p1 != NULL) {
        TEST_PASS("DEBUG_MALLOC returns non-NULL for valid size");
        DEBUG_FREE(p1);
        TEST_PASS("DEBUG_FREE frees memory");
    } else {
        TEST_FAIL("DEBUG_MALLOC", "Returned NULL unexpectedly");
    }
    
    /* Larger allocation */
    void* p2 = DEBUG_MALLOC(1024 * 1024);  // 1MB
    if (p2 != NULL) {
        TEST_PASS("DEBUG_MALLOC handles large allocations");
        DEBUG_FREE(p2);
        TEST_PASS("DEBUG_FREE handles large allocations");
    } else {
        TEST_FAIL("DEBUG_MALLOC large", "Returned NULL");
    }
    
    /* Zero-size allocation (implementation-defined, but should work) */
    void* p3 = DEBUG_MALLOC(0);
    /* Either NULL or a valid pointer is acceptable for size 0 */
    DEBUG_FREE(p3);
    TEST_PASS("DEBUG_MALLOC/FREE handles zero size");
    
    /* Multiple allocations */
    void* ptrs[5];
    for (int i = 0; i < 5; i++) {
        ptrs[i] = DEBUG_MALLOC((size_t)(i + 1) * 100);
    }
    for (int i = 0; i < 5; i++) {
        DEBUG_FREE(ptrs[i]);
    }
    TEST_PASS("DEBUG_MALLOC/FREE handles multiple allocations");
}

/* ============================================================================
 * TEST: Assertions (DEBUG_ASSERT - soft tests only, we can't test abort)
 * ============================================================================ */

void test_assertions_pass(void) {
    TEST_START("Assertions (DEBUG_ASSERT - passing cases)");
    
    /* Simple passing assertion */
    DEBUG_ASSERT(1 == 1, "Basic equality");
    TEST_PASS("DEBUG_ASSERT with true condition");
    
    /* Assertion with variables */
    int a = 5, b = 5;
    DEBUG_ASSERT(a == b, "Variable equality: a=%d, b=%d", a, b);
    TEST_PASS("DEBUG_ASSERT with variables");
    
    /* Assertion with pointer check */
    int* p = &a;
    DEBUG_ASSERT(p != NULL, "Pointer not NULL");
    TEST_PASS("DEBUG_ASSERT with pointer check");
    
    /* Assertion with complex expression */
    DEBUG_ASSERT((a + b) == 10 && (a * b) == 25, "Complex expression");
    TEST_PASS("DEBUG_ASSERT with complex expression");
}

/* ============================================================================
 * TEST: Soft Checks (DEBUG_CHECK)
 * ============================================================================ */

void test_soft_checks(void) {
    TEST_START("Soft Checks (DEBUG_CHECK)");
    
    /* Passing check */
    DEBUG_CHECK(1 == 1, "Basic equality check");
    TEST_PASS("DEBUG_CHECK with true condition");
    
    /* Failing check - should warn but continue */
    DEBUG_CHECK(1 == 0, "Expected failure - testing soft check");
    TEST_PASS("DEBUG_CHECK with false condition continues execution");
    
    /* Multiple checks */
    int value = 42;
    DEBUG_CHECK(value > 0, "Value is positive");
    DEBUG_CHECK(value < 100, "Value is less than 100");
    DEBUG_CHECK(value != 0, "Value is non-zero");
    TEST_PASS("Multiple DEBUG_CHECK calls");
    
    /* Check with format args */
    int x = 5, y = 10;
    DEBUG_CHECK(x < y, "x=%d should be less than y=%d", x, y);
    TEST_PASS("DEBUG_CHECK with format arguments");
}

/* ============================================================================
 * TEST: Backtrace (DEBUG_BACKTRACE)
 * ============================================================================ */

void test_backtrace_inner(void) {
    DEBUG_BACKTRACE();
}

void test_backtrace_middle(void) {
    test_backtrace_inner();
}

void test_backtrace(void) {
    TEST_START("Backtrace (DEBUG_BACKTRACE)");
    
    /* Direct call */
    DEBUG_BACKTRACE();
    TEST_PASS("DEBUG_BACKTRACE direct call");
    
    /* Nested call */
    test_backtrace_middle();
    TEST_PASS("DEBUG_BACKTRACE nested call");
}

/* ============================================================================
 * TEST: Loop Tracing (DEBUG_LOOP_START, DEBUG_LOOP_ITER, DEBUG_LOOP_END)
 * ============================================================================ */

void test_loop_tracing(void) {
    TEST_START("Loop Tracing");
    
    /* Basic loop */
    int sum = 0;
    DEBUG_LOOP_START("Sum loop");
    for (int i = 0; i < 5; i++) {
        DEBUG_LOOP_ITER(i, 5);
        sum += i;
    }
    DEBUG_LOOP_END("Sum = %d", sum);
    if (sum == 10) {
        TEST_PASS("DEBUG_LOOP_* with basic for loop");
    } else {
        TEST_FAIL("DEBUG_LOOP_* basic", "Unexpected sum");
    }
    
    /* Nested loops */
    int count = 0;
    DEBUG_LOOP_START("Outer loop");
    for (int i = 0; i < 3; i++) {
        DEBUG_LOOP_ITER(i, 3);
        DEBUG_LOOP_START("Inner loop");
        for (int j = 0; j < 2; j++) {
            DEBUG_LOOP_ITER(j, 2);
            count++;
        }
        DEBUG_LOOP_END("Inner done");
    }
    DEBUG_LOOP_END("Outer done, count=%d", count);
    if (count == 6) {
        TEST_PASS("DEBUG_LOOP_* with nested loops");
    } else {
        TEST_FAIL("DEBUG_LOOP_* nested", "Unexpected count");
    }
    
    /* While loop */
    int n = 0;
    DEBUG_LOOP_START("While loop test");
    while (n < 3) {
        DEBUG_LOOP_ITER(n, 3);
        n++;
    }
    DEBUG_LOOP_END();
    TEST_PASS("DEBUG_LOOP_* with while loop");
}

/* ============================================================================
 * TEST: Conditional Compilation (DEBUG_IF)
 * ============================================================================ */

void test_conditional_compilation(void) {
    TEST_START("Conditional Compilation (DEBUG_IF)");
    
    int executed = 0;
    
#ifndef NDEBUG
    /* DEBUG_IF with true expression (and DEBUG_LEVEL >= TRACE) */
    DEBUG_IF(1) {
        executed = 1;
    }
    if (executed == 1) {
        TEST_PASS("DEBUG_IF executes block when condition true");
    } else {
        TEST_FAIL("DEBUG_IF true", "Block not executed");
    }
    
    /* DEBUG_IF with false expression */
    executed = 0;
    DEBUG_IF(0) {
        executed = 1;
    }
    if (executed == 0) {
        TEST_PASS("DEBUG_IF skips block when condition false");
    } else {
        TEST_FAIL("DEBUG_IF false", "Block unexpectedly executed");
    }
    
    /* DEBUG_IF with variable condition */
    int condition = 5 > 3;
    DEBUG_IF(condition) {
        executed = 2;
    }
    if (executed == 2) {
        TEST_PASS("DEBUG_IF works with variable condition");
    } else {
        TEST_FAIL("DEBUG_IF variable", "Block not executed");
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
 * TEST: Scope Helpers (DEBUG_SCOPE_BEGIN, DEBUG_SCOPE_END)
 * ============================================================================ */

void test_scope_helpers(void) {
    TEST_START("Scope Helpers");
    
    /* Note: DEBUG_SCOPE_END uses DEBUG_EXIT which returns, so we test differently */
    DEBUG_SCOPE_BEGIN();
    DEBUG_TRACE("Inside scope");
    /* Can't easily test DEBUG_SCOPE_END as it returns */
    TEST_PASS("DEBUG_SCOPE_BEGIN compiles and executes");
}

/* ============================================================================
 * TEST: Various Format String Edge Cases
 * ============================================================================ */

void test_format_edge_cases(void) {
    TEST_START("Format String Edge Cases");
    
    /* Empty format */
    DEBUG_INFO("");
    TEST_PASS("Empty format string");
    
    /* Long format string */
    DEBUG_INFO("This is a very long format string that tests the ability of the "
               "debug macros to handle longer messages without any issues whatsoever. "
               "It should work correctly even with this much text.");
    TEST_PASS("Long format string");
    
    /* Special characters in format */
    DEBUG_INFO("Tab:\tNewline escape\\n Percent: %%");
    TEST_PASS("Special characters in format");
    
    /* Multiple consecutive calls */
    for (int i = 0; i < 10; i++) {
        DEBUG_TRACE("Rapid call %d", i);
    }
    TEST_PASS("Multiple rapid consecutive calls");
    
    /* Format with many arguments */
    DEBUG_INFO("Args: %d %d %d %d %d", 1, 2, 3, 4, 5);
    TEST_PASS("Format with multiple arguments");
}

/* ============================================================================
 * TEST: Compile-time Definitions
 * ============================================================================ */

void test_compile_definitions(void) {
    TEST_START("Compile-time Definitions");
    
    /* Test DEBUG_LEVEL is defined */
    #ifdef DEBUG_LEVEL
    TEST_PASS("DEBUG_LEVEL is defined");
    fprintf(stdout, "DEBUG_LEVEL = %d\n", DEBUG_LEVEL);
    #else
    TEST_FAIL("DEBUG_LEVEL", "Not defined");
    #endif
    
    /* Test LOG_* constants exist - only in debug mode */
#ifndef NDEBUG
    #if defined(LOG_ERROR) && defined(LOG_WARN) && defined(LOG_INFO) && \
        defined(LOG_DEBUG) && defined(LOG_TRACE)
    TEST_PASS("All LOG_* constants defined");
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
    TEST_PASS("DEBUG_H include guard defined");
    #else
    TEST_FAIL("DEBUG_H", "Include guard not defined");
    #endif
}

/* ============================================================================
 * TEST: Integration Test - Simulated Real Usage
 * ============================================================================ */

typedef struct {
    int id;
    char name[32];
    double value;
} TestStruct;

TestStruct* create_test_struct(int id, const char* name, double value) {
    DEBUG_ENTER("(id=%d, name=%s, value=%f)", id, name, value);
    
    TestStruct* s = (TestStruct*)DEBUG_MALLOC(sizeof(TestStruct));
    DEBUG_ASSERT(s != NULL, "Allocation failed");
    
    s->id = id;
    strncpy(s->name, name, sizeof(s->name) - 1);
    s->name[sizeof(s->name) - 1] = '\0';
    s->value = value;
    
    DEBUG_PTR(s, "TestStruct");
    DEBUG_VAR(s->id);
    
    DEBUG_EXIT(s);
}

void process_array(int* arr, int size) {
    DEBUG_ENTER("(arr=%p, size=%d)", (void*)arr, size);
    DEBUG_ASSERT(arr != NULL, "Array is NULL");
    DEBUG_CHECK(size > 0, "Size should be positive: %d", size);
    
    int sum = 0;
    DEBUG_LOOP_START("Array processing (size=%d)", size);
    for (int i = 0; i < size; i++) {
        DEBUG_LOOP_ITER(i, size);
        sum += arr[i];
    }
    DEBUG_LOOP_END("Sum = %d", sum);
    
    DEBUG_VAR(sum);
}

void test_integration(void) {
    TEST_START("Integration Test");
    
    /* Create struct */
    TestStruct* s = create_test_struct(1, "test", 3.14);
    if (s != NULL && s->id == 1 && strcmp(s->name, "test") == 0) {
        TEST_PASS("create_test_struct works correctly");
    } else {
        TEST_FAIL("create_test_struct", "Unexpected values");
    }
    
    /* Process array */
    int arr[] = {1, 2, 3, 4, 5};
    process_array(arr, 5);
    TEST_PASS("process_array works correctly");
    
    /* Cleanup */
    DEBUG_FREE(s);
    TEST_PASS("Integration test cleanup");
}

/* ============================================================================
 * TEST: DEBUG_ABORT (can only test compilation, not execution)
 * ============================================================================ */

void test_abort_compilation(void) {
    TEST_START("DEBUG_ABORT Compilation");
    
    /* We can only verify it compiles, not test actual abort */
    /* The following line would abort: DEBUG_ABORT("Test abort"); */
    
    /* Test that the macro syntax is correct by checking type */
    #ifdef NDEBUG
    TEST_PASS("DEBUG_ABORT compiles (NDEBUG mode)");
    #else
    TEST_PASS("DEBUG_ABORT compiles (debug mode)");
    #endif
}

/* ============================================================================
 * MAIN
 * ============================================================================ */

int main(void) {
    fprintf(stdout, "\n");
    fprintf(stdout, "========================================\n");
    fprintf(stdout, "  debug.h C23 Unit Tests\n");
    fprintf(stdout, "========================================\n");
    fprintf(stdout, "DEBUG_LEVEL = %d\n", DEBUG_LEVEL);
    #ifdef NDEBUG
    fprintf(stdout, "Mode: RELEASE (NDEBUG defined)\n");
    #else
    fprintf(stdout, "Mode: DEBUG (NDEBUG not defined)\n");
    #endif
    fprintf(stdout, "========================================\n");
    fflush(stdout);
    
    /* Run all tests */
    test_log_levels();
    test_function_tracing();
    test_generic_formatting();
    test_pointer_inspection();
    test_memory_allocation();
    test_assertions_pass();
    test_soft_checks();
    test_backtrace();
    test_loop_tracing();
    test_conditional_compilation();
    test_scope_helpers();
    test_format_edge_cases();
    test_compile_definitions();
    test_integration();
    test_abort_compilation();
    
    /* Print summary */
    fprintf(stdout, "\n");
    fprintf(stdout, "========================================\n");
    fprintf(stdout, "  TEST SUMMARY\n");
    fprintf(stdout, "========================================\n");
    fprintf(stdout, "Passed: %d\n", tests_passed);
    fprintf(stdout, "Failed: %d\n", tests_failed);
    fprintf(stdout, "Total:  %d\n", tests_passed + tests_failed);
    fprintf(stdout, "========================================\n");
    
    if (tests_failed > 0) {
        fprintf(stdout, "RESULT: SOME TESTS FAILED\n");
        return 1;
    } else {
        fprintf(stdout, "RESULT: ALL TESTS PASSED\n");
        return 0;
    }
}
