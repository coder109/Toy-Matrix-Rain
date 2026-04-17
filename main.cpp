#include <iostream>
#include "src/Matrix.hpp"
#include <csignal>

using namespace std;

volatile sig_atomic_t win_change_flag = 0;
volatile sig_atomic_t exit_flag = 0;

void handler(int signal_number) {
  if(signal_number == SIGWINCH) {
    win_change_flag = 1;
  } else if (signal_number == SIGINT || signal_number == SIGTERM) {
    exit_flag = 1;
  }
}

int main() {
  Matrix my_matrix;
  signal(SIGWINCH, handler);
  signal(SIGINT, handler);
  signal(SIGTERM, handler);
  while(!exit_flag) {
    my_matrix.Run();
    if(win_change_flag == 1) {
      my_matrix.SetWindowSize();
      win_change_flag = 0;
    }
  }
  return 0;
}
