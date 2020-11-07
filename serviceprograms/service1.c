#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<unistd.h>

unsigned int factorial(unsigned int);

int main(int argc, char * argv[]){
  printf("Hello, I am Service1 program.   My PID is %d\n", getpid());
  int i, pid, r_shmid, n;
  int* result;
  
  
  pid = atoi(argv[1]);
  r_shmid = atoi(argv[2]);
  n = atoi(argv[3]);
    
	result = (int*) shmat(r_shmid, NULL, 0);
	if(result == (void *) -1){
		perror("error2:");
		exit(1);
	}

  *result = factorial(n);

  kill(pid, SIGUSR1);
  return 0;
}

unsigned int factorial(unsigned int n) 
{ 
    if (n == 0) 
        return 1; 
    return n * factorial(n - 1); 
} 
