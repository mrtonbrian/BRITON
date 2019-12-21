//
// Created by brianton on 12/20/19.
//

#include "misc.h"
#include <random>

uint64_t random64BitInteger() {
    std::random_device seed;
    std::default_random_engine generator(seed());
    std::uniform_int_distribution<uint64_t> distribution(0, 0xFFFFFFFFFFFFFFFF);

    return distribution(generator);
}
