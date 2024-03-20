#include <iostream>
#include <vector>
#include <string>
using namespace std;

void creature_mas_rand(vector<int>& ptr); //создаю массив через датчик случайных чисел
void creature_mas_hands(vector<int>& ptr); //создание массива с клавиатуры
void print(vector<int>& ptr); //вывод текущего массива
void Quick_Sort(vector<int>& vect, int start_Index, int pivot_Index); //быстрая сортировка
int linear_search(vector<int>& vect, int element); //линейный поиск
int Binary_search(vector<int>& vect, int key_el); //бинарный поиск
int Interpolation_search(vector<int>& vect, int key_el); //интерполяционный поиск
int Direct_search(string str, string key_sub_str); //прямой поиск подстроки в строке

int main() {
    system("chcp 1251 > Null");
    srand(time(0));

    int choice_1, choice_2, index_find = -1, mas_size, desired_element;
    vector<int> vect;
    string all_str, sub_str;

    do { //выбор поиска
        cout << "Каким способом вы хотите совершить поиск? " << endl;
        cout << "1 - Линейный поиск" << endl;
        cout << "2 - Бинарный поиск" << endl;
        cout << "3 - Интерполяционный поиск" << endl;
        cout << "4 - Прямой поиск подстроки" << endl;
        cin >> choice_1;
    } while (choice_1 < 1 || choice_1 > 4);

    cout << endl;

    if (choice_1 != 4) {
        do {
            cout << "Введите размер массива (размер больше 0): ";
            cin >> mas_size; //ввод размера массива
        } while (mas_size < 1);

        vect.reserve(mas_size); //резервирую память

        do {
            cout << endl << "Каким способом вы хотите создать массив? " << endl;
            cout << "1 - Ввести ручками" << endl;
            cout << "2 - Создать случайно" << endl;
            cin >> choice_2;
        } while (choice_2 < 1 || choice_2 > 2);

        switch (choice_2) { //выбор способа создания массива
        case 1: {
            creature_mas_hands(vect);
            break;
        }
        default: {
            creature_mas_rand(vect); //создание массива случайно
            break;
        }
        }

        if (choice_1 == 2 || choice_1 == 3) { //если надо отсортировать
            Quick_Sort(vect, 0, vect.size() - 1);
        }
        
        print(vect);
        cout << "Введите элемент, который необходимо найти: ";
        cin >> desired_element;
    }
    else {
        cout << "Введите строку: ";
        cin.ignore();
        getline(cin, all_str);
        cout << "Введите ПОДстроку, которую необходимо найти: ";
        getline(cin, sub_str);
    }
    
    if (choice_1 == 1) { //линейный поиск
        index_find = linear_search(vect, desired_element);
    }
    else if (choice_1 == 2) { //бинарный поиск
        index_find = Binary_search(vect, desired_element);
    }
    else if (choice_1 == 3) { //интерполяционный поиск
        index_find = Interpolation_search(vect, desired_element);
    }
    else { //прямой поиск подстроки
        index_find = Direct_search(all_str, sub_str);
    }
    
    if (index_find == -1) {
        cout << endl << "Такого элемента нет!";
    }
    else {
        cout << endl << "Номер элемента - " << index_find + 1;
    }

    return 0;
}

void creature_mas_rand(vector<int>& ptr) { //создаю массив через датчик случайных чисел
    for (int i = 0; i < ptr.capacity(); i++) {
        ptr.push_back(rand() % 1000 + 1); //случайное число от 1 до 1000
    }
}

void creature_mas_hands(vector<int>& ptr) { //создание массива с клавиатуры
    cout << endl;
    int pointer;
    for (int i = 0; i < ptr.capacity(); i++) {
        cout << "Введите элемент " << i + 1 << ": ";
        cin >> pointer;
        ptr.push_back(pointer);
    }
}

void print(vector<int>& ptr) { //вывод текущего массива
    cout << endl << "Текущий массив:" << endl;
    for (int i = 0; i < ptr.size(); i++) { //прохожу по массиву
        cout << ptr[i] << ' ';
    }
    cout << endl << endl;
}

void Quick_Sort(vector<int>& vect, int start_Index, int pivot_Index) { //быстрая сортировка
    if (start_Index < pivot_Index) {
        int current_Index = start_Index;
        for (int i = current_Index; i < pivot_Index; i++) { //иду до опорного элемента
            if (vect[i] <= vect[pivot_Index]) {
                swap(vect[i], vect[current_Index++]); //меняю элементы местами
            }
        }
        swap(vect[current_Index], vect[pivot_Index]); //меняю элементы местами
        Quick_Sort(vect, start_Index, current_Index - 1);
        Quick_Sort(vect, current_Index + 1, pivot_Index);
    }
}

int linear_search(vector<int>& vect, int element) { //линейный поиск
    int index_el = -1;
    for (int i = 0; i < vect.size() && index_el == -1; i++) {
        if (vect[i] == element) { //если элемент совпал
            index_el = i;
        }
    }
    return index_el;
}

int Binary_search(vector<int>& vect, int key_el) { //бинарный поиск
    int index_el = -1, middle_index, the_left_border = 0, the_right_border = vect.size() - 1;
    while (the_left_border <= the_right_border && index_el == -1) {
        middle_index = (the_left_border + the_right_border) / 2; //средний элемент относительно текущих границ
        if (vect[middle_index] == key_el) { //если элемент совпал
            index_el = middle_index;
        }
        else {
            if (vect[middle_index] < key_el) { //если средний элемент меньше ключевого
                the_left_border = middle_index + 1; //меняю левую границу
            }
            else { //если средний элемент больше ключевого
                the_right_border = middle_index - 1; //меняю правую границу
            }
        }
    }
    return  index_el;
}

int Interpolation_search(vector<int>& vect, int key_el) { //интерполяционный поиск
    int index_el = -1, middle_index, the_left_border = 0, the_right_border = vect.size() - 1;
    while (the_left_border <= the_right_border && index_el == -1) {
        middle_index = the_left_border + (((key_el - vect[the_left_border]) * (the_right_border - the_left_border)) /
            (vect[the_right_border] - vect[the_left_border])); //средний элемент относительно текущих границ
        if (vect[middle_index] == key_el) { //если элемент совпал
            index_el = middle_index;
        }
        else {
            if (vect[middle_index] < key_el) { //если средний элемент меньше ключевого
                the_left_border = middle_index + 1; //меняю левую границу
            }
            else { //если средний элемент больше ключевого
                the_right_border = middle_index - 1; //меняю правую границу
            }
        }
    }
    return  index_el;
}

int Direct_search(string str, string key_sub_str) { //прямой поиск подстроки в строке
    int index_el = -1, len_sub_str = key_sub_str.size();
    for (int i = 0; i < str.size() - len_sub_str && index_el == -1; i++) { //иду по строке
        bool found = true; //статус совпадения подстроки и строки
        int j = 0; //длина совпадающей части
        while (j < len_sub_str && found) { //иду по ПОДстроке
            found = (str[i + j] == key_sub_str[j]); //совпадение символа строки и ПОДстроки
            j++; //длина совпадающей части
        }
        if (found) { //если все элементы совпали
            index_el = i; //индекс первого элемента
        }
    }
    return index_el;
}