#include "espresso.hpp"


#include "helpers.hpp"

namespace sis {


    espresso_command::espresso_command(covers* a_cover) : command(command_type::expresso), the_covers_(a_cover) {
    }

    void espresso_command::execute() {
        if(the_covers_ != nullptr) {
            for(auto a_function : the_covers_->get_functions()) {
                optimize_function(a_function);
            }
        }
    }

    

    void espresso_command::optimize_function(function& a_function) {
        for(auto& an_implicant : a_function.second) {
            for(unsigned int i = 0; i < an_implicant.size(); i++) {
                if(an_implicant[i] != '-') {
                    auto expanded_implicant = helpers::replace_char(an_implicant,i,"-");
                    if(expand(expanded_implicant, a_function)) {                        
                        an_implicant = expanded_implicant;
                    }
                }
            }
            remove_covered_implicants(an_implicant, a_function); // ignore if found, else remove covered implicants
        }
    }

    /**
     * @brief recursively checks whether implicant is covered
     * @param an_implicant 
     * @param a_function 
     * @return true if valid expansion
    */
    bool espresso_command::expand(const std::string& an_implicant, function& a_function) {
        // iterate through each element of the implicant
        for(unsigned int i = 0; i < an_implicant.size(); i++) {
            if(an_implicant[i] == '-') {
                const auto one_implicant = helpers::replace_char(an_implicant, i,"1");
                const auto zero_implicant = helpers::replace_char(an_implicant, i,"0");
                return expand(one_implicant,a_function) && expand(zero_implicant, a_function);
            }
        }
        return validity_check(an_implicant, a_function);        
    }

    bool espresso_command::reduce(const std::string& an_implicant, function& a_function) {
        return true;
    }

    /**
     * @brief remove covered implicants and add the implicant to the on set
     * @param an_implicant 
     * @param a_function 
     * @return true
    */
    bool espresso_command::remove_covered_implicants(const std::string& an_implicant, function& a_function) {
        std::vector<std::string> removal_list;
        if(!validity_check(an_implicant,a_function)) {
            for(auto another_implicant : a_function.second) {
                auto covered = true;
                for(unsigned int i = 0; i < another_implicant.size(); i++) {
                    if(an_implicant[i] != '-') {
                        if(an_implicant[i] != another_implicant[i]) {
                            covered = false;
                        }
                    }
                }
                if(covered) {
                    removal_list.push_back(another_implicant);
                }
            }
            for(const auto& the_string : removal_list) {
                auto itr = std::find(a_function.second.begin(), a_function.second.end(), the_string);
                if (itr != a_function.second.end()) 
                    a_function.second.erase(itr);
            }
            a_function.second.insert(a_function.second.begin(), an_implicant);
        }
        return true;
    }

    /**
     * @brief determines whether implicant exists in on or dc set
     * @param an_implicant 
     * @param a_function 
     * @return true if implicant exists, else false
    */
    bool espresso_command::validity_check(const std::string& an_implicant, function& a_function) {
        return is_on_set(an_implicant, a_function) || is_dc_set(an_implicant, a_function);
    }


    bool espresso_command::is_on_set(const std::string& an_implicant, function& a_function) {
        return std::find(a_function.second.begin(), a_function.second.end(), an_implicant) != a_function.second.end(); 
    }

    bool espresso_command::is_dc_set(const std::string& an_implicant, function& a_function) {
        return false;
    }

    void espresso_command::display(std::ostream& a_stream) {
    }

}
