#ifndef LIBCRASHD_H
#define LIBCRASHD_H

#include <string>

namespace Libcrashd {
    void CrashDialogue(const std::string& title = "This app crashed",
                       const std::string& message = "This application hang and crashed.\nPlease restart.",
                       const std::string& footer = "Error: 0000-000");

    void GenerateCrashReport(const std::string& reason);
    bool IsFunctionValid(void* func);
    std::string GetBacktrace();
}

#endif
