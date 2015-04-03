
//#include <nuttx/config.h>
#include <stdio.h>
#include <stdint.h>
//#include <nuttx/pwm.h>

#include "pwm_mock.h"

static struct pwm_state_s g_pwmstate;


int (*my_open)(char* path, int param);
void (*my_parse_args)(struct pwm_state_s* g_pwmstate,int argc , char *argv[] );
int (*my_ioctl)(int fd, int command, void * arg);
int (*my_pwm_devinit)();




int main(int argc , char *argv[] )
{
    my_open = &mock_open;
    my_ioctl = &mock_ioctl;
    my_parse_args = &mock_parse_args;
    my_pwm_devinit = &mock_pwm_devinit;
    start(argc , argv);
}

static void pwm_devpath(struct pwm_state_s *pwm, const char *devpath)
{
    if (pwm->devpath)
    {
      free(pwm->devpath);
    }

  pwm->devpath = strdup(devpath);
}

int start(int argc , char *argv[] )
{
    puts("2");

    struct pwm_info_s info;
    int fd;
    int ret;

    ret = my_pwm_devinit();

    if (!g_pwmstate.initialized)
    {
        g_pwmstate.duty        = 50;
        g_pwmstate.freq        = 100;
        g_pwmstate.duration    = 5;
        g_pwmstate.initialized = true;
    }

    my_parse_args(&g_pwmstate, argc, argv);

    if (!g_pwmstate.devpath){
        pwm_devpath(&g_pwmstate, "/dev/pwm0");
    }

    fd = my_open(g_pwmstate.devpath, O_RDONLY);

    info.frequency = g_pwmstate.freq;
    info.duty      = ((uint32_t)g_pwmstate.duty << 16) / 100;

    ret = my_ioctl(fd, PWMIOC_SETCHARACTERISTICS, (unsigned long)((uintptr_t)&info));

    ret = my_ioctl(fd, PWMIOC_START, 0);

    return 0;
}
