# unix-course-design

UNIX课程设计：设计玩具级并发服务器，客户机和服务器实现的功能自定义，并测试系统的并发性能

1. [封装裸socket函数库](./src/inet_stream_sockets.c)
	- 封装使用 socket API 完成的 TCP 连接请求和 TCP 监听两个功能，为下面三个方式的服务器以及客户端提供更简单易用的API，同时完成代码复用。
1. [多进程方式](./src/multi_processes_sv.c)
	- 父进程生成监听套接字后，循环 accept 阻塞地等待连接请求
	- 调用 accept 返回后，父进程 fork() 生成子进程为该客户请求提供服务
	- 对 SIGCHLD 信号配置信号处理函数，用于父进程回收僵尸子进程
	- syslog 调用将服务器的各种信息和错误写入日志 /var/log/syslog
1. [多线程方式](./src/multi_threads_sv.c)
1. [IO多路复用](./src/multi_io_sv.c)
