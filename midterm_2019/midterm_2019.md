<!--
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-04-08 21:44:56
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-09-01 23:00:37
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 -->
## Midterm of CS302_OS 2019

### P1 CPU Scheduling

#### Descipe
Consider the following single-threaded processes, and their arrival times, estimated CPU costs and their priorities (a process with a higher priority number has priority over a process with lower priority number): 

| Process | Estimated CPU Cost | Arrives | Priority |
| :--: | :--: | :--: | :--: |
| A | 4 | 1 | 1 |
| B | 1 | 2 | 2 |
| C | 2 | 4 | 3 |
| D | 3 | 5 | 4 |

#### Notes
+ Ignore context switching overhead.
+ If a process arrives at time x, they are ready to run at the beginning of
time x.
+ Highest response ratio next (HRRN) is a **non-preemptive** scheduling
algorithm. In HRRN, the next job is not that with the shorted estimated run time, but that with the highest response ratio defined as: 1+$\frac{waiting time}{Estimated CPU time}$.
+ Newly arrived processes are scheduled last for RR. When the RR quanta expires, the currently running thread is added at the end of to the ready list before any newly arriving threads.
+ The quanta for RR is 1 unit of time.
+ Priority scheduler is preemptive.
+ Break ties via priority in Shortest Remaining Time First (SRTF).
+ Average turn-around time is the average time a process takes to complete after it arrives.
finish the table

#### TODO

| Time | HRRN | FIFO/FCFS | RR | SJF | Priority |  SRJF|
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | 
| 1 |  |  |  |  |  |  |
| 2 |  |  |  |  |  |  |
| 3 |  |  |  |  |  |  |  
| 4 |  |  |  |  |  |  |  
| 5 |  |  |  |  |  |  |  
| 6 |  |  |  |  |  |  |  
| 7 |  |  |  |  |  |  |  
| 8 |  |  |  |  |  |  |  
| 9 |  |  |  |  |  |  |  
|10 |  |  |  |  |  |  |
|11 |  |  |  |  |  |  |
| Avg Turn_Around Time |  |  |  |  |  |  |

#### Answer:
PS:上标表示剩余Unit,下标表示优先级.默认Queue从左向右执行.
1. HRRN case  
PS: `estimated CPU time` is not rest CPU time, it do not change.(因为是非抢占式,执行就执行到底,所以不是零就是原值)  
PS2: Because waiting time join in the value of response ratio, so the value bigger, the process run earlier.

|Time|$P(A)$|$P(B)$|$P(C)$|$P(D)$| αβ |
|:--:|:--:|:--:|:--:|:--:|:--:|
| 1 | $1$ | Null | Null | Null | A |
| 2 | $1$ | $1$ | Null | Null | A |
| 3 | $1$ | $1+\frac{1}{1}=2$ | Null | Null | A |
| 4 | $1$ | $1+\frac{2}{1}=3$ | $1$ | Null | A |
| 5 | Null | $1+\frac{3}{1}=4$ | $1\frac{1}{2}$ | $1$ | B |
| 6 | Null | Null | $1+\frac{2}{2}=2$ | $1\frac{1}{3}$ | C |
| 7 | Null | Null | $1$ | $1\frac{2}{3}$ | C |
| 8 | Null | Null | Null | $1$ | D |
| 9 | Null | Null | Null | $1$ | D |
|10 | Null | Null | Null | $1$ | D |

Avg.Turn-Around Time = $((5-1)+(6-2)+(8-4)+(11-5))/4 = 4.5$

2. FIFO/FCFS
直接就是一串AAAABCCDDD,没有优先级划分,Avg.Turn-Around Time = $((5-1)+(6-2)+(8-4)+(11-5))/4=4.5$

3. RR 

|Time|<-Queue<|αβ|Describe(happen in begin of time)|
|:--|:--:|:--:| --:| 
| 1 |A   | A | $Null$$\rightarrow$$A^4$|
| 2 |AB  | A | $A^4$$\rightarrow$$A^3$$\rightarrow$$A^3B^1$|
| 3 |BA  | B | $A^3B^1$$\rightarrow$$B^1A^2$ |
| 4 |AC  | A | $B^1A^2$$\rightarrow$$A^2$$\rightarrow$$A^2C^2$ | 
| 5 |CAD | C | $A^2C^2$$\rightarrow$$C^2A^1$$\rightarrow$$C^2A^1D^3$ |
| 6 |ADC | A | $C^2A^1D^3$$\rightarrow$$A^1D^3C^1$ |
| 7 |DC  | D | $A^1D^3C^1$$\rightarrow$$D^3C^1$|
| 8 |CD  | C | $D^3C^1$$\rightarrow$$C^1D^2$ |
| 9 |D   | D | $C^1D^2$$\rightarrow$$D^2$|
|10 |D   | D | $D^2$$\rightarrow$$D^1$|
|11 |Null| Null| $D^1$$\rightarrow$$Null$| 

