/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	int notBothOne = ~(x & y);
	int notBothZero = ~((~x) & (~y));
	return notBothOne & notBothZero;
}

// P3
/*
 * clearByte - return x with the nth byte cleared to 0
 *   You can assume 0 <= n <= 3
 *   Example: clearByte(0x01020304, 2) = 0x01000304
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int clearByte(int x,int n) {
  int shift = n << 3;
  int mask = ~(0xFF << shift);
  return x & mask;
}

// P4
/* 
 * roundUp - round up x to the nearest multiple of 256 that is bigger than x
 *   Example: roundUp(0x117f) = 0x1200
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int roundUp(int x) {
  int mask = 0xFF;
  int hasRemainder = !!(x & mask);
  int base = x & ~mask;
  return base + (hasRemainder << 8);
}

// P5
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int sign = x >> 31;
  int negX = (~x + 1);
  return negX & sign;
}

// P6
/* 
 * isLargerOrEqual - return 1 if x >= y, else return 0 
 *   Example: isLargerOrEqual(5,4) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 4
 */
int isLargerOrEqual(int x, int y) {
  int signX = (x >> 31) & 1;
  int signY = (y >> 31) & 1;
  int signDiff = signX ^ signY;
  int diff = x + (~y + 1);
  int diffSign = (diff >> 31) & 1;
  int sameSignCmp = !diffSign;
  int sameSign = !signDiff;
  return (signDiff & signY) | (sameSign & sameSignCmp);
}

// P7
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int mask=((0x1<<(32+~n))+~0)|(0x1<<(32+~n));
  return (x>>n)&mask;
}

// P8
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int mask = 0x0F;                 // 合法常量
  mask = mask | (mask << 8);       // 得到 0x0F0F
  mask = mask | (mask << 16);      // 得到 0x0F0F0F0F
  // int lowPart = (x & mask) << 4;   // 取低 nibble 并左移
  // int highPart = (x >> 4) & mask;  // 取高 nibble 并右移
  // return lowPart | highPart;       // 合并
  return ((x & mask) << 4) | ((x >> 4) & mask);
}

// P9
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFC) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int firstZero = (~x) & (x + 1);
  int filled = x | firstZero;
  return (~filled) & (filled + 1);
}

// P10
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int mask = 31;
  int shift = n & mask;
  int negShift = (32 + (~shift + 1)) & mask;
  int leftPart = x << negShift;
  int rightShifted = x >> shift;
  int logicalMask = ~(((1 << 31) >> shift) << 1);
  int rightPart = rightShifted & logicalMask;
  return leftPart | rightPart;
}

// P11
/* 
 * fractions - return floor((x*5 + 8)/16) for 0 <= x <= (1 << 28), x is an integer 
 *   Example: fractions(20) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 5
 */
int fractions(int x) {
  int times4 = x << 2;
  int times5 = times4 + x;
  int biased = times5 + 8;
  return biased >> 4;
}


// P12
/* 
 * overflowCalc - given binary representations of three 32-bit positive numbers and add them together, 
 *      return the binary representation of the part where bits are higher than 32.
 *   Examples: overflowCalc(0xffffffff, 0xffffffff, 0xffffffff) = 2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7 
 */
