/*
Solution of Question 1 of Assignment 1

Shashank Kashyap
17114070
 */

#include <stdio.h>
#include <unistd.h>

int main() {

  int pid = -1, pid_child1 = -1, pid_child2 = -1;
  int pid_child1_of_child1 = -1, pid_child2_of_child1 = -1;
  int pid_child1_of_child2 = -1, pid_child2_of_child2 = -1;
  int ppppid = getpid();

  pid_child1 = fork(); // child1
  pid_child2 = fork(); //child2

  if(pid_child1>0 && pid_child2>0){ //parent
    printf("First child PID %d.\n", pid_child1);
    printf("Second child PID %d.\n", pid_child2);
  }
  else if(pid_child1==0 && pid_child2>0) { // child1

    pid_child1_of_child1 = pid_child2;
    pid_child2_of_child1 = fork();
    if(pid_child2_of_child1 != 0){ // child1
      printf("First Grandchild PID %d.\n", pid_child1_of_child1);
      printf("Second Grandchild PID %d.\n", pid_child2_of_child1);

    }
  }
  else if(pid_child2==0 && pid_child1!=0) {

    pid_child1_of_child2 = fork();
    if(pid_child1_of_child2 != 0){ //child2
      pid_child2_of_child2 = fork();
      if(pid_child2_of_child2 != 0){ //child2
        printf("Third Grandchild PID %d.\n", pid_child1_of_child2);
        printf("Fourth Grandchild PID %d.\n", pid_child2_of_child2);
        printf("Parent PID %d.\n", ppppid);
      }
    }
  }
}
