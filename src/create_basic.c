#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    DWORD parentPid = GetCurrentProcessId();
    printf("Parent process started. PID: %lu\n", parentPid);

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Command line: pass parent PID as argument
    char cmdLine[256];
    sprintf(cmdLine, "child_echo.exe %lu", parentPid);

    if (!CreateProcess(
            NULL,       // No module name
            cmdLine,    // Command line
            NULL, NULL,
            FALSE, 0, NULL, NULL,
            &si, &pi
        )) 
    {
        printf("Failed to create child process. Error %lu\n", GetLastError());
        return 1;
    }

    printf("Child created. PID: %lu\n", pi.dwProcessId);

    // Wait for child to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
        printf("Failed to get exit code. Error %lu\n", GetLastError());
        exitCode = 1;
    }

    printf("Child exited with code: %lu\n", exitCode);

    // Close handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
