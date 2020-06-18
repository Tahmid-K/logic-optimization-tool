#pragma once
#include <chrono>
#include <ctime>
namespace sis {
    class timer {
    public:

        explicit timer(const bool skip = true) : skip_(skip) {}

        void start() {
            if(!skip_) {
                start_ = std::chrono::high_resolution_clock::now();
            }
        }

        void stop() {
            if(!skip_) {
                end_ = std::chrono::high_resolution_clock::now();
            }
        }

        [[nodiscard]] double get_duration() const {
            if (start_ != end_) {
                const std::chrono::duration<double> the_duration = end_ - start_;
                return the_duration.count(); 
            }
            return 0.0;
        }

        [[nodiscard]] bool get_skip() const {return skip_;}
        void set_skip(const bool skip) {skip_ = skip;}
    protected:
        // temp solution
        bool skip_;
        std::chrono::time_point<std::chrono::high_resolution_clock> start_;
        std::chrono::time_point<std::chrono::high_resolution_clock> end_;
        
    };
}
