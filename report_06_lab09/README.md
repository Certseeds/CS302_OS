<!--
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-05-19 20:28:03
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-05-19 20:37:57
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 -->
## OS Lab8 Memory Management Guide
1. Basic requirements of code (50+10 points)
Understand the given code and complete it. So that it can achieve basic memory
management goals:
  1. allocate a given memory space to a process (15 points)
  2. kill a process and release the memory space the process kept(15 points)
  3. show the memory usage (5 points)
  4. realize three kinds of algorithms--First fit、Best fit、worst fit (15 points)
  5. realize Buddy system (bonus, 10 points)
2. Report (50 points)
3. Things help you to do this lab:
  1. More explanation about code:
    1. My idea: Keep a list of free-block, which stores memory blocks we can use. And also keep a list of allocated-block, which stores memory blocks we have allocated. When we allocated a memory block to a process, we also need to store the pid of this process. So when we want to kill process, we can find the correct block.
  2. Two import functions you need to complete:
    1. `int allocate_mem(allocated_block *ab)` which give a block memory space
    2. `int free_mem(allocated_block *ab)` which release the memory space for this block
    
    For allocate, you should use your own algorithm to allocate memory space. That means you need to do something on the `free-block list`.
    
    For free, when we free the memory space, we need to `add the block to the freeblock list`. At this time, you also need to change the list by your own algorithm. 
  3. Some other things:
    1. `typedef pair<int, string> My_algo`; This line define my own type called My_algo. You can declare a variable of this type. The first component is an integer, the second component is a string. That means:   
        My_algo algo;  
        algo = make_pair(0, “FirstFit”);  
        printf(“%d %s\n”, algo.first, algo.second);  
    After running this code, you will get result: 0 FirstFit
    make_pair is a function, which you don’t need to write by your own.
    2. NULL. When you deal with pointers, please pay attention to NULL. That is, only
when a pointer is not NULL, it can has next element.
4. Some Test cases:
  1. (1, 2048), 2, 1, 5, (3, 1024), 3(1023), 5, (4, 1), 5, (4, 2), 233
  2. (3, 1024), 5, (3, 1), (4, 1), 5, (4, 2), 233
  3. (1, 700), 2, 2, (3, 100), (3, 200), (3, 300), (4, 2), 5, (3, 300), 5, (4, 3), 5, 233 

5. Additional explanation for code mm.cpp of report6
  1. Menu option 1 will not be executed more than once
  2. Test cases would specify an algorithm before allocating space to the process
  3. Buddy system only allocate space of 2^k units, in which k is an integer
  4. If there has no enough space for a new process, the process will not execute.
  5. After killing a process, continuous free space needs to be merged

Here is an example for case 5:  

**after (2,1),(3,200),(3,300),(3,300),(3,200),5 you should get**:

``` log
******Free Memory******
 start_addr size
 1000 24
Totaly 1 free blocks
*******Used Memory*********
 PID ProcessName start_addr size
 1 process1 0 200
 2 process2 200 300
 3 process3 500 300
 4 process4 800 200
Totaly 4 allocated blocks
```

**Then,after (4,1),(4,2),(4,4),5 you should get**:

``` log
******Free Memory******
 start_addr size
 0 500
 800 124
Totaly 4 free blocks
*******Used Memory*********
 PID ProcessName start_addr size
 3 process3 500 300
Totaly 1 allocated blocks
```

**Then,after (3,100),5 you should get:**:

``` log
******Free Memory******
 start_addr size
 0 500
 900 124
Totaly 2 free blocks
*******Used Memory*********
 PID ProcessName start_addr size
 3 process3 500 300
 5 process5 800 100
Totaly 2 allocated blocks
```