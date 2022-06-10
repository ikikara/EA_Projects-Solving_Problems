# <p align="center">F - Queue processing time</p>
### Description
Given a list of tasks that arrive to an execution queue at a given time and that take a given amount of processing, find the total time needed to process all the tasks. Note that the tasks are processed in the order they arrive, and only one task is processed at each time.
##
### Input
The first line contains the number of tasks that arrive in the system. The following lines contain a task each, such that a task is described by two integers, the arrival time and the processing time. The list is guaranteed to be sorted by the arrival time.
## 
### Output
Return the time at which the system will have processed all the tasks, assuming that the tasks are processed in the order they arrive.
##
### Example
#### Input
4<br>
1 2<br>
1 1<br>
3 2<br>
4 1
#### Output
7
#### Explanation
Task #1 arrives at time 1, starts at time 1, and finishes at time 3<br>
Task #2 arrives at time 1, starts at time 3, and finishes at time 4<br>
Task #3 arrives at time 3, starts at time 4, and finishes at time 6<br>
Task #4 arrives at time 4, starts at time 6, and finishes at time 7<br>
System stops processing at time 7
