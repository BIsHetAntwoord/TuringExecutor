#ifndef _TURINGEXECUTOR_EXECUTOR_HPP
#define _TURINGEXECUTOR_EXECUTOR_HPP

class TuringTape;
class TuringMachine;

#include <iosfwd>

class TuringExecutor {
    private:
        TuringTape& tape;
        bool debug;
        std::ostream& output;

        void printTape();
    public:
        TuringExecutor(TuringTape&, bool, std::ostream&);

        bool execute(const TuringMachine&);
};

#endif
