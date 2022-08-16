#ifndef BIGINTEGER_BIGINTEGER_H
#define BIGINTEGER_BIGINTEGER_H

#include <string>
#include <cstring>
#include <vector>
#include <exception>


class BigInteger {
private:
    std::string digits;

public:
    //Constructors:
    BigInteger(unsigned long long n = 0);

    BigInteger(std::string &);

    BigInteger(const char *);

    BigInteger(const BigInteger &);

    BigInteger(BigInteger &&) noexcept;

    //Helper Functions:
    friend void divide_by_2(BigInteger &a);

    friend bool Null(const BigInteger &);

    friend int Length(const BigInteger &);

    int operator[] (int) const;

    const void *address() { return reinterpret_cast<void *>(digits.data()); }

    /* * * * Operator Overloading * * * */

    // Direct assignment
    BigInteger &operator = (const BigInteger &);
    BigInteger &operator = (BigInteger &&) noexcept;

    // Post/Pre - Incrementation
    BigInteger &operator ++ ();
    BigInteger &operator -- ();

    BigInteger operator ++ (int);
    BigInteger operator -- (int);

    //Addition and Subtraction
    friend BigInteger &operator += (BigInteger &, const BigInteger &);
    friend BigInteger &operator -= (BigInteger &, const BigInteger &);

    friend BigInteger operator + (const BigInteger &, const BigInteger &);
    friend BigInteger operator - (const BigInteger &, const BigInteger &);

    //Comparison operators
    friend bool operator == (const BigInteger &, const BigInteger &);
    friend bool operator != (const BigInteger &, const BigInteger &);

    friend bool operator > (const BigInteger &, const BigInteger &);
    friend bool operator < (const BigInteger &, const BigInteger &);

    friend bool operator >= (const BigInteger &, const BigInteger &);
    friend bool operator <= (const BigInteger &, const BigInteger &);

    //Multiplication and Division
    friend BigInteger operator * (const BigInteger &, const BigInteger &);
    friend BigInteger operator / (const BigInteger &, const BigInteger &);

    friend BigInteger &operator *= (BigInteger &, const BigInteger &);
    friend BigInteger &operator /= (BigInteger &, const BigInteger &);

    //Modulo
    friend BigInteger operator % (const BigInteger &, const BigInteger &);
    friend BigInteger &operator %= (BigInteger &, const BigInteger &);

    //Power Function
    friend BigInteger operator ^ (const BigInteger &, const BigInteger &);
    friend BigInteger &operator ^= (BigInteger &, const BigInteger &);

    //Square Root Function
    friend BigInteger sqrt(BigInteger &a);

    //Read and Write
    friend std::ostream &operator << (std::ostream &, const BigInteger &);
    friend std::istream &operator >> (std::istream &, BigInteger &);

    //Others
    static BigInteger catalan(int n);
    static BigInteger fibonacci(int n);
    static BigInteger factorial(int n);
};

BigInteger::BigInteger(std::string &s)
{
    digits = "";

    int n = static_cast<int>(s.size());

    for (int i = n - 1; i >= 0; i--)
    {
        if(!isdigit(s[i]))
        {
            std::string err_message;

            err_message = "Input Error: Could not parse \"";
            err_message += s;
            err_message += "\" to integer value.";

            throw std::invalid_argument(err_message);
        }
        digits.push_back(static_cast<char>(s[i] - '0'));
    }
}
BigInteger::BigInteger(unsigned long long nr)
{
    do
    {
        digits.push_back(static_cast<char>(nr % 10));
        nr /= 10;
    }
    while (nr);
}

BigInteger::BigInteger(const char *s)
{
    digits = "";

    for (int i = static_cast<int>(strlen(s)) - 1; i >= 0; i--)
    {
        if(!isdigit(s[i]))
        {
            std::string err_message;

            err_message = "Input Error: Could not parse \"";
            err_message += s;
            err_message += "\" to integer value.";

            throw std::invalid_argument(err_message);
        }
        digits.push_back(static_cast<char>(s[i] - '0'));
    }
}

BigInteger::BigInteger(const BigInteger &other) = default;

BigInteger::BigInteger(BigInteger &&other) noexcept : digits(std::move(other.digits)) {}

bool Null(const BigInteger& a)
{
    if(a.digits.size() == 1 && a.digits[0] == 0)
        return true;

    return false;
}

int Length(const BigInteger &a) {
    return static_cast<int>(a.digits.size());
}

int BigInteger::operator [] (const int index) const
{
    if(digits.size() <= index || index < 0) {
        throw std::invalid_argument("Out of bounds array index.");
    }
    return digits[index];
}

bool operator == (const BigInteger &a, const BigInteger &b) {
    return a.digits == b.digits;
}

