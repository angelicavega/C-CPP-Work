#include "stdio.h"
#include "pthread.h"
#include "semaphore.h"
#include "unistd.h"
#include "time.h"
#include "stdlib.h"



//--------------------------------
#define Students_In_Class 20 
//--------------------------------
void *Student(void *num);
void *Teacher(void *);
void randwait(int secs);
//--------------------------------
sem_t waitingRoom; sem_t Chair; sem_t teacherPillow; sem_t seatBelt;

int rec = 0;

int main(int argc, char *argv[]) {
	pthread_t btid;
		pthread_t tid[Students_In_Class];
			long RandSeed;
				int i, numStudent, numChairs=3;
				int Number[Students_In_Class];
//--------------------------------
printf("How many students are in the classroom? : "); scanf("%d",&numStudent) ;

if (numStudent > Students_In_Class) {

printf("The max amount of students in the classroom are:  %d.\n", Students_In_Class);
	exit(-1);
}
//--------------------------------
for (i=0; i<Students_In_Class; i++) {
Number[i] = i;
}
//--------------------------------
sem_init(&waitingRoom, 0, numChairs);
	sem_init(&Chair, 0, 1);
		sem_init(&teacherPillow, 0, 0);
			sem_init(&seatBelt, 0, 0);

pthread_create(&btid, NULL, Teacher, NULL);
	for (i=0; i<numStudent; i++) {

pthread_create(&tid[i], NULL,Student, (void *)&Number[i]);
sleep(1);
}

	for (i=0; i<numStudent; i++) {

pthread_join(tid[i],NULL);
sleep(1);
}

rec = 1;
	sem_post(&teacherPillow);
	pthread_join(btid,NULL);
}
//--------------------------------
void *Student(void *number) {
int num = *(int *)number;

printf("student %d is visiting the teachers office.\n", num+1);
randwait(2);

printf("student %d has arrived at the teachers office.\n", num+1);
	sem_wait(&waitingRoom);

printf("student %d is currently seated on the waiting chair.\n", num+1);
	sem_wait(&Chair);
	sem_post(&waitingRoom);

printf("student %d is waking up the teacher.\n", num+1);
	sem_post(&teacherPillow);
	sem_wait(&seatBelt);
	sem_post(&Chair);

printf("student %d is leaving the teachers office.\n", num+1);
}
//--------------------------------
void *Teacher(void *trash) {
	while (!rec) {

	printf("The teacher is now sleeping\n");
	sem_wait(&teacherPillow);

	if (!rec) {

	printf("The teacher is helping another student\n");
	randwait(2);
	printf("The teacher is now available.\n");

	sem_post(&seatBelt);
}

		else {
		printf("All students are free.\n");
		}
	}
}
//--------------------------------
void randwait(int secs) {
	int len;
	len = (int) ((1 * secs) + 1);
		sleep(len);
}