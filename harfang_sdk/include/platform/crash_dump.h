// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

namespace gs {

/// Install the global platform crash handler.
void InstallCrashHandler();

/// Set the crash report filename.
void SetCrashReportFilename(const char *name);
/// Set the crash dump filename.
void SetCrashDumpFilename(const char *name);

/// Enable crash handler files.
void EnableCrashHandlerFiles(bool enable_crash_report, bool enable_crash_minidump);

} // gs
