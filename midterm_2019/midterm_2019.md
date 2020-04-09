<!--
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-04-08 21:44:56
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-04-10 00:00:02
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
    int file_fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT,0666);
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
    int file_fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT,
0666);
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
