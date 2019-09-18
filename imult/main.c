//
//  main.c
//  imult
//
//  Created by David Hoy on 9/18/19.
//  Copyright © 2019 David Hoy. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <sys/time.h>


/***************************************************************
 * Type definitions
 ***************************************************************/
typedef int (*imult_func)(int a, int b);


/***************************************************************
 * imult0()
 * Muliply operands using standard C operator - provides baseline.
 * In: a - first operand
 *     b - second operand
 * Out: a times b
 ***************************************************************/
int imult0(int a, int b) {
    // Baseline function, using standard multiplication operator.
    int result = a * b;
    return result;
}


/***************************************************************
 * imult1()
 * Muliply operands using basic loop
 * In: a - first operand
 *     b - second operand
 * Out: a times b
 ***************************************************************/
int imult1(int a, int b) {
    // First iteration, simple loop adding a to result b times.
    int result = 0;
    while (b != 0) {
        result += a;
        b--;
    }
    return result;
}


/***************************************************************
 * imult2()
 * Muliply operands using shortened loop.
 * In: a - first operand
 *     b - second operand
 * Out: a times b
 ***************************************************************/
int imult2(int a, int b) {
    // Second iteration, limits loop to the smaller of the two values
    int result = 0;
    if (a > b) {
        while (b != 0) {
            result += a;
            b--;
        }
    }
    else {
        while (a != 0) {
            result += b;
            a--;
        }
    }
    return result;
}


/***************************************************************
 * imult3()
 * Muliply operands using inline assembler.
 * In: a - first operand
 *     b - second operand
 * Out: a times b
 ***************************************************************/
int imult3(int a, int b) {
    // OK, this is cheating a bit, not using C operator but instead the
    // processor's native assembly instruction instead ;-).
    // Will only work on x86.
    int result = 0;
    __asm("imull %%ebx, %%eax;" : "=a"(result) : "a"(a), "b"(b));
    return result;
}


/***************************************************************
 * timed_test_run()
 * Perform timed test run on the function given, using the arguments
 * provided.
 * In: func - function pointer for multiplication method
 *        a - first operand
 *        b - second operand
 * Out: void
 ***************************************************************/
void timed_test_run(imult_func func, int a, int b, int iterations) {
    struct timeval start, stop;
    gettimeofday(&start, NULL);
    for (int i = 0; i < iterations; i++) {
        int result = func(a, b);
        assert(result == (a*b));
    }
    gettimeofday(&stop, NULL);
    int elapsed = stop.tv_usec - start.tv_usec;
    printf("Func took %dms for %d iterations\n", elapsed, iterations);
}


/***************************************************************
 * main()
 * Entry point for the appliction
 * In: argc - count of command line arguments
 *     argv - string array of command line arguments
 * Out: irrelevant
 ***************************************************************/
int main(int argc, const char * argv[]) {
    // insert code here...
    
    int a = 23;
    int b = 435;
    int iterations = 10000;
    
    timed_test_run(imult0, a, b, iterations);       // Very fast, using C operator.
    timed_test_run(imult1, a, b, iterations);       // Slow, using simple loop.
    timed_test_run(imult2, a, b, iterations);       // Faster, depending on difference between a & b.
    timed_test_run(imult3, a, b, iterations);       // Very fast, using inline assembly.
    
    return 0;
}
