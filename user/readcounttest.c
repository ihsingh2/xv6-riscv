#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void test1();
void test2();

int main(int argc, char *argv[])
{
  test1();
  test2();
  exit(0);
}

void test1()
{
  int x1 = getreadcount();
  int x2 = getreadcount();
  char buf[100];
  (void) read(4, buf, 1);
  int x3 = getreadcount();
  for (int i = 0; i < 1000; i++) {
    (void) read(4, buf, 1);
  }
  int x4 = getreadcount();
  if ((x2 - x1 == 0) && (x3 - x2 == 1) && (x4 - x3 == 1000))
    printf("test1 passed\n");
  else
    printf("test1 failed\n");
}

void test2()
{
  int x1 = getreadcount();
  int rc = fork();
  for (int i = 0; i < 100000; i++) {
    char buf[100];
    (void) read(4, buf, 1);
  }
  // https://wiki.osdev.org/Shutdown
  // (void) shutdown();

  if (rc > 0) {
    (void) wait(&rc);
    int x2 = getreadcount();
    if (x2 - x1 == 200000)
      printf("test2 passed\n");
    else
      printf("test2 failed\n");
  }
}
