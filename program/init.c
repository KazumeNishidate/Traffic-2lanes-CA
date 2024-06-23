#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

/****
 set the initial configuration of the system
****/
void set_init_conf()
{
  int i, cnt=0;

  for (i = 2; i < ctl.mat_size+2; i++){
    sys.mat0[i] = (int)(ctl.max_velocity*ran1()+1)*
      ((int)(ran1()+ctl.concentration));
    sys.mat0b[i] = (int)(ctl.max_velocity*ran1()+1)*
      ((int)(ran1()+ctl.concentration));
    if(sys.mat0[i]>0) cnt++;
    if(sys.mat0b[i]>0) cnt++;    
  }
  sys.number_of_walkers = cnt;
/*
  printf("num = %d\n",cnt);
  printf("prob. = %f\n",(double)cnt/(double)ctl.mat_size);
  getchar();
*/
  set_bc(sys.mat0);
}

void open_files(void)
{
  if((fpout = fopen("../files/out","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
  if((fp_cars= fopen("../files/cars","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
  
}

void init_mem(void){
  int *mat_mem0, *mat_mem1, *mat_mem2;
  int *mat_mem0b, *mat_mem1b;

  mat_mem0 = (int *)calloc(ctl.mat_size+4, sizeof(int)); 
  mat_mem1 = (int *)calloc(ctl.mat_size+4, sizeof(int)); 
  mat_mem2 = (int *)calloc(ctl.mat_size+4, sizeof(int));
  mat_mem0b= (int *)calloc(ctl.mat_size+4, sizeof(int)); 
  mat_mem1b= (int *)calloc(ctl.mat_size+4, sizeof(int)); 
  
  sys.mat0 = mat_mem0;
  sys.mat1 = mat_mem1;
  sys.mat2 = mat_mem2;
  sys.mat0b= mat_mem0b;
  sys.mat1b= mat_mem1b;
  
}

void show_matrix(int *field){
  int i;
/*
  for(i=0; i<ctl.mat_size+4; i++){
    printf(" %d",field[i]);
  }
  printf("\n");
*/
  for(i=2; i<ctl.mat_size+2; i++){
    printf(" %d",field[i]);
  }
  printf("\n");

}

void print_matrix(int *field){
  int i;
  for(i=2; i<ctl.mat_size+2; i++){
    fprintf(fpout," %d",field[i]);
  }
  fprintf(fpout,"\n");
}

void print_number_of_cars(){
  int i, cntr=0, cntl=0, sum;
  
  for(i=2; i<ctl.mat_size+2; i++){
    if(sys.mat0[i]>0) cntl++;
    if(sys.mat0b[i]>0) cntr++;    
  }
  sum = cntl+cntr;
  fprintf(fp_cars,"%d  %d  %d  %d\n",sys.time_step,cntl,cntr,sum);
}
