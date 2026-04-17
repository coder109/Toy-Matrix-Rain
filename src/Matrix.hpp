/**********************************************
 * Author: Coder109
 * Date: 2023-07-20 15:39:50
 * Description: Header file for the matrix rain
 **********************************************/
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <ncurses.h>
#include <forward_list>
#include <vector>

class Matrix {
public:
  Matrix(int show_length = 9, int color = 0);
  bool Run();
  bool ShowColumn(int column);
  bool SetWindowSize();
  ~Matrix();
  
private:
  WINDOW* my_window;
  std::vector<int> row_recorder;
  int window_height;
  int window_width;
  int show_length;
  int color;
};

#endif
