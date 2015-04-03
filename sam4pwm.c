
//#include <nuttx/config.h>
#include <stdio.h>
#include <stdint.h>
//#include <nuttx/pwm.h>

#include "pwm_mock.h"

static struct pwm_state_s g_pwmstate;

static void pwm_devpath(struct pwm_state_s *pwm, const char *devpath)
{
    if (pwm->devpath)
    {
      free(pwm->devpath);
    }

  pwm->devpath = strdup(devpath);
}

int main(int argc, char *argv[])
{
    printf("Hello, World!!\n");

    struct pwm_info_s info;
    int fd;
    int ret;

    ret = pwm_devinit();

    if (!g_pwmstate.initialized)
    {
        g_pwmstate.duty        = 50;
        g_pwmstate.freq        = 100;
        g_pwmstate.duration    = 5;
        g_pwmstate.initialized = true;
    }

    parse_args(&g_pwmstate, argc, argv);

    if (!g_pwmstate.devpath){
        pwm_devpath(&g_pwmstate, "/dev/pwm0");
    }

    fd = opene(g_pwmstate.devpath, O_RDONLY);

    info.frequency = g_pwmstate.freq;
    info.duty      = ((uint32_t)g_pwmstate.duty << 16) / 100;

    ret = ioctle(fd, PWMIOC_SETCHARACTERISTICS, (unsigned long)((uintptr_t)&info));

    ret = ioctle(fd, PWMIOC_START, 0);

    return 0;
}
