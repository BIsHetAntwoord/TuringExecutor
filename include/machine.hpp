#ifndef _TURINGEXECUTOR_MACHINE_HPP
#define _TURINGEXECUTOR_MACHINE_HPP

#include <cstdint>
#include <unordered_map>
#include <vector>

enum class TuringDirection : uint8_t {
    STAY,
    LEFT,
    RIGHT
};

struct TuringTransition {
    uint64_t output;
    TuringDirection dir;
    uint64_t next_state;
};

struct TuringState {
    std::unordered_map<uint64_t, TuringTransition> transitions;
    TuringTransition def_transition;
};

struct TuringMachine {
    uint64_t start;
    uint64_t accept;
    uint64_t reject;

    std::unordered_map<uint64_t, TuringState> states;
};

#endif
