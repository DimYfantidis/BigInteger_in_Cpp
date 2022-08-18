#include "BigInteger.h"


/* * * * * * * * * * * Constructors * * * * * * * * * * */

BigInteger::BigInteger(int64_t nr)
{
    if (nr < 0)
    {
        sign = NEGATIVE;
        nr = -nr;
    }
    else
        sign = POSITIVE;

    do
    {
        digits.push_back(static_cast<char>(nr % 10));
        nr /= 10;
    }
    while (nr);
}

BigInteger::BigInteger(std::string &s)
{
    digits = "";

    int n = static_cast<int>(s.size());
    int end = 0;

    if (s[0] == '-')
    {
        sign = NEGATIVE;
        ++end;
    }

    if (s[0] == '+') ++end;

    for (int i = n - 1; i >= end; i--)
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

BigInteger::BigInteger(const char *s)
{
    digits = "";

    int n = static_cast<int>(strlen(s));
    int end = 0;

    if (s[0] == '-')
    {
        sign = NEGATIVE;
        ++end;
    }
    if (s[0] == '+') ++end;

    for (int i = n - 1; i >= end; i--)
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

/* * * * * * * * * * * Auxiliary Functions * * * * * * * * * * */

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

bool Null(const BigInteger& a)
{
    if(a.digits.size() == 1 && a.digits[0] == 0)
        return true;

    return false;
}

int Length(const BigInteger &a) {
    return static_cast<int>(a.digits.size());
}

void swap(BigInteger &a, BigInteger &b)
{
    BigInteger c = std::move(a);

    a = std::move(b);
    b = std::move(c);

    std::swap(a.sign, b.sign);
}

bool abs_less(const BigInteger &a, const BigInteger &b)
{
    int n = Length(a);
    int m = Length(b);

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

bool abs_more(const BigInteger &a, const BigInteger &b)
{
    const BigInteger &c = b;
    const BigInteger &d = a;
    return abs_less(c, d);
}

bool abs_equals(const BigInteger &a, const BigInteger &b) {
    return a.digits == b.digits;
}

// -------- Quick Modulus --------

BigInteger BigInteger::mod_2() const
{
    if (digits[0] % 2) {
        return BigConstants::ZERO;
    }
    return BigConstants::ONE;
}

BigInteger BigInteger::mod_5() const
{
    if (digits[0] >= 5) {
        return { digits[0] - 5 };
    }
    return { digits[0] };
}

BigInteger BigInteger::mod_10() const {
    return { digits[0] };
}

// -------- Decimal String representation --------
std::string BigInteger::toString() const
{
    std::string str = (sign == NEGATIVE ? "-" : "");

    for (int i = 0; i < digits.size(); ++i) {
        str += static_cast<char>(digits[digits.size() - i - 1] + '0');
    }
    return str;
}

// -------- Hexadecimal String Representation --------
std::string BigInteger::hex() const
{
    std::string hex_repr;

    BigInteger quotient(*this);

    static const char HEX_DIGITS[] = {
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };

    while (!Null(quotient))
    {
        hex_repr += HEX_DIGITS[static_cast<int64_t>(quotient % 16)];
        quotient /= 16;
    }
    if (sign == NEGATIVE) hex_repr += '-';

    std::reverse(hex_repr.begin(), hex_repr.end());

    return hex_repr;
}


/* * * * * * * * * * * Operator Overloading * * * * * * * * * * */

// -------- Direct assignment --------
BigInteger &BigInteger::operator = (const BigInteger &other)
{
    if (this != &other)
    {
        this->sign = other.sign;
        this->digits = other.digits;
    }
    return *this;
}

BigInteger &BigInteger::operator = (BigInteger &&other) noexcept
{
    if (this != &other)
    {
        this->sign = other.sign;
        this->digits = std::move(other.digits);
    }
    return *this;
}

// -------- Post/Pre - Incrementation --------
BigInteger &BigInteger::operator ++ () &
{
    int i;
    int n = static_cast<int>(digits.size());

    if (sign == POSITIVE)
    {
        for (i = 0; i < n && digits[i] == 9; i++) {
            digits[i] = 0;
        }
        if(i == n) {
            digits.push_back(1);
        }
        else {
            digits[i]++;
        }
    }
    else
    {
        for (i = 0; digits[i] == 0 && i < n; i++) {
            digits[i] = 9;
        }
        digits[i]--;

        if(n > 1 && digits[n - 1] == 0) {
            digits.pop_back();
        }

        if (Null(*this))
            sign = POSITIVE;
    }
    return *this;
}

BigInteger &BigInteger::operator -- () &
{
    int i;
    int n = static_cast<int>(digits.size());

    if (sign == NEGATIVE)
    {
        for (i = 0; i < n && digits[i] == 9; i++) {
            digits[i] = 0;
        }
        if(i == n) {
            digits.push_back(1);
        }
        else {
            digits[i]++;
        }

        if (Null(*this))
            sign = POSITIVE;
    }
    else
    {
        for (i = 0; digits[i] == 0 && i < n; i++) {
            digits[i] = 9;
        }
        digits[i]--;

        if(n > 1 && digits[n - 1] == 0) {
            digits.pop_back();
        }
    }
    return *this;
}

BigInteger BigInteger::operator ++ (int) &
{
    BigInteger aux(*this);

    ++(*this);

    return aux;
}

BigInteger BigInteger::operator -- (int) &
{
    BigInteger aux = *this;

    --(*this);

    return aux;
}

// -------- Cast to uint64_t --------
BigInteger::operator int64_t() const
{
    static const BigInteger LIMIT = INT64_MAX;

    if (abs_more(*this, LIMIT))
    {
        std::string err_message;

        err_message = "BigInteger: ";

        if (digits.size() < 25)
        {
            err_message += toString();
        }
        else
        {
            std::string buffer = digits.substr(digits.size() - 25, 25);
            std::reverse(buffer.begin(), buffer.end());

            for (char& c : buffer) {
                c += '0';
            }
            err_message += buffer;
            err_message += "...";
        }
        err_message += " out of int64_t data type bounds.";

        throw std::invalid_argument(err_message);
    }
    char data[30];

    uint64_t i = digits.size();
    int64_t res;

    data[i] = '\0';

    for (i = 0; i < digits.size(); ++i) {
        data[i] = static_cast<char>(digits[digits.size() - i - 1] + '0');
    }
    data[i] = '\0';

    res = strtoll(data, nullptr, 10);

    return res;
}

// -------- Subscript operator --------
int BigInteger::operator [] (const int index) const {
    return digits[index];
}

// -------- Addition and Subtraction --------
BigInteger &operator += (BigInteger &a, const BigInteger& b)
{
    int s;
    int i;
    int t = 0;

    int n = Length(a);
    int m = Length(b);

    if (a.sign == b.sign)
    {
        if (m > n) {
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
    }
    else
    {
        BigInteger c;

        const BigInteger *d;

        if (abs_less(a, b))
        {
            c = b;
            swap(a, c);
            std::swap(a.sign, c.sign);
            std::swap(m, n);
            d = &c;
        }
        else
            d = &b;

        for (i = 0; i < n; i++)
        {
            if(i < m)
                s = a.digits[i] - d->digits[i]+ t;
            else
                s = a.digits[i] + t;
            if(s < 0)
                s += 10, t = -1;
            else
                t = 0;

            a.digits[i] = static_cast<char>(s);
        }
        while(n > 1 && a.digits[n - 1] == 0)
            a.digits.pop_back(), n--;
    }
    return a;
}

BigInteger &operator -= (BigInteger&a, const BigInteger &b)
{
    int n = Length(a);
    int m = Length(b);

    int i;
    int s;
    int t = 0;

    if (a.sign != b.sign)
    {
        if (m > n) {
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
    }
    else
    {
        BigInteger c;

        const BigInteger *d;

        if (n < m || abs_less(a, b))
        {
            c = b;
            swap(a, c);
            std::swap(m, n);
            d = &c;
        }
        else
            d = &b;

        for (i = 0; i < n; i++)
        {
            if (i < m)
                s = a.digits[i] - d->digits[i]+ t;
            else
                s = a.digits[i] + t;
            if (s < 0)
                s += 10, t = -1;
            else
                t = 0;

            a.digits[i] = static_cast<char>(s);
        }
        while(n > 1 && a.digits[n - 1] == 0)
            a.digits.pop_back(), n--;
    }

    return a;
}

BigInteger operator + (const BigInteger &a, const BigInteger &b)
{
    BigInteger temp(a);
    temp += b;
    return temp;
}

BigInteger operator - (const BigInteger& a, const BigInteger& b)
{
    BigInteger temp(a);
    temp -= b;
    return temp;
}

// -------- Comparison operators --------
bool operator == (const BigInteger &a, const BigInteger &b) {
    if (a.sign != b.sign) {
        return false;
    }
    return a.digits == b.digits;
}

bool operator != (const BigInteger & a, const BigInteger &b){
    return !(a == b);
}

bool operator > (const BigInteger&a, const BigInteger&b) {
    return b < a;
}

bool operator < (const BigInteger&a, const BigInteger&b)
{
    int n = Length(a);
    int m = Length(b);

    if (a.sign != b.sign) {
        return a.sign == NEGATIVE;
    }

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

bool operator >= (const BigInteger&a, const BigInteger&b) {
    return !(a < b);
}

bool operator <= (const BigInteger&a, const BigInteger&b) {
    return !(a > b);
}

// -------- Multiplication and Division --------
BigInteger &operator *= (BigInteger &a, const BigInteger &b)
{
    if(Null(a) || Null(b))
    {
        a = BigConstants::ZERO;
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

    a.sign = (a.sign != b.sign ? NEGATIVE : POSITIVE);

    return a;
}

BigInteger &operator /= (BigInteger& a, const BigInteger &b)
{
    if(Null(b)) {
        throw std::invalid_argument("Arithmetic Error: Division By 0");
    }
    if(a < b)
    {
        a = BigConstants::ZERO;
        return a;
    }
    if(a == b)
    {
        a = BigConstants::ONE;
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

    a.sign = (a.sign != b.sign ? NEGATIVE : POSITIVE);

    return a;
}

BigInteger operator * (const BigInteger &a, const BigInteger &b)
{
    BigInteger temp(a);
    temp *= b;
    return temp;
}

BigInteger operator / (const BigInteger &a, const BigInteger &b)
{
    BigInteger temp(a);
    temp /= b;
    return temp;
}

// -------- Modulo --------
BigInteger &operator %= (BigInteger &a, const BigInteger &b)
{
    if(Null(b)) {
        throw std::invalid_argument("Arithmetic Error: Division By 0");
    }
    if(a < b) {
        return a;
    }
    if(a == b)
    {
        a = BigConstants::ZERO;
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a);

    std::vector<int> cat(n, 0);

    BigInteger t;

    for (i = n - 1; t * BigConstants::TEN + a.digits[i] < b;i--)
    {
        t *= BigConstants::TEN;
        t += a.digits[i];
    }
    for (; i >= 0; i--)
    {
        t = t * BigConstants::TEN + a.digits[i];
        for (cc = 9; cc * b > t; cc--);
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

// -------- Power Function --------
BigInteger &operator ^= (BigInteger &a, const BigInteger &b)
{
    if (b.sign == NEGATIVE) {
        throw std::invalid_argument("Positive Exponents only");
    }
    BigInteger Exponent(b);
    BigInteger Base(a);

    a = BigConstants::ONE;

    while(!Null(Exponent))
    {
        if(Exponent[0] & 1) {
            a *= Base;
        }
        Base *= Base;
        divide_by_2(Exponent);
    }

    if (a.sign == NEGATIVE)
    {
        if (b.mod_2() == BigConstants::ZERO) {
           a.sign = POSITIVE;
        }
    }
    return a;
}

BigInteger operator ^ (const BigInteger &a, const BigInteger &b)
{
    BigInteger temp(a);
    temp ^= b;
    return temp;
}

// -------- Read and Write --------
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
    if (a.sign == NEGATIVE) {
        os << '-';
    }
    for (int i = static_cast<int>(a.digits.size()) - 1; i >= 0; i--) {
        os << static_cast<short>(a.digits[i]);
    }
    return os;
}

// -------- Square Root Function --------
BigInteger BigInteger::sqrt(const BigInteger &n)
{
    if (n.sign == NEGATIVE) {
        throw std::invalid_argument("Arithmetic Error: sqrt(x) not difined for negative x.");
    }
    BigInteger left(1), right(n), v(1), mid, prod;

    divide_by_2(right);

    while(left <= right)
    {
        mid += left;
        mid += right;

        divide_by_2(mid);

        prod = (mid * mid);

        if(prod <= n)
        {
            v = mid;
            ++mid;
            left = std::move(mid);
        }
        else{
            --mid;
            right = std::move(mid);
        }
        mid = BigConstants::ZERO;
    }
    return v;
}

BigInteger BigInteger::log2(const BigInteger &n) {
    if (n.sign == NEGATIVE) {
        throw std::invalid_argument("Arithmetic Error: log2(x) not difined for negative x.");
    }
    return { static_cast<int64_t>(LOG2_10 * (double)(n.digits.size() - 1)) };
}

BigInteger BigInteger::log10(const BigInteger &n) {
    if (n.sign == NEGATIVE) {
        throw std::invalid_argument("Arithmetic Error: log10(x) not difined for negative x.");
    }
    return { static_cast<int64_t>(n.digits.size() - 1) };
}

BigInteger BigInteger::abs(const BigInteger &n)
{
    BigInteger abs_n(n);

    abs_n.sign = POSITIVE;

    return abs_n;
}

BigInteger BigInteger::catalan(int n)
{
    BigInteger a(1), b;
    BigInteger N(n);

    for (BigInteger i = 2; i <= N; ++i)
        a *= i;

    b = a;

    BigInteger _2n = BigConstants::TWO * n;

    for (BigInteger i = n + 1; i <= _2n; ++i)
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
    BigInteger N(n);

    for (BigInteger i = BigConstants::TWO; i <= N; ++i) {
        f *= i;
    }
    return f;
}

#undef LOG2_10
#undef POSITIVE
#undef NEGATIVE
