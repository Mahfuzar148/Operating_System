

---

## 📘 **Creating an Orphan Process in C**

---

### 🧠 **What is an Orphan Process?**

An **orphan process** is a **child process whose parent has terminated or exited** before the child.
When the parent dies, the orphan child gets **adopted by the `init` process** (PID 1) in Linux-based systems (or `systemd` in modern distros).

---

### 🏗️ **How to Create an Orphan Process**

To create an orphan:

1. **Fork a child process** using `fork()`.
2. In the **parent**, call `exit(0)` immediately.
3. In the **child**, add `sleep()` to delay it, so that when it prints, the parent has already exited.

---

### ✅ **Example Code:**

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Error occurred
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        sleep(5); // Let parent exit first
        printf("Orphan Child Process:\n");
        printf("PID: %d, New Parent PID (should be 1): %d\n", getpid(), getppid());
    } else {
        // Parent process
        printf("Parent Process (PID: %d) is exiting now...\n", getpid());
        exit(0); // Parent exits immediately
    }

    return 0;
}
```

---

### 🧪 **Expected Output:**

```bash
Parent Process (PID: 1234) is exiting now...
Orphan Child Process:
PID: 1235, New Parent PID (should be 1): 1
```

> You may see PPID = 1 (init) or PPID = some other PID if `systemd` is used.

---

### 🧾 **How It Works:**

| Component   | Description                           |
| ----------- | ------------------------------------- |
| `fork()`    | Creates a child process               |
| `sleep(5)`  | Delays child so parent can exit first |
| `exit(0)`   | Terminates parent before child ends   |
| `getppid()` | Returns current parent PID            |

---

### 🔍 **How to Check in Terminal**

Use `ps -ef | grep <child_pid>` and check `PPID` (Parent PID). It should show `1` (init).

Or use:

```bash
ps -elf | grep a.out
```

---

### 🛠️ **Compilation & Run**

```bash
gcc orphan.c -o orphan
./orphan
```

---

### 🧭 **Summary**

| Term         | Meaning                            |
| ------------ | ---------------------------------- |
| Orphan       | Child whose parent has exited      |
| Adopted By   | `init` or `systemd` (PID 1)        |
| Key Behavior | Child runs after parent terminates |

---


