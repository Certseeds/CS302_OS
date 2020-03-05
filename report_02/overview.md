<!--
 * @Github: https://github.com/Certseeds
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-03-04 20:35:10
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-03-05 17:50:27
 -->
1. 下载文件 忽略
2. 什么是系统调用?
+ 系统调用就是操作系统内核提供的,运行在Kernel mode的一系列功能强大的底层函数,这些函数的功能内置在内核中,而不依赖于其他语言的库.是内核提供给用户程序的接口.
3. 简述fork调用.<del>`进程===Process`</del>
  + 首先,fork是一个system call,由内核提供.
  + 随后,fork的功能是,为调用其的进程(父进程)创建一个新的进程(子进程)副本.
  + 子进程与父进程的Program Counter,Code,Memory以及文件等user-data都将完全一致.
  + 在执行方面,父进程与子进程也将从相同的位置开始执行.
  + 但是,父进程与子进程的PCN将会存在不一致,父进程pid不变,子进程被分配新的pid;parent process id(ppid)不一致,父进程ppid不变,子进程ppid为父进程pid;Running Time也不同,父进程保持不变,子进程从零开始计算;父进程的file lock不变,但是子进程没有file lock的权限等等,pcb会存在很多不一致.
  + 然后,在执行上,fork将对父进程返回子进程的Process Id(pid),并对子进程返回 0.
  + 最后,fork不对父进程与子进程的执行顺序做任何保证.
4. 如何实现进程间通信
  + 父进程与子进程之间,通常使用匿名管道的方式进行通信,声明一个int pi [2],通过pipe()指令将其转化为文件描述符,之后父进程写入pi[1],子进程读取pi[0],实现进程间通信.通过对文件的读写来完成.
  + 不相关的两个进程之间,可以使用有名管道的方式进行通讯,使用mkfifo(pathname,mode)的方式在pathname处实现一个可以被读写的文件.进程之间通过读写文件实现通信.
  + 进程之间可以用信号的方式实现通讯,发送使用kill,raise等函数,接收方可以对接收到的信号执行默认操作,捕捉或忽略等处理方式(并不是全部进程都可以).
  + 消息队列,存放在内核中的消息链表,通过描述符来识别,可以在进程间读写.
  + 信号量可以实现进程间通信(通常配合其他方式使用)
  + 进程间可以共享内存,最快,但是也需要配合其他方式使用.
  + 进程间可以使用socket通信,由于socket格式较为固定,所以移植性较好.
5. TODO
6. 通过`man fork`,可知fork的函数原型为 `pid_t fork(void);`
7. 通过`man signal`,可知signal的函数原型为`void (*signal(int sig, void (*handler)(int)))(int);`(在note部分有特别标明未经typedef的版本)
8. 通过`man pipe`,可知pipe的函数原型为`int pipe(int pipefd[2]);`
9. 通过`man tcsetpgrp`,可知pipe的函数原型为`int tcsetpgrp(int fd, pid_t pgrp);`
10. 
  + 结果为
   只有`ls -l /`的输出.
   分析如下:
  + 首先在父进程执行fork,创建子进程,之后子进程pid由空闲pid分配,ppid分配为父进程的pid(故为18775),fork()成功,没有返回值小于0,不输出错误信息.
  + 而父进程的pid不变,ppid为shell的进程(本处为zsh的pid)
  + 子进程中fork()的返回值为零,所以进入if的大括号中,但是printf的输出没有显示,因为缓冲区没有刷新就使用execvp()进入了新进程.
  + 父进程进入下方的括号中,使用waitpid()直到子进程执行结束再结束,同样没有输出.
  + 故只有`ls -l /`的输出.
  + 如果我们在printf()与execvp()之间加入`fflush(stdout);`,则可以看见有其他输出(`argc = 1,argv[0] = ./fork`),证明printf()输出成功,输出信息意为执行该文件为直接在对应目录下执行,并没有其他命令行参数.
11.  
  + 只有`ls -l /`的输出.
  分析如下:
  + 首先在父进程执行fork,创建子进程,之后子进程pid由空闲pid分配,ppid分配为父进程的pid(故为18775),fork()成功,没有返回值小于0,不输出错误信息.
  + 而父进程的pid不变,ppid为shell的进程(本处为zsh的pid)
  + 子进程中fork()的返回值为零,所以进入if的大括号中,但是printf的输出没有显示,因为缓冲区没有刷新就使用execvp()进入了新进程.
  + 父进程进入下方的括号中,使用waitpid()直到子进程执行结束再结束,同样没有输出.
  + 故只有`ls -l /`的输出.
  + 如果我们在printf()与execvp()之间加入`fflush(stdout);`,则可以看见有其他输出(`argc = 1,argv[0] = ./fork`),证明printf()输出成功,输出信息意为执行该文件为直接在对应目录下执行,并没有其他命令行参数.
  + 程序中可以通过检测fork()返回值是否为0,来区分父进程子进程,父进程的fork()返回值不为0,子进程fork()返回值为0.(fork()失败时会向父进程返回负值,无子进程).
