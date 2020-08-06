#include <stdlib.h>
#include "poli_defs.h"


/*TextFormatter*/
func_ptr textFormatter_vptr[] = {(func_ptr)TextFormatter_dtor,(func_ptr)TextFormatter_print};

/*virtual*/void TextFormatter_dtor(TextFormatter* const this)
{}

void TextFormatter_print(const TextFormatter* const this, const char* text)
{}

/*DefaultTextFormatter Defs*/
func_ptr defaultTextFormatter_vptr[2] = {(func_ptr)DefaultTextFormatter_dtor,(func_ptr)DefaultTextFormatter_print_c};

int next_id = 0;

void DefaultTextFormatter_ctor(DefaultTextFormatter* const this)
{ 
	//this->textFormatter.vptr = textFormatter_vptr;//optimisation
	this->textFormatter.vptr = defaultTextFormatter_vptr;
	this->id = next_id++;
	printf("--- DefaultTextFormatter Default CTOR\n########## C %d ##########\n", this->id);
}

void DefaultTextFormatter_cpyCtor(DefaultTextFormatter* const this, const DefaultTextFormatter* const other)
{
	this->textFormatter.vptr  = other->textFormatter.vptr;
	this->id = next_id++;
	printf("--- DefaultTextFormatter Copy CTOR, from id: %d\n########## C %d ##########\n", other->id, this->id);
}


DefaultTextFormatter asOp(DefaultTextFormatter* const this, const DefaultTextFormatter* const other)
{
	printf("--- DefaultTextFormatter operator=(), from id: %d to id: %d\n", other->id, this->id);
    return *this;
}

void DefaultTextFormatter_dtor(DefaultTextFormatter* const this)
{
	printf("--- DefaultTextFormatter DTOR\n########## D %d ##########\n", this->id);
	this->textFormatter.vptr = textFormatter_vptr;
	TextFormatter_dtor((TextFormatter*)this);
}

void DefaultTextFormatter_print_c(const DefaultTextFormatter* const this, const char* text)
{
	printf("%-60s | ", "[DefaultTextFormatter::print(const char*)]"); 
	printf("%s\n", text);
}

DefaultTextFormatter* generateFormatterArray()
{
    return malloc(3*sizeof(DefaultTextFormatter));
}

/*PrePostFixer Defs*/
func_ptr prePostFixer_vptr[] = {(func_ptr)PrePostFixer_dtor,(func_ptr)PrePostFixer_print_c,(func_ptr)PrePostFixer_print_lc,(func_ptr)PrePostFixer_getDefaultSymbol};

void PrePostFixer_ctor(PrePostFixer* const this, const char* prefix, const char* postfix)
{	
	DefaultTextFormatter_ctor(&(this->defaultTextFormatter));
	this->defaultTextFormatter.textFormatter.vptr = prePostFixer_vptr;
	this->pre = prefix;
	this->post = postfix;
	printf("--- PrePostFixer CTOR: \"%s\"...\"%s\"\n", this->pre, this->post);
}

/*virtual*/void PrePostFixer_dtor(PrePostFixer* const this)
{
	printf("--- PrePostFixer DTOR: \"%s\"...\"%s\"\n", this->pre, this->post);
	this->defaultTextFormatter.textFormatter.vptr = defaultTextFormatter_vptr;
	DefaultTextFormatter_dtor(&this->defaultTextFormatter);
}

/*virtual*/void PrePostFixer_print_c(const PrePostFixer* const this, const char* text)
{
	 printf("%-60s | ", "[PrePostFixer::print(const char*)]"); 
	printf("%s%s%s\n", this->pre, text, this->post);
}

/*virtual*/void PrePostFixer_print_lc(const PrePostFixer* const this, long num, char symbol/* = '\0'*/)
{
	printf("%-60s | ", "[PrePostFixer::print(long, char)]");
    printf("-->\n");
    
    if (symbol)    
     {
        printf("%-60s | ", "[PrePostFixer::print_num(long, char)]");  
    	printf("%s%c%ld%s\n", this->pre, symbol, num, this->post);
     }
    else
    {
    	printf("%-60s | ", "[PrePostFixer::print_num(long)]");  
    	printf("%s%ld%s\n", this->pre, num, this->post); 
    }
}

