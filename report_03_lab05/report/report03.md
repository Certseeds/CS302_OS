<!--
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-03-31 21:30:24
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-04-01 00:44:48
 -->
1. What is a process? What is a program? And what is the difference? 说明进程与程序的区别：
    + 程序就只是代码的集合,是文件,是非动态的,不会主动做任何行为.
    + 进程是操作系统中有由程序,数据,控制块组成的一个执行程序,是由系统对进程和进程之间进行资源(CPU时间片,内存等)分配和管理调度的独立基本单位,是为正在运行的程序提供的运行环境.
    + 所以,程序只是一个文件,而进程是动态下操作系统维护的一个实体.

2. What is job? And what is the difference between process and job? | 说明进程与作业的区别：
    + 进程是操作系统中有由程序,数据,控制块组成的一个执行程序,是由系统对进程和进程之间进行资源(CPU时间片,内存等)分配和管理调度的独立基本单位,是为正在运行的程序提供的运行环境.
    + 作业(job)是用户向计算机提交任务的任务实体,由大于等于一个进程组成,主要概念用于批处理中,是用户需要计算机完成的某项任务,是要求计算机所做工作的集合.
    + 进程是一个程序对某个数据集的执行过程,作业时用户需要计算机完成的某项任务,作业可以包含一个或多个进程.

3. What are the differences between job scheduling and process scheduling? 说明作业调度与进程调度的区别：
    + 作业调度较为高级,进程调度较为低级.
    + 作业调度利用某种算法,在资源满足时,从就绪的后备作业队列中选择作业装入内存运行,并生成和作业相应的进程,并负责给进程分配相关资源,以及在作业执行完毕后,负责回收系统资源.
    + 而进程钓鱼则按照一定的算法,动态的将处理及分配给处于就绪状态中的某一个进程,并令其执行.
    + 总结来看,作业调度使得某个作业有了运行的机会,但是进程调度才是细化到令某个进程运行的调度算法.

4. What are the similarities and differences among structures, classes, and unions： 说明结构、类和联合的相同点和不同点：
    + 首先在C语言中,没有class的概念,所以只讨论structures和unions.
    + 他们都可以存放任意的,不同类型的变量.但是结构可以同时存放所有成员,而联合只能存放一个成员.
    + 其次,在C++中,类和结构高度重合,只不过结构的成员默认是public,而类的默认可见性为private.所以可以合在一起讨论.class可以用在模板中替代typename，struct不能.
    + 在c++中,类和结构都可以存放任意的,不同类型的变量, 同时可以由构造函数,析构函数,等等函数,但是联合虽然可以由很多成员,但是只能同时存放一个成员,而且不能由虚函数,不能有基类且不能用作基类,不能拥有引用类型的非静态数据成员等等.
    + 总结:结构,类和联合都可以包含不同类型的变量,但是类(如果有的话)和结构可以同时存储并存在所有成员,但是结构只能同时存在一个被选中的成员.

5. How many statuses are in a job(in the code for this report—scheduler)? And what are they? 本次实验作业有几种状态(在本次报告的代码中-scheduler)？请列举
    + 有三种状态
    + 分别为 READY 作业准备就绪,可以运行, RUNNING 作业正在运行, DONE 作业已经运行结束，可以退出.

6. What programs for job control are used in this experiment? And their function? 本实验作业控制命令处理程序包括哪些？它们分别实现什么功能？
    + 本次作业的控制命令处理程序包括:enq命令,stat命令,deq命令.
    + 实现的功能有:
    + enq命令,给scheduler调度程序发送入队请求,并可以指定入队的程序的优先级和命令行参数.
    + deq命令,给scheduler调度程序发送出队请求,需要指定出队的jid.
    + stat命令,给scheduler调度程序发送输出请求,并使得scheduler调度程序在stdout上输出当前运行中的作业以及deque中所有作业的信息.