int overflowCalc(int x, int y, int z) {
  int sum1 = x + y;
  int sum2 = sum1 + z;
  int carry1 = ((x & y) | ((x ^ y) & ~sum1)) >> 31 & 1;
  int carry2 = ((sum1 & z) | ((sum1 ^ z) & ~sum2)) >> 31 & 1;
  return carry1 + carry2;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 36
 *   Rating: 7
 */
int mul5Sat(int x) {
  int c2 = 1 << 31;
  int c1 = c2 + (~0);
  int mark = x >> 31;
  int absx = (x ^ mark) + (~mark) + 1;
  int sign1 = (absx << 2) >> 31;
  int sign2 = ((absx << 1) + absx) >> 31;
  int sign3 = ((absx << 2) + absx) >> 31;
  int sign4 = sign1 | sign2 | sign3;
  return (sign4 & ((mark & c2) | ((~mark) & c1))) | (~sign4 & ((x << 2) + x));
}

// P14
/* 
 * float_inv - Return bit-level equivalent of expression 1/x (x is an integer) for
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   When x is 0, return NaN.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 120
 *   Rating: 3
 *   For mercy, x is between -16777216 and 16777216, meaning that you don't have
 *   to handle denormalized numbers.
 */
unsigned float_inv(int x) {
  
  unsigned sign = 0;
  unsigned result_mantissa;
  int exp = 0;
  unsigned temp;
  unsigned x_mantissa = 0;
  int new_exp;
  unsigned denominator;
  unsigned quotient_high;
  unsigned quotient_low;
  unsigned remainder;
  unsigned final_quotient;
  int i;

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

  temp = x;
  while (temp) {
    temp >>= 1;
    exp++;
  }
  exp--; // Adjust for 0-based indexing
  
  // Extract mantissa for x in float format

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
  

  if (x_mantissa == 0) {
    // x is a power of 2, so 1/x is also a power of 2 with mantissa = 0
    result_mantissa = 0;
  } else {
    // For the new mantissa, we need to compute 2 * (1/(1 + x_mantissa/2^23)) - 1
    // This gives us the fractional part when the result is normalized to [1,2)
    
    // Manual 64-bit division: numerator = 2^47, denominator = 2^23 + x_mantissa
    // We'll compute this as: (2^47) / (2^23 + x_mantissa)
    
    denominator = (1U << 23) + x_mantissa;
    
    // numerator = 2^47 = 0x800000000000 (high=0x8000, low=0x00000000)
    // We'll do long division bit by bit
    quotient_high = 0;
    quotient_low = 0;
    remainder = 0;
    
    // Start with the high bit of numerator (bit 47)
    // Since numerator = 2^47, only bit 47 is set, so we start there
    
    for (i = 47; i >= 0; i--) {
      remainder <<= 1;
      if (i == 47) remainder |= 1; // Only bit 47 is set in numerator
      
      if (remainder >= denominator) {
        remainder -= denominator;
        if (i >= 32) {
          quotient_high |= (1U << (i - 32));
        } else {
          quotient_low |= (1U << i);
        }
      }
    }
    
    // Handle rounding: if remainder >= denominator/2, round up
    if (remainder * 2 >= denominator) {
      quotient_low++;
      if (quotient_low == 0) quotient_high++; // Handle carry
    }
    
    // The quotient represents 2^24 * (1/(1 + x_mantissa/2^23))
    // Subtract 2^24 to get the fractional part
    // 2^24 = 0x01000000, so we subtract from quotient_low
    final_quotient = quotient_low - (1U << 24);
    result_mantissa = final_quotient & 0x7FFFFF;
  }
  
  return sign | (new_exp << 23) | result_mantissa;
}

// P15
/* 
 * float_half - Return bit-level equivalent of expression f/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 32
 *   Rating: 4
 */
unsigned float_half(unsigned f) {
  unsigned sign = f & (1 << 31);
  unsigned exp = (f >> 23) & 0xFF;
  unsigned frac = f & ((1 << 23) - 1);
  unsigned rounding;

  if (exp == 0xFF) {
      return f; // NaN 或 Infinity 返回自身
  }

  if (exp == 0 || exp == 1) {
    // 非标准化数或指数为1的情况，需要处理尾数并考虑舍入
    if (exp == 1) {
        frac = frac | (1 << 23);
    }

    // 检查被移出的位以决定是否需要舍入
    rounding = (frac & 3); // 取尾数的最低两位

    frac = frac >> 1; // 尾数右移一位

    if (rounding == 3) { // 11就加1
        frac = frac + 1;
    }

    // 指数变为0（非标准化数）
    exp = 0;

    return sign | (exp << 23) | (frac & ((1 << 23) - 1));
  } else {
    exp = exp - 1;
    return sign | (exp << 23) | frac;
  }
}

// P16
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 7
 */
unsigned float_i2f(int x) {
  int fx, exp, nx, wx;
  unsigned ans, sign, tag;
  if (!x) return x;
  if (x == 1 << 31) return 0xcf << 24; 
    sign = x >> 31;
    wx = fx = (x ^ sign) + (~sign) + 1;
    exp = 0;
    while (wx){
    exp++;
    wx >>= 1;
  }
  exp--;
  ans = (x & (1 << 31)) | ((exp + 127) << 23);
  if (exp <= 23) ans = ans | (fx & (~(1 << exp))) << (23 - exp);
  else{
    nx = fx >> (exp - 24);
    wx = (1 << (exp - 24)) - 1;
    if (fx & wx) tag = (nx & 1) == 1;
    else tag = (nx & 3) == 3; // 五成双
    ans = (ans | (((nx >> 1) & (~(1 << 23))))) + tag; 
  }
  return ans;
}


#ifdef NOT_SUPPOSED_TO_BE_DEFINED
#   __          __  _                          
#   \ \        / / | |                         
#    \ \  /\  / /__| | ___ ___  _ __ ___   ___ 
#     \ \/  \/ / _ \ |/ __/ _ \| '_ ' _ \ / _ \
#      \  /\  /  __/ | (_| (_) | | | | | |  __/       
#       \/  \/ \___|_|\___\___/|_| |_| |_|\___|
#                                              

#  ██╗  ██╗ ██████╗ ███╗   ██╗ ██████╗ ██████╗     ██████╗  █████╗ ██████╗ ████████╗
#  ██║  ██║██╔═══██╗████╗  ██║██╔═══██╗██╔══██╗    ██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝
#  ███████║██║   ██║██╔██╗ ██║██║   ██║██████╔╝    ██████╔╝███████║██████╔╝   ██║   
#  ██╔══██║██║   ██║██║╚██╗██║██║   ██║██╔══██╗    ██╔═══╝ ██╔══██║██╔══██╗   ██║   
#  ██║  ██║╚██████╔╝██║ ╚████║╚██████╔╝██║  ██║    ██║     ██║  ██║██║  ██║   ██║   
#  ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝    ╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   
#                                                                                   
#endif

// P17
/*
 * oddParity - return the odd parity bit of x, that is, 
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 2
 */
int oddParity(int x) {
  x ^= (x >> 16);
  x ^= (x >> 8);
  x ^= (x >> 4);
  x ^= (x >> 2);
  x ^= (x >> 1);
  return !(x & 1);
}

// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 2
 */
int bitCount(int x) {
  int mask1, mask2, mask3, mask4, mask5;
  mask1 = 0x55 | (0x55 << 8); 
  mask1 = mask1 | (mask1 << 16);  
  mask2 = 0x33 | (0x33 << 8);   
  mask2 = mask2 | (mask2 << 16);  
  mask3 = 0x0F | (0x0F << 8);  
  mask3 = mask3 | (mask3 << 16); 
  mask4 = 0xFF | (0xFF << 16);
  mask5 = 0xFF | (0xFF << 8);      

  x = (x & mask1) + ((x >> 1) & mask1);
  x = (x & mask2) + ((x >> 2) & mask2);
  x = (x & mask3) + ((x >> 4) & mask3);
  x = (x & mask4) + ((x >> 8) & mask4);
  x = (x & mask5) + ((x >> 16) & mask5);

  return x;
}
