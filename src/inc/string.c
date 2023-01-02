#include <stddef.h>
#include "string.h"


// implementação absurdamente rápida da função strlen
// TODOS OS CREDITOS VÃO AO https://github.com/Ch4r0nN/
size_t strlen(const char *str) { 
    register int count ; 
    
    // output = count
    // input = src, 0, 0xffffffff
    __asm__ __volatile__ ("cld      \n\t"            
        "repne    \n\t" 
        "scasb    \n\t"
        "notl %0  \n\t"
        "decl %0"      
        : "=c" (count)
        : "D" (str), "a" (0), "0" (0xffffffff)); 

    return count; 
}

// implementação absurdamente rápida da função strcat
// TODOS OS CREDITOS VÃO AO https://github.com/Ch4r0nN/
char *strcat(char *dest, const char *src) { 
    // input = src, dest, 0, 0xffffffff
    __asm__ __volatile__ ("cld             \n\t" 
                          "repne           \n\t" 
                          "scasb           \n\t" 
                          "decl %1         \n" 
                          "1:\tlodsb       \n\t" 
                          "stosb           \n\t" 
                          "testb %%al,%%al \n\t" 
                          "jne 1b" 
                          :
                          :"S" (src),"D" (dest),"a" (0),"c" (0xffffffff)); 
    return dest; 
}