#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char **argv)
{
  if (argc != 3) {
    fprintf(2, "usage: %s <pid> <priority>\n", argv[0]);
    exit(1);
  }

  int pid, oldsp, newsp;
  pid = atoi(argv[1]);
  newsp = atoi(argv[2]);

#ifdef PBS
  if (pid <= 0) {
    fprintf(2, "error: pid must be positive\n");
    exit(1);
  }
  if (newsp < 0 || MAX_SP < newsp) {
    fprintf(2, "error: priority should be in the range [0,%d]\n", MAX_SP);
    exit(1);
  }
#endif

  oldsp = setpriority(pid, newsp);
  if (oldsp < 0) {
    fprintf(2, "error: setpriority failed with return %d\n", oldsp);
    exit(1);
  }

  printf("priority updated from %d to %d\n", oldsp, newsp);
  exit(0);
}