/*virtual*/char PrePostFixer_getDefaultSymbol(const PrePostFixer* const this)
{
	return '\0';
}

/* PrePostDollarFixer */

func_ptr PrePostDollarFixer_vptr[] = {(func_ptr)PrePostDollarFixer_dtor, (func_ptr)PrePostFixer_print_c,(func_ptr)PrePostDollarFixer_print_lc, (func_ptr)PrePostDollarFixer_getDefaultSymbol};

void PrePostDollarFixer_ctor(PrePostDollarFixer* const this, const char* prefix, const char* postfix)
{
	PrePostFixer_ctor(&(this->prePostFixer), prefix, postfix);
	this->prePostFixer.defaultTextFormatter.textFormatter.vptr = PrePostDollarFixer_vptr;
	printf("--- PrePostDollarFixer CTOR: \"%s\"...\"%s\"\n", this->prePostFixer.pre, this->prePostFixer.post);
}

void PrePostDollarFixer_cpyCtor(PrePostDollarFixer* const this, const PrePostDollarFixer* const other)
{
	DefaultTextFormatter_cpyCtor(&(this->prePostFixer.defaultTextFormatter),&(other->prePostFixer.defaultTextFormatter));
	this->prePostFixer.defaultTextFormatter.textFormatter.vptr = PrePostDollarFixer_vptr;

	this->prePostFixer.pre = other->prePostFixer.pre;
	this->prePostFixer.post = other->prePostFixer.post;
	 printf("--- PrePostDollarFixer Copy CTOR: \"%s\"...\"%s\"\n", this->prePostFixer.pre, this->prePostFixer.post);
}

void PrePostDollarFixer_dtor(PrePostDollarFixer* const this)
{
	printf("--- PrePostDollarFixer DTOR: \"%s\"...\"%s\"\n", this->prePostFixer.pre, this->prePostFixer.post);
	
	PrePostFixer_dtor(&(this->prePostFixer));
}

void PrePostDollarFixer_print_ic(const PrePostDollarFixer* const this, int num, char symbol/* = '$'*/)
{
	printf("%-60s | ", "[PrePostDollarFixer::print(int, char)]"); 
    printf("-->\n");

    (this->prePostFixer.defaultTextFormatter.textFormatter.vptr)[2](this, (long)num, symbol);
}

/*virtual*/void PrePostDollarFixer_print_lc(const PrePostDollarFixer* const this, long num, char symbol /*= '$'*/)
{
	printf("%-60s | ", "[PrePostDollarFixer::print(long, char)]"); 
    printf("-->\n");
	PrePostFixer_print_lc(&(this->prePostFixer), num, symbol);
}

void PrePostDollarFixer_print_dc(const PrePostDollarFixer* const this, double num, char symbol /*= '$'*/)
{
	printf("%-60s | ", "[PrePostDollarFixer::print(double, char)]"); 
    printf("%s%c%f%s\n", this->prePostFixer.pre, symbol, num, this->prePostFixer.post);
}

/*virtual*/char PrePostDollarFixer_getDefaultSymbol(const PrePostDollarFixer* const this)
{
	return '$';
}

/*PrePostHashFixer*/

func_ptr prePostHashFixer_vptr[] = {(func_ptr)PrePostHashFixer_dtor, (func_ptr)PrePostFixer_print_c,(func_ptr)PrePostHashFixer_print_ic, (func_ptr)PrePostHashFixer_getDefaultSymbol};


/*virtual*/char PrePostHashFixer_getDefaultSymbol(const PrePostHashFixer* const this)
{
    return '#';
}


