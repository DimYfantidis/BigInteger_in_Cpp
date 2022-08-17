#ifndef BIGINTEGER_BIGDECIMAL_H
#define BIGINTEGER_BIGDECIMAL_H

#include "BigInteger.h"

#include <fstream>


class BigDecimal {
private:
    BigInteger exponent;

    BigInteger mantissa;

public:
    // Constructors
    BigDecimal() = default;

    BigDecimal(double);

    BigDecimal(std::string &s);

    BigDecimal(const char *s);

    BigDecimal(const BigDecimal &);

    BigDecimal(BigDecimal&&);

    BigDecimal(const BigInteger &);

    ~BigDecimal() = default;


    // Decimal String representation:
    std::string toString() const;

    friend bool Null(const BigDecimal &);


    /* * * * Operator Overloading * * * */

    // Direct assignment
    BigDecimal &operator = (const BigInteger &);
    BigDecimal &operator = (BigInteger &&) noexcept;

    // Cast to double
    explicit operator double() const;

    // Cast to Integer
    explicit operator BigInteger() const;

    // Comparison operators
    friend bool operator == (const BigDecimal &, const BigDecimal &);
    friend bool operator != (const BigDecimal &, const BigDecimal &);

    friend bool operator > (const BigDecimal &, const BigDecimal &);
    friend bool operator < (const BigDecimal &, const BigDecimal &);

    friend bool operator >= (const BigDecimal &, const BigDecimal &);
    friend bool operator <= (const BigDecimal &, const BigDecimal &);

    // Multiplication and Division
    friend BigDecimal &operator *= (BigDecimal &, const BigDecimal &);
    friend BigDecimal &operator /= (BigDecimal &, const BigDecimal &);

    friend BigDecimal operator * (const BigDecimal &, const BigDecimal &);
    friend BigDecimal operator / (const BigDecimal &, const BigDecimal&);

    // Power Function
    friend BigDecimal &operator ^= (BigDecimal &, const BigDecimal &);
    friend BigDecimal operator ^ (const BigDecimal &, const BigDecimal &);

    // Read and Write
    friend std::ostream &operator << (std::ostream &, const BigDecimal &);
    friend std::istream &operator >> (std::istream &, BigDecimal &);


    /* * * * Arithmetic functions * * * */

    // Basic functions
    static BigDecimal sqrt(const BigDecimal &);
    static BigDecimal sqrt_n(int, const BigDecimal &);
    static BigDecimal log2(const BigDecimal &);
    static BigDecimal log10(const BigDecimal &);

    // Trigonometric functions
    static BigDecimal sin(const BigDecimal &);
    static BigDecimal cos(const BigDecimal &);
    static BigDecimal tan(const BigDecimal &);
    static BigDecimal cot(const BigDecimal &);

    static BigDecimal asin(const BigDecimal &);
    static BigDecimal acos(const BigDecimal &);
    static BigDecimal atan(const BigDecimal &);
    static BigDecimal acot(const BigDecimal &);

    static BigDecimal asec(const BigDecimal &);
    static BigDecimal acsc(const BigDecimal &);
};

namespace BigConstants
{
    BigDecimal& PI();
    BigDecimal& E();
}

#define BIG_PI  PI()
#define BIG_E   E()

#endif //BIGINTEGER_BIGDECIMAL_H
