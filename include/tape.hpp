#ifndef _TURINGEXECUTOR_TAPE_HPP
#define _TURINGEXECUTOR_TAPE_HPP

#include <vector>
#include <iosfwd>
#include <cstdint>

#include "machine.hpp"

class TuringTape {
    private:
        std::vector<uint16_t> tape;
        size_t head;

        void expandTape(size_t);
    public:
        TuringTape();

        void move(TuringDirection);

        uint16_t read();
        void write(uint16_t);

        void set(size_t, uint16_t);
        void set(size_t, uint16_t*, size_t);
        void setHead(size_t);

        void print(std::ostream&);
};

#endif
