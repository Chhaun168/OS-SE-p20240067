#include <stdio.h>
#include <windows.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    printf("Parent process (PID: %lu)\n", GetCurrentProcessId());

    char cmd[] = "mspaint";

if (!CreateProcess(
    NULL,
    cmd,
    NULL,
    NULL,
    FALSE,
    0,
    NULL,
    NULL,
    &si,
    &pi))
    {
        printf("CreateProcess failed (%lu)\n", GetLastError());
        return 1;
    }

    printf("Child process created!\n");
    printf("Child PID: %lu\n", pi.dwProcessId);

    printf("Open Task Manager NOW!\n");

    WaitForSingleObject(pi.hProcess, INFINITE);

    printf("Child exited.\n");

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