12. 运行"pipe.c", 观察结果并简述结果(不是执行结果):
  + 就现象来说,首先输出一行send,之后为start1|send,之后输出start1|rec,随后进入more界面,输出ls的内容.
  + ##### 分析
  + 首先创建管道和创建第一个子进程,一般来说不会出现错误,故没有failed输出
  + 然后,第一个子进程处于阻塞状态,等待父进程写管道.
  + 父进程创建第二个子进程,一般不会出现错误,无fileed报错.
  + 之后,子进程2将管道描述符复制给标准输入,并以execvp()启动`/bin/more`,从管道中国读取输入并输出.
  + 此时,父进程与子进程2的顺序并不确定,但是确定的是父进程一定是在向管道内写入后子进程1才开始调用`ls`,子进程1将`ls`的输出写入管道内.父进程将"start2"写入管道内.
  + 随后,子进程2将从管道中读取,并展示出来,而子进程1,父进程都已结束.
  + 在接收到q或者翻页到末尾之后,子进程2退出.
13. 运行" pipe.c", 观察结果。execvp(prog2_argv[0],prog2_argv)（第56行）是否执行，如果没有执行是什么原因：
  + 显然执行了,因为输出中含有`ls`的输出,输出了/etc中的文件列表.
14. 运行" signal.c", 观察结果并简述结果（不是执行结果）：
  + 将会以1s为周期,随机顺序输出`PID(parent): 父进程pid`,`PID(child): 子进程pid`,最后可以按`Ctrl+C`结束,结束前没有其他输出.
  + ##### 分析如下
  + 首先声明了一个sigaction的结构体,action,随后注册了信号处理函数,并将结构体的sa_mask全部置为1,接受所有信号.
  + 随后将结构体的信号处理函数声明为带有三个函数的sa_sigaction.
  + 之后,fork()进程,显然,如果没有外来信号,那么父进程和子进程都只会不断地printf(),而不会有跳转到 ChildHandler中.
15. 运行" signal.c", 观察结果。请回答，怎样让函数ChildHandler执行？
  + 因为signal.c中ChildHandler为信号处理函数,所以需要外来的信号,所以需要通过控制台对其输入一些信号量来使得进程接收到信号.
  + 最好的方式是新开一个Terminal,并使用Kill命令使父进程或者子进程接收到信号,这样能够同时观察两方终端,便于观察.
  + 使用`kill -STOP` `kill -CONT` `kill -INT` `kill -KILL`等操作,对进程进行操作,可以观察到,对子进程进行的操作,在对子进程`kill -KILL`时会有The child is gong输出,其他情况下有时会无输出(比如直接`KILL -INT`),其他状态下会有Uninteresting.
16. 运行" process.c", 观察结果并简述结果（不是执行结果）：
  + 首先,在不做任何改动的情况下,将会随机输出父子进程的pid,并卡住,只能`Ctrl+C`
  + fix bugs.(执行环境为WSL)
  + 将子进程中的`setpgid(0,0)`注释掉.
  + 使用一个char* prog_argv[3]来存储参数,调用部分代码改动如下.
  ``` c
  char* prog_argv[3];
  prog_argv[0]="/usr/bin/vi";
  prog_argv[1]="vi";
	prog_argv[2]=NULL;
    //execvp("/usr/bin/vi","vi",NULL);
	execvp(prog_argv[0],prog_argv);
  ```
  + 出于未知原因,复制多个`fprintf(stdout,"ID(parent)=%d\n",ppid);`可以降低运行时出现
`suspended(tty output)`的概率.
  + 执行`./process`后可以分成三部分
  + 1. 第一,输出ID(parent)=父进程pid,ID(child)=子进程id,顺序不限.
    1. 第二,进入vi的界面,需要手动操作后退出,会在`./`下生成vi文件.
    2. 第三,等待终端输入并回显,需要使用`Ctrl+C`退出.
  + ##### 分析
  + 首先创建子进程,若创建失败则退出父进程.
  + 创建成功后,父子进程输出提示信息.
  + 由于父子进程执行顺序不固定,故需要在两方分别设置进程组和控制终端.
  + 随后,子进程启动,并进入vi中,父进程设置进程组并设置控制终端.
  + 由于控制终端被设置成子进程,进入vi界面.
  + 子进程退出后,返回父进程,并将控制终端返回给父线程.
  + 父进程读入输入并回显,使用`Ctrl+C`停止.
  + 