7. What is used for inter-process communication in this experiment? And its function? 本实验采用什么进行进程之间的通信？它相当于什么作用？
    + 第一,本实验采用了具名管道,或称有名管道,命名管道,Named pipes,FIFO进行进程间的通信.
    + 它的作用: 具名管道利用文件系统,将一个路径名和管道关联,以FIFO的文件形式存在于文件系统中,使得和具名管道没有亲缘关系的进程,可以通过访问该路径,打开,读写该管道,并借此实现FIFO的互相通信.
    + 第二,本实验还采用了信号来进行进程间通信,比如使用定时器,每隔100ms,向自己的进程发送`SIGVTALRM`信号,以及子进程结束向父进程发送`SIGCHLD`信号,使用kill向进程发送`SIGSTOP`以停止进程,以及`SIGCONT`以开始进程.
    + 它的作用:实现进程间互相的提示,子进程结束时的提示,以及对进程的暂停和开始.

8. What should be noted when printing out the job name: 在打印出作业名称的时候应该注意什么问题:
    + 要注意不要使用popen等方式,通过另开一个shell进程的方式,试图通过pid获取作业名称.
    + 如果使用了子进程获取作业名称,则子进程在退出时会给父进程发送SIGCHLD信号,scheduler则会认为是正在运行的子进程结束,则会将正在运行的子进程标为DONE并剔除.会干扰正常作业,所以不能使用任何新建子进程的方式.
    + 所以,需要使用访问`/proc/${pid}/status`文件的方式,由pid获取作业名称.
    + 最后,作业的名称通常都比较长,需要多加两个制表符确保美观.

9. Submit a job that takes more than 100 milliseconds to run（pleas paste your code): 提交一个运行时间超过100毫秒的作业（请直接粘贴代码):
``` c
#include <stdio.h>
#ifdef __GNUC__
#include <unistd.h>
#define sleepTime 1
#else
#include<windows.h>
#define sleepTime 1000
#endif
int main(){
    int x = 114514;
    printf("%d",x);
    for(int i = 0;i<5000;i++){
        printf("%d \n",x);
        sleep(1);
        printf("%d \n",x);
        fflush(stdout);
    }
    printf("%d\n",x);
    return 0;
```

