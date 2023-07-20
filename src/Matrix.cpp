/*****************************************
 * Author: Coder109
 * Date: 2023-07-20 15:39:59
 * Description: Deal with the matrix rain
 *****************************************/

#include "Matrix.hpp"
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <curses.h>
#include <ncurses.h>
#include <unistd.h>

const char character_list[] =
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYXZ";

Matrix::Matrix(int show_length, int color) {
  this->show_length = show_length;
  this->color = color;
  this->my_window = initscr();
  refresh();
  getmaxyx(this->my_window, this->window_height, this->window_width);
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  init_pair(3, COLOR_BLACK, COLOR_BLACK);
  attron(A_BOLD);

  for (int i = 0; i < 8192; i++) {
    this->row_recorder[i] = -rand() % 30;
  }
}

Matrix::~Matrix() {}

bool Matrix::ShowColumn(int column) {
  int curr_row = 0;
  if (this->row_recorder[column] >= this->window_height + this->show_length) {
    curr_row = 0;
    this->row_recorder[column] = 0;
  } else {
    curr_row = this->row_recorder[column]++;
  }

  // Output empty char in order to solve the problem:
  // When clearing the screen, the terminal will flicker.
  for (int curr_processing_row = 0;
       curr_processing_row < curr_row - this->show_length;
       curr_processing_row++) {
    attron(COLOR_PAIR(3));
    mvaddch(curr_processing_row, column, ' ');
    attroff(COLOR_PAIR(3));
  }

  // Upper half of the column should be darker, and the bottom char should be
  // white
  for (int curr_processing_row = curr_row - this->show_length;
       curr_processing_row <= curr_row; ++curr_processing_row) {
    char show_char = character_list[std::rand() % strlen(character_list)];
    if (curr_processing_row < 0) {
      continue;
    } else if (curr_processing_row >= this->window_height) {
      break;
    } else if (curr_processing_row == curr_row) {
      attron(COLOR_PAIR(2));
      mvaddch(curr_processing_row, column, show_char);
      attroff(COLOR_PAIR(2));
    } else if (curr_processing_row < curr_row - this->show_length / 2) {
      attron(COLOR_PAIR(1));
      attron(A_DIM);
      mvaddch(curr_processing_row, column, show_char);
      attroff(A_DIM);
      attron(COLOR_PAIR(1));
    } else {
      attron(COLOR_PAIR(1));
      mvaddch(curr_processing_row, column, show_char);
      attroff(COLOR_PAIR(1));
    }
  }

  // Output empty char in order to solve the problem:
  // When clearing the screen, the terminal will flicker.
  for (int curr_processing_row = curr_row + 1;
       curr_processing_row < this->window_height; curr_processing_row++) {
    attron(COLOR_PAIR(3));
    mvaddch(curr_processing_row, column, ' ');
    attroff(COLOR_PAIR(3));
  }

  return true;
}

bool Matrix::Run() {
  for (int curr_column = 0; curr_column < window_width; curr_column++) {
    if (!this->ShowColumn(curr_column)) {
      return false;
    }
  }
  refresh();
  usleep(70000);
  return true;
}

bool Matrix::SetWindowSize() {
  endwin();
  
  this->my_window = initscr();
  refresh();
  getmaxyx(this->my_window, this->window_height, this->window_width);
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  init_pair(3, COLOR_BLACK, COLOR_BLACK);
  attron(A_BOLD);

  for (int i = 0; i < 8192; i++) {
    this->row_recorder[i] = -rand() % 30;
  }

  return true;
}
