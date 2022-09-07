#pragma once

#include <iostream>

std::string error_name;

#define MomoInfo(error_name) { printf("Momo's Quest [INFO]: %s\n", error_name); }
#define MomoWarning(error_name) { printf("Momo's Quest [WARNING]: %s\n", error_name); }
#define MomoError(error_name) { printf("Momo's Quest [ERROR]: %s\n", error_name); }