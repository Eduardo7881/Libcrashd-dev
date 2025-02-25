#include "libcrashd.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <csignal>
#include <execinfo.h>
#include <gtk/gtk.h>

namespace Libcrashd {

    void LogError(const std::string& message) {
        std::ofstream logFile("crashd.log", std::ios::app);
        if (logFile.is_open()) {
            time_t now = time(0);
            char* dt = ctime(&now);
            logFile << "[CRASH] " << dt << message << std::endl;
            logFile.close();
        }
    }

    std::string GetBacktrace() {
        void* callstack[128];
        int frames = backtrace(callstack, 128);
        char** symbols = backtrace_symbols(callstack, frames);
        
        std::string backtraceInfo = "Backtrace:\n";
        if (symbols) {
            for (int i = 0; i < frames; ++i) {
                backtraceInfo += std::to_string(i) + ": " + symbols[i] + "\n";
            }
            free(symbols);
        } else {
            backtraceInfo += "Failed to generate backtrace.\n";
        }

        return backtraceInfo;
    }

    void GenerateCrashReport(const std::string& reason) {
        std::string backtrace = GetBacktrace();
        std::string crashReport = "===== CRASH REPORT =====\n";
        crashReport += "Reason: " + reason + "\n";
        crashReport += backtrace + "\n";
        crashReport += "========================\n";

        LogError(crashReport);
        std::cerr << crashReport;
    }

    void CrashDialogue(const std::string& title, const std::string& message, const std::string& footer) {
        std::string fullMessage = message + "\n\n" + footer + "\n\n" + GetBacktrace();
        GenerateCrashReport(fullMessage);

        if (!gtk_init_check(0, nullptr)) {
            std::cerr << title << "\n" << fullMessage << std::endl;
            exit(EXIT_FAILURE);
        }

        GtkWidget *dialog = gtk_message_dialog_new(
            NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "%s", fullMessage.c_str());
        gtk_window_set_title(GTK_WINDOW(dialog), title.c_str());
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        exit(EXIT_FAILURE);
    }

    bool IsFunctionValid(void* func) {
        if (func == nullptr) {
            GenerateCrashReport("Attempt to call a null function!");
            return false;
        }
        return true;
    }
}
