<!--
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-04-08 21:44:56
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-04-09 11:26:59
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