<!--
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-05-19 20:38:38
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-08-04 12:07:10
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 -->

# Assignment: Banker’s Algorithm

+ You are asked to implement a Banker’s Algorithm, your code will be judged by standard test case.
+ language: C++11, you are free to use all STL
+ Input:
  + First line is ***an integer r***, which is the number of resource types.
  + The second line will be ***r integers***, which are the maximum quantity of each resource.
  + Then will be following a list of commands. The commands are in three form:
    1. New process registering, such as ***"1678 new 6 5 0 7"***, means process 1678 is a new process, whose maximum need of each resource is 6 5 0 7 (assume r is 4)
    2. Resource requesting, such as ***"233 request 0 4 5 3"***, means process 233 is an old process, it request more resource, the need of each resource is 0 4 5 3.
    3. Process termination, such as ***"233 terminate"***, means process 233 terminate and return all resources it holding.
  + PS: all input is legal, which means 
    1. before new, the process is havn't appear or is terminate.
    2. before request, the process's new is success.
    3. before terminate, there must have a success new. 
  + PS2: 
    1. but the pid can use multiply times. (new,terminate) can happen multiply times.
    2. Although before terminate must have new, but there can do not have terminate for new. new and terminate's appear is not pair.
    3. new just means process statement it's maxmium resource need, not means it must alloc those resources.
+ Output:
  + For each command, output "***OK***" or "***NOT OK***" to determine if the command can execute. If OK, ***execute the command***.
