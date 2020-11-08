/*THIS IS THE CLIENT PROCESS*/
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


void my_handler(){}

int main(){
  printf("Client Program Started...\n");
  signal(SIGUSR1,my_handler);
  int r_shmid;
  int* result;
	key_t r_key;
	r_key = ftok("clients.txt", 12);
	if(r_key<0){
		perror("error0:");
		exit(1);
	}
	r_shmid = shmget(r_key, sizeof(int), IPC_CREAT | 0666);
	if(r_shmid<0){
		perror("error1:");
		exit(1);
	}
	result = (int*) shmat(r_shmid, NULL, 0);
	if(result == (void *) -1){
		perror("error2:");
		exit(1);
	}

    int shmid, i, n[4];
	queue* Q;
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
    

  printf("Enter Your Choice (1/2/3), Press -1 to exit: \n1.Factorial of 1 integers\n2.GCD of 2 integers\n3.LCM of 4 integers\n");
  scanf("%d", &Q->service_type[Q->count]);
  if(Q->service_type[Q->count] == -1){
    shmdt(result); 
    shmctl(r_shmid,IPC_RMID,NULL);
    printf("Client Program Exiting...\n");
    return 0;
  }

  if(Q->service_type[Q->count] == 1){
    printf("Enter value of n:  ");
    scanf("%d", &n[0]);
    sprintf(Q->s1[Q->count], "%d", n[0]);
    sprintf(Q->client_pid[Q->count], "%d", getpid());
    sprintf(Q->r_shmid[Q->count], "%d", r_shmid);
    Q->count++;
    Q->rear++;
  }

  else if(Q->service_type[Q->count] == 2){
    printf("Enter value of n1 and n2:  ");
    scanf("%d %d", &n[0], &n[1]);
    sprintf(Q->s2[Q->count][0], "%d", n[0]);
    sprintf(Q->s2[Q->count][1], "%d", n[1]);
    sprintf(Q->client_pid[Q->count], "%d", getpid());
    sprintf(Q->r_shmid[Q->count], "%d", r_shmid);
    Q->count++;
    Q->rear++;
  }

  else if(Q->service_type[Q->count] == 3){
    printf("Enter value of n1, n2, n3 and n4:  ");
    scanf("%d %d %d %d", &n[0], &n[1], &n[2], &n[3]);
    sprintf(Q->s3[Q->count][0], "%d", n[0]);
    sprintf(Q->s3[Q->count][1], "%d", n[1]);
    sprintf(Q->s3[Q->count][2], "%d", n[2]);
    sprintf(Q->s3[Q->count][3], "%d", n[3]);
    sprintf(Q->client_pid[Q->count], "%d", getpid());
    sprintf(Q->r_shmid[Q->count], "%d", r_shmid);
    Q->count++;
    Q->rear++;
  }

  else {
    printf("You have entered invalid choice.\n");
    shmdt(result); 
    shmctl(r_shmid,IPC_RMID,NULL);
    printf("Client Program Exiting...\n");
    return 0;
  }

pause();

printf("\nAnswer: %d\n", *result);
shmdt(result); 
shmctl(r_shmid,IPC_RMID,NULL);
printf("Client Program Exiting...\n");
return 0;
}


