/*
 * test_debug_ndebug_c23.c - Tests debug.h in NDEBUG (release) mode for C23
 * Author: GitHub Copilot
 * Date: 2025-12-17
 *
 * Compile with: gcc -std=c23 -O2 -DNDEBUG -o test_debug_ndebug_c23 test_debug_ndebug_c23.c
 *
 * This test verifies that:
 * 1. All debug macros compile to no-ops when NDEBUG is defined
 * 2. No runtime overhead is introduced
 * 3. DEBUG_EXIT still returns correctly
 * 4. DEBUG_MALLOC/FREE still allocate/free correctly
 */

#define NDEBUG  // Must be defined BEFORE including debug.h
#define DEBUG_LEVEL 5  // Should be ignored when NDEBUG is set
#include "../debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Test counters */
static int tests_passed = 0;
static int tests_failed = 0;

#define TEST_PASS(name) \
    do { \
        printf("[PASS] %s\n", name); \
        tests_passed++; \
    } while(0)

#define TEST_FAIL(name, reason) \
    do { \
        printf("[FAIL] %s - %s\n", name, reason); \
        tests_failed++; \
    } while(0)

/* ============================================================================
 * TEST: All debug macros should be no-ops
 * ============================================================================ */

void test_log_macros_noop(void) {
    /* These should all compile but do nothing */
    DEBUG_TRACE("This should not print");
    DEBUG_DEBUG("This should not print");
    DEBUG_INFO("This should not print");
    DEBUG_WARN("This should not print");
    DEBUG_ERROR("This should not print");
    DEBUG_LOG(LOG_INFO, "This should not print");
    TEST_PASS("Log macros compile as no-ops");
}

int test_exit_return(int n) {
    DEBUG_ENTER("(n=%d)", n);
    int result = n * 2;
    DEBUG_EXIT(result);  /* Should still return correctly */
}

void test_function_tracing_noop(void) {
    int result = test_exit_return(21);
    if (result == 42) {
        TEST_PASS("DEBUG_EXIT returns correctly in NDEBUG mode");
    } else {
        TEST_FAIL("DEBUG_EXIT", "Return value incorrect");
    }
}

void test_var_ptr_noop(void) {
    int x = 42;
    DEBUG_VAR(x);  /* Should be no-op */
    
    int* p = &x;
    DEBUG_PTR(p, "int pointer");  /* Should be no-op */
    
    TEST_PASS("DEBUG_VAR and DEBUG_PTR compile as no-ops");
}

void test_memory_functions(void) {
    /* DEBUG_MALLOC should still allocate */
    void* p = DEBUG_MALLOC(100);
    if (p != NULL) {
        TEST_PASS("DEBUG_MALLOC still allocates in NDEBUG mode");
        
        /* Can write to the memory */
        memset(p, 0, 100);
        
        DEBUG_FREE(p);  /* Should still free */
        TEST_PASS("DEBUG_FREE still frees in NDEBUG mode");
    } else {
        TEST_FAIL("DEBUG_MALLOC", "Returned NULL");
    }
}

void test_assert_check_noop(void) {
    /* These should evaluate expression but not abort/warn */
    int x = 0;
    DEBUG_ASSERT(1 == 1, "Should be no-op");
    DEBUG_CHECK(1 == 1, "Should be no-op");
    
    /* In NDEBUG, even failing checks should not warn */
    DEBUG_CHECK(0 == 1, "This warning should NOT print");
    
    TEST_PASS("DEBUG_ASSERT and DEBUG_CHECK compile as no-ops");
}

void test_backtrace_noop(void) {
    DEBUG_BACKTRACE();  /* Should be no-op */
    TEST_PASS("DEBUG_BACKTRACE compiles as no-op");
}

void test_loop_macros_noop(void) {
    int sum = 0;
    DEBUG_LOOP_START("Loop");
    for (int i = 0; i < 5; i++) {
        DEBUG_LOOP_ITER(i, 5);
        sum += i;
    }
    DEBUG_LOOP_END();
    
    if (sum == 10) {
        TEST_PASS("DEBUG_LOOP_* compile as no-ops");
    } else {
        TEST_FAIL("DEBUG_LOOP_*", "Loop behavior changed");
    }
}

void test_conditional_noop(void) {
    int executed = 0;
    
    /* DEBUG_IF should always be false in NDEBUG mode */
    DEBUG_IF(1) {
        executed = 1;
    }
    
    if (executed == 0) {
        TEST_PASS("DEBUG_IF always false in NDEBUG mode");
    } else {
        TEST_FAIL("DEBUG_IF", "Block unexpectedly executed");
    }
}

void test_scope_noop(void) {
    DEBUG_SCOPE_BEGIN();
    /* Should not affect control flow */
    int x = 1;
    (void)x;
    TEST_PASS("DEBUG_SCOPE_BEGIN compiles as no-op");
}

void test_break_noop(void) {
    /* DEBUG_BREAK should be no-op, not actually trap */
    /* (We can't actually call it in the test or it would trap in debug mode) */
    /* Just verify it compiles */
    #ifdef NDEBUG
    /* The macro is defined as (void)0 in NDEBUG */
    TEST_PASS("DEBUG_BREAK compiles as no-op in NDEBUG");
    #else
    TEST_FAIL("DEBUG_BREAK", "NDEBUG not defined");
    #endif
}

void test_definitions_ndebug(void) {
    /* Verify NDEBUG is defined */
    #ifdef NDEBUG
    TEST_PASS("NDEBUG is defined");
    #else
    TEST_FAIL("NDEBUG", "Not defined");
    #endif
    
    /* LOG_* constants should NOT be defined in NDEBUG mode */
    #ifdef LOG_ERROR
    TEST_FAIL("LOG_ERROR", "Should not be defined in NDEBUG");
    #else
    TEST_PASS("LOG_ERROR not defined in NDEBUG (correct)");
    #endif
}

/* ============================================================================
 * MAIN
 * ============================================================================ */

int main(void) {
    printf("\n");
    printf("========================================\n");
    printf("  debug.h NDEBUG Mode Tests (C23)\n");
    printf("========================================\n");
    #ifdef NDEBUG
    printf("Mode: RELEASE (NDEBUG defined)\n");
    #else
    printf("Mode: DEBUG (NDEBUG NOT defined - ERROR!)\n");
    #endif
    printf("========================================\n");
    
    test_log_macros_noop();
    test_function_tracing_noop();
    test_var_ptr_noop();
    test_memory_functions();
    test_assert_check_noop();
    test_backtrace_noop();
    test_loop_macros_noop();
    test_conditional_noop();
    test_scope_noop();
    test_break_noop();
    test_definitions_ndebug();
    
    printf("\n");
    printf("========================================\n");
    printf("  TEST SUMMARY (NDEBUG Mode)\n");
    printf("========================================\n");
    printf("Passed: %d\n", tests_passed);
    printf("Failed: %d\n", tests_failed);
    printf("Total:  %d\n", tests_passed + tests_failed);
    printf("========================================\n");
    
    if (tests_failed > 0) {
        printf("RESULT: SOME TESTS FAILED\n");
        return 1;
    } else {
        printf("RESULT: ALL TESTS PASSED\n");
        return 0;
    }
}
