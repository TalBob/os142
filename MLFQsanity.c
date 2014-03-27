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
  int found;
  int pidz[20];
  int orderdPidz[20];
  int stat[20][4];
  int i, cid,k,j, c;
  int lock = 1;
  int avgwait, avgrun, avgturnaround;
  int avgwait2, avgrun2, avgturnaround2;
  int totalWait, totalRun, totalTurnaround;
  avgwait = 0;
  avgrun = 0;
  avgturnaround = 0;
  avgwait2 = 0;
  avgrun2 = 0;
  avgturnaround2 = 0;
  totalRun = 0;
  totalWait = 0;
  totalTurnaround = 0;
  c = 0;
  printf(1, "MLFQ sanity tests is starting....\n");
  for(i = 0; i<20; i++){
    
    if(lock!=0){
	lock= fork();
	pidz[i] = lock;
    }
    if(lock == 0){
	cid = i;
	break;
    }
    
  }
  if(lock == 0){ //child code
	if(cid%2==0){
	  for(k=0; k<10000; k++){
	    for(i=0; i<10000; i++){
	      c = c+1;
	    }
	  }
	}else{
	  sleep(7);
	}
	  
  }
  if(lock == 0){
      for(i = 0; i < 500; i++){
	printf(1,"cid: %d for the %d time\n", cid, i);
      }
  }
   
  else{ //father code =)
      for(i=0; i<20; i++){
	  orderdPidz[i] = wait2(&stat[i][0],&stat[i][1],&stat[i][2]);
      }
      printf(1, "-------done waiting------------------\n");
      for(i=0; i<20; i++){
	  found = 0;
	  for(j=0; j<20; j++){
	      if(pidz[i] == orderdPidz[j] && !found){
		  found = 1;
		  if(i%2==0){
		      avgwait = avgwait + stat[i][0];
		      avgrun = avgrun + stat[i][1];
		      avgturnaround = avgturnaround + stat[i][0] + stat[i][1] + stat[i][2];
		  }else{
		      avgwait2 = avgwait2 + stat[i][0];
		      avgrun2 = avgrun2 + stat[i][1];
		      avgturnaround2 = avgturnaround2 + stat[i][0] + stat[i][1] + stat[i][2];
		  }
	      }
	  }
       }
      
      totalWait = (avgwait + avgwait2) / 20;
      avgwait = avgwait / 10;
      avgwait2 = avgwait2 / 10;
      
      totalRun = (avgrun + avgrun2) / 20;
      avgrun = avgrun /10;
      avgrun2 = avgrun2 /10;
      
      totalTurnaround = (avgturnaround + avgturnaround2) / 20;
      avgturnaround = avgturnaround /10;
      avgturnaround2 = avgturnaround2 /10;
      
      printf(1, "Total average waiting time: %d\n", totalWait);
      printf(1, "Total average running time: %d\n", totalRun);
      printf(1, "Total average turnaround time: %d\n\n", totalTurnaround);
      printf(1, "Group 1:\n");
      printf(1, "Average waiting time: %d\n", avgwait);
      printf(1, "Average running time: %d\n", avgrun);
      printf(1, "Average turnaround time: %d\n\n", avgturnaround);
      printf(1, "Group 2:\n");
      printf(1, "Average waiting time: %d\n", avgwait2);
      printf(1, "Average running time: %d\n", avgrun2);
      printf(1, "Average turnaround time: %d\n\n", avgturnaround2);
       for(i=0; i<20; i++){
	  found = 0;
	  for(j=0; j<20; j++){
	      if(pidz[i] == orderdPidz[j] && !found){
		  found = 1;
		    printf(1," child %d: wating time:%d Running time:%d TurnAround time:%d\n", i, stat[i][0],stat[i][1],stat[i][0] + stat[i][1] + stat[i][2]);
		  }
	      }
	  }
      
     }
  
  exit();
}