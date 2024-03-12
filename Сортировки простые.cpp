#include <iostream>
#include <chrono>
using namespace std;

void creature_mas_rand(int* ptr, int n); //создание массива случайно
void creature_mas_hands(int* ptr, int n); //создание массива с клавиатуры
void print(int* ptr, int n); //вывод массива
void Merge_mas(int* mas, int first_index, int last_index, int all_size); //слияние массивов
void Merge_Sort(int* mas, int first_index, int last_index, int all_size); //Сортировка слиянием
void Quick_Sort(int* mas, int size); //быстрая Сортировка
void Sort_by_Count(int* A_mas, int mas_size); //сортировка подсчетом
void Block_Sort(int* mas, int size_mas); //блочная сортировка
void Shell_Sort(int* mas, int size_mas); //Сортровка Шелла
void Khoar_Sort(int* mas, int left, int right, int N); //Сортировка Хоара

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    int mas_size = 25, choice;
    int* mas = new int[mas_size]; //создание массива

    do {
        cout << "Каким способом вы хотите создать массив? " << endl;
        cout << "1 - Ввести ручками" << endl;
        cout << "2 - Создать случайно" << endl;
        cin >> choice;
    } while (choice < 1 || choice > 2);

    switch (choice) { //выбор способа создания массива
    case 1: {
        creature_mas_hands(mas, mas_size);
        break;
    }
    default: {
        creature_mas_rand(mas, mas_size); //создание массива случайно
        break;
    }
    }

    cout << endl << "Создан массив!" << endl;
    print(mas, mas_size); //вывод массива

    do { //выбор сортировки
        cout << "Каким способом отсортировать массив? " << endl;
        cout << "1 - Сортировка слиянием" << endl;
        cout << "2 - Быстрая сортировка" << endl;
        cout << "3 - Сортировка подсчетом" << endl;
        cout << "4 - Блочная  сортировка" << endl;
        cout << "5 - Сортировка Шелла" << endl;
        cout << "6 - Сортировка Хоара" << endl;
        cin >> choice;
    } while (choice < 1 || choice > 6);

    auto start_time_recursive = chrono::steady_clock::now();  // начальное время
    switch (choice) { //выбор сортировки
    case 1: {
        Merge_Sort(mas, 0, mas_size - 1, mas_size); //сортировка слиянием
        break;
    }
    case 2: {
        Quick_Sort(mas, mas_size); //быстрая сортировка
        break;
    }
    case 3: {
        Sort_by_Count(mas, mas_size); //сортировка подсчетом
        break;
    }
    case 4: {
        Block_Sort(mas, mas_size); //блочная сортировка
        break;
    }
    case 5: {
        Shell_Sort(mas, mas_size); //сортировка шелла
        break;
    }
    default: {
        Khoar_Sort(mas, 0, mas_size - 1, mas_size); //сортировка хоара
        break;
    }
    }
    auto end_time_recursive = chrono::steady_clock::now(); // конечное время
    auto diff_time = end_time_recursive - start_time_recursive; //разница между начальным и конечным временем
    print(mas, mas_size); //вывод массива

    cout << "Сортировка выполнена за " << chrono::duration <double, milli>(diff_time).count() << " ms" << endl << endl;

    return 0;
}

void creature_mas_rand(int* ptr, int n) { //создаю массив через датчик случайных чисел
    for (int i = 0; i < n; i++) {
        ptr[i] = rand() % 1000 + 1; //случайное число от 1 до 1000
    }
}
void creature_mas_hands(int* ptr, int n) { //создание массива с клавиатуры
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << "Введите элемент " << i + 1 << ": ";
        cin >> ptr[i];
    }
}
void print(int* ptr, int n) { //вывод текущего массива
    cout << endl << "Текущий массив:" << endl;
    for (int i = 0; i < n; i++) { //прохожу по массиву
        cout << ptr[i] << ' ';
    }
    cout << endl << endl;
}

