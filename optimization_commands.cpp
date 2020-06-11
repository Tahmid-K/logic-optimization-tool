#include "optimization_commands.hpp"
namespace sis {

    optimization_command::optimization_command(const command_type a_command_type) : command(a_command_type) {
    }

    expresso_command::expresso_command(const command_type a_command_type) : optimization_command(a_command_type){
    }

    void expresso_command::execute() {
    }

    void expresso_command::display(std::ostream& a_stream) {
    }
}