10. List the bugs you found and your fix(Describe the cause of bugs in detail and how to modify it)：列举出你找到的bug并给出你的解决方案（请仔细描述bug的原因以及修复方案)：
    1. 第一个BUG是第84行(未修改的文件,下同)的最后.
        + 第84行最后,出现了一个中文符号,在windows1252下显示为乱码,切换为UTF-8后可见,为一个`；`,中文逗号.
        + BUG原因:中文标点无法被编译器识别.
        + 修复方案,将`；`替换为`;`,并将编码切换为UTF-8.
        + 将输入法的标点改成半角,既只输入英文符号可以避免该问题.
    2. 第二个BUG出现在第464行.
        + 第464行,将tv_usec设置为了100,是一个逻辑方面的BUG.
        + BUG原因,tv_usec的单位为微秒,既10^-6s,将其设定为100,并且计时器的tv_sec为零,则会每10^-4s,既0.1ms触发一次.
        + 修复方案:计算所需的100ms,为10^-3s*10^2 = 10^-1s = 10^-6μs * 10^5.所以tv_usec应该设置成10^5,在代码中体现为100000. 
    3. 第三个BUG出在第80,84行.
        + BUG原因: 因为每个时间片内为100ms,所以每次update应该使运行的进程的时间(run_time)加一百,而不是加一,每次等待的进程的时间也应该加100,而不是加一.
        + 修复方案:将80,84行的`1`,替换为`100`.
    4. 第四个BUG出现在88行`jobselect()`函数内.
        + BUG原因: 分情况讨论一下,如果head为空,则显然于预期一样,如果head不为空,则进入到96行开始的循环中.
        + 同时,如果head节点就是这个队列中highest最大(在完成需求后,还有highest于其他节点相同时的等待时间最长),则select与selectprev都为head节点.则在运行到第108行时,会直接将head置为NULL,同时返回head节点赋值给next.这就意味着head节点的next节点也一同被赋给了next节点,并在之后`jobswitch`中赋给了current.这样一来,造成的直接后果有:1.在`updateall`中无法对head以及其next节点们进行wait_time的累计(因为这种情况下,current后面挂着很多next,但是head却只有一个).2.一旦head只有一个,那么下次调用`jobselect()`会默认使得select与selectprev只能为head,使得只能返回head节点.造成在下次调用`jobswitch`时,head已经为null,实现head和current与本次相反.和设计逻辑完全不一致.
        + 若head不是队列中最大值,则没有问题.
        + 解决方案: 在`jobselect()`内部进行详尽的分类讨论,避免出现错误,代码段如下:对if(head)内的代码整体做了修改.
        ``` cpp
        if(head){
        // 有元素
        if(head->next){
            //多于一个元素
            for (prev = head, p = head; p != NULL; prev = p, p = p->next) {
                if (p->job->curpri > highest) {
                    select = p;
                    selectprev = prev;
                    highest = p->job->curpri;
                }else if(highest == p->job->curpri
                    && p->job->wait_time > select->job->wait_time){
                    select = p;
                    selectprev = prev;
                }
            }
            //*Find Bug 3.
            if(selectprev == select){
                struct waitqueue* temp = head->next;
                select = head;
                select->next=NULL;
                head = temp;
            }else{
                selectprev->next = select->next;
                select->next = NULL;
            }
        }else{
            //只有一个元素
            select = head;
            head = NULL;
        }
        }//没有元素 省去
        ```
        在代码中,head为空直接返回NULL;head没有next直接返回head,并将head置为NULL;
        head不为空,且head->next不为空则进行遍历deque,若head即为最大的节点,则将head置为head->next,并返回head节点.若head不是最大的节点,则将head的前一个节点的next置为head的next,并将head节点返回.
        保证了返回的节点要么为空,要么会一个没有next的节点.同时不会对head节点进行破坏.
        + 我认为这个BUG就可能是导致无法添加进多于3个进程的原因,因为只有一个的时候,只有current不会触发,只有两个的时候,一个current,一个head,互相交换也不会出发,3个及以上就会触发,因为head可能有next.
    5. 第五个BUG出现在317行`do_deq()`函数内.
        + BUG原因:这个BUG和上面的BUG4相同,同样属于逻辑不严密导致的错误
        + 首先,如果Head为NULL,则不会触发该BUG.
        + 其次,当Head不为NULL,则有可能head的pid和要deq的pid一致,此时,selectprev和select在第360行的判断一定成立,则head会被置为NULL,但是head有可能还有next,而且因为selectprev和select相同,所以第359行`selectprev->next = select->next;`也不会生效,导致了直接后果,head直接为NULL,同时head节点被free.直接导致了head的next节点们消失,无法被利用.
        + 解决方案:在head内部分类讨论,提前规避问题.(对if (head}{}内的代码整体做了修改)
        ``` cpp
        if (head) {
            if(deqid == head->job->jid){
                select=head;
                head=head->next;
            }else{
                for (prev = head, p = head; p != NULL; prev = p, p = p->next) {
                    if (p->job->jid == deqid) {
                        select = p;
                        selectprev = prev;
                        break;
                    }
                }
                if(selectprev && select){
                    selectprev->next = select->next;
                }
            }
        }
        ```
        在修改后,直接规避了head可能的问题,确保了head的next的安全性.确保每次只会有一个节点被free,同时其他head的next节点们不会消失.

11. Run the job scheduler program, And analyze the execution of the submitted job: 运行作业调度程序，分析提交作业后的作业的执行过程:
    + 运行scheduler之后,每100ms,schdduler都会从具名管道中读取新的动作,并或者增加进作业,或者显示输出,或者将某个作业踢出队列.所有提交的作业都在一个就绪的队列中(就绪队列为head,current为正在执行的作业).并在读取动作之后,将等待作业的优先级+1,并将其等待时间加一百ms,并挑选出下一次指向的作业(先根据最高优先级curpri挑选,相同则挑选等待时间wait_time最长的),将本次执行的作业等待时间归0,并将本次执行的作业的优先级重置为初始优先级,将其暂停执行,放入就绪队列中,并开始执行本次挑选出的作业,执行任务的切换.

