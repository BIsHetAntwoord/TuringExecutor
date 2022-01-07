#ifndef _TURINGEXECUTOR_PARSER_HPP
#define _TURINGEXECUTOR_PARSER_HPP

#include <iostream>
#include <stdexcept>

#include "machine.hpp"

class TuringParser {
    private:
        std::istream& input;

        TuringTransition parseTransition();
        void parseState(TuringMachine&);

        template <typename T>
        T read();
    public:
        TuringParser(std::istream&);

        TuringMachine parse();
};

template <typename T>
T TuringParser::read() {
    T result;
    this->input.read((char*)&result, sizeof(T));

    if(!this->input)
        throw std::runtime_error("Failed to read input file");

    return result;
}

#endif
