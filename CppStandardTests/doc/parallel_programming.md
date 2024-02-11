# Parallel programming

## Algorithms

- use std::execution::par algorithms (std::execution::par algorithms are good for big set of data)
- do not call two parallel algorithms one by one - try to combine in one algorithm

## Thread pools

- use thread pools (not in std - use library...)

## JThread

- use dedicated threads for background task - std::jthread
- use std::stop_source and std::stop_token to ASK background task to stop. BG task have to check and may not stop
- use stop_callback to react on request_stop and note that code will be executed in request_stop caller thread

## Data synchronization

You can use stuff like (ordered by usage priority):
- latches
- barriers
- future
- mutex
- semaphore
- atomic

### Latches

Single use counter going to 0. Not reusable - goes to 0 and that's it.

Can be used to wait several thread to be finished or assure that several threads ill be started at the same time. Example: multi thread code testing - assure all threads run at the same time.

### Barriers

Kind of like latch, but with possibility to execute callback when barrier achieved and restart it. Example: you can you it in a loop to synchronize loops of different threads.

Also you can "leave" barrier and do not participate in synchronization any more.

Final callback will be called in one of the participating threads.

Good for parallel processing of chunked data (each thread process part of a file), or to process data in sequence (data transferred from thread to tread in line like car assembly line).

### Futures

Future/Promise mechanism presented on C++-11.

- std::async
- std::promise
- std::packaged_task (needs to be called directly with parameters and will not start automatically)

In case of future received from async, future dtor will wait for thread to be finished.

Since future is one shot, you maybe want to use shared_future.

### Mutex

Prevent concurrent execution.

There are 6 types of mutex, but mostly you will use only first one:
- mutex
- timed_mutex
- recursive_mutex
- recursive_timed_mutex
- shared_mutex
- shred_timed_mutex

There are 4 types of locking and unlocking mechanism, but you should prefer first one:
- scoped_lock - like lock_guard but can work with several mutexes with guarantee that all of them will be locked and released at the same time (prevent deadlock situation)
- unique_lock
- lock_guard
- shared_lock - for shared_mutex

Always minimize lock scope!

#### unique_lock

Lock that allows to unlock mutex while unique_lock is still alive. Also has strategies allowed to create lock without immediate mutex locking.

#### conditional_variable.

Good to be used with unique_lock and allows us to wait for condition around data in another thread. Other thread modifying waiting data should notify waiting thread using notify_one().

If you want to use stop_token, use conditional_variable_any.

### Semaphores

Represents a number of available "slots". Max count passed to std::semaphore\<XXX>(YYY) can be bigger than YY which is start value.

### Atomic

Type of atomic must "support" memcpy and memcmp.

Two cases not meet upper requirement that cen be used in atomic - std::shared_ptr and std::weak_ptr.

std::atomic<T>::is_always_lock_free will help you to check is your T is really atomic and not using mutex under the hood.

# Summary

- avoid managing thread manually
- use std::jthread for thread
- use std::stop_token for cancellation
- use std::latch, std::barrier and std::future where your can
- use std::mutex in other case (with std::scoped_lock)
- use std::atomic rarely
