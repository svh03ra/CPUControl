// Author: svh03ra
// (C) 2025, All rights reserved

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "data.h"

int debug_enabled = 0;

int write_batch_file(const char *path) {
    unsigned char *decoded = (unsigned char *)malloc(sizeof(data));
    if (!decoded) return 0;

    for (size_t i = 0; i < sizeof(data); ++i) {
        decoded[i] = data[i] ^ 0xA5;
    }

    FILE *fp = fopen(path, "wb");
    if (!fp) {
        MessageBoxA(NULL, "Failed to open file for writing.", "Write Error", MB_OK | MB_ICONERROR);
        free(decoded);
        return 0;
    }

    size_t written = fwrite(decoded, 1, sizeof(data) - 1, fp);
    fclose(fp);
    free(decoded);

    if (written == 0) {
        MessageBoxA(NULL, "Failed to write any data to the file.", "Write Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    return 1;
}

int main(int argc, char *argv[]) {
    // Check for debug flags in application
    for (int i = 1; i < argc; ++i) {
        if (
            strcmp(argv[i], "-debug") == 0 ||
            strcmp(argv[i], "--debug") == 0 ||
            strcmp(argv[i], "-d") == 0 ||
            strcmp(argv[i], "--d") == 0
        ) {
            debug_enabled = 1;
        }
    }

    char tempPath[MAX_PATH];
    char tempFile[MAX_PATH];

    // Get temp path
    if (!GetTempPathA(MAX_PATH, tempPath)) {
        MessageBoxA(NULL, "Failed to get path!", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Get temp filename
    if (!GetTempFileNameA(tempPath, "bat", 0, tempFile)) {
        MessageBoxA(NULL, "Failed to generate file!", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Append .bat extension
    strcat(tempFile, ".bat");

    // Write payload to file
    if (!write_batch_file(tempFile)) {
        return 1;
    }

    // Set up process launch
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    char cmdline[MAX_PATH + 64];

    // Always forward "--debug" if any of the flags were used
    if (debug_enabled) {
        snprintf(cmdline, sizeof(cmdline), "cmd.exe /c call \"%s\" --debug", tempFile);
    } else {
        snprintf(cmdline, sizeof(cmdline), "cmd.exe /c call \"%s\"", tempFile);
    }

    if (!CreateProcessA(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        MessageBoxA(NULL, "Failed to launch the batch file!", "Launch Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Wait for batch process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Delete the batch file
    DeleteFileA(tempFile);

    return 0;
}