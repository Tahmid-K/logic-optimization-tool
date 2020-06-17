#include "espresso.hpp"


#include "helpers.hpp"

namespace sis {


    espresso_command::espresso_command(covers* a_cover) : command(command_type::expresso), the_covers_(a_cover) {
    }

    void espresso_command::execute() {
        if (the_covers_ != nullptr) {
            // for each function         
            for (unsigned int i = 0; i < the_covers_->get_on_set().size(); i++) {
                auto& the_on_set = the_covers_->get_on_set()[i];
                auto& the_dc_set = the_covers_->get_dc_set()[i];
                // for each implicant in the on set
                for (auto& an_implicant : the_on_set) {
                    // attempt to expand
                    if (expand(an_implicant, the_on_set, the_dc_set)) {
                        // remove covered implicants if successful expansion
                        remove_covered_implicants(an_implicant, the_on_set);
                    }
                }
            }
        }
    }

    void espresso_command::display(std::ostream& a_stream) {
    }


    bool espresso_command::validity_check(const std::string& an_implicant, implicants& the_on_set,
                                          implicants& the_dc_set) {
        for (unsigned int i = 0; i < an_implicant.size(); i++) {
            if (an_implicant[i] == '-') {
                const auto one_implicant = helpers::replace_char(an_implicant, i, "1");
                const auto zero_implicant = helpers::replace_char(an_implicant, i, "0");
                return validity_check(one_implicant, the_on_set, the_dc_set)
                    && validity_check(zero_implicant, the_on_set, the_dc_set);
            }
        }
        return is_covered(an_implicant, the_on_set) || is_covered(an_implicant, the_dc_set);
    }

    bool espresso_command::is_covered(const std::string& an_implicant, implicants& the_set) {
        // for every implicant an in the set
        for (auto set_implicant : the_set) {
            // assume the implicant from set does not cover 
            auto not_covered = true;
            for (unsigned int i = 0; i < set_implicant.size(); i++) {
                // check every character for a discrepancy
                if (set_implicant[i] != '-') {
                    if (an_implicant[i] != set_implicant[i]) {
                        not_covered = false;
                    }
                }
            }
            if (not_covered)
                return true;
        }
        return false;
    }


    bool espresso_command::expand(std::string& an_implicant, implicants& the_on_set, implicants& the_dc_set) {
        auto has_expanded = false;
        for (unsigned int j = 0; j < an_implicant.size(); j++) {
            // if literal is not a dc
            if (an_implicant[j] != '-') {
                // attempt to expand
                auto expanded_implicant = helpers::replace_char(an_implicant, j, "-");
                if (validity_check(expanded_implicant, the_on_set, the_dc_set)) {
                    an_implicant = expanded_implicant;
                    has_expanded = true;
                }
            }
        }
        return has_expanded;
    }

    bool espresso_command::reduce(const std::string& an_implicant, implicants& a_function) {
        return false;
    }

    /**
     * @brief remove covered implicants and add the implicant to the on set
     * @param an_implicant 
     * @param the_on_set 
     * @return true
    */
    bool espresso_command::remove_covered_implicants(const std::string& an_implicant, implicants& the_on_set) {
        std::vector<std::string> removal_list;
        // for each implicant in the on set
        for (auto on_implicant : the_on_set) {
            // assume the on implicant is covered
            auto covered = true;
            // for every literal in the implicant
            for (unsigned int i = 0; i < on_implicant.size(); i++) {
                if (an_implicant[i] != '-') { // what if the literal in the on set is a don't care?
                    // check for a discrepancy
                    if (an_implicant[i] != on_implicant[i]) {
                        covered = false;
                    }
                }
            }
            // ignore discrepancy if the implicants match
            if (an_implicant == on_implicant) { // move this
                covered = false;
            }
            // mark the implicant for removal if it is covered
            // TODO: verify error does occur as a result of deferring removal until all checks are made
            if (covered) {
                removal_list.push_back(on_implicant);
            }
        }
        for (const auto& the_string : removal_list) {
            auto itr = std::find(the_on_set.begin(), the_on_set.end(), the_string);
            if (itr != the_on_set.end())
                the_on_set.erase(itr);
        }
        return true;
    }


}
