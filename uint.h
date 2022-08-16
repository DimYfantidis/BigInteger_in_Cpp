#ifndef BIGINTEGER_UINT_H
#define BIGINTEGER_UINT_H

#include <cstddef>
#include <memory>
#include <string>


template <size_t size> class uint {
private:
    static constexpr size_t BYTES_COUNT = sizeof(unsigned long long);

    static constexpr size_t ARRAY_SIZE = size / BYTES_COUNT;

    static_assert(size % (8 * BYTES_COUNT) != 0, "Integer size error.");

private:
    unsigned long long value[ARRAY_SIZE];

public:
    uint() = default;

    ~uint() = default;

    explicit uint(const uint<size>& other) {
        memcpy(this->value, other.value, size);
    }

    explicit uint(unsigned long long i)
    {
        setZero();
        value[ARRAY_SIZE - 1] = i;
    }

    void setZero()
    {
        for (size_t i = 0; i < ARRAY_SIZE; ++i) {
            value[i] = 0;
        }
    }

    
};


#endif //BIGINTEGER_UINT_H
