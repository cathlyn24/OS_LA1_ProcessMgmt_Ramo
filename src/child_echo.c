#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char *argv[]) {
    DWORD pid = GetCurrentProcessId();

    if (argc < 2) {
        printf("Parent PID not provided as argument.\n");
        return 1;
    }

    DWORD parentPid = atoi(argv[1]);

    printf("Child process started. PID: %lu\n", pid);
    printf("Parent PID (argument): %lu\n", parentPid);

    // Pause for observation (10 seconds)
    Sleep(30000); // 10000 milliseconds = 10 seconds

    return 0;
}
