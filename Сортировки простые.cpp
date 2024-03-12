#include <iostream>
using namespace std;

void creature_mas(int* ptr, int n); //создание массива
void print(int* ptr, int n); //вывод массива

void Merge_mas(int* mas, int first_index, int last_index, int all_size); //слияние массивов
void Merge_Sort(int* mas, int first_index, int last_index, int all_size); //Сортировка слиянием

void qsortRecursive(int* mas, int size); //быстрая Сортировка

void Sort_by_Count(int* A_mas, int mas_size); //блочная сортировка


void Block_Sort(int* mas, int size_mas) {

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


void shellSort(int* array, int size) {
    int j;
    int tmp;
    for (int step = size / 2; step > 0; step /= 2) {
        for (int i = step; i < size; i++) {
            tmp = array[i];
            for (j = i; j >= step; j -= step) {
                if (tmp < array[j - step]) {
                    array[j] = array[j - step];
                }
                else {
                    break;
                }
            }
            array[j] = tmp;
        }
    }
}

void quicksort(int* items, int left, int right, int N) {
    int i, j, pivot, tmp; // tmp - временная переменная для обмена
    i = left; // левая граница
    j = right; // правая граница
    pivot = items[(left + right) / 2]; //pivot - опорный элемент
    do {
        while ((items[i] < pivot) && (i < right)) i++;
        while ((pivot < items[j]) && (j > left)) j--;
        if (i <=j) {
            tmp = items[i];
            items[i] = items[j];
            items[j] = tmp;
            i++;
            j--;

        }
    } while (i <= j);

    if (left < j) quicksort(items, left, j, N);
    if (i < right) quicksort(items, i, right, N);
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    int mas_size, choice;
    
    do {
        cout << "Сколько элементов в массиве?  ";
        cin >> mas_size;
    } while (mas_size < 1);

    int* mas = new int[mas_size];

    creature_mas(mas, mas_size); //создание массива
    cout << endl << "Создан массив " << endl;
    print(mas, mas_size); //вывод массива

    do {
        cout << "Каким способом отсортировать массив? " << endl;
        cout << "1 - Сортировка слиянием" << endl;
        cout << "2 - Быстрая сортировка" << endl;
        cout << "3 - Сортировка подсчетом" << endl;
        cout << "4 - Блочная  сортировка" << endl;
        cout << "5 - Сортировка Шелла" << endl;
        cout << "6 - Сортировка Хоара" << endl;
        cin >> choice;
    } while (choice < 1 || choice > 6);

    switch (choice) { //выбор сортировки
    case 1: {
        Merge_Sort(mas, 0, mas_size - 1, mas_size); //сортировка слиянием
        break;
    }
    case 2: {
        qsortRecursive(mas, mas_size);
        break;
    }
    case 3: {
        Sort_by_Count(mas, mas_size);
        break;
    }
    case 4: {
        Block_Sort(mas, mas_size);
        break;
    }
    case 5: {
        shellSort(mas, mas_size);
        break;
    }
    case 6: {
        quicksort(mas, 0, mas_size - 1, mas_size);
        break;
    }
    }
    print(mas, mas_size); //вывод массива

    return 0;
}

void creature_mas(int* ptr, int n) { //создаю массив через датчик случайных чисел
    for (int i = 0; i < n; i++) {
        ptr[i] = rand() % 100 + 1;
    }
}

void print(int* ptr, int n) { //вывод текущего массива
    cout << endl << "Текущий массив" << endl;
    for (int i = 0; i < n; i++) {
        cout << ptr[i] << ' ';
    }
    cout << endl << endl;
}

//Сортировка слиянием----------------------
void Merge_mas(int* mas, int first_index, int last_index, int all_size) { //слияние массивов
    int arithmetic_mean, start, final, j;
    int* new_mas = new int[all_size];

    arithmetic_mean = (first_index + last_index) / 2; //вычисление среднего арифметического
    start = first_index; //начало левой части

    final = arithmetic_mean + 1; //начало правой части
    for (j = first_index; j <= last_index; j++) { //иду от начала до конца
        if ((start <= arithmetic_mean) && ((final > last_index) || (mas[start] < mas[final]))) {
            new_mas[j] = mas[start];
            start++;
        }
        else {
            new_mas[j] = mas[final];
            final++;
        }
    }
    for (j = first_index; j <= last_index; j++) {
        mas[j] = new_mas[j];
    }
    delete[] new_mas;
}

void Merge_Sort(int* mas, int first_index, int last_index, int all_size) { //рекурсивная процедура сортировки
    if (first_index < last_index) {
        Merge_Sort(mas, first_index, (first_index + last_index) / 2, all_size); //сортировка левой части
        Merge_Sort(mas, (first_index + last_index) / 2 + 1, last_index, all_size); //сортировка правой части
        Merge_mas(mas, first_index, last_index, all_size); //слияние двух частей

    }
}
//------------------------------------------

void qsortRecursive(int* mas, int size) { //быстрая Сортировка
    int first_index = 0; //указатели в начало и конец массива
    int last_index = size - 1;
    int middle = mas[size / 2];//центральный элемент массива

    do { //деление массива
        //в левой части оставляем элементы которые меньше центрального
        while (mas[first_index] < middle) {
            first_index++;
        }
        //в правой части оставляем элементы которые больше центрального
        while (mas[last_index] > middle) {
            last_index--;
        }
        //меняю элементы местами
        if (first_index <= last_index) {
            int tmp = mas[first_index];
            mas[first_index] = mas[last_index];
            mas[last_index] = tmp;
            first_index++;
            last_index--;
        }
    } while (first_index <= last_index);

    //рекурсивные вызовы, если осталось что сортировать
    if (last_index > 0) {
        //левая часть
        qsortRecursive(mas, last_index + 1);
    }
    if (first_index < size) {
        //правая часть
        qsortRecursive(&mas[first_index], size - first_index);
    }
}

void Sort_by_Count(int* A_mas, int mas_size) { //блочная сортировка
    int max_index = 0, min_index = 0;
    for (int i = 0; i < mas_size; i++) { //нахожу максимальный и минимальный элементы
        if (A_mas[i] > max_index)
            max_index = A_mas[i]; //индекс максимального элемента
        if (A_mas[i] < min_index)
            min_index = A_mas[i]; //индекс минимального элемента
    }
    int L_mas = max_index - min_index + 1;
    int* B_mas = new int[L_mas];
    for (int i = 0; i < L_mas; i++) { //заполняю 0 новый массив
        B_mas[i] = 0;
    }
    for (int i = 0; i < mas_size; i++) {
        B_mas[A_mas[i] - min_index]++;
    }
    int counter = 0;
    for (int i = 0; i < L_mas; i++) {
        for (int j = 0; j < B_mas[i]; j++) {
            A_mas[counter++] = i + min_index;
        }
    }
    delete[] B_mas; //очищаю память
}
