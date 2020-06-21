# 互联网程序设计实验

## Lesson 1: 单元测试环境与BOOST使用

### 目录树结构
```txt
lesson 1
└── boost_test
    ├── Makefile
    ├── showcase
    │   └── 2020062110561477.png
    ├── src
    │   ├── basic_mstring.h
    │   └── test.cpp
    └── 实验1报告.doc
```

### 内容

- 新建一个SecureCRT的会话,并进行配置
- 实验boost::unit_test单元测试框架
- 学会使用CMake进行项目配置

### 目的

- 学会使用SecureCRT
- 熟悉Boost库并会使用Boost库中单元测试部分
- 学会使用CMake,对于大型项目来说,CMake可以大大降低在Linux下编译工程的时间消耗,不必花较多时间在Makefile文件上,而是用简单的语句达到同样的效果

### 运行

```bash
make
./bin/test
```

## Lesson 2: socket封装

### 目录树结构

```txt
lesson 2
└── socket_programming
    ├── Makefile
    ├── README.md
    ├── showcase
    │   └── 202006211050300001.png
    ├── src
    │   ├── Address.cpp
    │   ├── Address.h
    │   ├── PlatformHeader.h
    │   ├── Socket.cpp
    │   ├── Socket.h
    │   ├── TaskThread.cpp
    │   ├── TaskThread.h
    │   ├── TcpSocket.cpp
    │   ├── TcpSocket.h
    │   ├── Thread.cpp
    │   ├── Thread.h
    │   └── main.cpp
    └── 实验2报告.doc
```

### 内容

- 以C++类封装socket
- 封装TcpSocket类

### 目的

- 学会使用socket, send, recv,connect,accept等网络编程函数
- 掌握阻塞和非阻塞的区别
- 学会控制并发,使用信号量机制sem_init ,sem_post, sem_wait,来控制线程的走向
- 学会使用互斥锁unique_lock,shared_lock,write_lock,try_lock等等,控制线程的走向
- 学会使用gdb来debug,找到问题所在,如何设置断点,编译时加入-g来取消可执行程序的编译优化,从而可以使用gdb来调试可执行程序
- 学会使用虚函数,类继承,多态封装等思想

### 运行

```bash
make
./bin/main
```

## Lesson 3: 线程与线程池

### 目录树结构

```txt
lesson 3
└── threadpool
    ├── Makefile
    ├── README.md
    ├── showcase
    │   └── 2020062111005978.png
    ├── src
    │   ├── Address.cpp
    │   ├── Address.h
    │   ├── PlatformHeader.h
    │   ├── Socket.cpp
    │   ├── Socket.h
    │   ├── TaskThread.cpp
    │   ├── TaskThread.h
    │   ├── TcpSocket.cpp
    │   ├── TcpSocket.h
    │   ├── Thread.cpp
    │   ├── Thread.h
    │   └── main.cpp
    └── 实验3报告.doc
```

### 内容

- 封装抽象基类Thread
- 封装线程类TaskThread和线程池类TaskThreadPool

### 目的

- 学会使用pthread_mutex_lock, pthread_mutex_unlock
- 掌握条件变量的使用pthread_cond_signal, pthread_cond_broadcast, pthread_cond_init, pthread_cond_wait
- 掌握如何创建线程pthread_create,如何使用pthread_join

### 运行

```bash
make
./bin/main
```

## Lesson 4: epoll与reactor模式

### 目录树结构

```txt
lesson 4
└── reactor_server
    ├── Makefile
    ├── README.md
    ├── showcase
    │   ├── 2020040719035911.png
    │   ├── 2020040719211812.png
    │   ├── 2020040719384413.png
    │   └── 2020040720232216.png
    ├── src
    │   ├── Address.cpp
    │   ├── Address.h
    │   ├── Dispatcher.cpp
    │   ├── Dispatcher.h
    │   ├── EventHandler.cpp
    │   ├── EventHandler.h
    │   ├── Socket.cpp
    │   ├── Socket.h
    │   ├── Task.cpp
    │   ├── Task.h
    │   ├── TaskThread.cpp
    │   ├── TaskThread.h
    │   ├── TcpListenerSocket.cpp
    │   ├── TcpListenerSocket.h
    │   ├── TcpSession.cpp
    │   ├── TcpSession.h
    │   ├── TcpSocket.cpp
    │   ├── TcpSocket.h
    │   ├── Thread.cpp
    │   ├── Thread.h
    │   ├── common.h
    │   └── main.cpp
    └── 实验4报告.doc
```

### 内容

- 使用epoll实现一个reactor模式的服务端雏形.

### 目的

- 学会使用epoll_create, epoll_wait, epoll_ctl
- 掌握reactor模式的整体架构, 使用互斥锁来控制线程间的并发, 使用信号量来保证线程间的同步.
- 掌握如何在高并发程序中排错, 如何构建简单的高并发框架.
- 掌握如何在构建多线程项目.

### 运行

```bash
make
./bin/main
```

## Lesson 5: 时间轮

### 目录树结构

```txt
lesson 5
└── timer
    ├── Makefile
    ├── README.md
    ├── showcase
    │   └── 2020013114584486.gif
    ├── src
    │   ├── AdvanceTimeWheel.h
    │   ├── HourTimer.h
    │   ├── ListNode.h
    │   ├── MinTimer.h
    │   ├── PlatformHeader.h
    │   ├── SecTimer.h
    │   ├── TimeDriver.h
    │   ├── TimeDriverInterface.cpp
    │   ├── TimeDriverInterface.h
    │   ├── TimeWheel.cpp
    │   ├── TimeWheel.h
    │   ├── TimeWheelInterface.cpp
    │   ├── TimeWheelInterface.h
    │   ├── Timer.cpp
    │   ├── Timer.h
    │   ├── TimerInterface.cpp
    │   ├── TimerInterface.h
    │   └── main.cpp
    └── 实验5报告.doc
```

### 内容

- 设计时间轮方案,实现并提交实验结果

### 目的

- 掌握时间轮的各种算法,尤其是水表算法.
- 学会如何实现一个定时器, 如何维护每个水表上的timer队列,在O(1)算法时间实现每个水表上的timer可以井然有序的被触发.
- 本次实验的水表算法设置了三个TimeWheel,TimeWheelSize分别为60,60,24,对应于60秒一圈,60分一圈,24小时一圈.当秒针转到59时,会自动将分钟表盘上的下一分钟的所有任务填充到秒针表盘,当分针转到59时,会自动将小时表盘上的下一小时的所有任务填充到分钟表盘.因此这样就实现了每个表盘上都需要管理对应单位的timer队列.
- 这次实验最难的地方就在于AdvanceTimeWheel中的run和addTimer的实现,由于TimeDriver的时间粒度为1毫秒,而AdvanceTimeWheel的时间粒度为1s,因此需要进行统计转换. 并且需要按照表盘操作,每一个表盘转一圈后,下一个表盘内的指针自动加1, addTimer也是需要事先计算好timer的timespan,然后计算出下次触发的各个表盘指针对应的位置.

### 运行

```bash
make
./bin/main
```

# 作者

- BrianYi