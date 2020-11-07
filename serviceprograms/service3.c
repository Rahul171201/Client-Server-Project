#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<unistd.h>

int lcm(int, int);
int gcd(int, int);

int main(int argc, char * argv[]){
  printf("Hello, I am Service3 program.   My PID is %d\n", getpid());
  int i, pid, r_shmid, n[4];
  int* result;
  
  
  pid = atoi(argv[1]);
  r_shmid = atoi(argv[2]);
  n[0] = atoi(argv[3]);
  n[1] = atoi(argv[4]);
  n[2] = atoi(argv[5]);
  n[3] = atoi(argv[6]);
  
  
	result = (int*) shmat(r_shmid, NULL, 0);
	if(result == (void *) -1){
		perror("error2:");
		exit(1);
	}
  
  *result = n[0];
  for (i = 1; i < 4; i++)
  {
    *result = lcm(*result, n[i]);
  }

  kill(pid, SIGUSR1);
  return 0;
}

int gcd(int x, int y){
	if (x == 0){
  		return y;
  }
 	while (y != 0){
    	if (x > y) {
      		x = x - y;
      }
      else{
      		y = y - x;
      }
  }
  	return x;
}

int lcm(int a, int b){
    return (a/gcd(a,b))*b;
}
