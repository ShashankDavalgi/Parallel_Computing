#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

void main(){
int i=0;
int s=2;
int e=50000;
// Initializing the process id.
pid_t pid;

//creating child process
pid=fork();

  //checking whether the process is child.
if(pid==0){
	int s1=s;
	int f1=e/2;
	int i=0,j=0,count1=0,pc=0;

	
	for(i=2; i<=f1; i++) {
			
			int count1 = 0;
			
			for(j=1; j<=i; j++) {
								
				if((i%j) == 0) {
					
					count1++;
				}
			}
		if(count1 == 2) {
				
				pc++;
				//System.out.print("  " + i);
			}
}
printf("Child Process: %d\n",pc);
}

  //Parent process
  
else{
	int s2=e/2;
	int f2=e;
	int i1=0,j1=0,count2=0,pc1=0;
	for(i1=s2; i1<=f2; i1++) {
			
			int count2 = 0;
			
			for(j1=1; j1<=i1; j1++) {
								
				if((i1%j1) == 0) {
					
					count2++;
				}
			}
		if(count2 == 2) {
				
				pc1++;
				//System.out.print("  " + i);
			}
	}
printf("Parent Process: %d\n",pc1);

}
}
