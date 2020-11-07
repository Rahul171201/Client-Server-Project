#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<unistd.h>

int gcd(int, int);

int main(int argc, char * argv[]){
  printf("Hello, I am Service2 program.   My PID is %d\n", getpid());
  int i, pid, r_shmid, n[2];
  int* result;
  
  
  pid = atoi(argv[1]);
  r_shmid = atoi(argv[2]);
  n[0] = atoi(argv[3]);
  n[1] = atoi(argv[4]);
  
  
	result = (int*) shmat(r_shmid, NULL, 0);
	if(result == (void *) -1){
		perror("error2:");
		exit(1);
	}

  *result = gcd(n[0], n[1]);

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
