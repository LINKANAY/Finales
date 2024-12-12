#include "dna.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef TEST

void test_dna_creation()
{
    dna_t dnaT = dna_T();
    dna_t dnaC = dna_C();
    dna_t dnaA = dna_A();
    dna_t dnaG = dna_G();

    dna_destroy(dnaT);
    dna_destroy(dnaC);
    dna_destroy(dnaA);
    dna_destroy(dnaG);
}

void test_dna_print()
{
    dna_t dna = dna_T();
    dna_print(dna);
    dna_destroy(dna);
}

void test_dna_is_equal()
{
    dna_t dna1 = dna_T();
    dna_t dna2 = dna_T();
    dna_t dna3 = dna_C();

    assert(dna_is_equal(dna1, dna2) == true);
    assert(dna_is_equal(dna1, dna3) == false);

    dna_destroy(dna1);
    dna_destroy(dna2);
    dna_destroy(dna3);
}

int main()
{
    test_dna_creation();
    test_dna_print();
    test_dna_is_equal();

    printf("All tests passed!\n");
    return 0;
}

#endif
