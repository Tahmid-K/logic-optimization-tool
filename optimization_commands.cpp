#include "optimization_commands.hpp"
namespace sis {

    optimization_command::optimization_command(const command_type a_command_type) : command(a_command_type) {
    }

    espresso_command::espresso_command(covers* a_cover) : optimization_command(command_type::expresso), a_cover_(a_cover) {
    }

    void espresso_command::execute() {
    }

    void espresso_command::display(std::ostream& a_stream) {
    }
}
