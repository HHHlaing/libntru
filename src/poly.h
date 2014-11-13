#ifndef NTRU_POLY_H
#define NTRU_POLY_H

#include <stdint.h>
#include "rand.h"
#include "types.h"

/**
 * @brief Random ternary polynomial
 *
 * Generates a random ternary polynomial.
 *
 * @param N the number of coefficients; must be NTRU_MAX_N or less
 * @param num_ones number of ones
 * @param num_neg_ones number of negative ones
 * @param poly output parameter; a pointer to store the new polynomial
 * @param rand_ctx a random number generator
 * @return 1 for success, 0 for failure
 */
uint8_t ntru_rand_tern(uint16_t N, uint16_t num_ones, uint16_t num_neg_ones, NtruTernPoly *poly, NtruRandContext *rand_ctx);

#ifndef NTRU_AVOID_HAMMING_WT_PATENT
/**
 * @brief Random product-form polynomial
 *
 * Generates a random product-form polynomial consisting of 3 random ternary polynomials.
 *
 * @param N the number of coefficients; must be NTRU_MAX_N or less
 * @param df1 number of ones and negative ones in the first ternary polynomial
 * @param df2 number of ones and negative ones in the second ternary polynomial
 * @param df3_ones number of ones ones in the third ternary polynomial
 * @param df3_neg_ones number of negative ones in the third ternary polynomial
 * @param poly output parameter; a pointer to store the new polynomial
 * @param rand_ctx a random number generator
 * @return 1 for success, 0 for failure
 */
uint8_t ntru_rand_prod(uint16_t N, uint16_t df1, uint16_t df2, uint16_t df3_ones, uint16_t df3_neg_ones, NtruProdPoly *poly, NtruRandContext *rand_ctx);
#endif   /* NTRU_AVOID_HAMMING_WT_PATENT */

/**
 * @brief Ternary to general integer polynomial
 *
 * Converts a NtruTernPoly to an equivalent NtruIntPoly.
 *
 * @param a a ternary polynomial
 * @param b output parameter; a pointer to store the new polynomial
 */
void ntru_tern_to_int(NtruTernPoly *a, NtruIntPoly *b);

/**
 * @brief Addition of two polynomials
 *
 * Adds a NtruIntPoly to another.
 * The polynomial b must not have more coefficients than a.
 *
 * @param a input and output parameter; coefficients are overwritten
 * @param b a polynomial to add to the polynomial a
 */
void ntru_add_int(NtruIntPoly *a, NtruIntPoly *b);

/**
 * @brief Addition of two polynomials with a modulus
 *
 * Adds a NtruIntPoly to another, taking the coefficient values modulo an integer.
 * The polynomial b must not have more coefficients than a.
 *
 * @param a input and output parameter; coefficients are overwritten
 * @param b a polynomial to add to the polynomial a
 * @param modulus the modulus to apply to the coefficients of c
 */
void ntru_add_int_mod(NtruIntPoly *a, NtruIntPoly *b, uint16_t modulus);

/**
 * @brief Subtraction of two polynomials
 *
 * Subtracts a NtruIntPoly from another.
 * The polynomial b must not have more coefficients than a.
 *
 * @param a input and output parameter; coefficients are overwritten
 * @param b a polynomial to subtract from the polynomial a
 */
void ntru_sub_int(NtruIntPoly *a, NtruIntPoly *b);

#ifndef NTRU_AVOID_HAMMING_WT_PATENT
/**
 * @brief Product-form to general polynomial
 *
 * Converts a NtruProdPoly to an equivalent NtruIntPoly.
 *
 * @param a a product-form polynomial
 * @param b output parameter; a pointer to store the new polynomial
 */
void ntru_prod_to_int(NtruProdPoly *a, NtruIntPoly *b);
#endif   /* NTRU_AVOID_HAMMING_WT_PATENT */

/**
 * @brief General polynomial by ternary polynomial multiplication
 *
 * Multiplies a NtruIntPoly by a NtruTernPoly. The number of coefficients
 * must be the same for both polynomials.
 *
 * @param a a general polynomial
 * @param b a ternary polynomial
 * @param c output parameter; a pointer to store the new polynomial
 * @return 0 if the number of coefficients differ, 1 otherwise
 */
uint8_t ntru_mult_tern(NtruIntPoly *a, NtruTernPoly *b, NtruIntPoly *c);

#ifndef NTRU_AVOID_HAMMING_WT_PATENT
/**
 * @brief General polynomial by product-form polynomial multiplication
 *
 * Multiplies a NtruIntPoly by a NtruProdPoly. The number of coefficients
 * must be the same for both polynomials.
 *
 * @param a a general polynomial
 * @param b a product-form polynomial
 * @param c output parameter; a pointer to store the new polynomial
 * @return 0 if the number of coefficients differ, 1 otherwise
 */
uint8_t ntru_mult_prod(NtruIntPoly *a, NtruProdPoly *b, NtruIntPoly *c);
#endif   /* NTRU_AVOID_HAMMING_WT_PATENT */

/**
 * @brief Polynomial to binary
 *
 * Converts a NtruIntPoly to a uint8_t array. Each coefficient is encoded
 * in (log q) bits.
 *
 * @param p a polynomial
 * @param p the modulus; must be a power of two
 * @param a output parameter; a pointer to store the encoded polynomial
 */
