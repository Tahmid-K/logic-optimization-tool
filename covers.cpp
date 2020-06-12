#include "covers.hpp"

void sis::covers::add_function(function a_function) {
    the_functions_.push_back(a_function);
}

void sis::covers::add_input_names(const std::string& a_name) {
    input_names_.push_back(a_name);
}
