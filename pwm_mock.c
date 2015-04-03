#include "pwm_mock.h"

CODE int set(FAR struct pwm_lowerhalf_s *dev)
{
	puts("1");
	return 0;
}

CODE int shut(FAR struct pwm_lowerhalf_s *dev)
{
	puts("2");
	return 0;
}

CODE int start(FAR struct pwm_lowerhalf_s *dev,
			   FAR const struct pwm_info_s *info)
{
	puts("3");
	return 0;	
}

CODE int stop(FAR struct pwm_lowerhalf_s *dev)
{
	puts("4");
	return 0;
}

FAR const struct pwm_ops_s sam4s_pwm_vt =
{
	&set,
	&shut,
	&start,
	&stop,
	&ioctl
};

struct pwm_lowerhalf_s sam4s_pwm =
{
	&sam4s_pwm_vt
};


void mock_parse_args(struct pwm_state_s* g_pwmstate,int argc , char *argv[] ){
	puts("parse_args");
}

int mock_ioctl(int fd, int command, void * arg){
	puts("ioctl");
	return 2;
};

int mock_open(char* path, int param){
	puts("open");
	return 3;
}

int mock_pwm_register(FAR const char *path, FAR struct pwm_lowerhalf_s *dev){
	puts("pwm_register");
	return 4;
}

int mock_pwm_devinit(){
	puts("pwm_devinit");
	pwm_register("/dev/pwm0", &sam4s_pwm);
	return 8;
}