//Сортировка слиянием----------------------
void Merge_mas(int* mas, int first_index, int last_index, int all_size) { //слияние массивов
    int arithmetic_mean, start, final;
    int* new_mas = new int[all_size];

    arithmetic_mean = (first_index + last_index) / 2; //вычисление среднего арифметического
    start = first_index; //начало левой части

    final = arithmetic_mean + 1; //начало правой части
    for (int i = first_index; i <= last_index; i++) { //иду от начала до конца
        if ((start <= arithmetic_mean) && ((final > last_index) || (mas[start] < mas[final]))) {
            new_mas[i] = mas[start]; //запись начала
            start++; //меняю начало
        }
        else {
            new_mas[i] = mas[final]; //запись конца
            final++; //меняю конец
        }
    }
    for (int i = first_index; i <= last_index; i++) { //запись в основной массив
        mas[i] = new_mas[i]; //запись
    }
    delete[] new_mas; //освобождаю память
}

void Merge_Sort(int* mas, int first_index, int last_index, int all_size) { //рекурсивная процедура сортировки
    if (first_index < last_index) {
        Merge_Sort(mas, first_index, (first_index + last_index) / 2, all_size); //сортировка левой части
        Merge_Sort(mas, (first_index + last_index) / 2 + 1, last_index, all_size); //сортировка правой части
        Merge_mas(mas, first_index, last_index, all_size); //слияние двух частей

    }
}
//------------------------------------------

void Quick_Sort(int* mas, int size) { //быстрая Сортировка
    int first_index = 0; //указатель в начало массива
    int last_index = size - 1; //указатель в конец массива
    int middle = mas[size / 2];//центральный элемент массива
    do { //деление массива
        while (mas[first_index] < middle) { //в левой части оставляем элементы которые меньше центрального
            first_index++;
        }
        while (mas[last_index] > middle) { //в правой части оставляем элементы которые больше центрального
            last_index--;
        }
        //меняю элементы местами
        if (first_index <= last_index) { //если индекс первого элемента меньше индекса последнего
            int tmp = mas[first_index];
            mas[first_index] = mas[last_index];
            mas[last_index] = tmp;
            first_index++; //увеличиваю индекс начала
            last_index--; //уменьшаю индекс конца
        }
    } while (first_index <= last_index);

    //если осталось что сортировать - рекурсия
    if (last_index > 0) {
        Quick_Sort(mas, last_index + 1); //левая часть
    }
    if (first_index < size) {
        Quick_Sort(&mas[first_index], size - first_index); //правая часть
    }
}

void Sort_by_Count(int* A_mas, int mas_size) { //сортировка подсчетом
    int max_index = 0, min_index = 0;
    for (int i = 0; i < mas_size; i++) { //нахожу максимальный и минимальный элементы
        if (A_mas[i] > max_index)
            max_index = A_mas[i]; //индекс максимального элемента
        if (A_mas[i] < min_index)
            min_index = A_mas[i]; //индекс минимального элемента
    }
    int number_of_different_values = max_index - min_index + 1; //максимально возможное количество разных значений в массиве
    int* B_mas = new int[number_of_different_values]; //массив для подсчета количество разных значений в основном массиве
    for (int i = 0; i < number_of_different_values; i++) { //заполняю 0 новый массив
        B_mas[i] = 0;
    }
    for (int i = 0; i < mas_size; i++) { //подсчет количества каждого значения
        B_mas[A_mas[i] - min_index]++;
    }
    int counter = 0; //счетчик индекса для основного массива
    for (int i = 0; i < number_of_different_values; i++) { //проход по массиву значений
        for (int j = 0; j < B_mas[i]; j++) { //запись значения необходимое число раз
            A_mas[counter++] = i + min_index; //запись значения в основной массив
        }
    }
    delete[] B_mas; //очищаю память
}

