<!--
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-04-23 10:26:20
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-04-23 13:23:57
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 -->
0. 
    1. 内碎片:分配出去了,但是没有被使用(分配了8,只用了7)
    2. 外碎片: 空闲空闲太小,用不了的碎片.
1. What is Uniprogramming, What is the shortcoming of Uniprogramming:
    1. UNiprogramming 是指内存中除了OS之外,一个时间内只有单独一个程序存在,因此,同一时间也只能运行一个程序.
    2. 缺点是效率非常低(因为同一时间内存中只能存在一个程序,如果需要运行多个程序需要反复进行读写内存),功能性也非常弱,因为没有办法真正的同时运行多个程序.

2. What is Multiprogramming,What is the shortcoming of Multiprogramming?
    1. Multiprogramming是指在内存中,除了OS之外,可以同时存在多个程序,因此可以在进程Wait(比如访问IO设备等)时,可以从READY队列中选择另外一个程序并执行.
    2. 内存分配问题变得更复杂,需要考虑进程之间内存隔离,分页等等问题,会产生内碎片与外碎片.

3. What is the segmentation mechanism and its advantages & disadvantages:
    1. 分段机制将内存分成长度不定的段,并将每一段中的虚拟地址空间映射到物理地址空间(每一段中对应的物理地址是连续的).
    2. 分段机制的优点:将地址空间隔离,进程之间不会互相影响;运行时地址较为确定,方便使用.
    3. 缺点:由于段的长度不确定,所以会产生碎片.

4. What is the paging mechanism and its advantages & disadvantages:
    1. 内存分页将内存分为很多大小相同的帧,进程被分为与帧相同大小的页.要将进程装入内存中,就将进程所有的页装入内存.虽然进程中页内部的虚拟地址所对应的物理地址是连续的,但是对进程分配的帧之间,只有虚拟地址是连续的,帧和帧之间的物理地址不要求连续.同时维护一个分页表,通过分页表来维护虚拟地址和物理地址之间的关系.
    2. 优点:不会产生外碎片,内碎片只会在进程的最后一页出现.更高效的利用内存,进程可以利用不连续的内存.
    3. 缺点:较为复杂,需要另外使用页表存储虚拟地址和物理地址之间的关系.

5. How to reduce the occurrence of internal fragmentation when allocating memory? Briefly explain why this method works.
    1. 使用分页的方式,使得内碎片只会在进程的最后一页出现;使用动态分区,使得空间正好适合进程(当然,这种方式会使得外碎片产生);设定阈值,限制每次分配空间时内碎片的量;使用Best Fit的方式,尽量分配最适合的块给进程.
    2. 分页的方式可以使得内碎片只在进程的最后一页产生,相对来说限制了内碎片的大小和出现位置,较为方便管理.(虽然每次都会出现,但是有了限制).
    3. 动态分区则完全使内碎片不存在,因为每次分配的空间都正好适合进程.
    4. 阈值可以使每次分配时的冗余空间得到控制.
    5. Best Fit的方式和阈值配合,可以使每次分配的冗余空间尽量小.
    
6. How to reduce the occurrence of external fragmentation when allocating memory? Briefly explain why this method works.
    1. 使用分页的方式;使用Worst FIt分配算法;使用压缩手段.
    2. 分页时,每一页都会被分配给进程,所以完全没有外部碎片存在的可能性.
    3. Worst FIt分配算法,使得每次都是较大的内存空间被分配,这样就可以保证尽量不出现小的碎片,而大的空间不被称为碎片.所以可以降低外部碎片.
    4. 压缩手段可以将不连续的进程所用的地址聚合到一起,使得进程之间的外部碎片减少,外部碎片的空间连接到一起,成为一块大空间,方便使用.