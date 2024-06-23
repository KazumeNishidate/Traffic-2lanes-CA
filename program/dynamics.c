#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

#define MIN(i, j) (((i) < (j)) ? (i) : (j))

void lane_change(int *mat0, int *mat0b, double p){
  int i, j, x, y;
  int id, sum, sumb;
  for (i = 2; i < ctl.mat_size+2; i++){
    x = mat0[i];
    y = mat0b[i];
    sum = 0;
    if(x>1 && y==0){
      for(j=1;j<ctl.max_velocity;j++){
	id=i+j;
	if(id > ctl.mat_size+2) id -= (ctl.mat_size);  // BC
	sum+=mat0[id];
      }
      if(sum>0){
	sumb =0;
	for(j=1;j<ctl.max_velocity;j++){
	  id=i+j;
	  if(id > ctl.mat_size+2) id -= (ctl.mat_size);  // BC
	  sumb+=mat0b[id];
	}
      }
      if(sumb == 0){
	//	printf("lane change %d: %d  %d !\n",i,mat0[i],mat0b[i]);
	if((int)(ran1()+p) == 1){
	  mat0b[i] = mat0[i];
	  mat0[i]  = 0;
	  //      printf("lane change %d: %d  %d !\n",i,mat0[i],mat0b[i]);
	}
      }
    }
  }

}


void rand_decelerate(int *mat0)
{
  int x, i;
  for (i = 2; i < ctl.mat_size+2; i++){
    x = mat0[i];
    if(x==0||x==1) continue;
    mat0[i] -=(int)(ran1()+ctl.dcl_p);
  }
  
}


void accelerate(int *mat0)
{                                         /*   mat0 = 1   :  there is a car      */
  int i;                                  /*   mat0 = 1+v :  its velocity is 'v' */
  for (i = 2; i < ctl.mat_size+2; i++){
    if(mat0[i]==ctl.max_velocity+1) continue;   /* speed limit */
    if(mat0[i]>0) mat0[i] +=1;    /*   accelerate  */
  }
}

/* measure the number of vacant cites ahead of a car to maintain its */ 
/* possible v_max .leq. to the vacant cites                          */
void decelerate(int *mat0)
{
  int i, j, cnt, idex;
  set_bc(mat0);
  
  for (i = 2; i < ctl.mat_size+2; i++){
    if(mat0[i]>0) {
      cnt = 0;  
               
      for(j=1; j<= ctl.max_velocity; j++){
	idex = i+j;
	if(idex > ctl.mat_size+2) {
	  idex -= (ctl.mat_size);   /* cyclic bc */
	}
	if(mat0[idex]>0) {
	  break;
	} else if(mat0[idex]==0) {
	  cnt+=1;
	}
      }
      mat0[i]=MIN(mat0[i],cnt+1);
    }
  }

}

void move_tf_1d(int *mat0, int *mat1)
{
  int i, i2, x;
  //  int cnt=0;
  for (i = 2; i < ctl.mat_size+2; i++){
    x = mat0[i];
    //    if(x>0) cnt++;
    if(x==1) mat1[i]=1;  /* stay there */

    if(x>1){            /* move              */
      mat1[i]=0;   
      i2 = i+(x-1);         /* i2:  new position */
      if(i2 >= ctl.mat_size+2) {
	i2 -= ctl.mat_size;   /* cyclic BC  */
      }
      mat1[i2] = x;
    }
  }
  // printf("number of walkers = %d \n",cnt);
}

void set_bc(int *ants)
{
/*****************************************************************/
/* corner adjustment                                             */
/*                                                               */
/* for system size = 5 case (ctl.mat_size=5)                     */
/*                                                               */
/*   actual system elements (size = 5)          |a|b|c|d|e|      */
/*   ants matrix elements No.               |0|1|2|3|4|5|6|7|8|  */
/*                                                               */
/* boarder fixing procedure                                      */
/*                                                               */
/*   ants[0] <= [d] <= ants[5]   <= ants[ctl.mat_size]           */
/*   ants[1] <= [e] <= ants[5+1] <= ants[ctl.mat_size+1]         */
/*   ants[7] = ants[ctl.mat_size+2] <= [a] <= ants[2]            */
/*   ants[8] = ants[ctl.mat_size+3] <= [b] <= ants[3]            */
/*                                                               */
/*****************************************************************/

  *ants       = *(ants+(ctl.mat_size));
  *(ants+1)   = *(ants+(ctl.mat_size+1));
  *(ants+ctl.mat_size+2)     = *(ants+2);
  *(ants+ctl.mat_size+3)     = *(ants+3);
}

void mk_copy(int *original, int *copy)
{
  int i;

  for (i = 0; i < ctl.mat_size+4; i++){
      *(copy+i)  = *(original+i);
    }
}

