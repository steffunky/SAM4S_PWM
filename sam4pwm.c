#include <nuttx/config.h>
#include <stdio.h>

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int sam4pwm_main(int argc, char *argv[])
#endif
{
  printf("Hello, World!!\n");
  return 0;
}
