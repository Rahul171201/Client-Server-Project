/*THIS IS THE SERVER PROCESS*/
/*IN THIS EXAMPLE START THE SERVER PROCESS FIRST*/
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<unistd.h>

typedef struct {
  char s1[10][10];
  char s2[10][2][10];
  char s3[10][4][10];
  char client_pid[10][10];
  int service_type[10];
  char r_shmid[10][10];
  int count, head, rear;
} queue;

int itr=1;

void sigintHandler(int sig_num){ 
    itr=0;
}

int main(int argc, char * argv[]){
  
  signal(SIGINT, sigintHandler); 
  printf("Hello, I am Server Program.   My PID is %d\n", getpid());
  queue* Q;
        
  int shmid, n, pid;
	key_t key;
	key = ftok("server.txt", 10);
	if(key<0){
		perror("error0:");
		exit(1);
	}
	shmid = shmget(key, sizeof(queue), IPC_CREAT | 0666);
	if(shmid<0){
		perror("error1:");
		exit(1);
	}
	Q = (queue*) shmat(shmid, NULL, 0);
	if(Q == (void *) -1){
		perror("error2:");
		exit(1);
	}
	
	Q->head = -1;
	Q->rear = -1;

  while(itr){

    if(Q->count>0){
      Q->count--;
      pid = fork();
      if(pid == 0){       
       if(Q->service_type[Q->count] == 1){
        Q->head++;
        execl("./service1", "./service1", Q->client_pid[Q->count], Q->r_shmid[Q->count], Q->s1[Q->count], NULL);
       }

       if(Q->service_type[Q->count] == 2){
         Q->head++;
        execl("./service2", "./service2", Q->client_pid[Q->count], Q->r_shmid[Q->count], Q->s2[Q->count][0], Q->s2[Q->count][1], NULL);
       }

       if(Q->service_type[Q->count] == 3){
         Q->head++;
        execl("./service3", "./service3", Q->client_pid[Q->count], Q->r_shmid[Q->count], Q->s3[Q->count][0], Q->s3[Q->count][1], Q->s3[Q->count][2], Q->s3[Q->count][3], NULL);
       }
       else exit(0);
      }
  }}
  
  shmdt(Q); 
  shmctl(shmid,IPC_RMID,NULL);
  printf("Server Program Exiting...\n");
  return 0;
}
