#include "poli_defs.h"

void doPrePostFixer()
{
	PrePostFixer angleBrackets;
    printf("\n--- start doPrePostFixer() ---\n\n");

   	PrePostFixer_ctor(&angleBrackets,"<<< ", " >>>");
    PrePostFixer_print_c(&angleBrackets,"Hello World!");
    PrePostFixer_print_lc(&angleBrackets, -777, '\0');
   	PrePostFixer_print_lc(&angleBrackets, 350, '#');
    PrePostFixer_print_lc(&angleBrackets, (long int)(3.14), '\0');

    printf("\n--- end doPrePostFixer() ---\n\n");
    
    PrePostFixer_dtor(&angleBrackets);
}

void doPrePostDollarFixer()
{
    PrePostDollarFixer asterisks;
    printf("\n--- start doPrePostDollarFixer() ---\n\n");

    PrePostDollarFixer_ctor(&asterisks, "***** ", " *****");
    PrePostDollarFixer_print_ic(&asterisks,-777,'$');
    PrePostDollarFixer_print_ic(&asterisks,350, '#');
    PrePostDollarFixer_print_dc(&asterisks, 3.14f,'$');

    printf("\n--- end doPrePostDollarFixer() ---\n\n");
    
    PrePostDollarFixer_dtor(&asterisks);
}

void doPrePostChecker()
{
    PrePostChecker check;
    
    printf("\n--- start doPrePostChecker() ---\n\n");
    
    PrePostChecker_ctor(&check);
    
    printThisSymbolUsingFunc(&check);
    printThisSymbolDirectly(&check);
    printDollarSymbolByCastDirectly(&check);
    printDollarSymbolByScopeDirectly(&check);
    printDollarSymbolByCastUsingFunc(&check);
    printDollarSymbolByScopeUsingFunc(&check);

    printf("\n--- end doPrePostChecker() ---\n\n");
    
    PrePostChecker_dtor(&check);
}

void doPrePostFloatDollarFixer()
{
    PrePostFloatDollarFixer hashes;
    PrePostDollarFixer hashes2;
    
    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");

    PrePostFloatDollarFixer_ctor(&hashes,"### ", " ###");
    PrePostFloatDollarFixer_print_f(&hashes,-777);
    PrePostFloatDollarFixer_print_fc(&hashes,350, '#');
    PrePostFloatDollarFixer_print_f(&hashes,3.14f);

    PrePostDollarFixer_cpyCtor(&hashes2, (PrePostDollarFixer*)&hashes);
    
    PrePostDollarFixer_print_dc(&hashes2,7.5,'$');
    PrePostDollarFixer_print_ic(&hashes2,100,'$');

    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");
    PrePostDollarFixer_dtor(&hashes2);
    PrePostFloatDollarFixer_dtor(&hashes);
}

void runAsPrePostFixerRef(const PrePostFixer* pp)
{
    printf("\n--- start runAsPrePostFixerRef() ---\n\n");

    (pp->defaultTextFormatter.textFormatter.vptr[2])(pp, 123, '\0');

    printf("\n--- end runAsPrePostFixerRef() ---\n\n");
}

int main()
{
    printf("\n--- Start main() ---\n\n");

    doPrePostFixer();
    doPrePostDollarFixer();
    doPrePostFloatDollarFixer();
    doPrePostChecker();

    /*PrePostHashFixer hfix;
    runAsPrePostFixerRef(hfix);
    runAsPrePostDollarFixerRef(hfix);
    runAsPrePostDollarFixerObj(hfix);
    runAsPrePostHashFixerRef(hfix);

    doMultiplier();

    doFormatterArray();
    doFormatterPtrs();
    doFormatterDynamicArray();*/

    printf("\n--- End main() ---\n\n");

    return 0;
}
