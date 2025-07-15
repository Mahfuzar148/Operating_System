

## 📘 **Creating Grandchildren in C Using fork()**

### 🧠 **Concept:**

* A *child* is created when a process calls `fork()`.
* If the *child process* itself calls `fork()`, the new process becomes a **grandchild** of the original process.

---

### 🧱 **Process Hierarchy Example:**

```
Parent (P)
 ├── Child (C)
 │    └── Grandchild (GC)
 ├── Child (C2)
 └── Child (C3)
```

---

### ✅ **Sample Code to Create One Grandchild**

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid, grandchild_pid;

    child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (child_pid == 0) {
        // Inside child process
        printf("Child process: PID = %d, PPID = %d\n", getpid(), getppid());

        grandchild_pid = fork();
        if (grandchild_pid < 0) {
            perror("Fork failed");
            exit(1);
        }

        if (grandchild_pid == 0) {
            // Inside grandchild process
            printf("Grandchild process: PID = %d, PPID = %d\n", getpid(), getppid());
        } else {
            // Child waits for grandchild
            wait(NULL);
        }

        exit(0);
    } else {
        // Parent process
        wait(NULL);  // Wait for child
        printf("Parent process: PID = %d\n", getpid());
    }

    return 0;
}
```

---

### 🖥️ **Expected Output Format**

```bash
Child process: PID = 1234, PPID = 1233
Grandchild process: PID = 1235, PPID = 1234
Parent process: PID = 1233
```

> Note: PIDs will vary.

---

### 📌 **How It Works:**

| Line            | Description                                                |
| --------------- | ---------------------------------------------------------- |
| `fork()`        | Creates a child process.                                   |
| `if (pid == 0)` | Ensures only the child process executes the next fork.     |
| Second `fork()` | Executed **inside** the child, creating a grandchild.      |
| `wait(NULL)`    | Makes parent/child wait for child/grandchild respectively. |

---

### 🔍 **Visualizing Process Tree**

Use `pstree` to see the hierarchy:

```bash
pstree -p <Parent_PID>
```

Install `pstree` if needed:

```bash
sudo apt install psmisc
```

---


