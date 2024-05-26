#include <cstdint>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

int dirtyrandom() {
    // Open /dev/urandom and create input stream iterator
    //    std::ifstream urandom("/dev/urandom", std::ios::binary);

    // Read 4 bytes and interpret as uint32_t
    //  int randomValue;

    // urandom.read((char *)&randomValue, 4);

    // Close /dev/urandom
    // urandom.close();

    // std::cout << "random value: " << randomValue << std::endl;
        srand(static_cast<unsigned int>(time(0)));

    // Generate and print a random number
    int random_number = rand();

    return random_number;
}
