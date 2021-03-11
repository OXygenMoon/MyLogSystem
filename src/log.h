/************************************************************************
    > File Name: log.h
    > Author: Lao Zhenyu
    > Mail: LaoZhenyu_961112@163.com 
    > Created Time: 四  3/11 19:35:08 2021
************************************************************************/

#ifndef __LOG_H__
#define __LOG_H__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdint.h>

enum LOGLEVEL {
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL,
};

/*
 * 初始化日志文件
*/ 
void initLogger(const std::string& info_log_filename, 
                const std::string& warn_log_filename,
                const std::string& error_log_filename);

/*
 * 实现日志类
*/ 

class Logger {
    friend void initLogger(const std::string& info_log_filename,
                          const std::string& warn_log_filename,
                          const std::string& error_log_filename);
    
    public:
        //构造函数
        Logger(LOGLEVEL loglevel) : loglevel(loglevel) {}
        ~Logger();
    
        /*
         * 输出日志信息
        */ 
        static std::ostream& start(LOGLEVEL loglevel,
                                   const int line,
                                   const std::string& function);

    private:
        
        static std::ostream& getStream(LOGLEVEL loglevel);
        static std::ofstream m_info_log_file;
        static std::ofstream m_warn_log_file;
        static std::ofstream m_error_log_file;
        LOGLEVEL loglevel;
};


#define LOG(loglevel) \
Logger(loglevel).start(loglevel, __LINE__, __FUNCTION__)


#define CHECK(a)                                            \
   if(!(a)) {                                              \
       LOG(ERROR) << " CHECK failed " << endl              \
                   << #a << "= " << (a) << endl;          \
       abort();                                            \
   }                                                      \

#define CHECK_NOTNULL(a)                                    \
   if( NULL == (a)) {                                      \
       LOG(ERROR) << " CHECK_NOTNULL failed "              \
                   << #a << "== NULL " << endl;           \
       abort();                                            \
    }

#define CHECK_NULL(a)                                       \
   if( NULL != (a)) {                                      \
       LOG(ERROR) << " CHECK_NULL failed " << endl         \
                   << #a << "!= NULL " << endl;           \
       abort();                                            \
    }


#define CHECK_EQ(a, b)                                      \
   if(!((a) == (b))) {                                     \
       LOG(ERROR) << " CHECK_EQ failed "  << endl          \
                   << #a << "= " << (a) << endl           \
                   << #b << "= " << (b) << endl;          \
       abort();                                            \
    }

#define CHECK_NE(a, b)                                      \
   if(!((a) != (b))) {                                     \
       LOG(ERROR) << " CHECK_NE failed " << endl           \
                   << #a << "= " << (a) << endl           \
                   << #b << "= " << (b) << endl;          \
       abort();                                            \
    }

#define CHECK_LT(a, b)                                      \
   if(!((a) < (b))) {                                      \
       LOG(ERROR) << " CHECK_LT failed "                   \
                   << #a << "= " << (a) << endl           \
                   << #b << "= " << (b) << endl;          \
       abort();                                            \
    }

#define CHECK_GT(a, b)                                      \
   if(!((a) > (b))) {                                      \
       LOG(ERROR) << " CHECK_GT failed "  << endl          \
                  << #a <<" = " << (a) << endl            \
                   << #b << "= " << (b) << endl;          \
       abort();                                            \
    }

#define CHECK_LE(a, b)                                      \
   if(!((a) <= (b))) {                                     \
       LOG(ERROR) << " CHECK_LE failed "  << endl          \
                   << #a << "= " << (a) << endl           \
                   << #b << "= " << (b) << endl;          \
       abort();                                            \
    }

#define CHECK_GE(a, b)                                      \
   if(!((a) >= (b))) {                                     \
       LOG(ERROR) << " CHECK_GE failed "  << endl          \
                   << #a << " = "<< (a) << endl            \
                   << #b << "= " << (b) << endl;          \
       abort();                                            \
    }

#define CHECK_DOUBLE_EQ(a, b)                               \
   do {                                                    \
       CHECK_LE((a), (b)+0.000000000000001L);              \
       CHECK_GE((a), (b)-0.000000000000001L);              \
    }while (0)

#endif
