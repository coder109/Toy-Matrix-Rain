/**********************************************
 * Author: Coder109
 * Date: 2023-07-20 15:39:50
 * Description: Header file for the matrix rain
 **********************************************/
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <ncurses.h>
#include <forward_list>

class Matrix {
public:
  Matrix(int show_length = 9, int color = 0);
  bool Run();
  bool ShowColumn(int column);
  bool SetWindowSize();
  ~Matrix();
  
private:
  WINDOW* my_window;
  int row_recorder[8192];
  int window_height;
  int window_width;
  int show_length;
  int color;
};

#endif
