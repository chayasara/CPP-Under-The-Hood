#ifndef __POLI_DEFS_H__
#define __POLI_DEFS_H__
#include <stdio.h>

typedef void (*func_ptr)(); 

/*inline void printFunc(const char* fname)
{
    printf("%-60s | ", fname); 
}*/

/* TextFormatter */
//func_ptr textFormatter_vptr[2];

typedef struct TextFormatter
{
	func_ptr* vptr;
}TextFormatter; 

void TextFormatter_dtor(TextFormatter* const this);
void TextFormatter_print(const TextFormatter* const this, const char* text);

/* DefaultTextFormatter */
//func_ptr defaultTextFormatter_vptr[4];
typedef struct DefaultTextFormatter
{
	//func_ptr* vptr;
	TextFormatter textFormatter;
	/*const*/ int id;
}DefaultTextFormatter;

void DefaultTextFormatter_ctor(DefaultTextFormatter* const this);
void DefaultTextFormatter_cpyCtor(DefaultTextFormatter* const this, const DefaultTextFormatter* const);
DefaultTextFormatter asOp(DefaultTextFormatter* const this, const DefaultTextFormatter* const);
void DefaultTextFormatter_dtor(DefaultTextFormatter* const this);

void DefaultTextFormatter_print_c(const DefaultTextFormatter* const this, const char* text);

typedef struct Ider{
	char buffer;
}Ider;

int next_id;
/*inline int getId() { return next_id++; }*/

DefaultTextFormatter* generateFormatterArray();

/*PrePostFixer*/
//func_ptr prePostFixer_vptr[4];
typedef struct PrePostFixer
{
	func_ptr* vptr;
	DefaultTextFormatter defaultTextFormatter;
	const char* pre;
    const char* post;
}PrePostFixer;

void PrePostFixer_ctor(PrePostFixer* const this, const char* prefix, const char* postfix);
/*virtual*/void PrePostFixer_dtor(PrePostFixer* const this);
/*virtual*/void PrePostFixer_print_c(const PrePostFixer* const this, const char* text);
/*virtual*/void PrePostFixer_print_lc(const PrePostFixer* const this, long num, char symbol);
/*virtual*/char PrePostFixer_getDefaultSymbol(const PrePostFixer* const this);

/*INLINE:
const char* PrePostFixer_getPrefix(const PrePostFixer* const this);
const char* PrePostFixer_getPostfix(const PrePostFixer* const this);

void PrePostFixer_print_num_l(const PrePostFixer* const this, long num);
void PrePostFixer_print_num_lc(const PrePostFixer* const this, long num, char symbol);*/


/* PrePostDollarFixer */
//func_ptr prePostDollarFixer_vptr[4];

typedef struct PrePostDollarFixer
{
	func_ptr* vptr;
	PrePostFixer prePostFixer;
}PrePostDollarFixer;

void PrePostDollarFixer_ctor(PrePostDollarFixer* const this, const char* prefix, const char* postfix);
void PrePostDollarFixer_cpyCtor(PrePostDollarFixer* const this, const PrePostDollarFixer* const other);
/*virtual*/void PrePostDollarFixer_dtor(PrePostDollarFixer* const this);

void PrePostDollarFixer_print_ic(const PrePostDollarFixer* const this, int num, char symbol/* = '$'*/);
/*virtual*/void PrePostDollarFixer_print_lc(const PrePostDollarFixer* const this, long num, char symbol /*= '$'*/);
void PrePostDollarFixer_print_dc(const PrePostDollarFixer* const this, double num, char symbol /*= '$'*/);
/*virtual*/char PrePostDollarFixer_getDefaultSymbol(const PrePostDollarFixer* const this);

/*inline char PrePostDollarFixer::getDefaultSymbol() const
{
    return '$';
}*/


/*PrePostHashFixer*/
typedef struct PrePostHashFixer{
	PrePostDollarFixer prePostDollarFixer;
	int precision;
}PrePostHashFixer;

void PrePostHashFixer_ctor(PrePostHashFixer* const this, int prc /*= 4*/);
/*virtual*/void PrePostHashFixer_dtor(PrePostHashFixer* const this);

void PrePostHashFixer_print_ic(const PrePostHashFixer* const this, int num, char symbol /* = #*/);
/*virtual*/void PrePostHashFixer_print_lc(const PrePostHashFixer* const this, long num, char symbol/* = #*/);
void PrePostHashFixer_print_dc(const PrePostHashFixer* const this, double num, char symbol/* = #*/);
/*virtual*/char PrePostHashFixer_getDefaultSymbol(const PrePostHashFixer* const this);

/*inline void PrePostHashFixer::print(double num, char symbol) const
{
    printFunc("[PrePostHashFixer::print(double, char)]"); 

    printf("%s[%c%.*f]%s\n", getPrefix(), symbol, precision, num, getPostfix());
}*/


/* PrePostFloatDollarFixer */
typedef struct PrePostFloatDollarFixer{
	PrePostDollarFixer prePostDollarFixer;
}PrePostFloatDollarFixer;

void PrePostFloatDollarFixer_ctor(PrePostFloatDollarFixer* const this, const char* prefix, const char* postfix);
/*virtual*/void PrePostFloatDollarFixer_dtor(PrePostFloatDollarFixer* const this);
void PrePostFloatDollarFixer_print_f(const PrePostFloatDollarFixer* const this, float num);
void PrePostFloatDollarFixer_print_fc(const PrePostFloatDollarFixer* const this, float num, char symbol);
/*virtual*/char PrePostFloatDollarFixer_getDefaultSymbol(const PrePostFloatDollarFixer* const this);

/*PrePostChecker */

typedef struct PrePostChecker{
	PrePostFloatDollarFixer prePostFloatDollarFixer;
}PrePostChecker;

void PrePostChecker_ctor(PrePostChecker* const this);
/*virtual*/void PrePostChecker_dtor(PrePostChecker* const this);
    
void printThisSymbolUsingFunc(const PrePostChecker* const this);
void printThisSymbolDirectly(const PrePostChecker* const this);    
void printDollarSymbolByCastUsingFunc(const PrePostChecker* const this);
void printDollarSymbolByScopeUsingFunc(const PrePostChecker* const this);
void printDollarSymbolByCastDirectly(const PrePostChecker* const this);
void printDollarSymbolByScopeDirectly(const PrePostChecker* const this);

/* Multiplier*/
typedef struct Multiplier{
	DefaultTextFormatter defaultTextFormatter;
	int times;
}Multiplier;

/*virtual*/void Multiplier_dtor(Multiplier* const this);

void Multiplier_print_c(const Multiplier* const this, const char*);

/*inline Multiplier::Multiplier(int t = 2)
:   times(t)
{
    printf("--- Multiplier CTOR: times = %d\n", times);
}*/

    
/*inline int Multiplier::getTimes() const
{
    return times;
}*/

/*inline void Multiplier::setTimes(int t)
{
    times = t;
}*/


















#endif
