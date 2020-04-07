<!--
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-04-07 23:55:42
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-04-08 01:39:20
 * @License: CC-BY-NC-SA-V4.0 or any later version
 -->
1. Describe Function(功能) of `pthread_create`:
    + 在调用函数的进程中创建线程(前提是在Unix环境下),其读取四个参数,分别为指向标识符的指针,设置线程属性,函数起始地址,以及运行时参数.

2. Describe Function(功能) of `pthread_join`:
    + 主要功能为用来等待一个线程的结束,通常主线程对所有创建的线程使用该函数,避免主线程在其他线程之前退出.读入参数有两个,第一个为线程标识符,用来标志等待线程;第二个为用户定义的指针,用来存储返回值.

3. Describe Function(功能) of `pthread_mutex_lock`:
    + 传入参数只有一个mutex指针,该函数可以锁住传入的互斥锁.如果传入的互斥锁没有上锁,则将互斥锁上锁;如果互斥锁已经上锁,那么调用的线程将阻塞到互斥锁可用为止.

4. Describe Function(功能) of `pthread_cond_wait`:
    + 该函数主要用于阻塞当前线程,等待其他线程使用`pthread_cond_signal()`或者`pthread_cond_broadcast`唤醒自己.通常和互斥锁搭配使用,先上锁,再阻塞,阻塞时解锁,阻塞唤醒时加锁.可以结合条件变量使用.

5. Describe Function(功能) of `pthread_cond_signal`:
    + 该函数主要用于给一个处于阻塞状态(比如使用`pthread_cond_wait`)的线程发送信号,使其脱离阻塞状态,继续执行.
    + 该函数主要用于在单核处理器上只会给一个线程发送信号,而在多核处理器上有可能向多个线程发送信号.可以配合条件变量使用

6. Describe Function(功能) of `pthread_mutex_unlock`:
    + 该函数传入参数只有一个互斥锁,会将传入的互斥锁解除锁定状态.

7. Describe Function(功能) of `sem_open`:
    + `sem_open`用于创建并初始化有名信号量或者打开一个已存在的有名信号量,有四个传入参数(或两个),第一个为信号量的名字,第二个为选择打开或者创建信号量的flag,第三个(可选)为权限,第四个为信号量的初始值(需要小于等于32767).

8. Describe Function(功能) of `sem_wait`:
    + `sem_wait`传入一个参数,信号量,并试图将信号量的值减一.若信号量的值大于0,则直接执行;若信号量的值小于等于0,则阻塞到信号量被其他线程改变为大于零.

9. Describe Function(功能) of `sem_post`:
    + `sem_post`读入一个参数,信号量,并将信号量的值加一.是一个原子操作,不会出现同时加一,结果只加了一之类的错误.

10. Describe Function(功能) of `sem_close`:
    + `sem_close`读入一个有名信号量,并关闭该有名信号量.(PS:关闭不是删除,删除需要使用unlink来实现).

11. Producer-Consumer Problem（understand producer_consumer.c）: Are the data that consumers read from the buffer are produced by the same producer?
    + 并不是,生产者可以有任意多个,当且仅当只有一个生产者时,消费者才只能从缓存中读取相同的生产者生产的产品.

12. Producer-Consumer Problem（understand producer_consumer.c）: What is the order of the consumer's read operations and the producer's write operations, and their relationship
    + 消费者的读取动作一定在生产者的写入操作后面,因为无法对空的Buffer进行读取,但是生产者可以对空的Buffer进行写入.生产者所的写入操作和消费者的读取操作存在时间上的先后关系,逻辑上的因果关系.

13. Producer-Consumer Problem（understand producer_consumer.c）: Briefly describe the result of the program
    + 首先,程序构造了一个生产者和一个消费者.并将其启动
    + 随后,生产者和消费者由一个互斥锁保证同时只有一个对象对Buffer进行操作.
    + 生产者会在环形队列满时使用pthread_cond_wait与一个条件变量full休眠,而消费者会在空时使用pthread_cond_wait进行休眠,保证读写的安全性.
    + 使用了一个互斥锁和两个条件变量保证了读写和队列的容量的安全,生产者每次随机产生一个字母填写到队列中,消费者每次从队列中选择一个字母展示出来.

14. Producer-Consumer Problem（understand producer_consumer.c）: What queue is used in this program, and its characteristics?
    + 环形队列,环形队列的特点是首尾相连,FIFO,采用数组的线性空间,组织简单,判别队列是满是空也比较简单方便.存储数据也比较快速.

15. Producer-Consumer Problem（understand producer_consumer.c）: Briefly describe the mutual exclusion mechanism of this program
    + 首先,该队列使用了互斥锁来保证同时只有一个对象读取或者写入对象.然后,生产者使用一个条件变量,在队列满时休眠,消费者使用一个条件变量,在队列空时休眠.这样就保证了队列只有一个对象操作,同时不会在满时写入或者空时读取.