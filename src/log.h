#pragma once

#include <iostream>

std::string logger_version = "0.1.3";
bool already_run{};

// Simple logging function(s) to handle certain events

void MomoInfo(std::string error_name) {
    printf("Momo's Quest Info [v%s]: %s\n", logger_version.c_str(), error_name.c_str());
}

void MomoWarning(std::string warning_name) {
    printf("Momo's Quest Warning [v%s]: %s\n", logger_version.c_str(), warning_name.c_str());
}

void MomoError(std::string error_name) {
    printf("Momo's Quest Error [v%s]: %s\n", logger_version.c_str(), error_name.c_str());
}
