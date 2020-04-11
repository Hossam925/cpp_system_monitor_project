#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include <string>
#include <unistd.h>
#include <iostream>

int main() {
  System system;
  NCursesDisplay::Display(system);
  //LinuxParser::UpTime(1);
}