12. Understand the process of job scheduling——Submit a new job (Execution results and corresponding code)： Schedueler作业调度的过程理解——提交新作业 （执行结果及代码表现)： 
    + 过程理解:每次接收到提交新作业,则按照新作业传入的参数,使用fork,exev创建一个进程,并将该进程的状态设置为READY(就绪),将其暂停(因为刚传入,还没有开始执行),并将该作业放到队列中.
    + 代码分析:此处原文件中没有bug,不需要修改.
    + 流程分析:首先先为jobinfo节点分配内存,初始化参数.接着给waitqueue分配内存,初始化参数,接下来将其接入队列(此处为head及其next).接下来使用fork和exec建立子进程并停止,主进程为新节点的pid赋值.
    + 代码表现:
``` cpp
    void do_enq(struct jobinfo *newjob, struct jobcmd enqcmd) {
    struct waitqueue *newnode, *p;
    int i = 0, pid;
    char *offset, *argvec, *q;
    char **arglist;
    sigset_t zeromask;

    sigemptyset(&zeromask);

    /* fill jobinfo struct */

    newjob = (struct jobinfo *) malloc(sizeof(struct jobinfo));
    newjob->jid = allocjid();
    newjob->defpri = enqcmd.defpri;
    newjob->curpri = enqcmd.defpri;
    newjob->ownerid = enqcmd.owner;
    newjob->state = READY;
    newjob->create_time = time(NULL);
    newjob->wait_time = 0;
    newjob->run_time = 0;
    arglist = (char **) malloc(sizeof(char *) * (enqcmd.argnum + 1));
    newjob->cmdarg = arglist;
    offset = enqcmd.data;
    argvec = enqcmd.data;
    while (i < enqcmd.argnum) {

        if (*offset == ':') {

            *(offset++) = '\0';
            q = (char *) malloc(sizeof(char)*(offset - argvec));
            strcpy(q, argvec);
            arglist[i] = q;
            i++;
            argvec = offset;

        } else{
            offset++;
        }
    }

    arglist[i] = NULL;

#ifdef DEBUG

    printf("enqcmd argnum %d\n",enqcmd.argnum);
    for (i = 0; i < enqcmd.argnum; i++){
        printf("parse enqcmd:%s\n",arglist[i]);
    }
#endif

    /* add new job to the queue */

    newnode = (struct waitqueue *) malloc(sizeof(struct waitqueue));
    newnode->next = NULL;
    newnode->job = newjob;

    if (head) {//非空
        for (p = head; p->next != NULL; p = p->next);

        p->next = newnode;
    } else{
        head = newnode;
    }
    /* create process for the job */

    if ((pid = fork()) < 0){
        error_sys("enq fork failed");
    }
    /* In child process */

    if (pid == 0) {

        newjob->pid = getpid();

        /* block the child wait for run */

        raise(SIGSTOP);

#ifdef DEBUG

        printf("begin running\n");
        for (i = 0; arglist[i] != NULL; i++){
            printf("arglist %s\n",arglist[i]);
        }
#endif

        /* dup the globalfile descriptor to stdout */
        dup2(globalfd, 1);
        // *UNREAL FIND BUG2
        if (execv(arglist[0], arglist) < 0){
            printf("exec failed\n");
        }
        exit(1);

    } else {
        newjob->pid = pid;
        printf("\nnew job: jid=%d, pid=%d\n", newjob->jid, newjob->pid);

    }
}
```

