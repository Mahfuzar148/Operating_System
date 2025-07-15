

---



**Write a C program to create a main process named `parent_process` having `n` child processes without any grandchildren.**
Child process names are passed as **command-line arguments**, like:

```bash
$ ./parent_process 3 child_1 child_2 child_3
```

The program should:

* Fork `n` child processes.
* Each child process prints its name, its PID, and its parent’s PID.
* No child creates another process (no grandchildren).
* Use `pstree` to visualize the process tree.

---

### 🧠 **Why `sleep()` is necessary**

Without `sleep()`, child processes may terminate immediately after creation. As a result, you won't see them using `pstree` or `ps`.
Using `sleep()` gives you time to run `pstree` and view the live process tree.

---

### ✅ **C Code with Documentation**

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <n> <child_1> <child_2> ... <child_n>\n", argv[0]);
        exit(1);
    }

    // Convert 1st argument to integer (number of children)
    int n = atoi(argv[1]);

    // Print parent information
    printf("Parent process (Name: parent_process, PID: %d)\n", getpid());

    // Loop to create n child processes
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        }
        if (pid == 0) {
            // In child process
            sleep(5);  // Keeps child alive to observe in pstree
            printf("Child process (Name: %s, PID: %d, PPID: %d)\n", argv[i + 2], getpid(), getppid());
            exit(0);   // Child exits, no grandchildren
        }
    }

    // Parent waits for all child processes to finish
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("Parent process (PID: %d) finished.\n", getpid());
    return 0;
}
```

---

### 🛠️ **Compilation & Execution**

1. **Compile** the code:

```bash
gcc parent_process.c -o parent_process
```

2. **Run with child names**:

```bash
./parent_process 3 child_1 child_2 child_3
```

3. **While program runs (within 5 seconds), open another terminal** and use:

```bash
pstree -p <parent_pid>
```

You’ll see something like:

```
parent_process(12345)─┬─child_1(12346)
                      ├─child_2(12347)
                      └─child_3(12348)
```

---

### 🧪 Sample Output

```
Parent process (Name: parent_process, PID: 12345)
Child process (Name: child_1, PID: 12346, PPID: 12345)
Child process (Name: child_2, PID: 12347, PPID: 12345)
Child process (Name: child_3, PID: 12348, PPID: 12345)
Parent process (PID: 12345) finished.
```

---

### ✅ Summary

| Part        | Description                                |
| ----------- | ------------------------------------------ |
| `argv[]`    | Receives number & names of child processes |
| `fork()`    | Creates each child                         |
| `sleep(5)`  | Prevents early child termination           |
| `wait()`    | Ensures parent waits for all children      |
| `pstree -p` | Shows process tree                         |

---


