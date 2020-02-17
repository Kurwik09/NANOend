#include <curses.h>

int main()
{
    initscr();
    refresh();

    int height{ 10 };
    int width{ 10 };
    int y{ 0 };
    int x{ 0 };

    WINDOW* win = newwin(height, width, y, x); /* creates a 10x10 window at index (0,0) on screen */

    if (win != nullptr) {
        box(win, 0, 0);                          /* creates a box around the window */
        wrefresh(win);                           /* refresh and update a window of our choice */
    }
    else {
        printw("window win wasn't created");
        refresh();                               /* refresh and update stdscr */
    }

    delwin(win);                               /* releases the memory allocated for the window */

    getch();
    endwin();
    return 0;
}