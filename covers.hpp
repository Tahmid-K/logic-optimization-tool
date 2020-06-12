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
        void add_function(function a_function);
        void add_input_names(const std::string& a_name);
        std::vector<function>& get_functions() {return the_functions_;}       
    protected:
        std::vector<function> the_functions_;
        std::vector<std::string> input_names_;
    };
}
