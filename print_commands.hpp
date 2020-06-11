#pragma once
#include "command.hpp"
#include <string>
#include <ostream>
namespace sis {
class print_command :
    public command
{
};

class help_command :
    public command {
public:
    explicit help_command(const command_type a_type);

    void execute() override;
    void display(std::ostream& a_stream) override;
};
}