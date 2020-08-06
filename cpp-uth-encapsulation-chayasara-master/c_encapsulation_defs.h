#ifndef __C_ENCAPSULATION_DEFS_H__
#define __C_ENCAPSULATION_DEFS_H__


/* Box */
 
typedef struct Box{

	double length;
	double width;
	double height;

}Box;

void _ZN3BoxC1Ed(Box* const, double dim);/*ctor1, dim dflt val is 1*/
void _ZN3BoxC1Eddd(Box* const, double l, double w, double h);/*ctor2*/

void _ZN3BoxD1Ev(Box* const);/*dtor*/

void _ZN3BoxmLEd(Box* const, double mult);/* *= */
void _ZNK3Box5printEv(const Box* const);/* print */


/* Shelf */

const char* const _ZN5Shelf7DEF_MSGE;
const char* _ZN5Shelf7messageE;


typedef struct Shelf{

	Box boxes[3];

}Shelf;

void _ZNK5Shelf5printEv(const Shelf* const this);/*print*/
void _ZN5Shelf6setBoxEiRK3Box(Shelf* const this, int index, const Box* dims);/*setBox*/
double _ZNK5Shelf9getVolumeEv(const Shelf* const this);/*getVolume*/

#endif /* __C_ENCAPSULATION_DEFS_H__*/


