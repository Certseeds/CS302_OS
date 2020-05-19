<!--
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-05-19 20:38:38
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-05-19 20:42:11
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 -->
## Assignment: Banker’s Algorithm
+ You are asked to implement a Banker’s Algorithm, your code will be judged by standard test case.
+ language: C++11, you are free to use all STL
+ Input:
  + First line is <font color="#dd0000">an integer r</font>, which is the number of resource types.
  + The second line will be <font color="#dd0000">r integers</font>, which are the maximum quantity of each resource.
  + Then will be following a list of commands. The commands are in three form:
    1. New process registering, such as "<font color="#dd0000">1678 new 6 5 0 7</font>", means process 1678 is a new process, whose maximum need of each resource is 6 5 0 7 (assume r is 4)
    2. Resource requesting, such as "<font color="#dd0000">233 request 0 4 5 3</font>", means process 233 is an old process, it request more resource, the need of each resource is 0 4 5 3.
    3. Process termination, such as "<font color="#dd0000">233 terminate</font>", means process 233 terminate and return all resources it holding.
+ Output:
  + For each command, output "<font color="#dd0000">OK</font>" or "<font color="#dd0000">NOT OK</font>" to determine if the command can execute. If OK, <font color="#dd0000">execute the command</font>.