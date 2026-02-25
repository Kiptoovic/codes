#include<stdio.h>
main()
{
 	int *p, q;
	p = &q;		/* get q’s address */
	p = 199;	/* assign q a value using a pointer */
	printf(“q’s value is %d”, q);
	return 0;
} 