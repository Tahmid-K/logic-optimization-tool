#pragma once
#include <string>
#include <filesystem>
#include <utility>
#include <fstream>
#include "command_handler.hpp"
namespace fs = std::filesystem;

namespace sis {

    class file_parser {
    public:
        explicit file_parser(fs::path a_file_path);
        file_parser();
        virtual ~file_parser() = default;
        virtual bool is_valid_path();
        virtual bool parse(command_handler& a_command_handler) = 0;
    protected:
        virtual fs::path string_to_path(const std::string& a_file_path_string);
        bool open_file();
        
        fs::path file_path_;
        std::ifstream a_stream_;
    };
}
