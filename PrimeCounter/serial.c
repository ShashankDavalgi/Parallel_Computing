#include<stdio.h>

void main()
{
	int i=0;
	int s=2;
	int e=50000;

	int j=0,count1=0,pc=0;

  //Outer for loop goes from 2 to the number chosen. the loop starts from 2 because 0 and 1 are not prime
	
	for(i=2; i<=e; i++) {
			
			int count1 = 0;
		
    // inner for loop finds whether it is prime or not for every number.
    
			for(j=1; j<=i; j++) {
								
        //If the remainder is 0, then there is a common factor.
        
				if((i%j) == 0) {
					
					count1++;
				}
			}
		if(count1 == 2) {
				
      // incrememnting the prime counter
      
				pc++;
				//System.out.print("  " + i);
			}
}
printf("%d\n",pc);
}
