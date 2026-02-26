#include<stdio.h>
main()
{
	int *p, q;
	q = 100;	/* assign q 100 */
	p = &q;	/* assign p the address of q*/
	printf(“%d”, *p); /* display q’s value using pointer*/
	
    
    return 0;
}