bool operator != (const BigInteger & a, const BigInteger &b){
    return !(a == b);
}

bool operator < (const BigInteger&a, const BigInteger&b)
{
    int n = Length(a), m = Length(b);

    if(n != m) {
        return n < m;
    }

    while(n--)
    {
        if (a.digits[n] != b.digits[n])
            return a.digits[n] < b.digits[n];
    }
    return false;
}

bool operator > (const BigInteger&a, const BigInteger&b) {
    return b < a;
}

bool operator >= (const BigInteger&a, const BigInteger&b) {
    return !(a < b);
}

bool operator <= (const BigInteger&a, const BigInteger&b) {
    return !(a > b);
}

BigInteger &BigInteger::operator = (const BigInteger &other)
{
    if (this != &other) {
        this->digits = other.digits;
    }
    return *this;
}

BigInteger &BigInteger::operator = (BigInteger &&other) noexcept
{
    if (this != &other) {
        this->digits = std::move(other.digits);
    }
    return *this;
}

BigInteger &BigInteger::operator ++ ()
{
    int i;
    int n = static_cast<int>(digits.size());

    for (i = 0; i < n && digits[i] == 9; i++) {
        digits[i] = 0;
    }
    if(i == n) {
        digits.push_back(1);
    }
    else {
        digits[i]++;
    }
    return *this;
}

BigInteger BigInteger::operator ++ (int)
{
    BigInteger aux(*this);

    ++(*this);

    return aux;
}

BigInteger &BigInteger::operator -- ()
{
    if(digits[0] == 0 && digits.size() == 1) {
        throw std::underflow_error("");
    }
    int i;
    int n = static_cast<int>(digits.size());

    for (i = 0; digits[i] == 0 && i < n; i++) {
        digits[i] = 9;
    }
    digits[i]--;

    if(n > 1 && digits[n - 1] == 0) {
        digits.pop_back();
    }
    return *this;
}

BigInteger BigInteger::operator -- (int)
{
    BigInteger aux = *this;

    --(*this);

    return aux;
}

BigInteger &operator += (BigInteger &a, const BigInteger& b)
{
    int s;
    int i;
    int t = 0;

    int n = Length(a);
    int m = Length(b);

    if(m > n) {
        a.digits.append(m - n, 0);
    }
    n = Length(a);

    for (i = 0; i < n; i++)
    {
        if(i < m)
            s = (a.digits[i] + b.digits[i]) + t;
        else
            s = a.digits[i] + t;

        t = s / 10;

        a.digits[i] = static_cast<char>(s % 10);
    }
    if (t) a.digits.push_back(static_cast<char>(t));

    return a;
}

BigInteger operator + (const BigInteger &a, const BigInteger &b)
{
    BigInteger temp(a);
    temp += b;
    return temp;
}

BigInteger &operator -= (BigInteger&a, const BigInteger &b)
{
    if(a < b) {
        throw std::underflow_error("");
    }
    int n = Length(a);
    int m = Length(b);

    int i;
    int s;
    int t = 0;

    for (i = 0; i < n; i++)
    {
        if(i < m)
            s = a.digits[i] - b.digits[i]+ t;
        else
            s = a.digits[i]+ t;
        if(s < 0)
            s += 10, t = -1;
        else
            t = 0;

        a.digits[i] = static_cast<char>(s);
    }
    while(n > 1 && a.digits[n - 1] == 0)
        a.digits.pop_back(), n--;

    return a;
}

BigInteger operator - (const BigInteger& a, const BigInteger& b)
{
    BigInteger temp(a);
    temp -= b;
    return temp;
}

BigInteger &operator *= (BigInteger &a, const BigInteger &b)
{
    if(Null(a) || Null(b))
    {
        a = BigInteger();
        return a;
    }

    int n = static_cast<int>(a.digits.size());
    int m = static_cast<int>(b.digits.size());
    int i, j, s, t;

    std::vector<int> v(n + m, 0);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++) {
            v[i + j] += (a.digits[i]) * (b.digits[j]);
        }
    }
    n += m;

    a.digits.resize(v.size());

    for (i = 0, t = 0; i < n; i++)
    {
        s = t + v[i];
        v[i] = s % 10;
        t = s / 10;
        a.digits[i] = static_cast<char>(v[i]);
    }

    for (i = n - 1; i >= 1 && !v[i]; i--)
        a.digits.pop_back();

    return a;
}
BigInteger operator * (const BigInteger &a, const BigInteger &b)
{
    BigInteger temp(a);
    temp *= b;

    return temp;
}

