#include "command.hpp"
#include "read_commands.hpp"

#include <utility>

#include "pla_parser.hpp"

namespace sis {

    read_command::read_command(const command_type a_command_type, command_handler& a_command_handler,
                               std::string a_file_name)
        : command(a_command_type), a_command_handler_(a_command_handler), file_name_(std::move(a_file_name)),
          parse_error_(false) {
    }

    read_pla_command::read_pla_command(command_handler& a_command_handler, std::string a_file_name)
        : read_command(command_type::read_pla, a_command_handler, std::move(a_file_name)) {
    }

    void read_pla_command::execute() {
        auto a_pla_parser = pla_parser(file_name_);
        if (!a_pla_parser.parse(a_command_handler_)) {
            parse_error_ = true;
        }
    }

    void read_pla_command::display(std::ostream& a_stream) {
        if (parse_error_)
            a_stream << "error parsing file";
    }
}
