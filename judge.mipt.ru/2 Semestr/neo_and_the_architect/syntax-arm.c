#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>
#include <string.h>

char a[100024];

int load_stream()
{
    char c;
    unsigned int i = 0;
    unsigned int flag = 1;
    while (scanf("%c", &c) == 1)
        if (c == '"')
            flag = !flag;
        else
            if (flag)
                a[i++] = towlower(c);
    return i;
}

void printf_stream(unsigned int length)
{
	int i;
    for ( i = 0; i < length; i++)
        printf("%c", a[i]);
}

int main()
{
    unsigned int length_of_stream = load_stream();
    if (strstr(a, "ldr"))
    {
        printf("0 ");
        if (strstr(a, "vldr") || strstr(a, "vstr"))
            printf("1");
        else
            printf("0");
    }
    else
        if(strstr(a, "ax") || strstr(a, "bx") || strstr(a, "cx") || strstr(a, "dx") || strstr(a, "sp")
                || strstr(a, "bp") || strstr(a, "cs") || strstr(a, "ds") || strstr(a, "ss") || strstr(a, "si") || strstr(a, "di"))
        {
            printf("86 ");
            if (strstr(a, "rax") || strstr(a, "rbx") || strstr(a, "rcx") || strstr(a, "rdx") || strstr(a, "rsp")
                    || strstr(a, "rbp") || strstr(a, "rcs") || strstr(a, "rds") || strstr(a, "rss") || strstr(a, "rsi") || strstr(a, "rdi"))
            {
                if (strstr(a, "%rax") || strstr(a, "%rbx") || strstr(a, "%rcx") || strstr(a, "%rdx") || strstr(a, "%rsp")
                        || strstr(a, "%rbp") || strstr(a, "%rcs") || strstr(a, "%rds") || strstr(a, "%rss") || strstr(a, "%rsi") || strstr(a, "%rdi")
                        || strstr(a, "%eax") || strstr(a, "%ebx") || strstr(a, "%ecx") || strstr(a, "%edx") || strstr(a, "%esp")
                        || strstr(a, "%ebp") || strstr(a, "%ecs") || strstr(a, "%eds") || strstr(a, "%ess") || strstr(a, "%esi") || strstr(a, "%edi")
                        || strstr(a, "%ax") || strstr(a, "%bx") || strstr(a, "%cx") || strstr(a, "%dx") || strstr(a, "%sp")
                        || strstr(a, "%bp") || strstr(a, "%cs") || strstr(a, "%ds") || strstr(a, "%ss") || strstr(a, "%si") || strstr(a, "%di"))
                    printf("1 ");
                else
                    printf("0 ");

                if (strstr(a, "finit") || strstr(a, "fld") || strstr(a, "fst"))
                    printf("1 ");
                else
                    printf("0 ");
                printf("64");
            }
            else
                if (strstr(a, "eax") || strstr(a, "ebx") || strstr(a, "ecx") || strstr(a, "edx") || strstr(a, "esp")
                        || strstr(a, "ebp") || strstr(a, "ecs") || strstr(a, "eds") || strstr(a, "ess") || strstr(a, "esi") || strstr(a, "edi"))
                {
                    if (strstr(a, "%rax") || strstr(a, "%rbx") || strstr(a, "%rcx") || strstr(a, "%rdx") || strstr(a, "%rsp")
                            || strstr(a, "%rbp") || strstr(a, "%rcs") || strstr(a, "%rds") || strstr(a, "%rss") || strstr(a, "%rsi") || strstr(a, "%rdi")
                            || strstr(a, "%eax") || strstr(a, "%ebx") || strstr(a, "%ecx") || strstr(a, "%edx") || strstr(a, "%esp")
                            || strstr(a, "%ebp") || strstr(a, "%ecs") || strstr(a, "%eds") || strstr(a, "%ess") || strstr(a, "%esi") || strstr(a, "%edi")
                            || strstr(a, "%ax") || strstr(a, "%bx") || strstr(a, "%cx") || strstr(a, "%dx") || strstr(a, "%sp")
                            || strstr(a, "%bp") || strstr(a, "%cs") || strstr(a, "%ds") || strstr(a, "%ss") || strstr(a, "%si") || strstr(a, "%di"))
                        printf("1 ");
                    else
						printf("0 ");

                    if (strstr(a, "finit") || strstr(a, "fld") || strstr(a, "fst"))
                        printf("1 ");
                    else
                        printf("0 ");
                    printf("32");
                }
                else
                {
                    if (strstr(a, "%rax") || strstr(a, "%rbx") || strstr(a, "%rcx") || strstr(a, "%rdx") || strstr(a, "%rsp")
                            || strstr(a, "%rbp") || strstr(a, "%rcs") || strstr(a, "%rds") || strstr(a, "%rss") || strstr(a, "%rsi") || strstr(a, "%rdi")
                            || strstr(a, "%eax") || strstr(a, "%ebx") || strstr(a, "%ecx") || strstr(a, "%edx") || strstr(a, "%esp")
                            || strstr(a, "%ebp") || strstr(a, "%ecs") || strstr(a, "%eds") || strstr(a, "%ess") || strstr(a, "%esi") || strstr(a, "%edi")
                            || strstr(a, "%ax") || strstr(a, "%bx") || strstr(a, "%cx") || strstr(a, "%dx") || strstr(a, "%sp")
                            || strstr(a, "%bp") || strstr(a, "%cs") || strstr(a, "%ds") || strstr(a, "%ss") || strstr(a, "%si") || strstr(a, "%di"))
                        printf("1 ");
                    else
                        printf("0 ");

                    if (strstr(a, "finit") || strstr(a, "fld") || strstr(a, "fst"))
                        printf("1 ");
                    else
                        printf("0 ");

                    printf("16");
                }
        }
        else
            if (strstr(a, "ldr") || strstr(a, "str"))
            {
                printf("0 ");
                if (strstr(a, "vldr") || strstr(a, "vstr"))
                    printf("1");
                else
                    printf("0");
            }
    return 0;
}
