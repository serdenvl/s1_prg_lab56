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

    return (v == 0) ? 5 : scan_int_min("Размер матрицы: ",1);
}

void fill_matrix(int M, int N, int matrix[M][N])
{
    int v = scan_variant("Выберите способ заполнения матрицы", 3, (char*[]){
        "Заполнить случайными числами в диапазоне [10,29]",
        "Заполнить случайными числами в выбранном диапазоне",
        "Ввести вручную",
    });

    if(v < 2)
    {
        int min = (v == 0) ? 10 : scan_int("Минимум: ");
        int max = (v == 0) ? 29 : scan_int("Максимум: ");

        for(int i = 0; i < M; ++i)
            for(int j = 0; j < N; ++j)
                matrix[i][j] = random(min, max);
    }
    else if(v == 3)
    {
        for(int i = 0; i < M; ++i)
            for(int j = 0; j < N; ++j)
                matrix[i][j] = scan_int("");
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
    printf("\n\n");
}

void strange_average_columns(int M, int N, int matrix[M][N], int averages[N])
{
    for(int j = 0; j < N; ++j)
        averages[j] = 0;
    for(int i = 0; i < M; ++i)
        for(int j = 0; j < N; ++j)
            averages[j] += (i != j) ? matrix[i][j] : 0;
    for(int j = 0; j < N; ++j)
        averages[j] /= N-1;
}

int array_min(int* array, int length)
{
    int res = array[0];
    for(int i = 1; i < length; ++i)
        res = (array[i] < res) ? array[i] : res;
    return res; 
}

int main()
{
    int N = select_size();
    int matrix[N][N];
    
    fill_matrix(N, N, matrix);

    printf("Матрица: ");
    print_matrix(N, N, matrix);

    int averages[N];
    strange_average_columns(N, N, matrix, averages);
    printf("\nСреднее арифметическое стобцов: ");
    print_array(averages, N);

    printf("\nМинимум из средних арифметических: %d", array_min(averages, N));

}