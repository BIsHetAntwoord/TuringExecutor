#include "tape.hpp"

#include <bit>
#include <iostream>
#include <iomanip>

const size_t MIN_TAPE_SIZE = 16;

inline size_t nearest_power_2(size_t value) {
    return std::bit_ceil(value);
}

TuringTape::TuringTape() : head(0) {
    this->tape.resize(MIN_TAPE_SIZE);
}

void TuringTape::expandTape(size_t s) {
    if(this->tape.size() < s) {
        size_t new_size = s < MIN_TAPE_SIZE ? MIN_TAPE_SIZE : nearest_power_2(s);
        this->tape.resize(new_size);
    }
}

void TuringTape::move(TuringDirection dir) {
    switch(dir) {
        case TuringDirection::LEFT:
            if(this->head == 0)
                throw std::runtime_error("Program left the left side of the tape");
            --this->head;
            break;
        case TuringDirection::RIGHT:
            ++this->head;
            break;
        default:
            break;
    }
}

uint16_t TuringTape::read() {
    this->expandTape(this->head+1);

    return this->tape[this->head];
}

void TuringTape::write(uint16_t value) {
    this->set(this->head, value);
}

void TuringTape::set(size_t pos, uint16_t value) {
    this->expandTape(pos+1);
    this->tape[pos] = value;
}

void TuringTape::set(size_t pos, uint16_t* values, size_t num_values) {
    for(size_t i = 0; i < num_values; ++i)
        this->set(pos + i, values[i]);
}

void TuringTape::setHead(size_t pos) {
    this->head = pos;
}

void TuringTape::print(std::ostream& output) {
    for(size_t i = 0; i < this->tape.size(); ++i) {
        if(i % 16 == 0 && i > 0)
            output << std::endl;

        if(i == this->head)
            output << "[";
        else
            output << " ";
        output << std::setw(3) << this->tape[i];
        if(i == this->head)
            output << "]";
        else
            output << " ";
    }
}