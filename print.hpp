#pragma once
#include "command.hpp"
#include <string>
#include <ostream>
#include "covers.hpp"
namespace sis {

    class help_command :
        public command {
    public:
        explicit help_command();

        void execute() override;
        void display(std::ostream& a_stream) override;
    };

    class write_eqn_command :
        public command {
    public:
        explicit write_eqn_command(covers* the_covers);
        void execute() override;
        void display(std::ostream& a_stream) override;
    protected:
        void display_function(std::ostream& a_stream, unsigned int index) const;
        void display_implicant(std::ostream& a_stream, const std::string& an_implicant) const;
        covers* the_covers_;
    };

    class time_command :
        public command {
    public:
        time_command() = default;
        void execute() override {}
        void display(std::ostream& a_stream) override {}
    };

    class print_stats_command :
        public command {
    public:
        explicit print_stats_command(covers* the_covers);
        void execute() override;
        void display(std::ostream& a_stream) override;
    protected:
        uint32_t count_literals();
        uint32_t count_product_terms();
        covers* the_covers_;
    };
}
