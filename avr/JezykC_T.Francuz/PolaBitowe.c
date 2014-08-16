
/* definicja pozwala poprzez symbol _PORTB 
odwoływać się do PORTUB procesora np:
	_PORTB.b1=1;
	_PORTB.b3=0;                        */

typedef struct 
{
	unsigned int b0:1;
	unsigned int b1:1;
	unsigned int b2:1;
	unsigned int b3:1;
	unsigned int b4:1;
	unsigned int b5:1;
	unsigned int b6:1;
	unsigned int b7:1;	
} IO;

#define _PORTB (*(volatile IO*)&PORTB)
