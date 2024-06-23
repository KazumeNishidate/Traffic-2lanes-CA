#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

#define TRUE  (1)
#define FALSE (0)

void get_control_param(void){ 
  long time_dumy;

  /* set up the system control parameters */
  ctl.max_time_step = 100000;   /* max time step */
  ctl.mat_size = 50;         /* system size   */
  ctl.concentration = 0.2;  /* initial concentration probability */
  ctl.max_velocity = 3;      /* maximum velocity */
  ctl.max_velocity = 5;      /* maximum velocity */  
  
  ctl.mat_size2 = ctl.mat_size/2;
  ctl.dcl_p = 0.5;

  /* set a "seed" for random number generator */
  sys.random_seed = (long *)calloc(1, sizeof(long)); 
  *sys.random_seed=-time(&time_dumy); /* set seed for random numbers */

}
