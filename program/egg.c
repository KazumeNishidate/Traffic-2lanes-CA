#include <eggx.h>
#include <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include  <string.h>
#include  <X11/Xlib.h>
#include  <X11/Xutil.h>
#include "rw.h"
#include "prototypes.h"
#define SCALE 20
#define X_MAX (ctl.mat_size+1)*SCALE
#define Y_MAX (SCALE*2+2)

#define X_ROAD 500
#define Y_TIME 1000

void egg_traffic(void){
  static int cnt=0, win;
  int i;
  
  if(cnt==0){
    win=gopen(X_ROAD,Y_TIME);
    layer(win, 0, 1);
  }

  for (i = 2; i < ctl.mat_size+2; i++){
      if(sys.mat0[i]>0){
	newpen(win, sys.mat0[i]);
	pset(win,(i-2)*2,Y_TIME-cnt);
      }
    }

  copylayer(win, 1, 0);
  cnt++;  

}


void egg_disp(void){
  static int cnt=0, win;
  int i;

  if(cnt==0){
    win=gopen(X_MAX,Y_MAX);
    layer(win, 0, 1);
  }

  newcolor(win, "Black");
  gclr(win) ;


  for (i = 2; i < ctl.mat_size+2; i++){
      if(sys.mat0[i]>0){
	newpen(win, sys.mat0[i]);
	fillrect(win, (i-2)*SCALE,SCALE+1, (SCALE-1), (SCALE-1));
      }
      if(sys.mat0b[i]>0){
	newpen(win, sys.mat0b[i]);	
	fillrect(win, (i-2)*SCALE, 0, (SCALE-1), (SCALE-1));
      }
    }

  copylayer(win, 1, 0);
  cnt++;  


}
