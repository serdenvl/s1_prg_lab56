#include <stdio.h>
#include <stdlib.h>

/*
Задание 22
 Для квадратной матрицы размера n*n подсчитать среднее арифметическое
элементов каждого столбца, исключая элемент на главной диагонали, и сформиро-
вать из них вектор. Найти минимальный элемент этого вектора.

 Решить для динамического и статического массива.
*/
/*
 Попытайтесь исполнить эту программу, изменив параметры циклов так, чтобы реально
обрабатываемый массив был меньше объявленного.
 Попытайтесь исполнить эту программу, изменив параметры циклов так, чтобы реально
обрабатываемый массив был больше объявленного.
 Переработайте программу, используя (вместо обращения по индексу) механизм обращения по адресу.
*/

#define random(min, max) ( (rand() % (max + 1 - min)) + min )

int select_size()
{
    int v = scan_variant("Выберите размер N квадратной матрицы", 2, (char*[]){
        "Размер по умолчанию (5)",
        "Ввести вручную",
    });

    return (v == 0) ? 5 : scan_int_min("Размер матрицы: ", 2);
}

void fill_matrix(int M, int N, int matrix[M][N])
{
    int v = scan_variant("Выберите способ заполнения матрицы", 3, (char*[]){
        "Заполнить случайными числами в диапазоне [10,29]",
        "Заполнить случайными числами в выбранном диапазоне",
        "Ввести вручную",
    });

    if(v == 0 || v == 1)
    {
        int min = (v == 0) ? 10 : scan_int("min, max:");
        int max = (v == 0) ? 29 : scan_int(0);

        printf("\nМинимум: %d\nМаксимум: %d", min, max);

        for(int i = 0; i < M; ++i)
            for(int j = 0; j < N; ++j)
                matrix[i][j] = random(min, max);
    }
    else
    {
        printf("Элементы: ");
        for(int i = 0; i < M; ++i)
            for(int j = 0; j < N; ++j)
                matrix[i][j] = scan_int(0);
    }
}

void print_matrix(int M, int N, int matrix[M][N])
{
    for(int i = 0; i < M; ++i)
    {
        printf("\n| ");
        for(int j = 0; j < N; ++j)
            printf("%d ", matrix[i][j]);
        printf("|");
    }
}

void strange_average_columns(int M, int N, int matrix[M][N], double averages[N])
{
    for(int j = 0; j < N; ++j)
        averages[j] = 0;
    for(int i = 0; i < M; ++i)
        for(int j = 0; j < N; ++j)
            averages[j] += (i != j) ? matrix[i][j] : 0;
    for(int j = 0; j < N; ++j)
        averages[j] /= N-1;
}

double array_min(double* array, int length)
{
    double res = array[0];
    for(int i = 1; i < length; ++i)
        res = (array[i] < res) ? array[i] : res;
    return res; 
}

#define description "Задание: \n\
Сформировать матрицу размера NxN\n\
Вывести средние арифметические столбцов, исключая главную диагональ\n\
Вывести наименьшее из значений вектора\n\
"

/** #define IS_STATIC /**/
#ifdef IS_STATIC
    #define DEF_ARRAY(t,name,M,N) t name[M][N]
    #define DEF_FREE(name) //
    #define ARRAY_TYPE_MESSAGE "статическим"
#else
    #define DEF_ARRAY(t,name,M,N) t *name = malloc(M*N*sizeof(t))
    #define DEF_FREE(name) free(name);
    #define ARRAY_TYPE_MESSAGE "динамическим"
#endif

int main()
{
    printf(description);
    printf("\nВариант с " ARRAY_TYPE_MESSAGE " массивом.\n\n");

    int N = select_size();
    DEF_ARRAY(int, matrix, N, N);
    
    printf("\n");
    fill_matrix(N, N, matrix);

    printf("\n\nМатрица: ");
    print_matrix(N, N, matrix);

    double averages[N];
    strange_average_columns(N, N, matrix, averages);
    printf("\n\nСреднее арифметическое стобцов: ");
    print_array_double(averages, N);

    printf("\nМинимум из средних арифметических: %.2lf", array_min(averages, N));
    DEF_FREE(matrix);

    getchar();
}