

---

## 💀 **Zombie Process in C**

---

### 🧠 **What is a Zombie Process?**

A **zombie process** is a **child process that has completed execution but still has an entry in the process table**.
This happens because the parent has **not yet read the child's exit status** using `wait()` or `waitpid()`.

Zombie processes remain in the system until the parent calls `wait()`.

---

### 🏗️ **How to Create a Zombie Process**

To create a zombie:

1. Fork a child process.
2. In the **child**, print a message and exit.
3. In the **parent**, call `sleep()` without calling `wait()`.
4. This delay keeps the zombie in the process table.

---

### ✅ **C Program:**

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Error
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) exiting.\n", getpid());
        exit(0);
    } else {
        // Parent process sleeps without waiting
        printf("Parent process (PID: %d) sleeping... (Check zombie with `ps -ef`)\n", getpid());
        sleep(30); // During this time, child is zombie
    }

    return 0;
}
```

---

### 🔍 **How to Observe Zombie:**

1. Run the compiled program:

   ```bash
   gcc zombie.c -o zombie
   ./zombie
   ```
2. While it's sleeping, open another terminal and run:

   ```bash
   ps -elf | grep zombie
   ```

   or

   ```bash
   ps aux | grep Z
   ```

Look for a process with **status `Z` (Zombie)** and check if the child is still listed.

---

### 🧾 **Explanation Table:**

| Term       | Description                            |
| ---------- | -------------------------------------- |
| `fork()`   | Creates child process                  |
| `exit(0)`  | Child exits early                      |
| `sleep()`  | Parent delays to simulate zombie state |
| `Z` status | Indicates zombie in `ps` output        |

---

### 💡 **How to Prevent Zombie**

Call `wait()` or `waitpid()` in the parent process to **"reap"** the child process and free system resources.

---

### 🔚 **Summary**

| Feature       | Value                        |
| ------------- | ---------------------------- |
| Process State | Zombie (`Z`)                 |
| Cause         | Parent did not `wait()`      |
| Impact        | Entry stays in process table |
| Solution      | Use `wait()` or `waitpid()`  |

---