BigInteger &operator /= (BigInteger& a, const BigInteger &b)
{
    if(Null(b)) {
        throw std::invalid_argument("Arithmetic Error: Division By 0");
    }
    if(a < b)
    {
        a = BigInteger();
        return a;
    }
    if(a == b)
    {
        a = BigInteger(1);
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a);

    std::vector<int> cat(n, 0);
    BigInteger t;

    for (i = n - 1; t * 10 + a.digits[i]  < b;i--)
    {
        t *= 10;
        t += a.digits[i] ;
    }
    for (; i >= 0; i--)
    {
        t = t * 10 + a.digits[i];
        for (cc = 9; cc * b > t;cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a.digits.resize(cat.size());

    for (i = 0; i < lgcat;i++)
        a.digits[i] = static_cast<char>(cat[lgcat - i - 1]);

    a.digits.resize(lgcat);

    return a;
}
BigInteger operator / (const BigInteger &a, const BigInteger &b)
{
    BigInteger temp;

    temp = a;
    temp /= b;

    return temp;
}

BigInteger &operator %= (BigInteger &a, const BigInteger &b)
{
    if(Null(b))
        throw std::invalid_argument("Arithmetic Error: Division By 0");
    if(a < b)
    {
        a = BigInteger();
        return a;
    }
    if(a == b)
    {
        a = BigInteger(1);
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a);

    std::vector<int> cat(n, 0);

    BigInteger t;
    const BigInteger TEN(10);

    for (i = n - 1; t * TEN + a.digits[i] < b;i--)
    {
        t *= TEN;
        t += a.digits[i];
    }
    for (; i >= 0; i--)
    {
        t = t * TEN + a.digits[i];
        for (cc = 9; cc * b > t;cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a = std::move(t);
    return a;
}
BigInteger operator % (const BigInteger &a, const BigInteger &b)
{
    BigInteger temp(a);
    temp %= b;
    return temp;
}

BigInteger &operator ^= (BigInteger &a, const BigInteger &b)
{
    BigInteger Exponent(b), Base(a);
    a = 1;

    while(!Null(Exponent))
    {
        if(Exponent[0] & 1)
            a *= Base;
        Base *= Base;
        divide_by_2(Exponent);
    }
    return a;
}

BigInteger operator ^ (const BigInteger &a, const BigInteger &b)
{
    BigInteger temp(a);
    temp ^= b;
    return temp;
}

void divide_by_2(BigInteger & a)
{
    int add = 0;
    int digit;

    for (int i = static_cast<int>(a.digits.size()) - 1; i >= 0; i--)
    {
        digit = (a.digits[i] >> 1) + add;
        add = ((a.digits[i] & 1) * 5);
        a.digits[i] = static_cast<char>(digit);
    }
    while(a.digits.size() > 1 && !a.digits.back()) {
        a.digits.pop_back();
    }
}

BigInteger sqrt(BigInteger & a)
{
    BigInteger left(1), right(a), v(1), mid, prod;

    divide_by_2(right);

    while(left <= right)
    {
        mid += left;
        mid += right;

        divide_by_2(mid);

        prod = (mid * mid);

        if(prod <= a)
        {
            v = mid;
            ++mid;
            left = std::move(mid);
        }
        else{
            --mid;
            right = std::move(mid);
        }
        mid = BigInteger();
    }
    return v;
}

BigInteger BigInteger::catalan(int n)
{
    BigInteger a(1), b;

    for (int i = 2; i <= n;i++)
        a *= i;

    b = a;

    for (int i = n + 1; i <= 2 * n;i++)
        b *= i;

    a *= a;
    a *= (n + 1);
    b /= a;

    return b;
}

BigInteger BigInteger::fibonacci(int n)
{
    BigInteger a(1), b(1), c;

    if(!n) return c;

    n--;

    while(n--)
    {
        c = a + b;
        b = std::move(a);
        a = std::move(c);
    }
    return b;
}

BigInteger BigInteger::factorial(int n)
{
    BigInteger f(1);

    for (int i = 2; i <= n;i++) {
        f *= i;
    }
    return f;
}


std::istream &operator >> (std::istream &is, BigInteger &a)
{
    std::string s;

    is >> s;

    int n = static_cast<int>(s.size());

    for (int i = n - 1; i >= 0; i--)
    {
        if(!isdigit(s[i]))
        {
            std::string err_message;

            err_message = "Input Error: Could not parse \"";
            err_message += s;
            err_message += "\" to integer value.";

            throw std::invalid_argument(err_message);
        }
        a.digits[n - i - 1] = s[i];
    }
    return is;
}

std::ostream &operator << (std::ostream &os, const BigInteger &a)
{
    for (int i = static_cast<int>(a.digits.size()) - 1; i >= 0; i--) {
        os << static_cast<short>(a.digits[i]);
    }
    return os;
}

#endif //BIGINTEGER_BIGINTEGER_H
