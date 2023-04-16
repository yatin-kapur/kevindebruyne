#pragma once

#include <iostream>
#include <ctime>
#include <iomanip>
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
        std::time_t now = std::time(0);
        std::tm* gmt = std::gmtime(&now);

        std::stringstream timess;
        timess << std::put_time(gmt, "%Y-%m-%d %H:%M:%S");
        return timess.str();
    }

    template <typename T>
    void error(T const& message)
    {
        if (m_log_level >= log_level_error) 
        {
            std::lock_guard<std::mutex> guard(m_logMutex);
            std::cout << now() << " [ERROR] [" << m_class << "]: " << message << std::endl;
        }
    }

    template <typename T>
    void warn(T const& message)
    {
        if (m_log_level >= log_level_warning)
        {
            std::lock_guard<std::mutex> guard(m_logMutex); 
            std::cout << now() << " [WARNING] [" << m_class << "]: " << message << std::endl;
        }
    }

    template <typename T>
    void info(T const& message)
    {
        if (m_log_level >= log_level_error) 
        {
            std::lock_guard<std::mutex> guard(m_logMutex);
            std::cout << now() << " [INFO] [" << m_class << "]: " << message << std::endl;
        }
    }
};