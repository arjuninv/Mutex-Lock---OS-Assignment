# Mutex Lock with condition broadcasting
A multithreded program that establishes priority in execution between two categories of threads. This implementation makes use of "mutex locks" and "condition variables" wherin the last instance higher priority thread broadcasts a signal to trigger the execution of the lower priority counterparts. 


## Test Cases
| Branch | Status                                                                                                             |
|--------|--------------------------------------------------------------------------------------------------------------------|
| master | ![C/C++ CI](https://github.com/ArjunInventor/Mutex-Lock---OS-Assignment/workflows/C/C++%20CI/badge.svg?event=push) |
