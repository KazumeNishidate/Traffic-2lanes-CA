#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

/* RWCA-1d uder cyclic boundary condition */

int main(void){

  open_files();
  get_control_param();
  init_mem();

  set_init_conf();

  /*----------- RWCA moving step -----------*/
  for(sys.time_step=0;
      sys.time_step<ctl.max_time_step;sys.time_step++) {
/*-------------- X interface -------------------*/
      egg_disp();
      //      egg_traffic();
      usleep(30000);
      
      print_number_of_cars();
      
      lane_change(sys.mat0,sys.mat0b,0.2);   // step 1
      mk_copy(sys.mat0, sys.mat1);
      mk_copy(sys.mat0b, sys.mat1b);
      
      lane_change(sys.mat0b,sys.mat0,0.9);   // step 2
      mk_copy(sys.mat0, sys.mat1);
      mk_copy(sys.mat0b, sys.mat1b);  
      
      accelerate(sys.mat0);     // step 3-1
      accelerate(sys.mat0b);
      
      decelerate(sys.mat0);     // step 3-2
      decelerate(sys.mat0b);
      
      rand_decelerate(sys.mat0); // step 3-3
      rand_decelerate(sys.mat0b);

      move_tf_1d(sys.mat0,sys.mat1); // step 4
      move_tf_1d(sys.mat0b,sys.mat1b);      
      
      mk_copy(sys.mat1, sys.mat0);    /* sys.mat1  =>  sys.mat0 */
      mk_copy(sys.mat1b, sys.mat0b);  /* sys.mat1  =>  sys.mat0 */      
  }
  /*-------- end of RWCA moving step -------*/
  return 0;  
}