void Block_Sort(int* mas, int size_mas) { //блочная сортировка

    int max_element = mas[0]; //максимальный элемент
    int min_element = mas[0]; //минимальный элемент

    for (int i = 1; i < size_mas; i++) {
        if (mas[i] > max_element) { //нахожу максимальный элемент
            max_element = mas[i];
        }
        if (mas[i] < min_element) { //нахожу минимальный элемент
            min_element = mas[i];
        }
    }

    int the_numbers_in_the_block = 5; //сколько чисел максимум войдет в один блок
    int total_blocks = ((max_element - min_element) / the_numbers_in_the_block); //количество блоков
    int** blocks{ new int* [total_blocks] }; //двумерный массив блоков

    for (int i = 0; i < total_blocks; i++) { //инициализация массива
        blocks[i] = new int[size_mas];
    }

    for (int i = 0; i < size_mas; i++) { //распределение чесел по блокам
        int bucket_index = ((mas[i] - min_element) / total_blocks); //в какой блок определить элемент
        blocks[bucket_index][i] = mas[i]; //записываю число в блок
    }
    //сортировка каждого блока методом всавки
    for (int i = 0; i < total_blocks; i++) { //проход по блокам
        for (int j = 0; j < size_mas; j++) { //первое число для сравнения
            for (int k = j + 1; k < size_mas; k++) { //второе число для сравнения
                if (blocks[i][j] > blocks[i][k]) { //если необходимо поменять элементы
                    int memory = blocks[i][j]; //временная переменная для запоминания
                    blocks[i][j] = blocks[i][k];
                    blocks[i][k] = memory;
                }
            }
        }
    }

    int counter = 0; //счетчик для основного массива
    for (int i = 0; i < total_blocks; i++) { //прохожу по блокам
        for (int j = 0; j < size_mas; j++) { //прохожу по элементам в блоке
            if (blocks[i][j] > -1) { //если элемент - НЕ мусор
                mas[counter++] = blocks[i][j]; //запись элемента
            }
        }
    }

    for (int i = 0; i < total_blocks; i++) { //освобождение памяти
        delete[] blocks[i]; //удаление элемента в блоке
    }
    delete[] blocks; //удаление массива
}

void Shell_Sort(int* mas, int size_mas) { //Сортровка Шелла
    int tmp, j;
    for (int step = size_mas / 2; step > 0; step /= 2) { //пока длина шага больше 0. после каждой итерации шаг уменьшается
        for (int i = step; i < size_mas; i++) { //прохожу по массиву с шагом step
            tmp = mas[i]; //запоминаю значение текущего элемента
            for (j = i; j >= step; j -= step) { //прохожу с шагом step
                if (tmp < mas[j - step]) { //Если tmp меньше, мы меняем местами tmp и элемент массива на j - step
                    mas[j] = mas[j - step];
                }
                else { //Если tmp больше или равен элементу массива на j - step, мы прерываем цикл
                    break;
                }
            }
            mas[j] = tmp; //меняю значение текущего элемента
        }
    }
}

void Khoar_Sort(int* mas, int left, int right, int N) { //Сортировка Хоара
    int i, j, support_element, tmp; // tmp - временная переменная для обмена
    i = left; // левая граница
    j = right; // правая граница
    support_element = mas[(left + right) / 2]; //опорный элемент для сортировки
    do {
        while ((mas[i] < support_element) && (i < right)) i++; //пока элемент массива на позиции i не станет больше или равен опорному и i не станет больше правой границы
        while ((support_element < mas[j]) && (j > left)) j--; //пока элемент массива на позиции j не станет меньше или равен опорному и j не станет меньше левой границы
        if (i <= j) { //меняем местами элементы массива на позициях i и j с помощью переменной tmp
            tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;
            i++; //увеличиваю левую границу
            j--; //уменьшаю правую границу

        }
    } while (i <= j);
    //проверяем, не выходят ли границы i и j за пределы массива
    if (left < j) Khoar_Sort(mas, left, j, N);
    if (i < right) Khoar_Sort(mas, i, right, N);
}
/*
156 
492 
707 
267 
184 
305 
418 
537 
1 
818 
845 
805 
1 
136 
209 
996 
231 
231 
58 
879 
435 
180 
839 
975 
231
*/