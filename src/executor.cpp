#include "executor.hpp"
#include "machine.hpp"
#include "tape.hpp"

#include <stdexcept>
#include <limits>
#include <sstream>

const uint64_t TRANS_WILDCARD = std::numeric_limits<uint64_t>::max();

TuringExecutor::TuringExecutor(TuringTape& tape, bool debug, std::ostream& output) : tape(tape), debug(debug), output(output) {}

void TuringExecutor::printTape() {
    if(this->debug) {
        this->tape.print(this->output);
        output << std::endl << std::endl;
    }
}

bool TuringExecutor::execute(const TuringMachine& machine) {
    size_t current_state = machine.start;

    size_t steps = 0;

    if(this->debug)
        this->output << "Initial state " << current_state << std::endl;

    while(!(current_state == machine.accept || current_state == machine.reject)) {
        ++steps;
        this->printTape();
        uint16_t lookahead = this->tape.read();

        if(machine.states.count(current_state) == 0) {
            std::stringstream ss;
            ss << "Machine reached unknown state " << current_state;
            throw std::runtime_error(ss.str());
        }
        const TuringState& state = machine.states.at(current_state);

        TuringTransition transition = state.def_transition;
        if(state.transitions.count(lookahead) > 0)
            transition = state.transitions.at(lookahead);

        if(transition.output == TRANS_WILDCARD)
            transition.output = lookahead;

        if(this->debug)
            this->output << "Taking transition to state " << transition.next_state << " with output " << transition.output << " at step " << steps << std::endl;


        this->tape.write(transition.output);
        this->tape.move(transition.dir);
        current_state = transition.next_state;
    }

    this->printTape();

    return current_state == machine.accept;
}