#include <stdint.h>
#ifndef PWM_MOCK_H
#define PWM_MOCK_H

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t ub16_t;

#ifndef __cplusplus
typedef int bool;
const int true = 1;
const int false = 0;
#endif
#define O_RDONLY 21
#define PWMIOC_SETCHARACTERISTICS 45
#define PWMIOC_START 74
#define FAR
#define CODE

struct pwm_info_s
{
	uint32_t frequency; /* Frequency of the pulse train */
	ub16_t   duty;      /* Duty of the pulse train, "1"-to-"0" duration.
						 * Maximum: 65535/65536 (0x0000ffff)
						 * Minimum:     1/65536 (0x00000001) */
};

struct pwm_state_s
{
  bool      initialized;
  char 		*devpath;
  uint8_t   duty;
  uint32_t  freq;
  int       duration;
};

void mock_parse_args(struct pwm_state_s* g_pwmstate,int argc , char *argv[] );

int mock_ioctl(int fd, int command, void * arg);

int mock_open(char* path, int param);

int mock_pwm_devinit();



#ifdef __cplusplus
}
#endif
	
#endif /* PWM_MOCK_H */

