#include <stdio.h>

/* 
 * float_inv - Return bit-level equivalent of expression 1/x (x is an integer) for
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   When x is 0, return NaN.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 114514
 *   Rating: 3
 *   For mercy, x is between -16777216 and 16777216, meaning that you don't have
 *   to handle denormalized numbers.
 */
unsigned float_inv(int x) {
  // x is an integer!
  // return a unsigned(but interpreted as a float)
  
  // Handle x = 0 case - return positive infinity
  if (x == 0) {
    return 0x7F800000; // +infinity: exp = 0xFF, mantissa = 0
  }
  
  // Handle special cases first
  if (x == 1) return 0x3F800000;  // 1.0
  if (x == -1) return 0xBF800000; // -1.0
  if (x == 2) return 0x3F000000;  // 0.5
  if (x == -2) return 0xBF000000; // -0.5
  
  // Extract sign
  unsigned sign = 0;
  if (x < 0) {
    sign = 0x80000000;
    if (x == 0x80000000) {
      // Special case: x = -2^31
      return sign | (95 << 23); // exp = 127 - 32 = 95
    }
    x = -x; // Make x positive
  }
  
  // Convert x to float first using the float_i2f approach
  // Find the number of bits needed to represent x
  int exp = 0;
  unsigned temp = x;
  while (temp) {
    temp >>= 1;
    exp++;
  }
  exp--; // Adjust for 0-based indexing
  
  // Extract mantissa for x in float format
  unsigned x_mantissa = 0;
  if (exp <= 23) {
    x_mantissa = (x & ((1U << exp) - 1)) << (23 - exp);
  } else {
    x_mantissa = (x & ((1U << exp) - 1)) >> (exp - 23);
    // Handle rounding here if needed
  }
  
  // Now x in float format has:
  // exponent: 127 + exp
  // mantissa: x_mantissa
  
  // For 1/x:
  // If x is a power of 2 (mantissa = 0), then 1/x is also a power of 2
  // Otherwise, 1/(1.m * 2^e) = (1/1.m) * 2^(-e) and 1/1.m is in [0.5, 1)
  int new_exp;
  if (x_mantissa == 0) {
    // x is a power of 2, so 1/x = 2^(-exp)
    new_exp = 127 - exp;
  } else {
    // Need normalization: exponent becomes 127 + (-exp - 1) = 126 - exp
    new_exp = 126 - exp;
  }
  
  // Handle underflow/overflow
  if (new_exp <= 0) return sign; // underflow to zero
  if (new_exp >= 255) return sign | 0x7F800000; // overflow to infinity
  
  unsigned result_mantissa;
  if (x_mantissa == 0) {
    // x is a power of 2, so 1/x is also a power of 2 with mantissa = 0
    result_mantissa = 0;
  } else {
    // For the new mantissa, we need to compute 2 * (1/(1 + x_mantissa/2^23)) - 1
    // This gives us the fractional part when the result is normalized to [1,2)
    unsigned long long numerator = (1ULL << 47); // 2^47 (multiply by 2)
    unsigned long long denominator = (1ULL << 23) + x_mantissa;
    unsigned long long quotient = numerator / denominator;
    unsigned long long remainder = numerator % denominator;
    
    // Handle rounding: if remainder >= denominator/2, round up
    if (remainder * 2 >= denominator) {
      quotient++;
    }
    
    // The quotient represents 2^24 * (1/(1 + x_mantissa/2^23))
    // Subtract 2^24 to get the fractional part
    result_mantissa = (quotient - (1ULL << 24)) & 0x7FFFFF;
  }
  
  return sign | (new_exp << 23) | result_mantissa;
}


unsigned float_inv_answer(int x) {
    union {
        unsigned u;
        float f;
    } a;
    a.f = 1.0 / x;
    return a.u;
}

int main() {
    for (int i = 0; i <= 16777216; i++) {
        if (float_inv(-i) != float_inv_answer(-i)) {
            printf("float_inv(%d) = 0x%x, float_inv_answer(%d) = 0x%x\n", -i, float_inv(-i), -i, float_inv_answer(-i));
            break;
        }
        if (float_inv(i) != float_inv_answer(i)) {
            printf("float_inv(%d) = 0x%x, float_inv_answer(%d) = 0x%x\n", i, float_inv(i), i, float_inv_answer(i));
            break;
        }
    }
    return 0;
}