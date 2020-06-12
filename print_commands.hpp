#pragma once
#include "command.hpp"
#include <string>
#include <ostream>

namespace sis {
    class covers;

    class print_command :
        public command {
    };

    class help_command :
        public command {
    public:
        explicit help_command();

        void execute() override;
        void display(std::ostream& a_stream) override;
    };

    class write_eqn_command :
        public command {
    public:
        explicit write_eqn_command(covers* the_covers);
        void execute() override;
        void display(std::ostream& a_stream) override;
    protected:
        covers* the_covers_;
    };
}
