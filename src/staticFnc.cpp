#include "staticFnc.hpp"

#include <iostream>
#include <string>

bool isBigEndian(){
  float f = -1;
  char *b  = reinterpret_cast<char*>(&f);

  #ifdef DEBUG
  std::cout << static_cast<int>(b[0]) << "-"
            << static_cast<int>(b[1]) << "-"
            << static_cast<int>(b[2]) << "-"
            << static_cast<int>(b[3]) << std::endl;
  #endif

  return b[0] != 0;
}

std::string mes(int code)
{
  std::string es = "Error: ";
  return es.append(std::to_string(code));
}

std::string mes(const char* message)
{
  std::string es = "Error: ";
  return es.append(message);
}
