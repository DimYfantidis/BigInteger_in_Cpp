#include <iostream>

#include "Timer.h"
#include "BigInteger.h"


int main()
{
    Timer t(std::cout, "main");

    int n;

    BigInteger fib_n;
    BigInteger fact_n;
    BigInteger cat_n;

    BigInteger u1;
    BigInteger u2;


    t.pause();

    std::cout << "Give number: ";
    std::cin >> n;
    std::cout << '\n';

    t.unpause();

    {
        Timer fibonacci_timer(std::cout, "main::local_scope_fibonacci");
        fib_n = BigInteger::fibonacci(n);
    }

    {
        Timer factorial_timer(std::cout, "main::local_scope_factorial");
        fact_n = BigInteger::factorial(n);
    }

    {
        Timer catalan_timer(std::cout, "main::local_scope_catalan");
        cat_n  = BigInteger::catalan(n);
    }

    {
        Timer exponent_timer(std::cout, "main::local_scope_exponentiation");
        u1 = fib_n ^ 17;
    }

    {
        Timer modulo_timer(std::cout, "main::local_scope_modulo");
        u2 = fact_n % cat_n;
    }

    std::cout << "\nVAL: fibonacci(" << n << ") = " << fib_n << '\n'
              << "\nVAL: " << n << "! = " << fact_n << '\n'
              << "\nVAL: catalan(" << n << ") = " << cat_n << '\n';

    std::cout << "\nEXPR: fibonacci(" << n << ")^17 = " << u1 << '\n'
              << "\nEXPR: " << n << "! % catalan(" << n << ") = " << u2 << '\n'
              << std::endl;

    return EXIT_SUCCESS;
}
