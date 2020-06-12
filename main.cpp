#include <iostream>
#include <string>
#include <sstream>
#include "command.hpp"
#include "command_handler.hpp"
#include "helpers.hpp"

int main() {
    auto run = true;
    std::cout << "UC San Diego, SIS Clone 1.0 (compiled June 11 2020 17:14:33)" << std::endl;
    do {
        std::string the_user_input;
        std::cout << "sis> ";
        if (std::getline(std::cin, the_user_input)) {
            if(sis::helpers::str_to_lower(the_user_input) == "quit") {
                run = false;
            }
            else if (!the_user_input.empty()) {
                std::stringstream a_string_stream(the_user_input);
                auto the_cmd_handler = sis::command_handler(a_string_stream);
                auto* the_command = the_cmd_handler.handle();
                if(the_command != nullptr) {
                    the_command->execute();
                    the_command->display(std::cout);
                    delete the_command;
                }
                else
                    std::cout << "invalid command" << std::endl;
            }
        }
    }
    while (run);

    return 0;
}