void ntru_to_arr(NtruIntPoly *p, uint16_t q, uint8_t *a);

/**
 * @brief Polynomial to binary modulo 4
 *
 * Optimized version of ntru_to_arr() for q=4.
 * Encodes the low 2 bits of all coefficients in a uint8_t array.
 *
 * @param p a polynomial
 * @param arr output parameter; a pointer to store the encoded polynomial
 */
void ntru_to_arr4(NtruIntPoly *p, uint8_t *arr);

void ntru_from_arr(uint8_t *arr, uint16_t N, uint16_t q, NtruIntPoly *p);

/**
 * @brief Multiplies a polynomial by a factor
 *
 * Multiplies each coefficient of an NtruIntPoly by an integer.
 *
 * @param a input and output parameter; coefficients are overwritten
 * @param factor the factor to multiply by
 */
void ntru_mult_fac(NtruIntPoly *a, int16_t factor);

/**
 * @brief Multiplication of two general polynomials with a modulus
 *
 * Multiplies a NtruIntPoly by another, taking the coefficient values modulo an integer.
 * The number of coefficients must be the same for both polynomials.
 *
 * @param a input and output parameter; coefficients are overwritten
 * @param b a polynomial to multiply by
 * @param c output parameter; a pointer to store the new polynomial
 * @param modulus the modulus to apply to the coefficients of c
 * @return 0 if the number of coefficients differ, 1 otherwise
 */
uint8_t ntru_mult_int_mod(NtruIntPoly *a, NtruIntPoly *b, NtruIntPoly *c, uint16_t modulus);

/**
 * @brief Reduction modulo an integer
 *
 * Reduces the coefficients of an NtruIntPoly modulo an integer.
 *
 * @param p input and output parameter; coefficients are overwritten
 * @param modulus the modulus to apply to the coefficients of c
 */
void ntru_mod(NtruIntPoly *p, uint16_t modulus);

/**
 * @brief Reduction modulo 3
 *
 * Reduces the coefficients of an NtruIntPoly modulo 3 such that all
 * coefficients are ternary.
 *
 * @param p input and output parameter; coefficients are overwritten
 * @param modulus the modulus to apply to the coefficients of c
 */
void ntru_mod3(NtruIntPoly *p);

/**
 * @brief Reduction modulo an integer, centered
 *
 * Reduces the coefficients of an NtruIntPoly modulo an integer such that
 * -q/2 <= p->coeffs[i] < q/2 for all coefficients.
 *
 * @param p input and output parameter; coefficients are overwritten
 * @param modulus the modulus to apply to the coefficients of p
 */
void ntru_mod_center(NtruIntPoly *p, uint16_t modulus);

/**
 * @brief Equality with one
 *
 * Tests if p(x) = 1
 *
 * @param p a polynomial
 * @return 1 iff all coefficients are equal to zero, except for the lowest coefficient which must equal 1
 */
uint8_t ntru_equals1(NtruIntPoly *p);

/**
 * @brief Equality of two polynomials
 *
 * Tests if a(x) = b(x)
 *
 * @param a a polynomial
 * @param b a polynomial
 * @return 1 iff all coefficients are equal
 */
uint8_t ntru_equals_int(NtruIntPoly *a, NtruIntPoly *b);

/**
 * @brief Frequency of a coefficient
 *
 * Returns the number of times a coefficient value occurs
 * in a polynomial.
 *
 * @param a a polynomial
 * @param value
 * @return the number of coefficients equal to the value
 */
uint16_t ntru_count(NtruIntPoly *p, int16_t value);

/**
 * @brief Erases a ternary polynomial
 *
 * Overwrites all coefficients of a ternary polynomial with zeros.
 *
 * @param p a polynomial
 */
void ntru_clear_tern(NtruTernPoly *p);

/**
 * @brief Erases a general polynomial
 *
 * Overwrites all coefficients of a polynomial with zeros.
 *
 * @param p a polynomial
 */
void ntru_clear_int(NtruIntPoly *p);

/**
 * @brief Inverse modulo q
 *
 * Computes the inverse mod q; q must be a power of 2.
 * Returns 0 if the polynomial is not invertible, 1 otherwise.
 * The algorithm is described in "Almost Inverses and Fast NTRU Key Generation" at
 * http://www.securityinnovation.com/uploads/Crypto/NTRUTech014.pdf
 *
 * @param a a polynomial
 * @param q the modulus
 * @param Fq output parameter; a pointer to store the new polynomial
 * @return 1 if a is invertible, 0 otherwise
 */
uint8_t ntru_invert(NtruIntPoly *a, uint16_t q, NtruIntPoly *Fq);

uint8_t ntru_is_invertible_pow2(NtruIntPoly *a);

/**
 * @brief Sum of coefficients
 *
 * Returns the sum of all coefficients except the lowest coefficient,
 * i.e. evaluates the polynomial at 1 and subtracts the constant coefficient.
 *
 * @param a a polynomial
 * @return the sum of all coefficients
 */
int32_t ntru_sum_coeffs(NtruIntPoly *a);

#endif   /* NTRU_POLY_H */
