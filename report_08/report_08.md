<!--
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-05-19 17:14:20
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-08-24 11:24:23
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 -->
[Toc]
### 1
Questions:

   1. I/O control methods can be classified as (1)_________(2)__________.

   2. Each physical record on the disk has a unique address that consists of three parts: (1)______________(2)_______________(3)________________.

   3. Data READ/WRITE time = (1)_____________ + (2) ____________ +(3)____________.

   4. The metric for measuring I/O performance are (1)__________,(2)___________.

Answer:
1. I/O 控制方式大体上可以分成四种, 
    1. Programmed I/O
    2. DMA 
    3. Interrupt-Based I/O
    4. Polling.
    但是我们要填空的话就填前两个.
   
2. 磁盘的图就不放了,这个可以看作一个圆柱坐标系,所以三个元素决定一个点. 
    1. 第一个因素是Z轴H,Head identifier,决定在那个磁片的哪个方向.
    2. 第二个因素是某个磁片上的圆周,或者说半径R,用磁片上的专业词汇来说,是Track identifier
    3. 第三个是圆周上的那一段圆弧,或者说,角度θ,用磁片上的专业词汇来说是Sector identifier.
   
3. 读写磁盘三个过程
    1. 寻道时间:seek time,寻找正确的Track.
    2. 旋转等待时间:Rotational Latency,寻找正确的Sector.
    3. 读写时间:Transfer time找到了基本的sector之后进行读写.
    
4. 衡量I/O性能的自然就是延迟和带宽,(其他条件相同时)延迟越小越好,带宽越大越好.
Latency and bandwidth.
   
### 2
Question:
What are the work steps of the DMA controller? 
Please answer it and briefly describe the process of each step.

Answer:
1. device driver is told (by CPU) to transfer disk data to buffer at address X.
(cpu tell device driver).
2. device  driver tell disk controller to transfer data to buffer at address X.
(device driver tell disk controller).
3. disk controller initial DMA transfer,
(then CPU can transfer to do other things).
4. disk controller send byte by byte to DMA controller.
(then, CPU is doing other things).
5. DMA controller transfer bytes to Buffer X while increasing memory address and decrease C one by one until C is zero.
(then, CPU is still doing other things, step 4& 5 is parallel).
6. When C = 0, DMA controller interrput CPU to signal transfer completion.
(then,CPU come back to read data from address X).

### 3
Question:
Under what circumstance, the SSTF algorithm will cause starvation?

Answer:如果有一个距离当前磁道比较远的磁道在等待,
但是不断有距离当前磁道距离较小的磁道访问请求产生时,会连续访问距离较小的磁道,此时饥饿产生.

### 4
Question:
Suppose the computer system uses the disk as the following
Let a single-sided disk rotation speed be 12000r/min
each track has 100 sectors, 200 tracks in total
and the average movement time between adjacent tracks is 1 ms.

If at some point, the head is located at track 100 and moves in the direction in which the track number increases, the track number request queue is 70, 90, 30, 120, 20, 60. For each track in the request queue, a randomly distributed sector is read.

1. If the C-SCAN algorithm is used to read the six sectors,
  1. Write the track access sequence (5 points)
  2. How much time is required in total? The calculation process is required. (15 points).

2.  If using SSD, which scheduling algorithm do you think should be used, and explain why? (10 points)

Answer:
1. C-SCAN算法,始终按一个方向-也就是起始方向,磁道低->高移动.
  1. 移动顺序:先sort为20,30,60,70,90,120.
  起始100,然后120,然后读到199(而不是200,因为从0开始计数),此时回归起点:0->20->30->60->70->90.  
  所以,最终答案为100,120,199,0,20,30,60,70,90.  
  2. 总共需要的时间为寻道时间+旋转等待时间,旋转等待时间中,每分钟12000转,平均每秒200转,每转平均5ms.而需要进行的旋转有五次,所以一共30ms.如果将199到0的过程认为消耗寻道时间的话,一共消耗(199-100)+(90-0)+(199-0)=388ms,如果不认为的话,一共小号(199-100)+(90-0) =189ms.
  所以如果不认为从最高磁道到最低磁道消耗时间需要计算的话,一共消耗219ms,如果认为需要消耗的话(实际上,这个观点来自Lab10 Disk Scheduling guide的样例,在资料中C-look就计算了这个时间,并且CLook作为C-Scan的改进,很难想象花费的时间比C-Scan还多),一共需要418ms.
  PS:另一种思路是每转平均需要2.5ms,所以是388+15=403.
  fix: 正确答案为403ms.
2. 如果使用SSD,当然要使用FIFO算法,因为SSD的寻道时间几乎可以忽略不计,所以这些优化方式都没有必要进行.