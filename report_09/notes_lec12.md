<!--
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-05-30 18:23:32
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-08-24 11:42:23
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 -->
1. 如何计算inode表结构的大小:
  1. 每个inode_table中,有12个直接指针,1个一级指针,1个二级指针,1个三级指针,每个指针指向一个block,大小为4*1024Bytes=4KBytes.每个指针的大小是4Bytes.
  2. 则直接指针可以存储12*4KB=48KBytes.
  3. 一级指针指向一块4KBytes,4Bytes/指针,所以1024个指针,1024*4KBytes = 4MBytes.
  4. 二级指针指向1024个一级指针,可以存储1024*4Mbytes=4GBytes.
  5. 三级指针可以存储4Tbytes.
  6. 一共4TB+4GB+4MB+48KB. 

2. 以此类推,如果有x级指针体系,每级指针有[$a_1$,$a_2$,....$a_x$]个指针,每个Block的size为$2^y$Bytes,每个指针大小为$2^z$Bytes.
则其总的大小为$\sum_{i=1}^{x}$$({a_i}*{2^{(y-z)*i}})$