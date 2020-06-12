#include "covers.hpp"
#include <ostream>

namespace sis {
    void covers::add_function(const function& a_function) {
        the_functions_.push_back(a_function);
    }

    void covers::add_input_names(const std::string& a_name) {
        the_input_names_.push_back(a_name);
    }

    void covers::add_implicant(const std::string& an_implicant, const unsigned int an_index) {
        if (the_functions_.size() > an_index) {
            the_functions_[an_index].second.push_back(an_implicant);
        }
    }

    void covers::show_inputs(std::ostream& a_stream) {
        for (const auto& an_input : the_input_names_) {
            a_stream << " " << an_input;
        }
        a_stream << ";" << std::endl;
    }

    void covers::show_outputs(std::ostream& a_stream) {
        for (const auto& a_function : the_functions_) {
            a_stream << " " << a_function.first;
        }
        a_stream << ";" << std::endl;
    }
}
