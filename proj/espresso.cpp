#include "espresso.hpp"


#include "helpers.hpp"

namespace sis {


    espresso_command::espresso_command(covers* a_cover) : command(command_type::expresso), the_covers_(a_cover) {
    }

    /**
     * @brief executes espresso heuristic on every function in the current set of covers
    */
    void espresso_command::execute() {
        if (the_covers_ != nullptr) {
            // for each function         
            for (unsigned int i = 0; i < the_covers_->get_on_sets().size(); i++) {
                auto& the_on_set = the_covers_->get_on_sets()[i];
                auto& the_dc_set = the_covers_->get_dc_sets()[i];
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

    /**
     * @brief must override, displays nothing
     * @param a_stream 
    */
    void espresso_command::display(std::ostream& a_stream) {
    }

    /**
     * @brief determines whether the given implicant is valid for the given on/dc set
     * @param an_implicant - implicant to be checked
     * @param the_on_set - the on set of the function being optimized
     * @param the_dc_set - the dc set of the function being optimized
     * @return true if the implicant is covered by the on/dc set, false otherwise
    */
    bool espresso_command::validity_check(const std::string& an_implicant, implicants& the_on_set,
                                          implicants& the_dc_set) {
        // for each literal in the implicant
        for (unsigned int i = 0; i < an_implicant.size(); i++) {
            // if the literal is not a don't care
            if (an_implicant[i] == '-') {
                // replace the literal with a don't care
                const auto one_implicant = helpers::replace_char(an_implicant, i, "1");
                const auto zero_implicant = helpers::replace_char(an_implicant, i, "0");
                // check validity of new implicant
                return validity_check(one_implicant, the_on_set, the_dc_set)
                    && validity_check(zero_implicant, the_on_set, the_dc_set);
            }
        }
        // check if the implicant, with no don't cares, is covered by the on set or dc set
        return is_covered(an_implicant, the_on_set) || is_covered(an_implicant, the_dc_set);
    }

    /**
     * @brief determines whether the given implicant is covered by the given set
     * @param an_implicant - implicant to be checked
     * @param the_set - set to be checked
     * @return true if the implicant is covered by the given set, false otherwise
    */
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

    /**
     * @brief attempts to expand the implicant
     * @param an_implicant 
     * @param the_on_set - the on set of the function being optimized
     * @param the_dc_set - the dc set of the function being optimized
     * @return true if implicant successfully expanded, else false
    */
    bool espresso_command::expand(std::string& an_implicant, implicants& the_on_set, implicants& the_dc_set) {
        auto has_expanded = false;
        for (unsigned int j = 0; j < an_implicant.size(); j++) {
            // if literal is not a dc
            if (an_implicant[j] != '-') {
                // attempt to expand
                auto expanded_implicant = helpers::replace_char(an_implicant, j, "-");
                if (validity_check(expanded_implicant, the_on_set, the_dc_set)) {
                    // ok to expand
                    an_implicant = expanded_implicant;
                    has_expanded = true;
                }
            }
        }
        return has_expanded;
    }

    // TODO
    bool espresso_command::reduce(const std::string& an_implicant, implicants& a_function) {
        return false;
    }

    /**
     * @brief remove covered implicants and add the implicant to the on set
     * @param an_implicant 
     * @param the_on_set 
     * @return true
    */
    bool espresso_command::remove_covered_implicants(const std::string& an_implicant, implicants& the_on_set) const {
        std::vector<std::string> removal_list;
        // for each implicant in the on set
        for (auto on_implicant : the_on_set) {
            // assume the on implicant is covered
            auto covered = true;
            // ignore if the implicants match
            if (an_implicant != on_implicant) {
                // for every literal in the implicant
                for (unsigned int i = 0; i < on_implicant.size(); i++) {
                    if (an_implicant[i] != '-') {
                        // check for a discrepancy
                        if (an_implicant[i] != on_implicant[i]) {
                            covered = false;
                        }
                    }
                }
            }
            else {
                covered = false;
            }
            // mark the implicant for removal if it is covered
            if (covered) {
                removal_list.push_back(on_implicant);
            }
        }
        // remove implicants marked for removal
        for (const auto& the_string : removal_list) {
            auto itr = std::find(the_on_set.begin(), the_on_set.end(), the_string);
            if (itr != the_on_set.end())
                the_on_set.erase(itr);
        }
        return true;
    }


}
