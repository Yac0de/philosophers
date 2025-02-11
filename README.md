# Philosophers - Dining Philosophers Problem

## Table of Contents

1. [Project Overview](#project-overview)
2. [Project Structure](#project-structure)
3. [Compilation & Execution](#compilation--execution)
4. [Understanding the Problem](#understanding-the-problem)
5. [Key Concepts Explained](#key-concepts-explained)
   - Threads & Mutexes (Mandatory)
   - Processes & Semaphores (Bonus)
   - Race Conditions & Synchronization
6. [Edge Cases & Common Mistakes](#edge-cases--common-mistakes)
7. [Example Test Cases](#example-test-cases)

## Project Overview

The **Philosophers** project is a concurrency problem that introduces concepts such as **threads, mutexes, processes, and semaphores**. The goal is to simulate philosophers sitting around a table, following specific rules for eating, thinking, and sleeping, without causing **deadlocks** or **data races**, which occur when multiple threads access shared memory without proper synchronization, leading to unpredictable behavior.

The project consists of two implementations:

- **Mandatory Part:** Uses **threads** and **mutexes**.
- **Bonus Part:** Uses **processes** and **semaphores**.

This project is useful for understanding **multi-threading**, **synchronization**, and **inter-process communication**.

## Project Structure

```
.
├── philo
│   ├── Makefile
│   ├── inc/
│   │   └── philo.h
│   ├── src/
│   │   ├── actions.c
│   │   ├── check_args.c
│   │   ├── display.c
│   │   ├── ft_str.c
│   │   ├── init.c
│   │   ├── main.c
│   │   ├── threads_death.c
│   │   ├── threads_routine.c
│   │   └── utils.c
│
├── philo_bonus
│   ├── Makefile
│   ├── inc/
│   │   └── philo.h
│   ├── src/
│   │   ├── actions_bonus.c
│   │   ├── check_args_bonus.c
│   │   ├── display_bonus.c
│   │   ├── ft_str_bonus.c
│   │   ├── init_bonus.c
│   │   ├── main_bonus.c
│   │   ├── process_death_bonus.c
│   │   ├── process_routine_bonus.c
│   │   ├── utils_bonus.c
│   │   ├── free_bonus.c
```

## Compilation & Execution

### Mandatory Version (Threads & Mutexes)

```sh
cd philo
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```sh
./philo 5 800 200 200
```

### Bonus Version (Processes & Semaphores)

```sh
cd philo_bonus
make
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```sh
./philo_bonus 5 800 200 200
```

## Understanding the Problem

The **Dining Philosophers Problem** is a classic synchronization problem that illustrates the challenges of **resource sharing** and **deadlock prevention**.

- Each philosopher must **eat, think, and sleep**.
- To eat, a philosopher must acquire **two forks** (one on the left, one on the right).
- If a philosopher **does not eat within ****************************************************************`time_to_die`**************************************************************** milliseconds**, they die, and the simulation stops.
- Philosophers do not communicate with each other, meaning they **do not know when others are about to die**.

## Key Concepts Explained

### **Threads vs Processes**

A **thread** is a lightweight unit of execution that shares the same memory space as its parent process. In contrast, a **process** has its own separate memory space.

| Feature | Thread (`pthread_create`) | Process (`fork`) |
|---------|----------------|----------------|
| Memory | Shares memory with parent | Has its own memory space |
| Creation Speed | Fast | Slower due to memory duplication |
| Communication | Uses shared memory | Requires inter-process communication (IPC) |
| Use Case | Efficient for shared tasks | Good for isolated execution |

Example of creating a **thread**:
```c
pthread_t thread;
pthread_create(&thread, NULL, &routine, NULL);
```

Example of creating a **process**:
```c
pid_t pid = fork();
if (pid == 0) {
    // Child process code
} else {
    // Parent process code
}
}
```

### **Threads & Mutexes (Mandatory Part)**

- Each philosopher is represented by a **thread**.
- Forks are protected by **mutexes** to avoid data races.
- `pthread_mutex_lock()` ensures that only one philosopher can take a fork at a time.
- `pthread_create()` is used to launch threads, and `pthread_join()` ensures proper cleanup.

Example of thread creation:

```c
pthread_create(&philo->thread_life_id, NULL, &philosopher_routine, philo);
```

### **Processes & Semaphores (Bonus Part)**

- Instead of threads, each philosopher is a **separate process** created using `fork()`.
- Forks are managed using **semaphores** (`sem_t`) instead of mutexes.
- `sem_wait()` and `sem_post()` regulate resource access.

Example of semaphore usage:

```c
sem_wait(data->sem_forks);
// Take a fork
sem_post(data->sem_forks);
```

### **Mutex vs Semaphore**

Mutexes and semaphores are both synchronization tools, but they serve different purposes:

| Feature | Mutex | Semaphore |
|---------|-------|-----------|
| Nature | Binary lock (1 or 0) | Counting mechanism |
| Usage | Ensures **mutual exclusion**, allowing only one thread at a time | Allows multiple processes/threads access based on counter |
| Scope | Used **only for threads** within a single process | Can be used **across processes** |
| Example | `pthread_mutex_lock()` / `pthread_mutex_unlock()` | `sem_wait()` / `sem_post()` |
| Blocking Behavior | If locked, other threads must **wait** | If counter > 0, other threads can proceed |

### **System Calls & Functions Used**

Understanding the key system calls and functions used in this project is crucial for handling **threads, processes, mutexes, and semaphores**. Below are the main functions along with their prototypes:

#### **Threads & Mutexes**
```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
int pthread_join(pthread_t thread, void **retval);
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```
- `pthread_create()` starts a new thread.
- `pthread_join()` waits for a thread to finish execution.
- `pthread_mutex_init()` initializes a mutex.
- `pthread_mutex_lock()` locks a mutex to prevent race conditions.
- `pthread_mutex_unlock()` unlocks a mutex when a critical section is done.

#### **Processes & Semaphores**
```c
pid_t fork(void);
sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
int sem_wait(sem_t *sem);
int sem_post(sem_t *sem);
int sem_close(sem_t *sem);
int sem_unlink(const char *name);
```
- `fork()` creates a child process.
- `sem_open()` initializes a named semaphore.
- `sem_wait()` decreases the semaphore value, blocking if the value is 0.
- `sem_post()` increases the semaphore value, allowing blocked processes to proceed.
- `sem_close()` closes a semaphore.
- `sem_unlink()` removes a named semaphore from the system.

### **Race Conditions & Synchronization**

A **race condition** occurs when multiple threads/processes access shared data simultaneously without synchronization, leading to unpredictable behavior.

- In **threads**, mutexes prevent race conditions by ensuring mutual exclusion.
- In **processes**, semaphores regulate access to shared resources.

## Edge Cases & Common Mistakes

- ✅ **Deadlocks:** Ensure philosophers **do not wait indefinitely** for forks. Use strategies like **odd/even philosopher staggering**.
- ✅ **Memory & Resource Cleanup:** Ensure all `malloc()`, `pthread_mutex_destroy()`, and `sem_unlink()` calls are properly handled.

## Example Test Cases

### Basic Test (Check for Proper Execution)

```sh
./philo 5 800 200 200
```

### Single Philosopher Test (Should Die)

```sh
./philo 1 300 100 100
```

### Memory Leak Check (Valgrind)

```sh
valgrind --leak-check=full ./philo 5 800 200 200
```

### Process Cleanup Check (Bonus Part)

```sh

ps aux | grep philo
```

Expected: No lingering `philo_bonus` processes after execution.

---
