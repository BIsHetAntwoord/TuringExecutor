#include <iostream>
#include <fstream>
#include <limits>

#include "parser.hpp"
#include "machine.hpp"
#include "executor.hpp"
#include "tape.hpp"

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cerr << "No file given" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1], std::ifstream::binary);
    if(!input) {
        std::cerr << "Failed to open file " << argv[1] << std::endl;
        return 1;
    }

    TuringParser parser(input);
    TuringMachine machine = parser.parse();

    // auto print_trans = [](const TuringTransition& trans) {
    //     if(trans.output == std::numeric_limits<size_t>::max())
    //         std::cout << "*";
    //     else
    //         std::cout << trans.output;
    //     std::cout << " ";
    //     switch(trans.dir) {
    //         case TuringDirection::STAY:
    //             std::cout << "!";
    //             break;
    //         case TuringDirection::LEFT:
    //             std::cout << "<";
    //             break;
    //         case TuringDirection::RIGHT:
    //             std::cout << ">";
    //             break;
    //     }
    //     std::cout << " " << trans.next_state;
    // };

    // std::cout << "Current VM: (start = " << machine.start << ", accept = " <<
    //     machine.accept << ", reject = " << machine.reject << ")" << std::endl;
    // for(const auto& state_it : machine.states) {
    //     std::cout << "State " << state_it.first << ":" << std::endl;
    //     const TuringState& state = state_it.second;

    //     for(const auto& trans_it : state.transitions) {
    //         TuringTransition trans = trans_it.second;
    //         std::cout << "    " << trans_it.first << " -> ";
    //         print_trans(trans);
    //         std::cout << std::endl;
    //     }
    //     std::cout << "    * -> ";
    //     print_trans(state.def_transition);
    //     std::cout << std::endl;
    // }

    TuringTape tape;
    TuringExecutor executor(tape, true, std::cout);

    bool result = executor.execute(machine);
    std::cout << (result ? "Accepted" : "Rejected") << std::endl;

    return 0;
}