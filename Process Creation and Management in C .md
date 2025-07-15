

## 📘 **Topic Name: Process Creation and Management in C (Fork, Wait, Process Tree)**

---

## 📝 **Program Title:**

**Creating a Parent Process with 3 Child Processes Performing Arithmetic Operations**

---

## 🎯 **Objective:**

* Create a main process named `parent_process`.
* Spawn 3 child processes (no grandchildren).
* Each child process performs one arithmetic operation (Addition, Subtraction, Multiplication) on two variables initialized in the parent.
* Display each process’s PID and PPID.
* Observe process hierarchy using the process tree.

---

## 📄 **Code with Explanation:**

```c
#include <stdio.h>      // For printf()
#include <stdlib.h>     // For exit()
#include <unistd.h>     // For fork(), getpid(), getppid()
#include <sys/wait.h>   // For wait()
```

### 🔧 **Initialize Variables and Start Parent Process**

```c
int a = 10, b = 5;
pid_t pid1, pid2, pid3;

printf("Parent process started (Name: parent_process, PID: %d)\n", getpid());
```

* `a` and `b` are variables for arithmetic operations.
* `getpid()` returns the current process ID.
* `pid1`, `pid2`, `pid3` will store child process IDs.

---

### 👶 **Create 3 Child Processes**

#### ➕ Child 1 - Addition

```c
pid1 = fork();
if (pid1 == 0) {
    printf("Child process (Name: child_1, PID: %d, PPID: %d) - ADDITION\n", getpid(), getppid());
    printf("Result: %d + %d = %d\n", a, b, a + b);
    exit(0);
}
```

#### ➖ Child 2 - Subtraction

```c
pid2 = fork();
if (pid2 == 0) {
    printf("Child process (Name: child_2, PID: %d, PPID: %d) - SUBTRACTION\n", getpid(), getppid());
    printf("Result: %d - %d = %d\n", a, b, a - b);
    exit(0);
}
```

#### ✖️ Child 3 - Multiplication

```c
pid3 = fork();
if (pid3 == 0) {
    printf("Child process (Name: child_3, PID: %d, PPID: %d) - MULTIPLICATION\n", getpid(), getppid());
    printf("Result: %d * %d = %d\n", a, b, a * b);
    exit(0);
}
```

* `fork()` creates a new process. It returns `0` in the child and PID of child in the parent.
* `getppid()` gets the parent’s process ID.
* Each child prints operation name and result, then exits.

---

### ⏳ **Wait for Child Processes to Finish**

```c
wait(NULL);
wait(NULL);
wait(NULL);
```

* `wait(NULL)` ensures the parent waits for all child processes to finish.

---

### 🧹 **End of Parent Process**

```c
printf("Parent process (PID: %d) finished.\n", getpid());
return 0;
```

---

## 🌳 **Process Tree Visualization (Linux):**

To visualize the parent-child relationship, use this command after compiling and running:

```bash
ps -f --forest -C a.out
```

Or use:

```bash
pstree -p <parent_pid>
```

---

## 📌 **Important Concepts Covered:**

| Concept      | Description                                                |
| ------------ | ---------------------------------------------------------- |
| `fork()`     | Creates a new child process                                |
| `getpid()`   | Returns current process ID                                 |
| `getppid()`  | Returns parent process ID                                  |
| `wait()`     | Waits for a child process to finish                        |
| `exit()`     | Ends the child process cleanly                             |
| Process Tree | Visual structure showing parent-child process relationship |

---

## ✅ **Output Example:**

```
Parent process started (Name: parent_process, PID: 5432)
Child process (Name: child_1, PID: 5433, PPID: 5432) - ADDITION
Result: 10 + 5 = 15
Child process (Name: child_2, PID: 5434, PPID: 5432) - SUBTRACTION
Result: 10 - 5 = 5
Child process (Name: child_3, PID: 5435, PPID: 5432) - MULTIPLICATION
Result: 10 * 5 = 50
Parent process (PID: 5432) finished.
```

> 🔔 Note: The order may vary due to concurrent execution of child processes.

---

