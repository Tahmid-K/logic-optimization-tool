#include "covers.hpp"
#include <ostream>

namespace sis {

    void covers::add_input_names(const std::string& a_name) {
        input_names_.push_back(a_name);
    }

    void covers::add_output_names(const std::string& a_name) {
        output_names_.push_back(a_name);
    }

    void covers::add_on_set(const std::string& an_implicant, const unsigned int an_index) {
        if(on_set_.size() > an_index) {
            on_set_[an_index].push_back(an_implicant); 
        }
    }

    void covers::add_dc_set(const std::string& an_implicant, const unsigned int an_index) {
        if(dc_set_.size() > an_index) {
            dc_set_[an_index].push_back(an_implicant); 
        }
    }


    void covers::show_inputs(std::ostream& a_stream) {
        for (const auto& an_input : input_names_) {
            a_stream << " " << an_input;
        }
        a_stream << ";" << std::endl;
    }

    void covers::show_outputs(std::ostream& a_stream) {
        for (const auto& an_output : output_names_) {
            a_stream << " " << an_output;
        }
        a_stream << ";" << std::endl;
    }
}
