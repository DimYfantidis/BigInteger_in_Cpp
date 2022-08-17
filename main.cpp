#include <iostream>
#include <chrono>
#include <cmath>

#include "Timer.h"
#include "BigInteger.h"


int main()
{
    Timer t(std::cout, "main");

    int n;

    t.pause();

    std::cout << "Give number: ";
    std::cin >> n;

    t.unpause();

    BigInteger N;

    BigInteger fib_n  = BigInteger::fibonacci(n);
    BigInteger fact_n = BigInteger::factorial(n);
    BigInteger cat_n  = BigInteger::catalan(n);

    BigInteger u1 = fib_n ^ 3;
    BigInteger u2 = fact_n % cat_n;

    std::cout << "\nVAL: fibonacci(" << n << ") = " << fib_n << '\n'
              << "\nVAL: " << n << "! = " << fact_n << '\n'
              << "\nVAL: catalan(" << n << ") = " << cat_n << '\n';

    std::cout << "\nEXPR: fibonacci(" << n << ")^2 = " << u1 << '\n'
              << "\nEXPR: " << n << "! % catalan(" << n << ") = " << u2 << '\n'
              << std::endl;

    return EXIT_SUCCESS;
}
