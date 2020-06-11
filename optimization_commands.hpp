#pragma once
#include "command.hpp"

namespace sis {
    class optimization_command :
        public command
    {
    public:
        explicit optimization_command(command_type a_command_type);
    };

    class expresso_command :
        public optimization_command {
    public:
        explicit expresso_command(command_type a_command_type);
        void execute() override;
        void display(std::ostream& a_stream) override;

    };
}

