#include <stdio.h>

int question(char *message)
{
    while (1)
    {
        if (message[0] != '\n')
            printf("\n");
        printf(message);
        printf(" (Y/N):");

        switch (getchar())
        {
        case 'n':
        case 'N':
            return 0;
        case 'y':
        case 'Y':
            return 1;
        default:
            while (getchar() != '\n')
                ;
            printf("Wrong answer");
        }
    }
}

int scan_int(char* message)
{
    int buff;

    if (message != 0)
    {
        if (message[0] != '\n')
            printf("\n");
        printf(message);
    }
    scanf("%d", &buff);
    
    return buff;
}

int scan_int_min(char *message, int min)
{
    int buff;
    do
    {
        buff = scan_int(message);

        if (buff < min)
            printf("\nЗначение должно быть не меньше %d", min);
    } while (buff < min);

    return buff;
}

void print_array(int *array, int length)
{
    printf("| ");
    for (int i = 0; i < length; ++i)
        printf("%d ", array[i]);
    printf("|");
}

void print_array_double(double *array, int length)
{
    printf("| ");
    for (int i = 0; i < length; ++i)
        printf("%.2lf ", array[i]);
    printf("|");
}

int scan_variant(char* message, int count, char* variantes[count])
{
    printf(message);
    printf(" (введите 0-%d)", count-1);

    char buff;

    while(1)
    {
        for(int i = 0; i < count; ++i)
            printf("\n%d - %s", i, variantes[i]);
        printf("\nНомер варианта: ");

        buff = getchar();
        while(getchar() != '\n');

        if('0' <= buff && buff < '0' + count)
            return buff - '0';

        printf("wrong\n");
    }
}