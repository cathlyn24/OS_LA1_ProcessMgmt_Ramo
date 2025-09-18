#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD exitCode;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Create child process: cmd /c dir
    if (!CreateProcess(
            NULL,
            "cmd /c dir", // command to run
            NULL, NULL, FALSE,
            0, NULL, NULL,
            &si, &pi
        )) 
    {
        printf("Failed to create process. Error %lu\n", GetLastError());
        return 1;
    }

    printf("Parent PID: %lu created process PID: %lu\n", GetCurrentProcessId(), pi.dwProcessId);

    // Wait for the child process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Get the exit code of the child
    if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
        printf("Failed to get exit code. Error %lu\n", GetLastError());
        exitCode = 1;
    }

    printf("Child exited with code: %lu\n", exitCode);

    // Close handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Exit with the same code as the child
    return exitCode;
}
