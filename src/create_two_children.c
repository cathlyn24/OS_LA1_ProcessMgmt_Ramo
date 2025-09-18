#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si[2];
    PROCESS_INFORMATION pi[2];
    DWORD exitCode[2];
    char cmd[2][256];

    DWORD parentPID = GetCurrentProcessId();
    printf("Parent process started. PID: %lu\n", parentPID);

    // Create two child processes
    for (int i = 0; i < 2; i++) {
        ZeroMemory(&si[i], sizeof(si[i]));
        si[i].cb = sizeof(si[i]);
        ZeroMemory(&pi[i], sizeof(pi[i]));

        sprintf(cmd[i], "child_echo.exe %lu", parentPID);

        if (!CreateProcess(
                NULL,          // application name
                cmd[i],        // command line
                NULL,          // process security
                NULL,          // thread security
                FALSE,         // inherit handles
                0,             // creation flags
                NULL,          // environment
                NULL,          // current directory
                &si[i],        // startup info
                &pi[i]         // process info
            )) {
            printf("CreateProcess failed (%lu).\n", GetLastError());
            return 1;
        } else {
            printf("Child %d created. Handle=%p, PID=%lu\n", 
                   i+1, pi[i].hProcess, pi[i].dwProcessId);
        }
    }

    // Wait for both children (method 1: WaitForMultipleObjects)
    HANDLE handles[2] = { pi[0].hProcess, pi[1].hProcess };
    WaitForMultipleObjects(2, handles, TRUE, INFINITE);

    // Get exit codes
    for (int i = 0; i < 2; i++) {
        GetExitCodeProcess(pi[i].hProcess, &exitCode[i]);
        printf("Child %d (PID=%lu) exited with code: %lu\n",
               i+1, pi[i].dwProcessId, exitCode[i]);
        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }

    return 0;
}