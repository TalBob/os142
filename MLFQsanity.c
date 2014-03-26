#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

int
main(int argc, char *argv[])
{
  int stat[10][3];
  int i, j;
  int lock=1;
  printf(1, "MLFQ sanity tests is starting....\n");
  for(i = 0; i<20; i++){
    
    if(lock!=0){
	lock= fork();
    }

  }
  if(lock == 0){
      for(j=0; j<1000; j++){
	  printf(1," child %d prints for the %d time\n", getpid(), j);
      }
  }
   
  else{
      for(i=0; i<10; i++){
	  wait2(&stat[i][0],&stat[i][1],&stat[i][2]);
      }
      for(i=0; i<10; i++){
	  printf(1, "waiting time of %d: %d\n", i, stat[i][0]);
	  printf(1, "running time of %d: %d\n", i, stat[i][1]);
	  printf(1, "turnaround time of %d: %d\n", i, (stat[i][0]+stat[i][1]+stat[i][2]));
      }
   }
  
  exit();
}