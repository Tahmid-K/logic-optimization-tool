#include <iostream>
#include <string>
#include <sstream>
#include "command.hpp"
#include "command_handler.hpp"
#include "helpers.hpp"

int main() {
    auto run = true;
    std::cout << "UC San Diego, SIS Clone 1.0 (compiled June 11 2020 17:14:33)" << std::endl;
    auto* the_cmd_handler = new sis::command_handler();
    do {
        std::string the_user_input;       
        std::cout << "sis> ";
        if (std::getline(std::cin, the_user_input)) {
            if(sis::helpers::str_to_lower(the_user_input) == "quit") {
                run = false;
            }
            else if (!the_user_input.empty()) {
                auto* the_command = the_cmd_handler->handle(the_user_input);
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
    delete the_cmd_handler;
    return 0;
}