<del>
错误的解释:看上去顺序应该是,每次先把进来的放进Queue最后,然后再把上一次的进程放到Queue最后,然后把Queue第一个推出去当作本时刻的动作.
</del></br>
正确的解析:按照

> When the RR quanta expires, the currently running thread is added at the end of to the ready list **before any** newly arriving threads.

的说法,1 Unit开始时,Queue头弹出,然后(如果还有时间就)加回Queue尾,然后再加入新Thread.  
写法就用上标表示剩余时间,每次先更新队列,然后踢出耗尽时间的,随后加入新Thread.  
Avg.Turn-Around Time = $((7-1)+(4-2)+(9-4)+(11-5))/4=4.75$

4. SJF (似乎从名字就能判断是非抢占的,因为抢占的被称为SRJF)
因为是非抢占的,所以

|Time|Describe(happen in begin of time)|
|:--| --:| 
|1 | $Null$$\rightarrow$$A^4$|
|1->5 |$A^4$$\rightarrow$$Null$$\rightarrow$$B^1C^2D^3$|
|5->6 |$B^1C^2D^3$$\rightarrow$$C^2D^3$ |
|6->8 |$C^2D^3$$\rightarrow$$D^3$ |
|8->11 |$D^3$$\rightarrow$$Null$ |

直接将执行阶段的请求阻塞,然后每执行完一个集中处理一次.
顺序就是ABCD.  
Avg.Turn-Around Time = $((5-1)+(6-2)+(8-4)+(11-5))/4=4.5$

5. Proority 纯优先级,抢占式.
每进一个Thread先判断优先级更新,之后更新queue,逐个执行.  
PS:也是优先级越高,执行越向前.

|Time|Queue(after update)|
|:--| --:|
|1|$A_1$|
|2|$B_2^1A_1^3$|
|3|$A_1^3$|
|4|$C_4^2A_1^2$|
|5|$C_4^1D_3^3A_1^2$|
|6|$D_3^3A_1^2$|
|9|$A_1^2$|
|11|$Null$|

执行顺序,ABACCDDDAA
Avg.Turn-around Time:$((11-1)+(3-2)+(6-4)+(9-5))/4=4.25$
6. SRJF 抢占式最短时间算法
每次有新来的Thread就判断一下,之后更新queue,逐个执行.

|Time|αβ|Describe(happen in begin of time)|
|:--| :--:|--: |
|1 | A |$Null$$\rightarrow$$A^4$|
|2 | B | $A^4$$\rightarrow$$B^1A^3$|
|3 | A | $B^1A^3$$\rightarrow$$A^3$|
|4 | C | $A^3$$\rightarrow$$C^2A^2$|
|5 | C | $C^2A^2$$\rightarrow$$C^1A^2D^3$|
|6 | A | $C^1A^2D^3$$\rightarrow$$A^2D^3$|
|7 | A | $A^2D^3$$\rightarrow$$A^1D^3$|
|8 | D | $A^1D^3$$\rightarrow$$D^3$|
|9 | D | $D^3$$\rightarrow$$D^2$|
|10 | D | $D^2$$\rightarrow$$D^1$|
|11 | Null | $D^1$$\rightarrow$$Null$|

执行顺序,ABACCAADDD.  
Avg.Turn-around Time:  
$((8-1)+(3-2)+(6-4)+(11-5))/4=4$.

7. Result:

| Time | HRRN | FIFO/FCFS | RR | SJF | Priority |  SRJF|
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | 
| 1 | A | A | A | A | A | A |
| 2 | A | A | A | A | B | B |
| 3 | A | A | B | A | A | A |  
| 4 | A | A | A | A | C | C |  
| 5 | B | B | C | B | C | C |  
| 6 | C | C | A | C | D | A |  
| 7 | C | C | D | C | D | A |  
| 8 | D | D | C | D | D | D |  
| 9 | D | D | D | D | A | D |  
|10 | D | D | D | D | A | D |
| Avg Turn_Around Time | 4.5 | 4.5 | 4.75 | 4.5 | 4.25 | 4 |

### P2 MultiThreading

#### Description
Consider the following two threads, to be run concurrently in a shared memory
(all variables are shared between the two threads):
``` cpp
Thread 1
for (i=0; i<5; i++) {
    x = x + 2;
} 
```
``` cpp
Thread 2
for (j=0; j<5; j++) {
    x = x + 3;
} 
```
Assume a single-processor system, that load and store are atomic, that x is
initialized to 0 before either thread starts, and that x must be loaded into a
register before being incremented (and stored back to memory afterwards). The
following questions consider the final value of x after both threads have
completed. 
#### Analysis
1. 两个线程在同一个进程内,共享同一个变量,所有变量共享.
2. 单处理器系统,一次只能执行一条汇编语句.
3. 每个线程开启的时候都会把x初始化成0,相当于for前面+了一句x=0;
4. 
>x must be loaded into a
register before being incremented (and stored back to memory afterwards)</br>