void PrePostHashFixer_ctor(PrePostHashFixer* const this, int prc) 
{
    PrePostDollarFixer_ctor(&(this->prePostDollarFixer), "===> ", " <===");
    this->prePostDollarFixer.prePostFixer.defaultTextFormatter.textFormatter.vptr = prePostHashFixer_vptr;
    this->precision = prc;
    printf("--- PrePostHashFixer CTOR: \"%s\"...\"%s\", precision: %d\n", this->prePostDollarFixer.prePostFixer.pre, this->prePostDollarFixer.prePostFixer.post, this->precision);   

    printf("%-60s | ","[PrePostHashFixer::print(double, char)]");

    printf("%s[%c%.*f]%s\n", this->prePostDollarFixer.prePostFixer.pre, '#', this->precision, 9999.9999, this->prePostDollarFixer.prePostFixer.post);
}

void PrePostHashFixer_dtor(PrePostHashFixer* const this)
{
    printf("--- PrePostHashFixer DTOR: \"%s\"...\"%s\"\n", this->prePostDollarFixer.prePostFixer.pre, this->prePostDollarFixer.prePostFixer.post);
    this->prePostDollarFixer.prePostFixer.defaultTextFormatter.textFormatter.vptr = PrePostDollarFixer_vptr;
    PrePostDollarFixer_dtor(&(this->prePostDollarFixer));
}
    
void PrePostHashFixer_print_ic(const PrePostHashFixer* const this, int num, char symbol)
{
    printf("%-60s | ", "[PrePostHashFixer::print(int, char)]"); 
    printf("-->\n");

    printf("%-60s | ","[PrePostHashFixer::print(double, char)]");

    printf("%s[%c%.*f]%s\n", this->prePostDollarFixer.prePostFixer.pre, symbol, this->precision, (double)num, this->prePostDollarFixer.prePostFixer.post);
}

void PrePostHashFixer_print_lc(const PrePostHashFixer* const this, long num, char symbol)
{
    printf("%-60s | ", "[PrePostHashFixer::print(long, char)]");
    printf("-->\n");
	
	printf("%-60s | ","[PrePostHashFixer::print(double, char)]");

    printf("%s[%c%.*f]%s\n", this->prePostDollarFixer.prePostFixer.pre, symbol, this->precision, (double)num, this->prePostDollarFixer.prePostFixer.post);
}

/* PrePostFloatDollarFixer Defs */
func_ptr PrePostFloatDollarFixer_vptr[] = {(func_ptr)PrePostFloatDollarFixer_dtor, (func_ptr)PrePostFixer_print_c,(func_ptr)PrePostHashFixer_print_ic, (func_ptr)PrePostFloatDollarFixer_getDefaultSymbol};

void PrePostFloatDollarFixer_ctor(PrePostFloatDollarFixer* const this, const char* prefix, const char* postfix)
{
    PrePostDollarFixer_ctor(&(this->prePostDollarFixer),prefix, postfix);
    this->prePostDollarFixer.prePostFixer.defaultTextFormatter.textFormatter.vptr = PrePostFloatDollarFixer_vptr;
    printf("--- PrePostFloatDollarFixer CTOR: \"%s\"...\"%s\"\n", this->prePostDollarFixer.prePostFixer.pre, this->prePostDollarFixer.prePostFixer.post);
}

void PrePostFloatDollarFixer_dtor(PrePostFloatDollarFixer* const this)
{
    printf("--- PrePostFloatDollarFixer DTOR: \"%s\"...\"%s\"\n", this->prePostDollarFixer.prePostFixer.pre, this->prePostDollarFixer.prePostFixer.post);
    PrePostDollarFixer_dtor(&(this->prePostDollarFixer));
}

void PrePostFloatDollarFixer_print_f(const PrePostFloatDollarFixer* const this, float num)
{
    printf("%-60s | ", "[PrePostFloatDollarFixer::print(float)]"); 
    printf("-->\n");

    PrePostFloatDollarFixer_print_fc(this, num, '@');
}

void PrePostFloatDollarFixer_print_fc(const PrePostFloatDollarFixer* const this, float num, char symbol)
{
     printf("%-60s | ","[PrePostFloatDollarFixer::print(float, char)]"); 

    printf("%s%c%.2f%s\n", this->prePostDollarFixer.prePostFixer.pre, symbol, num, this->prePostDollarFixer.prePostFixer.post);
}

