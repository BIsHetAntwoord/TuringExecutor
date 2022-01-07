#include "parser.hpp"

TuringParser::TuringParser(std::istream& input) : input(input) {}

TuringTransition TuringParser::parseTransition() {
    TuringTransition result;
    result.output = this->read<uint64_t>();
    result.dir = (TuringDirection)this->read<uint8_t>();
    result.next_state = this->read<uint64_t>();
    return result;
}

void TuringParser::parseState(TuringMachine& machine) {
    uint64_t state_id = this->read<uint64_t>();
    uint64_t extra_states = this->read<uint64_t>();

    TuringState state;
    state.def_transition = this->parseTransition();

    for(uint64_t i = 0; i < extra_states; ++i) {
        uint64_t input = this->read<uint64_t>();
        state.transitions[input] = this->parseTransition();
    }

    machine.states[state_id] = state;
}

TuringMachine TuringParser::parse() {
    TuringMachine machine;

    machine.start = this->read<uint64_t>();
    machine.accept = this->read<uint64_t>();
    machine.reject = this->read<uint64_t>();

    uint64_t num_states = this->read<uint64_t>();
    for(uint64_t i = 0; i < num_states; ++i) {
        this->parseState(machine);
    }

    return machine;
}