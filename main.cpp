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
    explicit timer(std::ostream& arg) : os(arg) {
        t0 = std::chrono::high_resolution_clock::now();
    }

    ~timer() {
        t1 = std::chrono::high_resolution_clock::now();
        os << "\nFunction time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "ms\n";
    }
};

int main()
{
    timer t(std::cout);


    return 0;
}