/*virtual*/char PrePostFloatDollarFixer_getDefaultSymbol(const PrePostFloatDollarFixer* const this)
{
	return '@';
}


/* PrePostChecker Defs */

func_ptr PrePostChecker_vptr[] = {(func_ptr)PrePostChecker_dtor, (func_ptr)PrePostFixer_print_c,(func_ptr)PrePostHashFixer_print_ic, (func_ptr)PrePostFloatDollarFixer_getDefaultSymbol};

void PrePostChecker_ctor(PrePostChecker* const this)
{
	PrePostFloatDollarFixer_ctor(&(this->prePostFloatDollarFixer),"[[[[ ", " ]]]]");
	this->prePostFloatDollarFixer.prePostDollarFixer.prePostFixer.defaultTextFormatter.textFormatter.vptr = PrePostFloatDollarFixer_vptr;
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", 
    this->prePostFloatDollarFixer.prePostDollarFixer.prePostFixer.pre, 
    this->prePostFloatDollarFixer.prePostDollarFixer.prePostFixer.post);
}    

/*virtual*/void PrePostChecker_dtor(PrePostChecker* const this)
{
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", this->prePostFloatDollarFixer.prePostDollarFixer.prePostFixer.pre, 
    this->prePostFloatDollarFixer.prePostDollarFixer.prePostFixer.post);
    PrePostFloatDollarFixer_dtor(&(this->prePostFloatDollarFixer));
}

void printThisSymbolUsingFunc(const PrePostChecker* const this)
{
    printf("%-60s | ","[PrePostChecker::printThisSymbolUsingFunc()]");

    printf("Default symbol is %c\n", 
    ((char(*)())this->prePostFloatDollarFixer.prePostDollarFixer.prePostFixer.defaultTextFormatter.textFormatter.vptr[3])(&(this->prePostFloatDollarFixer)));

}

void printThisSymbolDirectly(const PrePostChecker* const this)
{
    printf("%-60s | ","[PrePostChecker::printThisSymbolDirectly()]");

    printf("Default symbol is %c\n", '@');
}

void printDollarSymbolByCastUsingFunc(const PrePostChecker* const this)
{
    printf("%-60s | ","[PrePostChecker::printDollarSymbolByCastUsingFunc()]");

    printf("Default symbol is %c\n",((char(*)())((PrePostDollarFixer*)(this))->prePostFixer.defaultTextFormatter.textFormatter.vptr[3])(this));
}

void printDollarSymbolByScopeUsingFunc(const PrePostChecker* const this)
{
    printf("%-60s | ","[PrePostChecker::printDollarSymbolByScopeUsingFunc()]");

    printf("Default symbol is %c\n", PrePostDollarFixer_getDefaultSymbol(&(this->prePostFloatDollarFixer.prePostDollarFixer)));
}

void printDollarSymbolByCastDirectly(const PrePostChecker* const this)
{
    printf("%-60s | ","[PrePostChecker::printDollarSymbolByCastDirectly()]");

    printf("Default symbol is %c\n", '$');
}

void printDollarSymbolByScopeDirectly(const PrePostChecker* const this)
{
     printf("%-60s | ","[PrePostChecker::printDollarSymbolByScopeDirectly()]");

    printf("Default symbol is %c\n",'$');
}


/* Multiplier Defs */
  
func_ptr Multiplier_vptr[] = {(func_ptr)Multiplier_dtor,(func_ptr)DefaultTextFormatter_print_c};
  
/*virtual*/void Multiplier_dtor(Multiplier* const this)
{
    printf("--- Multiplier DTOR: times = %d\n", this->times);
    this->defaultTextFormatter.textFormatter.vptr = defaultTextFormatter_vptr;
    DefaultTextFormatter_dtor(&(this->defaultTextFormatter));
}

    
void Multiplier_print_c(const Multiplier* const this, const char* text)
{
  	printf("%-60s | ","[Multiplier::print(const char*)]");
    
    for (int i = 0; i < (this->times); ++i)
        printf("%s", text);
    printf("\n");
}














