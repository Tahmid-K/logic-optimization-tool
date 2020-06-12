#pragma once
#include <chrono>
#include <ctime>
namespace sis {
    class timer {
    public:

        timer() {
            stopped = started = std::chrono::high_resolution_clock::now();
        };

        timer& start() {
            started = std::chrono::high_resolution_clock::now();
            return *this;
        }

        timer& stop() {
            stopped = std::chrono::high_resolution_clock::now();
            return *this;
        }

        double elapsed() const {
            if (started != stopped) {
                const std::chrono::duration<double> elapsed = stopped - started;
                return elapsed.count(); 
            }
            return 0.0;
        }
    protected:
        std::chrono::time_point<std::chrono::high_resolution_clock> started;
        std::chrono::time_point<std::chrono::high_resolution_clock> stopped;
        
    };
}
