# unix-course-design

UNIX课程设计：设计玩具级并发服务器，客户机和服务器实现的功能自定义，并测试系统的并发性能

1. [封装裸socket函数库 inet_stream_sockets.c](./src/inet_stream_sockets.c)
	- 封装使用 socket API 完成的 TCP 连接请求和 TCP 监听服务两个功能，为下面三个方式的服务器以及客户端提供更简单易用的API，同时完成代码复用。
1. [多进程方式 multi_processes_sv.c](./src/multi_processes_sv.c)
	- 通过我们之前实现的库，父进程生成监听套接字，循环 accept 阻塞地等待连接请求
	- 调用 accept 返回后，父进程 fork() 生成子进程为该客户请求提供服务
	- 对 SIGCHLD 信号配置信号处理函数，用于父进程回收僵尸子进程
	- syslog 调用将服务器的各种信息和错误写入日志 /var/log/syslog
1. [多线程方式 multi_threads_sv.c](./src/multi_threads_sv.c)
	- 主线程生成监听套接字后，循环 accept 阻塞地等待连接请求
	- 调用 accept 返回后，主线程 pthread_create 创建新的对等线程并为客户提供服务
	- syslog 调用将服务器的各种信息和错误写入日志 /var/log/syslog
1. [IO多路复用 multi_io_sv.c](./src/multi_io_sv.c)
	- 创建监听套接字，创建 epoll 对象，并把监听套接字的 fd 加入 epoll 监听队列
	- epoll_wait 发现监听套接字可读，accept 生成连接套接字，并加入 epoll 监听队列，继续循环
	- epoll_wait 发现连接套接字可读，读取一次（避免阻塞卡死服务器）连接套接字，提供服务后继续循环
1. [单次请求 single_client.c](./src/single_client.c)
	- 单次请求服务器服务
1. [并发请求测试 test_client.c](./src/test_client.c)
	- 产生大量的并发请求，记录时间，评测性能
