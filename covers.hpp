#pragma once
#include <string>
#include <vector>

namespace sis {
    // pair of output and implicants
    using implicants = std::vector<std::string>;
    class covers {
    public:
        covers() = default;
        ~covers() = default;
        covers(covers& a_copy) = default;
        covers& operator=(const covers& a_cover) = default;
        void add_input_names(const std::string& a_name);
        void add_output_names(const std::string& a_name);
        void add_on_set(const std::string& an_implicant, const unsigned int an_index);
        void add_dc_set(const std::string& an_implicant, const unsigned int an_index);

        std::vector<std::string>& get_input_names() {return input_names_;}
        std::vector<std::string>& get_output_names() {return output_names_;}
        std::vector<implicants>& get_on_set() {return on_set_;}
        std::vector<implicants>& get_dc_set() {return dc_set_;}

        void show_inputs(std::ostream& a_stream);
        void show_outputs(std::ostream& a_stream);

    protected:     
        std::vector<std::string> input_names_;
        std::vector<std::string> output_names_;
        std::vector<implicants> on_set_;
        std::vector<implicants> dc_set_;
    };
}
