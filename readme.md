# Mutex Lock with condition broadcasting
A multi-threaded program that establishes priority in execution between two categories of threads (reader and writer). This implementation makes use of "mutex locks" and "condition variables" wherin the last instance of the higher priority thread (reader) broadcasts a signal to trigger the execution of the lower priority counterparts (writers). 


## Test Cases
| Branch | Status                                                                                                             |
|--------|--------------------------------------------------------------------------------------------------------------------|
| master | ![C/C++ CI](https://github.com/ArjunInventor/Mutex-Lock---OS-Assignment/workflows/C/C++%20CI/badge.svg?event=push) |
