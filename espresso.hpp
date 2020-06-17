#pragma once
#include <string>

#include "command.hpp"
#include "covers.hpp"
namespace sis {
   
    class espresso_command :
        public command {
    public:
        explicit espresso_command(covers* a_cover);
        void execute() override;
        void display(std::ostream& a_stream) override;
    protected:
        covers* the_covers_;
        std::vector<std::string> add_list_;
        void optimize_function(implicants& the_on_set);
        // Expresso methods
        // EXPAND, REDUCE, REMOVE_COVERED_IMPLICANTS, VALIDITY_CHECK
        bool expand(std::string& an_implicant, implicants& the_on_set, implicants& the_dc_set);
        bool reduce(const std::string& an_implicant, implicants& a_function);
        bool remove_covered_implicants(const std::string& an_implicant, implicants& the_on_set);
        bool validity_check(const std::string& an_implicant, implicants& the_on_set, implicants& the_dc_set);
        static bool is_covered(const std::string& an_implicant, implicants& the_set);

        
    };
}

