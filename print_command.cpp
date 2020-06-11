
#include "print_command.hpp"

namespace sis {

    help_command::help_command(const command_type a_type) : command(a_type) {
    }

    void help_command::execute() {
    }

    void help_command::display(std::ostream& a_stream) {
        const static std::string help_statements[] = {
        "help", "read_pla", "expresso", "print_stats",
        "history", "clear","write_eqn", "write_pla","invalid"
        };
        for(const auto& a_string : help_statements) {
            a_stream << a_string << std::endl;
        }
    }
}
