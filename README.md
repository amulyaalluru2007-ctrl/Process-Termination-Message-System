📌 Project Overview
In a multi-process environment, an application may create multiple child processes to perform different tasks. When a child process finishes execution, the parent process needs to know which process terminated, whether it terminated normally or abnormally, and how it terminated.
The Process Termination Message System provides a simple mechanism for detecting child-process termination and displaying this information to the parent process.
The project uses Linux process-management system calls such as fork(), wait(), and waitpid() to create and monitor child processes.

🎯 Objectives
Create multiple child processes.
Allow each child process to perform a different task.
Detect when a child process terminates.
Use wait() or waitpid() to collect termination status.
Display the PID of the terminated process.
Identify normally and abnormally terminated processes.
Display the child's exit status.
Detect whether a process was terminated by a signal.
Prevent terminated child processes from becoming zombie processes.

⚙️ How It Works
                Parent Process
                     |
          Creates Multiple Children
             /       |       \
            /        |        \
       Child 1    Child 2    Child 3
       Task A     Task B     Task C
          |          |          |
       Exit()     Exit()    Signal/Exit
          \          |          /
           \         |         /
             Parent waits
                  |
             wait()/waitpid()
                  |
        Collect termination status
                  |
          Display termination
              information
              
The parent process creates multiple child processes using fork().
Each child performs a different task.
After completing its task, a child terminates using exit() or may be terminated by a signal.
The parent uses wait() or waitpid() to detect the terminated child.
The termination status is analyzed.
The system displays:
Terminated process PID
Normal/abnormal termination
Exit status, if applicable
Signal information, if applicable
The parent collects the child's status so that the terminated child does not remain as a zombie.

🧠 OS Concepts Used
Process Creation
Parent-Child Processes
Process Lifecycle
Process Termination
Process Synchronization
Exit Status
Signals
fork()
wait()
waitpid()
exit()
Zombie Process Prevention

🛠️ Technologies Used
Operating System: Linux / Ubuntu
Programming Language: C
Compiler: GCC
APIs: POSIX / Linux System Calls
Version Control: Git & GitHub

📂 Suggested Project Structure
Process-Termination-Message-System/
│
├── src/
│   ├── main.c
│   ├── process.c
│   └── process.h
│
├── docs/
│   └── project-documentation.md
│
├── README.md
│
└── .gitignore

🖥️ Sample Output
Parent Process PID: 4521

Created Child 1 | PID: 4522
Created Child 2 | PID: 4523
Created Child 3 | PID: 4524

Child Process Terminated
PID: 4522
Termination Type: Normal
Exit Status: 0

Child Process Terminated
PID: 4523
Termination Type: Normal
Exit Status: 5

Child Process Terminated
PID: 4524
Termination Type: Signal
Signal: SIGTERM

All child processes have been collected.
No zombie processes remain.

👥 Team
KernalCrew_OSSP
Roll Number	Team Member
2520030032	A. Amulya
2520030275	Kunal Shahane
2520030600	Ch. Gayatri sri harshita

🚀 Future Scope
Add a graphical interface for displaying process information.
Support monitoring of a larger number of child processes.
Record termination events in a log file.
Provide timestamps for process creation and termination.
Add more detailed signal and exit-status reporting.

📜 Conclusion
The Process Termination Message System demonstrates how a Linux parent process can monitor and respond to the termination of its child processes. By using process-creation, synchronization, termination, and signal-handling mechanisms, the project provides practical understanding of process management in Linux. It also ensures that terminated child processes are properly collected, preventing zombie processes.
