📌 Project Overview

In a multi-process environment, an application may create multiple child processes to perform different tasks.When a child process finishes execution, the parent process needs to know which process terminated, whether it terminated normally or abnormally, and how it terminated.
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


Project Description:
The program creates three child processes from a parent process. Each child demonstrates a different termination condition.
Child 1: Normal termination with exit status 0
Child 2: Normal termination with exit status 5
Child 3: Termination using SIGTERM

🧠 OS Concepts Used
Exit Status
Signals
fork()
wait()
waitpid()
exit()
Zombie Process Prevention

Function 	Purpose
fork()-	Creates a child process
wait()-	Waits for a child to terminate and collects its status
exit()-	Terminates a process with an exit status
kill()-	Sends a signal to a process
getpid()-	Obtains the current process ID
WIFEXITED()-	Checks whether a child terminated normally
WEXITSTATUS()-	Obtains the exit status of a normally terminated child
WIFSIGNALED()-	Checks whether a child was terminated by a signal
WTERMSIG()-	Obtains the signal number that terminated the child
SIGTERM	Termination signal used in the signal-based termination demonstration

Termination Status Logic:
For normal termination:

WIFEXITED(status)
        ↓
     TRUE
        ↓
WEXITSTATUS(status)
        ↓
Exit value

For signal termination:

WIFSIGNALED(status)
        ↓
     TRUE
        ↓
WTERMSIG(status)
        ↓
Signal number


📜 Conclusion
The Process Termination Message System demonstrates how a Linux parent process can monitor and respond to the termination of its child processes. By using process-creation, synchronization, termination, and signal-handling mechanisms, the project provides practical understanding of process management in Linux. It also ensures that terminated child processes are properly collected, preventing zombie processes.
