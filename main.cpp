#include <iostream>
#include <chrono>

#include "BigInteger.h"


class timer
{
private:
    std::ostream& os;

    std::chrono::time_point<std::chrono::_V2::system_clock> t0;
    std::chrono::time_point<std::chrono::_V2::system_clock> t1;

public:
    explicit timer(std::ostream& arg)
    :   os(arg),
        t0(std::chrono::high_resolution_clock::now())
    {}

    ~timer()
    {
        t1 = std::chrono::high_resolution_clock::now();
        os  << "\nFunction elapsed time: "
            << static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()) / 1000.0
            << "sec\n";
    }
};

int main()
{
    int n;


    std::cout << "Give number: ";
    std::cin >> n;

    timer t(std::cout);

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

    uint64_t a;

    try
    {
        a = static_cast<uint64_t>(fib_n);
    }
    catch (std::exception &e)
    {
        std::cout << ">>> " << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
