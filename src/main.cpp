/************************************************************************
    > File Name: main.cpp
    > Author: Lao Zhenyu
    > Mail: LaoZhenyu_961112@163.com 
    > Created Time: 四  3/11 19:59:38 2021
************************************************************************/

#include "log.h"
#include <iostream>
using namespace std;

int test(int n){
    cout << n << endl;
    LOG(LOG_LEVEL_INFO) << "yourinfo";
    return n;
}

int main(int argc, char *argv[])
{
    initLogger("./logFile/info.md", "./logFile/warn.md", "./logFile/error.md");
    int times = 100;
    while(times--)  test(times);
    return 0;
}
