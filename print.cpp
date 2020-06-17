
#include "print.hpp"


namespace sis {
    help_command::help_command() : command(command_type::help) {
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

    write_eqn_command::write_eqn_command(covers* the_covers) : the_covers_(the_covers) {
    }

    void write_eqn_command::execute() {
    }

    void write_eqn_command::display(std::ostream& a_stream) {
        a_stream << "INORDER =";
        the_covers_->show_inputs(a_stream);
        a_stream << "OUTORDER = ";
        the_covers_->show_outputs(a_stream);
        //for(auto a_function : the_covers_->function)
    }
}
