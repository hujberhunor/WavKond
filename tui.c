/*
███▀▀██▀▀███            ██  
█▀   ██   ▀                
     ██    ███  ▀███ ▀███  
     ██      ██    ██   ██  
     ██      ██    ██   ██  
     ██      ██    ██   ██  
   ▄████▄    ▀████▀███▄████▄
*/

#include <ncurses.h>
#include "./inc/giraffe.h"


void draw_borders(WINDOW *screen) {
  int x, y, i;

  getmaxyx(screen, y, x); // Size of the terminal

  // 4 corners
  mvwprintw(screen, 0, 0, "+");
  mvwprintw(screen, y - 1, 0, "+");
  mvwprintw(screen, 0, x - 1, "+");
  mvwprintw(screen, y - 1, x - 1, "+");

  // sides
  for (i = 1; i < (y - 1); i++) {
    mvwprintw(screen, i, 0, "|");
    mvwprintw(screen, i, x - 1, "|");
  }

  // top and bottom
  for (i = 1; i < (x - 1); i++) {
    mvwprintw(screen, 0, i, "-");
    mvwprintw(screen, y - 1, i, "-");
  }
}

int main() {
  int parent_x, parent_y, new_x, new_y;
  int score_size = 10;

  initscr();
  noecho();

  // set up initial windows
  getmaxyx(stdscr, parent_y, parent_x);

  WINDOW *field = newwin(parent_y - score_size, parent_x, 0, 0);
  WINDOW *score = newwin(score_size, parent_x, parent_y - score_size, 0);

  draw_borders(field);
  draw_borders(score);

    getmaxyx(stdscr, new_y, new_x);

    if (new_y != parent_y || new_x != parent_x) {
      parent_x = new_x;
      parent_y = new_y;

      wresize(field, new_y - score_size, new_x);
      wresize(score, score_size, new_x);
      mvwin(score, new_y - score_size, 0);

      wclear(stdscr);
      wclear(field);
      wclear(score);

      draw_borders(field);
      draw_borders(score);
    }

    // draw to our windows
    mvwprintw(field, 1, 1, "Files");
    mvwprintw(score, 1, 1, "Song");

    // refresh each window
    wrefresh(field);
    wrefresh(score);
  endwin();

  return 0;
}
