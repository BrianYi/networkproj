#pragma once

#include "Thread.h"

class TaskThread:
    public Thread
{
public:
    TaskThread();
    ~TaskThread(){};
    void* entry();
    void waitForFinished();
};

class TaskThreadPool
{
public:
    static uint32_t addThread(uint32_t numThread);
    static TaskThread* getThread(uint32_t index);
    static uint32_t getThreadNum();
    static void waitForAll();
private:  
    static std::vector<TaskThread*> sTaskThreadArry;
};

