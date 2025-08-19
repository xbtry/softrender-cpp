#ifndef TIMER_H
#define TIMER_H

// Helper class

#include <chrono>
#include "logger.hpp"
#include <string>

class Timer{
public:
    static void start(){
        m_start_time = std::chrono::high_resolution_clock::now();
    }
    static void stop(const std::string &message){
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time-m_start_time).count();
        Logger::print(
            Logger::Color::Green, 
            message,
            " | " ,
            Logger::Color::Yellow, 
            "Time taken: ", 
            Logger::Color::Red, 
            duration, 
            Logger::Color::Blue, 
            " ms."
        );
    }
private:
    using clock = std::chrono::high_resolution_clock;
    static std::chrono::time_point<clock> m_start_time;
};

std::chrono::time_point<std::chrono::high_resolution_clock> Timer::m_start_time;

#endif