13. Understand the process of job scheduling——End of job execution (Execution results and corresponding code)： Schedueler作业调度的过程理解——作业正常执行结束 (执行结果及代码表现)
    + 正常执行结束,则其状态会改编为DONE,并从current(作业链表)被移除,并打印输出作业完成的语句.
    + 代码表现.
    + 状态更改为DONE的相关指令,出自原始版本的188-211行,其中`if (WIFEXITED(status)) `内为主要操作.

    ``` cpp
    case SIGCHLD:
        ret = waitpid(-1, &status, WNOHANG);
        if (ret == 0 || ret == -1)
            return;
        
        if (WIFEXITED(status)) {
        #ifdef DEBUG
        //printf("%d %d %d\n", ret, info->si_pid, current->job->pid);
        //do_stat();
        #endif
            current->job->state = DONE;
            printf("normal termation, exit status = %d\tjid = %d, pid = %d\n\n",
                WEXITSTATUS(status), current->job->jid, current->job->pid);

        }  else if (WIFSIGNALED(status)) {
            printf("abnormal termation, signal number = %d\tjid = %d, pid = %d\n\n",
                WTERMSIG(status), current->job->jid, current->job->pid);

        } else if (WIFSTOPPED(status)) {
            printf("child stopped, signal number = %d\tjid = %d, pid = %d\n\n",
                WSTOPSIG(status), current->job->jid, current->job->pid);
        }
        return;
    ```

    + current(作业链表)移除其的操作出自原始版本的119-132行.

    ``` cpp
    if (current && current->job->state == DONE) {           /* current job finished */
        
        /* job has been done, remove it */
        for (i = 0; (current->job->cmdarg)[i] != NULL; i++) {
            free((current->job->cmdarg)[i]);
            (current->job->cmdarg)[i] = NULL;
        }

        free(current->job->cmdarg);
        free(current->job);
        free(current);
        
        current = NULL;
    }
    ```

    + 打印作业输出完成的语句主要出自原始版本的199,200行.

    ``` cpp
    printf("normal termation, exit status = %d\tjid = %d, pid = %d\n\n",
                       WEXITSTATUS(status), current->job->jid, current->job->pid);
    ```

14. Understand the process of job scheduling——job scheduling due to Priority(Execution results and corresponding code)：Schedueler作业调度的过程理解——因为优先级和进行作业调度(执行结果及代码表现)
    + 在每隔100ms,进行的jobselect中,遍历所有作业,并挑选其中优先级最高以及等待时间最长的作业,并将其指定为下一个时间片(100ms)执行的作业.
    + 代码体现:与原始的`jobselect()`相比,有修改.主要为原文件97行开始的修改.

    ``` cpp
    if(head){
        // 有元素
        if(head->next){
            //多于一个元素
            for (prev = head, p = head; p != NULL; prev = p, p = p->next) {
                if (p->job->curpri > highest) {
                    select = p;
                    selectprev = prev;
                    highest = p->job->curpri;
                }else if(highest == p->job->curpri
                    && p->job->wait_time > select->job->wait_time){
                    select = p;
                    selectprev = prev;
                }
            }
            //*Find Bug 3.
            if(selectprev == select){
                struct waitqueue* temp = head->next;
                select = head;
                select->next=NULL;
                head = temp;
            }else{
                selectprev->next = select->next;
                select->next = NULL;
            }
        }else{
            //只有一个元素
            select = head;
            head = NULL;
        }
    }//没有元素 省去
    ```

    + 可见在判断时,先是使用curpri进行判断,随后根据wait_time进行判断,并对其他条件做了筛选.

15. Understand the process of job scheduling——Job scheduling due to time slice (Execution results and corresponding code)： Schedueler作业调度的过程理解——因为时间片而进行作业调度(执行结果及代码表现)：
    + 本次实验中,指定的时间片为100ms,(10^5μs).每个作业的每次执行的基本单位是100ms.在100ms内,作业一直在执行,除非任务自己结束,向父进程发送SIGCHLD信号.每隔100ms,作业就会暂停,重新选择下一个时间片执行的作业.
    + 代码体现:基本单位是100ms

    ``` cpp
        interval.tv_sec = 0;
        interval.tv_usec = 100000;
    ```

    出自原文件463,464行.
    其他的代码体现在上文已经出现,不再赘述.

16. Conclusion: 实验总结
    + Windows Subsystem of Linux 终究不是真正的Linux Kernel,比如这次实验中,wsl上完全无法接收到定时器发出的`SIGVTALRM`,还是需要完整的Linux环境.
    + VScode 的远程调试功能很好用,建议大家多尝试.
    + 通过这次实验我加深了命名管道的用法以及远程调试的技巧,巩固了C语言知识.