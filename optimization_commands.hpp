#pragma once
#include "command.hpp"

namespace sis {
    class covers;

    class optimization_command :
        public command
    {
    public:
        explicit optimization_command(command_type a_command_type);
    };

    class espresso_command :
        public optimization_command {
    public:
        explicit espresso_command(covers* a_cover);
        void execute() override;
        void display(std::ostream& a_stream) override;
    protected:
        covers* a_cover_;

    };
}