17. 运行" process.c", 观察结果。请回答，进程列表中有几个./process，区别在哪里：
  + 首先,在不做任何改动的情况下,将会随机输出父子进程的pid,并卡住,只能`Ctrl+C`
  + fix bugs.(执行环境为WSL)
  + 将子进程中的`setpgid(0,0)`注释掉.
  + 使用一个char* prog_argv[3]来存储参数,调用部分代码改动如下.
  ``` c
  char* prog_argv[3];
  prog_argv[0]="/usr/bin/vi";
  prog_argv[1]="vi";
	prog_argv[2]=NULL;
    //execvp("/usr/bin/vi","vi",NULL);
	execvp(prog_argv[0],prog_argv);
  ```
  + 出于未知原因,复制多个`fprintf(stdout,"ID(parent)=%d\n",ppid);`可以降低运行时出现
`suspended(tty output)`的概率.
  + 运行`./process`,由于printf()输出极快
  + 故只观察到了进程列表中有一个process,有一个vi(子进程)).
  + vi退出后,只剩一个process.
  + 退出process后,进程中没有process.
  + 如果说的是没有更改过的process.c文件(在这里的改变为,在16题基础上去掉注释`setpgid(cpid,cpid);`),则有两个process.无法回显,亦无法显示vi界面,使用`Ctrl+C`退出后,无法显示回显,并有`suspended(tty output)`产生,`ps -ef`可知退出的为子进程,父进程被挂起.
  + 此处可知,若去掉注释,则子进程由不明原因阻塞在`execvp()`之前,而父进程还可以`fg %1`调回前台.
18. 运行" process.c", 观察结果。请回答，杀死主进程后，出现什么情况：
  + 首先,在不做任何改动的情况下,将会随机输出父子进程的pid,并卡住,只能`Ctrl+C`
  + fix bugs.(执行环境为WSL)
  + 将子进程中的`setpgid(0,0)`注释掉.
  + 使用一个char* prog_argv[3]来存储参数,调用部分代码改动如下.
  ``` c
  char* prog_argv[3];
  prog_argv[0]="/usr/bin/vi";
  prog_argv[1]="vi";
	prog_argv[2]=NULL;
    //execvp("/usr/bin/vi","vi",NULL);
	execvp(prog_argv[0],prog_argv);
  ```
  + 出于未知原因,复制多个`fprintf(stdout,"ID(parent)=%d\n",ppid);`可以降低运行时出现
`suspended(tty output)`的概率.
  + 当子进程进入vi界面时,通过另一个终端kill掉父进程,则子进程将会立即退出,并输出`${父进程pid} killed ./process`.
  + 子进程无法使用fg调回前台,使用`kill -CONT pid`,没有反应,只能`kill -KILL pid`kill掉.
  










<del>
1.  运行并简述结果
  + 就现象来说,可以把pipe.c的运行分为三部分
  + 第一部分,随机先后输出父进程,子进程开始并输出各自pid
  + 第二部分,子进程读取控制台输入,通过匿名管道写入,父进程通过匿名管道将其输出,并循环直到控制台读取到SIGINT信号,进入第三部分
  + 第三部分.父子进程分别关闭匿名管道并输出提示信息,关闭进程.  
  ## 步骤分析如下
  + 首先,创造匿名管道,随后fork,fork之后并不会保证运行顺序,所以会随机的的输出子进程开始,父进程开始并输出进程pid.
  + 无论父进程子进程的执行顺序如何,父进程中输出语句与两个signal语句设定完毕后并没有主动进行操作,而是会在while()循环中无限循环,子进程则在输出之后主动使用kill()向自己的进程发送了SIGALRM信号,子进程(由于signal的设定)跳转到了write_date函数中.
  + (此处的易错点在于signal()不是阻塞执行,只是设定了接受信号之后的处理方式)子进程开始使用write_data函数,输出提示输入的字符串并阻塞读入,并在读入后将其写入匿名管道中.输出"Write finished",并用kill(getppid(),SIGALRM)向父进程发送SIGALRM信号(发送信号之前,父进程一直在循环中),之后子进程开始循环,父进程接收到SIGALRM信号,跳转到read_data()中.
  + 父进程使用read_data从匿名管道中读取,并将其输出,最后使用向子进程发送SIGALRM信号(子进程的pid已经在最初fork时提供).父进程返回循环中.
  + 子进程接收到SIGALRM信号,之后过程跳转到两步之前,开始循环.
  + 直到控制台接收到Ctrl+C等方式的SIGINT信号,子进程,父进程分别跳转到finish_write,finish_read中,关闭匿名管道并结束进程.
  </del>