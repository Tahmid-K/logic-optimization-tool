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
        void optimize_function(function& a_function);
        // Expresso methods
        // EXPAND, REDUCE, REMOVE_COVERED_IMPLICANTS, VALIDITY_CHECK
        bool expand(const std::string& an_implicant, function& a_function);
        bool reduce(const std::string& an_implicant, function& a_function);
        bool remove_covered_implicants(const std::string& an_implicant, function& a_function);
        bool validity_check(const std::string& an_implicant, function& a_function);
        bool is_on_set(const std::string& an_implicant, function& a_function);
        bool is_dc_set(const std::string& an_implicant, function& a_function);
        
    };
}

