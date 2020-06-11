#pragma once
#include <iosfwd>

namespace sis {
    enum class command_type {
        help,
        read_pla,
        expresso,
        print_stats,
        history,
        clear,
        write_eqn,
        write_pla,
        invalid
    };
    class command {
    public:
        explicit command(const command_type a_type = command_type::invalid) : a_type_(a_type) {}
        virtual ~command() = default;
        command(command& a_copy) = default;
        command& operator=(const command& a_command) = default;

        [[nodiscard]] command_type get_type() const {return a_type_;}
        virtual void execute() = 0;
        virtual void display(std::ostream& a_stream) = 0;

    protected:
        command_type a_type_;
    };
}
