#pragma once

#include <string>

bool isBigEndian();

std::string mes(int code);

std::string mes(const char* message);

void Interleave(float* l, float* r, float* res, size_t size);
