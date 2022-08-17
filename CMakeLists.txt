cmake_minimum_required(VERSION 3.23)
project(BigInteger)

set(CMAKE_CXX_STANDARD 20)

add_executable(BigInteger main.cpp BigInteger.h BigInteger.cpp BigDecimal.cpp BigDecimal.h Timer.h)
