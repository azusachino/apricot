#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// Linux namespaces, has been a feature of Linux since version 2.6.24 was released in 2008.

static char child_stack[1048576];

static int child_fn()
{
    // the pid inside the mounted namespace
    printf("PID: %ld\n", (long)getpid());
    printf("PPID: %ld\n", (long)getppid());
    return 0;
}

int main()
{
    pid_t child_pid = clone(child_fn, child_stack + 1048576, CLONE_NEWPID | SIGCHLD, NULL);
    // the actual pid in root namespace
    printf("clone() = %ld\n", (long)child_pid);

    waitpid(child_pid, NULL, 0);
    return 0;
}
