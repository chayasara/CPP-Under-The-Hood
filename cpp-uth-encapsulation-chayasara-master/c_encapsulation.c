#include <stdio.h>
#include "c_encapsulation_defs.h"

static Box _ZL8largeBox;
static Box _ZGVZ8thisFuncvE5box99;
static Box _ZGVZ8thatFuncvE5box88;

void _Z8thisFuncv()
{
	static int count = 0;
	
    printf("\n--- thisFunc() ---\n\n"); 
    
    if (count++ == 0)
    	_ZN3BoxC1Eddd(&_ZGVZ8thisFuncvE5box99, 99, 99, 99);
    	
    _ZN3BoxmLEd(&_ZGVZ8thisFuncvE5box99, 10);
}

void _Z8thatFuncv()
{
	static int count = 0;

    	
    
    printf("\n---thatFunc() ---\n\n"); 
    
    
    if (count++ == 0)
    	_ZN3BoxC1Eddd(&_ZGVZ8thatFuncvE5box88, 88, 88, 88);
    	
    _ZN3BoxmLEd(&_ZGVZ8thatFuncvE5box88, 10);
}



void doBoxes()
{
    Box b1, b2, b3, b4;
    
    printf("\n--- Start doBoxes() ---\n\n");

    
    _ZN3BoxC1Ed(&b1,3);
   
    _ZN3BoxC1Eddd(&b2, 4, 5, 6);
    
    printf("b1 volume: %f\n", b1.height*b1.width*b1.length);
    printf("b2 volume: %f\n", b2.height*b2.width*b2.length);

    _ZN3BoxmLEd(&b1, 1.5);
    _ZN3BoxmLEd(&b2, 0.5);

    printf("b1 volume: %f\n", b1.height*b1.width*b1.length);
    printf("b2 volume: %f\n", b2.height*b2.width*b2.length);

    b3 = b2;
    
    b4 = b2;
    _ZN3BoxmLEd(&b4, 3);
     
    printf("b3 %s b4\n",  b3.length == b4.length && b3.width == b4.width && b2.height == b4.height ? 
    		"equals" : "does not equal");

	_ZN3BoxmLEd(&b3, 1.5);
	_ZN3BoxmLEd(&b4, 0.5);
  
    printf("Now, b3 %s b4\n", b3.length == b4.length && b3.width == b4.width && b3.height == b4.height ? 
    		"equals" : "does not equal");

    printf("\n--- End doBoxes() ---\n\n");
    
    _ZN3BoxD1Ev(&b4);
    _ZN3BoxD1Ev(&b3);
    _ZN3BoxD1Ev(&b2);
    _ZN3BoxD1Ev(&b1);
}

void _Z9doShelvesv()
{
    size_t i;
    Box b1,b2,aBox;
    Shelf aShelf;
    
    printf("\n--- start _Z9doShelvesv() ---\n\n");

    
    _ZN3BoxC1Ed(&aBox, 5);

    for(i=0; i < 3; ++i)
		_ZN3BoxC1Ed(&aShelf.boxes[i],1);
		
    _ZNK5Shelf5printEv(&aShelf);
    _ZN5Shelf6setBoxEiRK3Box(&aShelf, 1, &_ZL8largeBox);
    _ZN5Shelf6setBoxEiRK3Box(&aShelf, 0, &aBox);

    _ZNK5Shelf5printEv(&aShelf);
    _ZN5Shelf7messageE = "This is the total volume on the shelf:";
    _ZNK5Shelf5printEv(&aShelf);
    _ZN5Shelf7messageE = "Shelf's volume:";
    _ZNK5Shelf5printEv(&aShelf);

    _ZN3BoxC1Eddd(&b1,2,4,6);
    _ZN5Shelf6setBoxEiRK3Box(&aShelf, 1, &b1);
 	_ZN3BoxD1Ev(&b1);
 
    _ZN3BoxC1Ed(&b2, 2);
    _ZN5Shelf6setBoxEiRK3Box(&aShelf, 2, &b2);
    _ZN3BoxD1Ev(&b2);
    _ZNK5Shelf5printEv(&aShelf);

    printf("\n--- end _Z9doShelvesv() ---\n\n");
    
    
     for(i=0; i < 3; ++i)
		_ZN3BoxD1Ev(&aShelf.boxes[3-i-1]);
	
    _ZN3BoxD1Ev(&aBox);
}

int main()
{
	_ZN3BoxC1Eddd(&_ZL8largeBox, 10, 20, 30);
    printf("\n--- Start main() ---\n\n");

    doBoxes();

    _Z8thisFuncv();
    _Z8thisFuncv();
    _Z8thisFuncv();
    _Z8thatFuncv();
    _Z8thatFuncv();

    _Z9doShelvesv();
        
    printf("\n--- End main() ---\n\n");
    _Z8thatFuncv();
    _Z8thisFuncv();
    _ZN3BoxD1Ev(&_ZGVZ8thatFuncvE5box88);
    _ZN3BoxD1Ev(&_ZGVZ8thisFuncvE5box99);
    
    _ZN3BoxD1Ev(&_ZL8largeBox);

    return 0;
}

