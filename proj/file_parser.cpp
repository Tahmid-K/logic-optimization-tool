#include "file_parser.hpp"
#include <utility>
#include <fstream>
namespace sis {

    file_parser::file_parser(fs::path a_file_path) : file_path_(std::move(a_file_path)) {       
    }

    file_parser::file_parser() {
        a_stream_.close();
    }

    fs::path file_parser::string_to_path(const std::string& a_file_path_string) {
        auto the_file_path = "./" + a_file_path_string;
        return fs::path(a_file_path_string);
    }

    bool file_parser::open_file() {
        a_stream_.open(file_path_, std::ios::in);
        return a_stream_.is_open();
    }

    bool file_parser::is_valid_path() {
        return fs::exists(file_path_);
    }
}
