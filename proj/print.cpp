#include "print.hpp"


namespace sis {
    help_command::help_command() : command(command_type::help) {
    }

    void help_command::execute() {
    }

    void help_command::display(std::ostream& a_stream) {
        const static std::string help_statements[] = {
            "help", "read_pla", "expresso", "print_stats",
            "quit", "write_eqn", "time"
        };
        for (const auto& a_string : help_statements) {
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
        for (unsigned int i = 0; i < the_covers_->get_output_names().size(); i++) {
            display_function(a_stream, i);
            a_stream << std::endl;
        }
    }

    void write_eqn_command::display_function(std::ostream& a_stream, const unsigned int index) const {
        a_stream << the_covers_->get_output_names()[index] << " = ";
        auto& the_on_set = the_covers_->get_on_sets()[index];
        if (!the_on_set.empty()) {
            for (auto i = the_on_set.size() - 1; i > 0 ; i--) {
                display_implicant(a_stream, the_on_set[i]);
                a_stream << " + ";
            }
            display_implicant(a_stream, the_on_set[0]);
            a_stream << ";";
            return;
        }
        a_stream << "0";
    }

    void write_eqn_command::display_implicant(std::ostream& a_stream, const std::string& an_implicant) const {
        // for each literal in the implicant
        auto first_literal = true;
        for (unsigned int i = 0; i < an_implicant.size(); i++) {
            // list if the literal is not a don't care
            if (an_implicant[i] != '-') {
                // if not the first literal prepend with multiplication sign
                if (!first_literal) {
                    a_stream << "*";
                }
                first_literal = false;
                // prepend with ! if 0
                if (an_implicant[i] == '0') {
                    a_stream << "!";
                }
                a_stream << the_covers_->get_input_names()[i];               
            }

        }
    }

    print_stats_command::print_stats_command(covers* the_covers) : the_covers_(the_covers) {
    }

    void print_stats_command::execute() {
    }

    void print_stats_command::display(std::ostream& a_stream) {
        // TODO save file name when parsing so that it can be output as well
        a_stream << "file_name_placeholder  ";
        a_stream << "pi= "  << the_covers_->get_input_names().size() << "  ";
        a_stream << "po= "  << the_covers_->get_output_names().size() << "  ";
        a_stream << "node= NULL  ";
        a_stream << "latch= NULL  ";
        a_stream << "lits(sop)= " << count_literals() << "  ";
        a_stream << "lits(ff)= NULL  ";
        a_stream << "product_terms= " << count_product_terms();
        a_stream << std::endl;
    }

    uint32_t print_stats_command::count_literals() const {
        auto num_literals = 0;
        auto& the_on_sets = the_covers_->get_on_sets();
        // for the on set of every function
        for(auto& an_on_set : the_on_sets) {
            // for every implicant in the on set
            for(auto& an_implicant : an_on_set) {
                // for every literal in the implicant
                for(auto a_literal : an_implicant) {
                    if(a_literal != '-') {
                        num_literals++;
                    }
                }
            }
        }
        return num_literals;
    }

    uint32_t print_stats_command::count_product_terms() const {
        auto num_product_terms = 0;
        auto& the_on_sets = the_covers_->get_on_sets();
        // for the on set of every function
        for(auto& an_on_set : the_on_sets) {
            // for every implicant in the on set
            for(auto& an_implicant : an_on_set) {
                num_product_terms++;
            }
        }
        return num_product_terms;
    }
}
