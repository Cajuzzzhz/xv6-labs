#include "kernel/types.h"
#include "user/user.h"

int main() {
  int pipe1[2]; 
  int pipe2[2];

  pipe(pipe1);
  pipe(pipe2);

  int pid = fork();

  if (pid < 0) {
    fprintf(2, "fork failed\n");
    exit(1);
  }

  if (pid == 0) {
    char buf;
    read(pipe1[0], &buf, 1);
    printf("%d: received ping\n", getpid());
    write(pipe2[1], &buf, 1);
    exit(0);
  } else {
    char buf = 'A';
    write(pipe1[1], &buf, 1);
    wait(0);
    read(pipe2[0], &buf, 1);
    printf("%d: received pong\n", getpid());
    exit(0);
  }
}
