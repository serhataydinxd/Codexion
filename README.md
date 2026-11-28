*This project has been created as part of the 42 curriculum by seraydin.*

# Codexion

## Description

Codexion is a C simulation of coders sharing USB dongles in a circular workspace.
Each coder runs in a thread and cycles through compiling, debugging, and
refactoring. Compiling requires both adjacent dongles, which become unavailable
for a cooldown period after release. A custom priority queue on each dongle
arbitrates requests using FIFO or earliest deadline first (EDF).

The simulation stops when every coder completes the required number of compiles
or when any coder burns out. Burnout is measured from the start of the coder's
last compile, or from the simulation start before their first compile.

## Instructions

Requirements: a C compiler (`cc`), Make, and POSIX threads.

```sh
make
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
./codexion 5 2000 100 100 100 5 50 edf
```

All eight arguments are mandatory. Times are in milliseconds and must be
nonnegative integers; coder and required compile counts must be positive.
Numeric values must fit in a signed 32-bit integer. The scheduler must be exactly
`fifo` or `edf`. Invalid arguments produce an error and a nonzero exit status.

FIFO orders requests by arrival sequence. EDF orders them by
`last_compile_start + time_to_burnout`, breaking equal deadlines by arrival
sequence. Logs use elapsed milliseconds and coder IDs starting at 1, and report
dongle acquisition, compiling, debugging, refactoring, and burnout.

`make clean` removes object files, `make fclean` also removes the executable, and
`make re` rebuilds the project. Run `norminette` to check the C coding style.

## Blocking cases handled

- **Deadlock:** dongle mutexes are always locked in increasing dongle ID order,
  breaking Coffman's circular-wait condition. A coder claims both dongles together
  and never holds one dongle while waiting for the other. Mutex protection and
  exclusive ownership preserve mutual exclusion.
- **Starvation:** per-dongle queues prevent requests from bypassing higher-priority
  requests. EDF prioritizes the earliest burnout deadline, with deterministic FIFO
  ties. These ordering rules alone do not establish the subject's full EDF
  liveness guarantee under all feasible parameters; further contention testing
  and scheduling analysis are still needed. Impossible parameters can cause
  burnout regardless of request ordering.
- **Cooldown:** each released dongle receives an availability timestamp; acquisition
  checks both dongles against these timestamps.
- **Single coder:** the coder takes the sole dongle but cannot compile, so the
  monitor eventually reports burnout.
- **Burnout and shutdown:** a separate monitor checks deadlines approximately every
  millisecond, targeting the subject's 10 ms reporting limit. Interruptible waits
  let workers stop promptly, and threads are joined before resources are freed.
- **Logging:** serialized output prevents interleaved lines, and normal event logs
  are suppressed after the simulation stops.

## Thread synchronization mechanisms

Each dongle has a `pthread_mutex_t` protecting its state, cooldown timestamp, and
request queue. Queue insertion and pair acquisition lock both adjacent dongles,
so competing coders cannot claim the same resource or modify its queue together.
The queues hold at most two requests because only the two adjacent coders can
request a dongle.

A shared state mutex protects simulation state, compile counters, compile start
updates, and the request sequence counter. For example, the monitor reads compile
counters under the same mutex workers use to increment them, preventing a data
race. A `pthread_cond_t` keeps workers and the monitor waiting until the main
thread sets their common start time and broadcasts the start signal.

A separate logging mutex serializes output. Logging also checks simulation state
under the state mutex, coordinating normal events with the monitor's final
burnout message. Waiting uses short `usleep` intervals and checks the shared stop
state between intervals.

## Resources

- The supplied `en.subject.pdf`, version 1.5, defines the project requirements.
- [POSIX threads overview](https://man7.org/linux/man-pages/man7/pthreads.7.html)
  and [condition variables](https://man7.org/linux/man-pages/man3/pthread_cond_wait.3p.html)
  document the threading primitives.
- [Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/)
  covers locks, condition variables, and concurrency bugs.
- AI assistance was used for explanations and code reviews throughout development,
  including parsing, initialization, thread creation, joining, and request heaps.
  Additional tasks included reviewing subject compliance, running
  build and runtime checks with Valgrind and Helgrind, drafting and updating
  this README, and updating the Makefile.
