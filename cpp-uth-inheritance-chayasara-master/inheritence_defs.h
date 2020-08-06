#ifndef __CPP2C_INHERITANCE_DEFS_H__
#define __CPP2C_INHERITANCE_DEFS_H__
#include <stdio.h>
#include "c_encapsulation_defs.h"


typedef enum Types{
	PLASTIC,
	METAL,
	WOOD,
	PAPER,
	OTHER
}Types;

const char* getName(Types type);

typedef struct Materials{
	char padding;
}Materials;


typedef struct Material_t{
	Types material;
}Material_t;


typedef struct PhysicalBox{
	Box box;
	Material_t material;
}PhysicalBox;

 void _ZN11PhysicalBoxC1Eddd(PhysicalBox* const this, double l, double w, double h);
 void _ZN11PhysicalBoxC1EdddN9Materials5TypesE(PhysicalBox* const this,
  double l,
   double w, 
   double h, Types t);
void _ZN11PhysicalBoxC2EN9Materials5TypesE(PhysicalBox* const this, Types t);
void _ZN11PhysicalBoxD1Ev(PhysicalBox* const this);
void printp(const PhysicalBox* const this);



typedef struct WeightBox{
	Box box;
	double weight;
}WeightBox;

void _ZN9WeightBoxC1Edddd(WeightBox* const this, double l, double w, double h, double wgt);/*ctor*/
void _ZN9WeightBoxC1ERKS_(WeightBox* const this,const WeightBox* const other);/*cpy ctor*/ 
void _ZN9WeightBoxD1Ev(WeightBox* const this);/*dtor*/
void _ZNK9WeightBox6printwEv(const WeightBox* const this);/*print*/

WeightBox _ZN9WeightBoxaSERKS_(WeightBox* const this, const WeightBox* const other);/*=*/




#endif
