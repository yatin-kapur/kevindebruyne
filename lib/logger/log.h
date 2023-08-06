#pragma once

#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <mutex>

class Log {
public:
    Log(std::string id, int level=2)
        : m_class(id),
          m_log_level(level)
        {} 

    const int log_level_error = 0;
    const int log_level_warning = 1;
    const int log_level_info = 2;
private:
    std::string m_class;
    int m_log_level;
    std::mutex m_logMutex;
public:
    void set_level(int level)
    { 
        m_log_level = level;
    }

    std::string now()
    {
        using namespace std::chrono;
        using clock = system_clock;
        
        const auto current_time_point {clock::now()};
        const auto current_time {clock::to_time_t (current_time_point)};
        const auto current_gmttime {*std::gmtime (&current_time)};
        const auto current_time_since_epoch {current_time_point.time_since_epoch()};
        const auto current_milliseconds {duration_cast<milliseconds> (current_time_since_epoch).count() % 1000};
        
        std::ostringstream stream;
        stream << std::put_time(&current_gmttime, "%Y-%m-%d %T") << "." << std::setw (3) << std::setfill ('0') << current_milliseconds;
        return stream.str();
    }

    template <typename T>
    void printlog(const std::string& prefix, T const& message)
    {
        const std::string& lvl = now() + " [" + prefix + "] [" + m_class + "]: " + message + "\n";
        std::cout << lvl;
    }

    template <typename T>
    void error(T const& message)
    {
        if (m_log_level >= log_level_error) 
        {
            std::lock_guard<std::mutex> guard(m_logMutex);
            printlog("ERROR", message);
        }
    }

    template <typename T>
    void warn(T const& message)
    {
        if (m_log_level >= log_level_warning)
        {
            std::lock_guard<std::mutex> guard(m_logMutex); 
            printlog("WARNING", message);
        }
    }

    template <typename T>
    void info(T const& message)
    {
        if (m_log_level >= log_level_error) 
        {
            std::lock_guard<std::mutex> guard(m_logMutex);
            printlog("INFO", message);
        }
    }
};