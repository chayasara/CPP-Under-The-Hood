#include "inheritence_defs.h"


const char* getName(Types type)
{
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    return names[type];
}

 void _ZN11PhysicalBoxC1Eddd(PhysicalBox* const this, double l, double w, double h)
 {
 	_ZN3BoxC1Eddd((Box*)this, l, w, h);
 	this->material.material = OTHER;
 	printf("Material created, set to %s\n", getName(this->material.material));
 	printp(this);
 }
 
 void _ZN11PhysicalBoxC1EdddN9Materials5TypesE(PhysicalBox* const this,
  double l,
   double w, 
   double h, Types t)
   {
   		_ZN3BoxC1Eddd((Box*)this, l, w, h);
   		this->material.material = t;
   		printf("Material created, set to %s\n", getName(this->material.material));
   		printp(this);
   }
   
void _ZN11PhysicalBoxC2EN9Materials5TypesE(PhysicalBox* const this, Types t)
{
	_ZN3BoxC1Ed((Box*)this,1);
	this->material.material = t;
   	printf("Material created, set to %s\n", getName(this->material.material));
   	printp(this);
}
void _ZN11PhysicalBoxD1Ev(PhysicalBox* const this)
{
	printf("PhysicalBox dtor, %f x %f x %f, %s; ", this->box.length, this->box.width, this->box.height, getName(this->material.material));
	_ZN3BoxD1Ev((Box*)this);
	
}
 
void printp(const PhysicalBox* const this)
{
	printf("PhysicalBox, made of %s; ", getName(this->material.material));
    _ZNK3Box5printEv((Box*)this);
}


/*weight*/
void _ZN9WeightBoxC1Edddd(WeightBox* const this, double l, double w, double h, double wgt)
{
	_ZN3BoxC1Eddd((Box*)this, l,w,h);
	this->weight = wgt;
	_ZNK9WeightBox6printwEv(this);
}

void _ZN9WeightBoxC1ERKS_(WeightBox* const this,const WeightBox* const other)/*cpy ctor*/
{
	_ZN3BoxC1Ed((Box*)this,1);
	this->weight = other->weight;
	_ZNK9WeightBox6printwEv(this);
}

void _ZN9WeightBoxD1Ev(WeightBox* const this)/*dtor*/
{
	printf("Destructing WeightBox; ");
    _ZNK9WeightBox6printwEv(this);
	_ZN3BoxD1Ev((Box*)this);
}

void _ZNK9WeightBox6printwEv(const WeightBox* const this)
{
	printf("WeightBox, weight: %f; ", this->weight);
    _ZNK3Box5printEv((Box*)this);
}

WeightBox _ZN9WeightBoxaSERKS_(WeightBox* const this, const WeightBox* const other)
{
	this->weight = other->weight;
	return *this;
}


















