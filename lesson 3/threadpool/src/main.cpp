#include "PlatformHeader.h"
#include "TaskThread.h"

int main()
{
    TaskThreadPool::addThread(5);    
    TaskThreadPool::waitForAll();
    return 0;
}

