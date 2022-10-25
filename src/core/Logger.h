#ifndef _SRC_CORE_LOGGER_H_
#define _SRC_CORE_LOGGER_H_
#include <memory>
#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace DEngine
{
    class Logger
    {
    public:
    static void Init();
    static std::shared_ptr<spdlog::logger> GetLogger(){

        return s_logger;
    }
    private: 
    static std::shared_ptr<spdlog::logger> s_logger;
    };
}

// Core Logging Macros
#define APP_TRACE(...) DEngine::Logger::GetLogger()->trace(__VA_ARGS__)
#define APP_INFO(...) DEngine::Logger::GetLogger()->info(__VA_ARGS__)
#define APP_WARN(...) DEngine::Logger::GetLogger()->warn(__VA_ARGS__)
#define APP_ERROR(...) DEngine::Logger::GetLogger()->error(__VA_ARGS__)
#endif