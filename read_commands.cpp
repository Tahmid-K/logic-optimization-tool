

#include "command.hpp"
#include "read_commands.hpp"

#include <utility>

#include "pla_parser.hpp"

namespace sis {

    read_command::read_command(command_type a_command_type, std::string a_file_name)
        : command(a_command_type), file_name_(std::move(a_file_name)) {
    }

    read_pla_command::read_pla_command(std::string a_file_name)
        : read_command(command_type::read_pla,std::move(a_file_name)) {
    }

    void read_pla_command::execute() {
        auto a_pla_parser = pla_parser(file_name_);
        if(!a_pla_parser.parse()) {
            throw std::runtime_error("could not open file");
        }
    }

    void read_pla_command::display(std::ostream& a_stream) {
    }
}
