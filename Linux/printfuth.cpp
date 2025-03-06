#include <bits/posix_opt.h>
#include <cstdio>
#include <termios.h>
#include <unistd.h>

int keypress() {
  struct termios saved_state, new_state;
  int c;
  if (tcgetattr(STDIN_FILENO, &saved_state) == -1) {
    return EOF;
  }
  new_state = saved_state;
  new_state.c_cflag &= ~(ICANON | ECHO);
  new_state.c_cc[VMIN] = 1;
  new_state.c_cc[VTIME] = 0;
  if (tcsetattr(STDIN_FILENO, TCSANOW, &new_state) == -1) {
    return EOF;
  }
  c = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &saved_state);
  return c;
}

int main() {
  std::printf("Running on terminal: %s\n", ttyname(STDIN_FILENO));
  std::printf("Hello, world!");
  keypress();
  return 0;
}
