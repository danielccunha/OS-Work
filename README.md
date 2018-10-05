# OS Work
Work of Operating Systems, where I had to implement **scheduling algorithms** working with semaphores and threads, using pthread.h and semaphore.h in C.

## Scheduling Algorithms
- Non-preemptive
  - [FCFS/FIFO](https://en.wikipedia.org/wiki/FIFO_(computing_and_electronics))
  - [SJF/SJN](https://en.wikipedia.org/wiki/Shortest_job_next)
  - [Non-preemptive Priority](https://www.javatpoint.com/os-non-preemptive-priority-scheduling)
  - [HRRN](https://en.wikipedia.org/wiki/Highest_response_ratio_next)
- Preemptive
  - [Round-robin](https://en.wikipedia.org/wiki/Round-robin_scheduling)
  - [Priority FIFO/FCFS](https://en.wikipedia.org/wiki/Fixed-priority_pre-emptive_scheduling)
  - [Priority with RR](https://en.wikipedia.org/wiki/Round-robin_scheduling)
  - [SRT](https://pt.wikipedia.org/wiki/Shortest_remaining_time)

## Compiling
The project was developed using Linux and `pthread.h`, so, in order to compile, you must be using a Linux distro. In your terminal, run the following commands:
```
git clone https://github.com/danielccunha/OS-Work.git
cd OS-Work
gcc program.c -lpthread
```

## Algorithms
1. FCFS/FIFO
2. SJF/SJN
3. Non-preemptive Priority
4. HRRN
5. Round-robin
6. Priority FIFO/FCFS (not implemented)
7. Priority with RR
8. SRT (not implemented)

## How to use
After compiling the project, in order to execute `program.c` you must pass eight arguments:
- N: numbers of processes
- T: size of queue/list in the algorithms
-	Min: processes' minimum time
-	Max: processes' maximum time
-	Pi: processes' minimum priority
- Pf: processes' maximum priority
-	A: algorithm to execute
-	Q: quantum size

Depending on the chosen algorithm, some arguments won't be used, but you must pass their values anyway. So, in the project folder, run `./a.out N T Min Max Pi Pf A Q`.

### Example
**Input**
```
./a.out 10 5 0 5 1 5 3 0
```
**Output**
```
Priority: 1. Initial time: 77002. Sleeping 0 seconds...
Priority: 1. Initial time: 77002. Sleeping 3 seconds...
Priority: 3. Initial time: 77002. Sleeping 4 seconds...
Priority: 3. Initial time: 77002. Sleeping 2 seconds...
Priority: 4. Initial time: 77002. Sleeping 3 seconds...
Priority: 2. Initial time: 77004. Sleeping 1 seconds...
Priority: 4. Initial time: 77004. Sleeping 4 seconds...
Priority: 5. Initial time: 77006. Sleeping 0 seconds...
Priority: 5. Initial time: 77010. Sleeping 0 seconds...
Priority: 5. Initial time: 77012. Sleeping 4 seconds...

Finished scheduler
Total time: 21
```

In this case, I've run a non-preemptive Priority algorithm, with minimum priority 1 and maximum priority 5. The values generated for priorities and time are totally random, so the result probably will be different on your machine.

## License
MIT License