这一句应该是指,x+=${value};这一条语句对应的不是一条汇编,而应该是3条,或者说三个原子操作.
``` mipsasm
# MIPS asm
lw ${r0},${x_address}
add ${r0},${r0},${value}
sw ${r0},${x_address}
```
5. 
这三个原子操作对单个线程的顺序是确定的,但是对两个线程之间执行的顺序是不确定的.
有可能是1_lw,1_add,2_lw,1_sw,2_add,2_sw.也就是说除非两个的lw在sw之后,否则会导致覆盖的问题.  
接下来就容易分析了.

#### Question and answers
##### **1**. Give a concise proof why x≤25 when both threads have completed.<br>**2**. Give a concise proof why x≠2 when both threads have completed.   
Answer:  
如果一个Thread x的一次加法没有被覆盖,那我们计Thread x为一次成功.
Thread 1,Thread 2的成功数量分别记为i,j.  
$$
\left\{
    \begin{array}{l}
            x = 2i+3j (x\in N^+)\\
            0 \leq i \leq 5 \\
            0 \leq j \leq 5 \\
            i + j \geq 5
        \end{array}
\right.
$$
1. 首先第一个等式很好理解,x的值最后就等于没有被覆盖的+2值+没有被覆盖的+3值.
2. 在最好情况下,Thread的1,2的三条原子指令都没有任何交集,则i/j可以取到5.当最坏的情况,1每次都被遮蔽,则i取0,同理,j也可以取0.
3. 我们将第k对Thread1,Thread2的三条源自指令编为一组,并忽略其中间的所有其他指令.无论怎么组合,这一组6个汇编指令的指令组也可以实现+2/+3/+5,或者说至少可以实现一个.所以有几个指令组,i+j就大于等于几.
4. 担心很多组指令混到一起的话,首先要考虑到Thread内部是顺序执行,lw,add,sw的顺序不会变化,其次,开头的一定是lw,结尾一定是sw.而且只会被覆盖,而不是消失.
5. 最后线性规划一下,轻易的出$x\in[10,25]$.
6. 为什么可以排除其等于2?要x=2,其只能是x在最后一次+2时,lw得到0,sw存储了2.而且后面没有任何一个x+=3指令.但是如果x+3没有在x+2后面出现,就只能在其前面出现,但是lw取得了0,所以就不能有x+=3被sw进去,只能是被x+=2覆盖.但这和x+=2,lw得到0又矛盾起来.综上所描述,x不能为2.(这个结论在x+=2,x+=3的循环只有两次时也可以使用,结论是只有12个原子操作时,x也不会是2,3,反面又验证了$i + j \geq 5$的正确性.)

同上

##### 3. Suppose we replace ‘x = x+3’ in Thread B with an atomic double increment operation atomicIncr2(x) that cannot be preempted while being executed. What are all the possible final values of x? Explain. 
Answer:
atomicIncr2(x)相当于将三条汇编指令转化为一条,成为了一个原子操作.
首先,如果没有任何混杂的情况下,x=5*2+5*2=20.
然后,在这种状态下,只有Thread1有可能将Thread2的结果遮蔽,Thread2无法遮蔽Thread1,全部遮蔽则为10,每少遮蔽一个则多2,所以10,12,14,16,18,20都可以取.

##### 4.  What needs to be saved and restored on a context switch between two threads in the same process? What if the two threads are in different processes? Be explicit. 
Answer: 在相同的进程中,上下文切换需要的只有Thread自己的线程块,包括PC,寄存器,栈指针等等.
在不同的进程之间的Thread之间的切换就是不同进程的切换,需要保存PCB,包括PC,寄存器,文件状态,内存分页表(Page table)等处理信息,进程优先级,等待时间,等调度信息以及进程pid,ppid,进程组等等进程信息.

##### 5. Under what circumstances can a multithreaded program complete more quickly than a non-multithreaded program? Keep in mind that multithreading has context-switch overhead associated with it. 
Answer:
1. 首先是问题易于切割,而且切分出来的数据的交叉较小,线程之间处理的数据较为独立的程序.
2. 其次是IO操作耗时较高的程序,可以在其他进程运行时休眠等待,提高资源利用率.或者说,多个进程利用资源的方向不同,可以使用多线程提高利用率.

### P3 Run code on paper.
#### Question 1 and answer.
##### Question 1
What is the output of this program? You can assume that no syscalls fail and
that the child’s PID is 123. Fill in the following table with your prediction of the
output:
``` cpp
int main() {
    printf("Starting main\n");
    int file_fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, 0666);
    dup2(file_fd, STDOUT_FILENO);
    pid_t child_pid = fork();
    if (child_pid != 0) {
        wait(NULL);
        printf("CS302 SUSTech, in parent\n");
    } else {
        printf("CS302 SUSTech, in child\n");
    } 
    printf("Ending main: %d\n", child_pid);
} 
```
##### Answer for question 1:  
Standard out:
``` log
Starting main
```
test.txt
``` log
CS302 SUSTech, in child
Ending main: 123
CS302 SUSTech, in parent
Ending main: 0
```
Analysis:
第一句没有疑问,然后dup2将file_fd复制到STDOUT_FILENO内,使得对Standard out的输出对外指向test.txt.然后父进程阻塞,子进程输出,父进程wait回来,输出,结果就是这样.

#### Question 2 and answer.
##### Question 2
Next, assume that we have altered this code as follows:
``` cpp
    int main() {
    printf("Starting main\n");
    int file_fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, 0666);
    int new_fd = dup(STDOUT_FILENO);
    dup2(file_fd, STDOUT_FILENO);
    pid_t child_pid = fork();
    if (child_pid != 0) {
        wait(NULL);
        printf("CS302 SUSTech, in parent \n");
    } else {
        dup2(new_fd, STDOUT_FILENO);
        printf("CS302 SUSTech, in child \n");
    }
    printf("Ending main: %d\n", child_pid);
    }
```
What is the output this time? Fill in the following table with your prediction of
the output
##### Answer for question 2
Standard out:
``` log
Starting main
CS302 SUSTech, in child
Ending main: 123
```
test.txt
``` log
CS302 SUSTech, in parent
Ending main: 0
```
Analysis:
第一句没有疑问,父进程内,new_fd复制了stdout,然后dup2将file_fd复制到stdout内,使得父进程的输出被导入stdout.然而在子进程内部,又使用dup2将stdout给复制了回去.所以会输出到stdout中.因此,第一句stdout,然后stdout子进程,随后test.txt父进程.

#### Question 3 and Answer
##### Question 3
Consider the following fragment of a program (which is missing lines of code). Fill in the blanks in the code to ensure that the output of this program is always the following two lines in the following order (under all interleavings or schedules):
``` log
Val = 0
Val = 1
```
No more than one function call (or system call) per blank! Your solution is not allowed to make assignments to the "val" variable. Also, no use of printf() or
other print statements!
``` cpp
void apple(){
    pid_t oval = __________;
    kill(oval,SIGTEST);
}
void orange(int i){
    val = 1;
}
int val = 0;
int main(){
    pid_t pid = fork();
    _____________;
    if(0 == pid){
        ___________;
    }else{
        ___________;
    }
    printf("val=%d\n",val);
}
```
##### Answer of question 3
1. 首先我们分析,按顺序指定,第一句就fork出了与1个子进程.之后既然钦定了 
> "not allowed to make assignment to the val variable"

所以能够调用的也就是apple(),orange(),等函数以及库函数.  
2. 第一想法是,首先给父进程上一个wait.让子进程调用orange,都不用管另外两个空白,但是这样是输出1,0.
3. 所以,肯定是要做点什么,想法是让子进程先跑,父进程wait,然后让子进程输出0,父进程输出1.而且不能在`2`处调用orange,那样就没有减一的办法了.所以只能是令子进程通知父进程,父进程调用orange.子进程通知父进程用的自然就是`apple()`.  
4. 所以现在的任务明确了  
    + apple()内要通知父进程.   
    + `2`要使线程收到信号调用orange.  
    + 子进程调用`apple()`  
    + 父进程`wait(pid)`等待. 
5. apple内通知的部分已经完成,要获取到父进程pid,正好可以用`getppid()`  
6. 而第二个空白,使用`signal(int signum, sighandler_t handler)`的方式,第一个参数设置为`SIGTEST`,第二个参数设置成`orange`.接收到`SIGTEST`就激发`orange`  
7. 这样,答案就出来了

``` cpp
void apple(){
    pid_t oval = getppid();
    kill(oval,SIGTEST);
}
void orange(int i){
    val = 1;
}
int val = 0;
int main(){
    pid_t pid = fork();
    signal(SIGTEST,orange);
    if(0 == pid){
        apple();
    }else{
        wait(pid);
    }
    printf("val=%d\n",val);
}
```
**Analysis**  
这里的最后两个空白应该可以比较容易的填出来,但是前两个难度比较大,主要是在于不容易想起`signal(int signum, sighandler_t handler)`这个函数以及`getppid()`这个函数正确的名字.

#### Question 4 and answer.
##### Question 4
1. If a child process sends a SIGKILL signal to its parent, what happens to the parent process and the child process? 
2. Can the parent prevent this from
happening?

##### answer for question 4
1. 
   + first, if the parent process(the process that fork the subprocess) is died before it's child, then the parent of the child is `init`. Then if the child kill it's parent, which is `init` now, it will happen nothing, because `init` do not recieve any siganl.Then 
   + <del>if the parent use `sighandler_t signal(int signum, sighandler_t handler)` to handle `SIGKILL`,then it can happen anything because the handle function so unpredictable.</del>
   + **`SIGKILL` signal can not be handle of ignore**, so once recieve it, the parent will dead, then the child will be a Orphan Process, which means the child-process's parent is `init`. 
2. 
   + if the prevent is prevent become `Oraphan Process`, then there have no way, because whether happen , subprocess should have a parent process, it must be adpated by `init`.
   + if the prevent is aim to being kill by child, it can kill itself before killed by child.


#### Question 5 and answer.
##### Question 5
Consider the following scenario. A process forks a child process and
the parent process waits on it. Then, the child exits normally and the parent is unblocked. Finally, the parent makes another wait call on the child process.
What happens to this last wait call and to the parent process?   

##### answer for question 5
1. the last wait call will stay there and do not change, it will always wait another process send signal to it.the parent will stay in the step and do nothing.

#### Question 6 and answer.
##### Question 6
Why do we switch from the user’s stack to a kernel stack when we enter the kernel (e.g. for a system call)? Why do we associate a unique kernel stack for each user thread? 

##### Answer for Question 6
1. All user stack is unbelievable ,so OS use another Kernal stack.
2. if is each to each, it cost too much time to store and load message.

### P4  Short answers,answer the question within 6 sentences or less
#### Question 1 and answer
##### Question 1
What is the difference between "Parallelism"(并行) and "Concurrent"(并发) in job
scheduling.
##### answer for question 1
1. "Parallelism" can run multiply program on a device(hardware support, usually 1+ core) at the same time.
2. "Concurrent" means multiply program run not devide one by one, their run order can be satisfy and load/store. means program can stay doing at same time(also doing, maybe be suspend).

#### Question 2 and answer
##### Question 2
Please draw the life cycle of process and thread, then compare the different of process and thread.

##### answer for question 2
对process:
五个状态,fork,killed(zombie?),Ready(waiting),Running,wait(un-interruptible)/blocked(interruptible)

``` flow
fork=>start: fork()
killed=>end: killed(zombie?)
ready=>operation: Ready
running=>operation: Running
judgement=>condition: Finish?
wait=>operation: wait(un-interruptible)/blocked(interruptible)
fork->ready->running->judgement
judgement(yes)->killed(left)
judgement(no)->wait(right)->ready
```
对Thread.
``` flow
init=>start: init()
finish=>end: finish
ready=>operation: Ready
running=>operation: Running
judgement=>condition: Finish?
wait=>operation: wait
init(right)->ready(right)->running(right)->judgement(right)
judgement(yes)->finish(right)
judgement(no,right)->wait(right)->ready(right)
```
compare  

|Part|Process|Thread|
|:--|:--:|:--:|
|Basic|Smallest part of scheduling resource|Smallest part of CPU schdule,Basic part that can run alone |
|memory|different process do not share memory|different thread that belong to same process shared memory.|
|Address sapce|have itself's|dont have itself's address space|
|Content switch message|PCB(TCBs,Process message, schedule messages),more complex|TCB(just have PC,register, stack pointer, etc)|
|Resource requirement|More| Less|

#### Question 3 and answer
##### Question 3
Please describe the actions in operating system when “fork()” function
executed.

##### Answer for Qustion3
1. fork先创建一个子进程
2. 复制父进程的大部分运行信息到新的进程中
3. 复制父进程的PCB(进程信息,调度信息)到新的进程中.
4. 对子进程的PCB中的一些子项进行处理,比如pid,ppid,parent,running time,waiting time等

#### Question 4 and answer
##### Question 4
Please list the storage unit with its access latency in a modern commodity personal computer (as many as possible), and analyze the underlying trade-off strategy in current storage system.

##### Answer for Question 4
|Level|Time|
|:--|--:|
|L1|1ns|
|L2|5ns|
|L3|15ns|
|Memory|50-100ns|
|Disk|10^5ns|

#### Questioin5 and answer
##### Question 5
Please give the clear definition of user time, system time and real time,
then give two concrete examples to show 
1. real time < user time + system
time.   
2. real time > user time + system time.

##### Answer for Question 5.

|Time|Defination|
| :-- | --: |
|User Time|CPU time that cost on user space|
|System time|CPU time that cost on kernel space|
|Real time|$start time-finish time$|

2. real time < user time+system time  
Answer:
if the process have multiply core and this process have mutilply thread, then it can do it at multiply core at same time.
3. real time > user time + system time  
Answer:
if the process have IO time or sleep and wait child process.<del>delay, it still run</del> 

### P5 Multiple Choices 选择题 <del>鬼知道到底选几个</del>

#### Question 1
##### Question
In which condition(s), a new process will be created in Linux?

|Option| Content|
|:--|--:|
|A|User login by remote ssh|
|B|execute `ls` on a shell|
|C|call `exec*()` in a program|
|D|call `pthread_create()` in a program|

##### Answer
1. 排除法,首先排除`exec*()`,只是进程的转变
2. 然后排除`pthread_create()`,再多线程也是一个进程,不会有新的进程.
3. 然后`ls`肯定是一个新进程,前面的report内有用`exec*()`调用ls.
4. 用户登录,为`init`进程创造出来的专用login进程等待登录,然后login创造shell进程.   
所以选择**AB**

#### Question 2
##### Question
Which of follows is(are) not shared by different thread in the same process?

|Option| Content|
|:--|-:|
|A|PID|
|B|File descriptor|
|C|Execution Stack|
|D|Progarm Conter(PC)|

##### Answer
1. PID是进程间的区别,同进程的线程间没有区别
2. File desciptor也是线程之间共享,都可以访问的,进程间不会共享.
3. Exection Stack,执行栈,相当于代码运行的所有上下文信息,比如上文的函数变量,结构等等.显然是线程之间也得保密的.
4. PC寄存器信息也是需要每个进程都保存的.  
所以选择:**CD**

#### Question 3
##### Question
Which threading model(s) is(are) not exist?(<del>再次显露根本就不告诉你选几个的奇妙题目</del>)

|Option| Content|
|:--|-:|
|A|One to many|
|B|Many to Many|
|C|Many to one|
|D|One to one|

##### Answer
1. 这里的Thread model不是指的process对thread的关系,而是user space 的process对kernel space的process.
2. 然后这就是个前面的是User space,后面的是Kernel space.BCD都是存在的,但是A,一个User process对应多个kernel process没啥用,浪费资源.所以不会出现.  
所以选择:**A**

#### Question 4
##### Question
Which system calls are employed to implement a C libary call `system()`?

|Option| Content|
|:--|-:|
|A|`fork()`|
|B|`exec*()`|
|C|`wait()`|
|D|`pipe()`|

##### Answer
`fork()`+`exec*()`+`wait()` == `system()`(即答)  
所以选择:**ABC**

#### Question 5
##### Question
Which will cause model transfer?

|Option| Content|
|:--|-:|
|A| system call|
|B| exception|
|C| function call|
|D| interrupt|

##### Answer
没什么好说的,model transfer有三个类型,system call,interrupt and (trap or exception)  
所以选择:**ABD**

#### Question 6
##### Question
Which is the proper time to reduce the priority of process?

|Option| Content|
|:--|-:|
|A|  the time slice of the process is used up.|
|B|  the process just finished I/O and enter into ready queue|
|C| the process stays in ready queue for a long time.|
|D| the state of the process changes from ready to running.|

##### Answer
1. priority越高,执行越向前,所以reduce priority of process 是降低优先级.
2. 等待时间越长,优先级越高,排除C.
3. 完成了IO,进入了ready queue,这时应该将其优先级调高,或者说不能降低.排除B.
4. 显然,正在执行的process的优先级最高,priority也应该最大.排除D
5. process时间片用完了,所以就应该从最高点下来,被砍.  
所以选择:**A**

#### Question 7
##### Question
In following options, () is the scheduling algorithm that satisfies Shortest Job First(SJF) and will not cause starvation.

|Option| Content|
|:--|-:|
|A| First Come First Serve(FCFS)|
|B| Highest Response Ratio Next(HRRN)|
|C| Round-robin |
|D|  Non-preemptive SJF|

##### Answer
1. FCFS/FIFO,这个根本就没有考虑什么SJF,完全就是先来后到,queue结构,不满足1,满足2.排除
2. HRRN,由于有waittime参与,不会导致starvation,而且也有CPU时间参与,都考虑到了.
3. Round-robin,只是一个使用了抢占式的FIFO,不会cause starvation,但是和SJF无关.排除.
4. 非抢占式SJF,由于可能有不断地小process进入,所以可能导致starvation.排除.  
所以选择:**B**

#### Question 8
##### Question
Which is executed during user space?

|Option| Content|
|:--|-:|
|A| command line interpreter (shell)|
|B| page fault handler|
|C| process scheduler|
|D| clock interrupt handler|
|E| I/O operation|

##### Answer
1. shell只是用户态的一个proces.
2. Page falut有关的都是内核态.
3. process scheduler也都是内核态.
4. clock interrput也都是内核态.
5. I/O也都是内核态.  
所以选择:**A**

#### Question 9
##### Question
Which does not happen in user space?

|Option| Content|
|:--|-:|
|A| system call|
|B| external interrupt|
|C| context switch|
|D| page fault|

##### Answer
1. system call 显然是在内核态.但是是用户态调用的,不清楚.
2. external interrupt,外部中断显然不发生在内核态.
3. context switch发生在内核态.
4. page fault,显然只在内核态.  
所以选择:**Unknown**  
描述很神秘,不知道发生指的是调用,还是出现,还是指操作的状态.

#### Question 10
##### Question
Both interrupt handling and subroutine calling need protection by stack pushing. Which is the content that interrupt handling has to save but subroutine calling not? 

|Option| Content|
|:--|-:|
|A| PC|
|B| flag register|
|C| data register|
|D| address register|
|E| PSW resister|

##### Answer
中断需要存储,子调用不需要存储.
$flag register == PSW register$:MIPS没有,但是X86/64和arm都有,表示进位之类的.
data resister:ALU需要的直接data.
address register:就像指针一样,存储memory地址.
1. PC必须要存储.否则回来就不知道干什么了.
2. data register&&address register必须存储,但是flag register在arm手册/x86/64手册中并没有明写要存储.
3. 但是  
所以选择:**BE**(最好用排除法,排除ACD)

#### Question 11
##### Question
If a user process read data from certain disk file by read() system call, then which of the following statement(s) is correct? 
1. If the data of file does not exist in main memory, then this process will change to waiting state.
2. Invoking read() system call will lead CPU change from user space to kernel space.
3. The argument of read() should include file name
4. The argument of read() should include file descriptor

|Option| Content|
|:--|-:|
|A| 1&2|
|B| &|
|C| &|
|D| 1&2&3|

##### Answer
1. 是显然的I/O等待,没有问题.
2. read()是一个system call,所以会发生转换.
3. read()应该是先通过` of read(const char* filename,int flags)`,将文件绑定到一个`file desciptor`上,然后再`ssize_t read(int fd,void* buf,size_t count)`,所以3是错误的,4是正确的.
4. 答案是$1+2$  
所以选择:**A**

#### Question 12
##### Question
In a multiprogramming system, only two jobs P1 and P2 exist. The arrival
time of P2 is 5ms later than that of P1, and their orders of CPU computation and I/O operation are shown as follows:
1. P1: Computation 60ms, I/O 80m, Computation 20ms
2. P2: Computation 120ms, I/O40ms, Computation 40ms  

If not considering scheduling and switch time，then the least time to finish both jobs is ()

|Option| Content|
|:--|-:|
|A| 240ms|
|B| 260ms|
|C| 340ms|
|D| 360ms|

##### Answer
1. 首先排除360ms,360ms那是没有任何并发处理,只管串行的结果.排除D.
2. 其次,将80ms的P1等待时间安排到P2运行时,结果直接跨到了$360-80=280ms$,排除了C.
3. 然后,如果I/O操作都可以安排成遮蔽的话,那就可以240ms,但是这真的可以吗?首先先安排P1的IO时间,需要80ms,只能在P2のIO前面才能同时运行,因为P2のIO后只有40ms.但是P2的IO同样必须在P1的IO前面才能,也是因为P1のIO后的时间小于IO时间,形成了死锁.所以没有办法到达240$ms$.
4. 现在给出一种260ms的方式  
$P1_{5},P2_{40},P1_{55},P2_{80},P1_{20},P2_{60}$
所以选择:**B**

PS:13 is Null

#### Question 14
##### Question
In a single-processor multi-process system, if there are several ready processes, then the wrong statement about process scheduling is ()

|Option| Content|
|:--|-:|
|A| process scheduling can execute when a process terminates|
|B| process scheduling can execute when a process creates|
|C| process scheduling can execute when a process is in critical section|
|D| process scheduling can execute when system call finished and system returns to user space|

##### Answer
1. 单处理器,多进程,可以并发,不能并行. 每当进程出现了新状态/状态转换,process schduling都会进行操作.
2. 而critical section不是任何关键时间节点,只是"重要时刻/关键部分",不会发生process schduling.  
<del>所以选择:**C**</del>  
真正的正确选项:没有正确选项.

#### Question 15
##### Question
For the statements about thread and process, which one is correct?

|Option| Content|
|:--|-:|
|A| No matter the system supports threads or not, process is the basic unit of resource allocation.|
|B| Thread is the basic unit of resource allocation and process is the basic unit of scheduling.|
|C| the switches of user-level and kernel-level threads all need the support of kernel.|
|D| every thread in the same process has distinct address space.|

##### Answer
1. 进程是资源调度的最小单位,正确.
2. 线程是任务分配的最小单位,这里面弄反了,错误.
3. switch of levels,包括user-to-user和user-to-kernel,前者和kernel无关,后者才与kernel有关,错误.
4. 地址空间只有不同process才不同,错误.
所以选择:**A**


#### Question 16
##### Question
Which will lead a user process switch from user space to kernel space?
1. division by zero
2. sin() function call 
3. read() system call

|Option| Content|
|:--|-:|
|A| 1&2|
|B| 1&3|
|C| 2&3|
|D| 1&2&3|

##### Answer
1. 第一个说的很不清楚,完全可以运算符重载直接捕捉住所有division zero的情况.那就变成了function call.可能是exception.
2. function call不会进入内核.
3. read(),system call会进入内核.
4. 综上,排除2,直接选B.
所以选择:**B**

#### Question 17
##### Question
After computer boosting, Operating System will be finally loaded to ()

|Option| Content|
|:--|-:|
|A| BIOS|
|B| ROM|
|C| Disk|
|D| RAM|

##### Answer
这里说的都是硬件.
1. BIOS是`basic input output system`,不是硬件,硬件是BIOS存储芯片.
2. ROM,`Read only memory`,实际生活中倾向于使用其描述存放固件/OS的存储设备.(虽然后来还是可以擦写)
3. Disk,速度太慢,见上文描述,与内存有10^3差别.
4. RAM,`Random-Access Memory`,随机存储器,内存,存放系统的位置.
一般情况下,BIOS存放在ROM(另有芯片存储)内,OS被从Disk的ROM部分读取到RAM中.   
所以选择:**D**

#### Question 18
##### Question
A system is running three processes P1, P2 and P3, the time ratios of CPU computation and I/O are shown as follows

|process|CPU Time|I/O Time|
|:--|:--:|--:|
|P1|90%|10%|
|P2|50%|50%|
|P3|15%|85%|

To improve the efficiency of resource usage, which priority setting for processes is more reasonable?

|Option| Content|
|:--|-:|
|A| P1>P2>P3|
|B| P3>P2>P1|
|C| P2>P1=P3|
|D| P1>P2=P3|

##### Answer
首先,我们将Resource 看为CPU时间.
1. 以SJF的角度来看,时间越短的越应该向前,这样剩下的高CPU利用率的正好和它互补,高CPU运行时后台高I/O时间,低CPU的后台是低I/O时间.而且进程等待时间也较短.倘若放I/O高的在后面,I/O时有可能没有其他进程,总时间就了一些.
2. 倘若认为Resource是I/O时间,那就反过来.(?存疑) //TODO
所以选择:**A**

#### Question 19
##### Question
Suppose the following instructions have been loaded to instruction registers, which instruction cannot lead CPU to switch from user space to kernel space?

|Option| Content|
|:--|-:|
|A| DIV RO,R1|
|B| INT n(软中断,不是声明值)|
|C| NOT R0|
|D| MOV R0,addr(指针操作)|

##### Answer
1. 除零会导致exception,会.
2. 软中断会进入kernel space.
3. NOT R0只有运算,不会进入kernel.
4. MOV r0,addr使用指针,操作了内存,会.
所以选择:**C**

#### Question 20
##### Question
Which will lead the state of a process to change from running to ready?

|Option| Content|
|:--|-:|
|A| execute wait()|
|B| fail to malloc()|
|C| start I/O device|
|D| preempt by high priority process|
|E| receive SIGSTOP signal|

##### Answer
1. 执行wait(),不会变成ready,只会变成wait/blocked状态.
2. file to malloc(),失败后会wait/blocked.
3. 请求I/O开始,会变成wait/blocked.
4. 从正在运行,插入了一个,那么刚才运行的会变成ready,存起来等着跑.
5. 接收到`SIGSTOP`信号,会从ready/running状态变成wait/blocked.
所以选择:**D**

NEED FIX:1 5 7 9 16 19.

#### Question 21
##### Question
Read following code and select all possible output.
``` cpp
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
int a = 0;
void my_thread(void *arg){
    a++;
    printf("%c%d",(char*)arg,a);
}
int main(){
    pthread_t thread[2];
    int rc = fork();
    if(0 == rc){
        pthread_create(&thread[0],NULL,my_thread,'A');
        pthread_join(thread[0],NULL);
        pthread_create(&thread[1],NULL,my_thread,'B');
    }else{
        wait(rc);
        pthread_create(&thread[0],NULL,my_thread,'C');
        pthread_join(thread[0],NULL);
        pthread_create(&thread[1],NULL,my_thread,'D');
    }
    pthread_exit(NULL);// delete this sentence.
}
```
|Option| Content|
|:--|-:|
|A| A1B2C3D4|
|B| C1D2A3B4|
|C| C1D2A1B2|
|D| A1B2C1D2|

##### Answer
1. 首先,fork出来的是子进程,变量是不相同的,所以排除所有$>2$的选项.
2. 然后,显然是子进程先行,所以是$A1B2C1D2$
所以选择:**D**

#### Question 22
##### Question
Which statement(s) is/are true?

|Option| Content|
|:--|-:|
|A| Job queue stores all processes which is ready to run.|
|B| CPU scheduler can control the degree of multiprogramming.|
|C| Job scheduler uses more frequent than CPU scheduler.|
|D| Swapping scheduler balance the mix of IO bound and CPU bound process.|

##### Answer
1. Job queue − This queue keeps all the processes in the system.
2. Job queue control the degree of multiprogramming,CPU scheduler provided lesser control over degree of multiprogramming.
3. Job scheduler is more high level than cpu scheduler, so it is less frequent.  
所以选择:**D**

#### Question 22
##### Question

|Option| Content|
|:--|-:|
|A| |
|B| |
|C| |
|D| |

##### Answer

所以选择:**NULL**

