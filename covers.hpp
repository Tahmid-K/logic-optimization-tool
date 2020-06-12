#pragma once
#include <string>
#include <vector>

namespace sis {
    // pair of output and implicants
    using implicants = std::vector<std::string>;
    using function = std::pair<std::string, implicants>;
    class covers {
    public:
        covers() = default;
        ~covers() = default;
        covers(covers& a_copy) = default;
        covers& operator=(const covers& a_cover) = default;
        void add_function(const function& a_function);
        void add_input_names(const std::string& a_name);
        void add_implicant(const std::string& an_implicant, unsigned int an_index);
        [[nodiscard]] std::vector<function>& get_functions() {return the_functions_;}
        [[nodiscard]] std::vector<std::string>& get_input_names() {return the_input_names_;}
        void show_inputs(std::ostream& a_stream);
        void show_outputs(std::ostream& a_stream);

    protected:
        std::vector<function> the_functions_;
        std::vector<std::string> the_input_names_;
    };
}
