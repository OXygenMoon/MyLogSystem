/************************************************************************
    > File Name: log.cpp
    > Author: Lao Zhenyu
    > Mail: LaoZhenyu_961112@163.com 
    > Created Time: 四  3/11 19:47:01 2021
************************************************************************/

#include "log.h"
#include <cstdlib>
#include <ctime>

std::ofstream Logger::m_info_log_file;
std::ofstream Logger::m_warn_log_file;
std::ofstream Logger::m_error_log_file;

void initLogger(const std::string& info_log_filename,
                const std::string& warn_log_filename,
                const std::string& error_log_filename){
   Logger::m_info_log_file.open(info_log_filename.c_str());
   Logger::m_warn_log_file.open(warn_log_filename.c_str());
   Logger::m_error_log_file.open(error_log_filename.c_str());
}

std::ostream& Logger::getStream(LOGLEVEL loglevel){
    return (LOG_LEVEL_INFO == loglevel) ? 
        (m_info_log_file.is_open() ? m_info_log_file : std::cout) :
        (LOG_LEVEL_WARNING == loglevel ?
            (m_warn_log_file.is_open() ? m_warn_log_file : std::cerr) :
            (m_error_log_file.is_open() ? m_error_log_file : std::cerr));

}

std::ostream& Logger::start(LOGLEVEL loglevel,
                            const int line,
                            const std::string& function){
    time_t tm;
    time(&tm);
    char time_string[128];
    ctime_r(&tm, time_string);
    return getStream(loglevel) << time_string << " function (" << function << ")" << " line " << line << std::flush;
}

Logger::~Logger(){
    getStream(loglevel) << std::endl << std::flush;
    if(LOG_LEVEL_FATAL == loglevel){
        m_info_log_file.close();
        m_warn_log_file.close();
        m_error_log_file.close();
        abort();
    }
}
