/** @file Q2.c
 *  @brief Solution of Question 2 of LA2. It demonstrates the creation of orphan and child process.
 *
 *  @author Shashank
 *
 * @date 7/31/2019
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {

		printf("Parent pid: %d \n", getpid());
		pid_t child_pid = fork();

    if (child_pid > 0) {
    		printf("Parent process is active... \n");
    		sleep(4);
    		printf("Parent process is terminated \n");
    }
    else if (child_pid == 0) {
    		printf("Child process created with pid %d from parent process pid %d \n", getpid(), getppid());
    		child_pid = fork();
    		if(child_pid > 0) {
    				sleep(1);
    				printf("Child process is sleeping... \n");
    				sleep(2);
    				printf("Child process awake again and active! \n");
    				sleep(2);
    				printf("Child process is an orphan process now! \n");
    		}
    		else if(child_pid == 0) {
    				printf("GrandChild process created with pid %d from parent process pid %d \n", getpid(), getppid());
    				sleep(1);
    				printf("Terminating grandchild process \n");
    				printf("Grandchild process is now a zombie process \n");
    		}
    }
    return 0;
}
