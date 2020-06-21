#include "TaskThread.h"

std::vector<TaskThread*> TaskThreadPool::sTaskThreadArry;

TaskThread::TaskThread():
    Thread()
{
    
}

void* TaskThread::entry()
{
    printf("Entering TaskThread %p\r\n", this);
    int i = 0;
    while (!fStop)
    {
        sleep(1);
        printf("TaskThread %p count %d\r\n", this, ++i);
        if (i == 3) 
            this->stop();
    }
    printf("Leaving TaskThread %p\r\n", this);
    return nullptr;
}

void TaskThread::waitForFinished()
{
    pthread_mutex_lock(&fMutex);
    while (!fStop)
    {
        pthread_cond_wait(&fCond, &fMutex);
    }
    pthread_mutex_unlock(&fMutex);
}

uint32_t TaskThreadPool::addThread(uint32_t numThread)
{
    for (uint32_t i = 0; i < numThread; ++i)
    {
        TaskThread* ptrTaskThread = new TaskThread();
        sTaskThreadArry.push_back(ptrTaskThread);
        ptrTaskThread->start();
    }
    return sTaskThreadArry.size();
}

TaskThread* TaskThreadPool::getThread(uint32_t index)
{
    if (index < 0 || index >= sTaskThreadArry.size())
        return nullptr;
    return sTaskThreadArry[index];
}

uint32_t TaskThreadPool::getThreadNum()
{
    return sTaskThreadArry.size();
}

void TaskThreadPool::waitForAll()
{
    for (uint32_t i = 0; i < sTaskThreadArry.size(); ++i)    
    {
        TaskThread* ptrTaskThread = sTaskThreadArry[i];
        ptrTaskThread->waitForFinished();
        delete ptrTaskThread;
    }
    sTaskThreadArry.clear();
}

