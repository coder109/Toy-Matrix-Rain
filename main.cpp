#include <iostream>
#include "src/Matrix.hpp"
#include <csignal>

using namespace std;

int win_change_flag = 0;

void handler(int signal_number) {
  if(signal_number == SIGWINCH) {
    win_change_flag = 1;
  }
}

int main(int argc, char **argv) {
  Matrix* my_matrix = new Matrix();
  signal(SIGWINCH, handler);
  while(1) {
    my_matrix->Run();
    if(win_change_flag == 1) {
      my_matrix->SetWindowSize();
      win_change_flag = 0;
    }
  }
  return 0;
}
