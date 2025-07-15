# IPC Shared Memory Communication in C

This project demonstrates inter-process communication (IPC) using **Shared Memory** and `fork()` in C.

## 🔧 Description

A basic producer-consumer model is implemented:
- The **Producer** (parent) process writes random integers (1–100) into shared memory every 3 seconds.
- The **Consumer** (child) process reads messages from the shared memory every 3 seconds.

## 📁 File Structure

```
.
├── ipc_shared_memory.c   # Main C source file
├── IPC_prj.pdf           # Project report (in Persian)
└── README.md             # This file
```

## 🚀 How to Compile & Run

```bash
gcc ipc_shared_memory.c -o ipc_ipc
./ipc_ipc
```

Make sure to compile with a GCC-compatible compiler on a UNIX-like OS (Linux/macOS).

## 📷 Sample Output

```
Producer started. Sending messages...
Sent: 42
Sent: 77

Consumer started. Waiting for messages...
Received: 42
Received: 77
```

## 📚 System Concepts Used

- `fork()` – to create child process
- `shmget`, `shmat`, `shmdt`, `shmctl` – for shared memory setup
- `sleep()` and `rand()` – for message generation and pacing
- Memory synchronization (basic via overwriting + zeroing)

## 📎 Language & Tools

- Language: C (GCC)
- Platform: Linux/Unix-based OS
- Libraries: `<sys/shm.h>`, `<unistd.h>`, `<time.h>`, `<stdio.h>`

## 🧠 Author & Credit

Developed by [Your Name]  
For **Operating Systems Course Project**  
Supervised by Dr. Ziaei – University of [Your University Name]  

## 📝 License

This project is free to use and modify under the [MIT License](LICENSE).
