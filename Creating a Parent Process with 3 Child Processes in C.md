

---

## 🧾 **Creating a Parent Process with 3 Child Processes in C**

### (No Grandchildren, With Custom Names and Process Tree Trace)

---

### 🧠 **Objective:**

Create a **main process** named `parent_process` which spawns **three child processes** (`child_1`, `child_2`, `child_3`) without creating any **grandchildren**.

You will:

* Print each process's name and PID.
* Show parent-child relationships using PID and PPID.
* Trace process positions using terminal tools.

---

### 🏗️ **How the Program Works:**

1. The **main process** prints its name and PID.
2. Using a loop or sequential `fork()`, it creates 3 child processes.
3. Each child process:

   * Prints its custom name (`child_1`, `child_2`, `child_3`)
   * Prints its own PID and parent PID.
   * Immediately exits (to prevent grandchildren).
4. The parent waits for all children to complete using `wait()`.

---

### ✅ **C Program:**

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3;

    printf("Main process (Name: parent_process, PID: %d)\n", getpid());

    // First child
    pid1 = fork();
    if (pid1 == 0) {
        printf("Child process (Name: child_1, PID: %d, PPID: %d)\n", getpid(), getppid());
        exit(0); // Exit to avoid creating grandchildren
    }

    // Second child
    pid2 = fork();
    if (pid2 == 0) {
        printf("Child process (Name: child_2, PID: %d, PPID: %d)\n", getpid(), getppid());
        exit(0);
    }

    // Third child
    pid3 = fork();
    if (pid3 == 0) {
        printf("Child process (Name: child_3, PID: %d, PPID: %d)\n", getpid(), getppid());
        exit(0);
    }

    // Parent waits for all child processes
    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("Parent process (PID: %d) finished.\n", getpid());

    return 0;
}
```

---

### 🔄 **How to Compile and Run**

```bash
gcc process_tree.c -o process_tree
./process_tree
```

---

### 🔍 **How to Trace the Process Tree**

While the program runs (use `sleep()` in children if needed), open another terminal and run:

```bash
ps -ef --forest
```

Or use:

```bash
pstree -p <parent_pid>
```

---

### 📌 **Key Points**

| Feature     | Description                                      |
| ----------- | ------------------------------------------------ |
| `fork()`    | Creates a new process                            |
| `getpid()`  | Gets the current process ID                      |
| `getppid()` | Gets parent process ID                           |
| `exit(0)`   | Exits child immediately to prevent grandchildren |
| `wait()`    | Parent waits for child processes                 |

---

### 🚫 **What This Program Avoids:**

* No **grandchildren** created (children exit immediately).
* Clean exit of all child processes to avoid **zombies**.

---

