#include <iostream>
#include <omp.h>
#include <locale.h>

void task1(){
    std::cout << "Последовательная область 1\n";
#pragma omp parallel
    {
        std::cout << "Параллельная область\n";
    }
    std::cout << "Последовательная область 2\n";
}

void task2() {
#pragma omp parallel
    {
#pragma omp master
        {
            std::cout << "Общее число порождённых нитей: " << omp_get_num_threads() << std::endl;
        }
        std::cout << "Мой порядковый номер: " << omp_get_thread_num() << std::endl;
    }
}

void task3() {
#pragma omp parallel
    {
        std::cout << "Параллельный регион 1\n";
    }
    std::cout << "\n";
#pragma omp parallel num_threads(3)
    {
        std::cout << "Параллельный регион 2\n";
    }
    std::cout << "\n";
    omp_set_num_threads(4);
#pragma omp parallel
    {
        std::cout << "Параллельный регион 3\n";
    }
}

void task4() {
    omp_set_dynamic(1); // 0 - позволит создать 128 нитей, 1 - позволит создать макс. число нитей, 16
#pragma omp parallel num_threads(128)
    {
#pragma omp master
        {
            std::cout << "Количество созданных нитей: " << omp_get_num_threads() << std::endl;
        }
        std::cout << "Мой порядковый номер: " << omp_get_thread_num() << std::endl;
    }
}

void task5(int argc, char* argv[]) {
    if (argc > 1) {
#pragma omp parallel if(!strcmp(argv[1], "parallel"))
        {
            std::cout << "Мой порядковый номер: " << omp_get_thread_num() << std::endl;
        }
    }
}

#ifdef _OPENMP
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");
    task1();
    task2();
    task3();
    task4();
    task5(argc, argv);
}
#endif


//     2 laba
// 
// pragma omp single
// pragma omp master
// 
// 
// zadanie 2.1
// auto t1 = omp_get_wtime
// #pragma omp parallel
// {
//  ...
// }
// auto t2 = omg_get_wtime - t
//
// 
// zadanie 2.7 (oblasti vidimosti)
// int a = 5;
// #pragma omp parallel shared(a) - chto-bi yavno ukazat' global a
// #pragma omp parallel private(a) - peredaet a i delaet ee local vnutri
// {
// int b = a*a;
// }
// 
// #pragma omp reduction