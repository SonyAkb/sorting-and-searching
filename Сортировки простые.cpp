#include <iostream>
#include <chrono>
using namespace std;

void creature_mas_rand(int* ptr, int n); //�������� ������� ��������
void creature_mas_hands(int* ptr, int n); //�������� ������� � ����������
void print(int* ptr, int n); //����� �������
void Merge_mas(int* mas, int first_index, int last_index, int all_size); //������� ��������
void Merge_Sort(int* mas, int first_index, int last_index, int all_size); //���������� ��������
void Quick_Sort(int* mas, int size); //������� ����������
void Sort_by_Count(int* A_mas, int mas_size); //���������� ���������
void Block_Sort(int* mas, int size_mas); //������� ����������
void Shell_Sort(int* mas, int size_mas); //��������� �����
void Khoar_Sort(int* mas, int left, int right, int N); //���������� �����

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    int mas_size = 25, choice;
    int* mas = new int[mas_size]; //�������� �������

    do {
        cout << "����� �������� �� ������ ������� ������? " << endl;
        cout << "1 - ������ �������" << endl;
        cout << "2 - ������� ��������" << endl;
        cin >> choice;
    } while (choice < 1 || choice > 2);

    switch (choice) { //����� ������� �������� �������
    case 1: {
        creature_mas_hands(mas, mas_size);
        break;
    }
    default: {
        creature_mas_rand(mas, mas_size); //�������� ������� ��������
        break;
    }
    }

    cout << endl << "������ ������!" << endl;
    print(mas, mas_size); //����� �������

    do { //����� ����������
        cout << "����� �������� ������������� ������? " << endl;
        cout << "1 - ���������� ��������" << endl;
        cout << "2 - ������� ����������" << endl;
        cout << "3 - ���������� ���������" << endl;
        cout << "4 - �������  ����������" << endl;
        cout << "5 - ���������� �����" << endl;
        cout << "6 - ���������� �����" << endl;
        cin >> choice;
    } while (choice < 1 || choice > 6);

    auto start_time_recursive = chrono::steady_clock::now();  // ��������� �����
    switch (choice) { //����� ����������
    case 1: {
        Merge_Sort(mas, 0, mas_size - 1, mas_size); //���������� ��������
        break;
    }
    case 2: {
        Quick_Sort(mas, mas_size); //������� ����������
        break;
    }
    case 3: {
        Sort_by_Count(mas, mas_size); //���������� ���������
        break;
    }
    case 4: {
        Block_Sort(mas, mas_size); //������� ����������
        break;
    }
    case 5: {
        Shell_Sort(mas, mas_size); //���������� �����
        break;
    }
    default: {
        Khoar_Sort(mas, 0, mas_size - 1, mas_size); //���������� �����
        break;
    }
    }
    auto end_time_recursive = chrono::steady_clock::now(); // �������� �����
    auto diff_time = end_time_recursive - start_time_recursive; //������� ����� ��������� � �������� ��������
    print(mas, mas_size); //����� �������

    cout << "���������� ��������� �� " << chrono::duration <double, milli>(diff_time).count() << " ms" << endl << endl;

    return 0;
}

void creature_mas_rand(int* ptr, int n) { //������ ������ ����� ������ ��������� �����
    for (int i = 0; i < n; i++) {
        ptr[i] = rand() % 1000 + 1; //��������� ����� �� 1 �� 1000
    }
}
void creature_mas_hands(int* ptr, int n) { //�������� ������� � ����������
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << "������� ������� " << i + 1 << ": ";
        cin >> ptr[i];
    }
}
void print(int* ptr, int n) { //����� �������� �������
    cout << endl << "������� ������:" << endl;
    for (int i = 0; i < n; i++) { //������� �� �������
        cout << ptr[i] << ' ';
    }
    cout << endl << endl;
}

//���������� ��������----------------------
void Merge_mas(int* mas, int first_index, int last_index, int all_size) { //������� ��������
    int arithmetic_mean, start, final;
    int* new_mas = new int[all_size];

    arithmetic_mean = (first_index + last_index) / 2; //���������� �������� ���������������
    start = first_index; //������ ����� �����

    final = arithmetic_mean + 1; //������ ������ �����
    for (int i = first_index; i <= last_index; i++) { //��� �� ������ �� �����
        if ((start <= arithmetic_mean) && ((final > last_index) || (mas[start] < mas[final]))) {
            new_mas[i] = mas[start]; //������ ������
            start++; //����� ������
        }
        else {
            new_mas[i] = mas[final]; //������ �����
            final++; //����� �����
        }
    }
    for (int i = first_index; i <= last_index; i++) { //������ � �������� ������
        mas[i] = new_mas[i]; //������
    }
    delete[] new_mas; //���������� ������
}

void Merge_Sort(int* mas, int first_index, int last_index, int all_size) { //����������� ��������� ����������
    if (first_index < last_index) {
        Merge_Sort(mas, first_index, (first_index + last_index) / 2, all_size); //���������� ����� �����
        Merge_Sort(mas, (first_index + last_index) / 2 + 1, last_index, all_size); //���������� ������ �����
        Merge_mas(mas, first_index, last_index, all_size); //������� ���� ������

    }
}
//------------------------------------------

void Quick_Sort(int* mas, int size) { //������� ����������
    int first_index = 0; //��������� � ������ �������
    int last_index = size - 1; //��������� � ����� �������
    int middle = mas[size / 2];//����������� ������� �������
    do { //������� �������
        while (mas[first_index] < middle) { //� ����� ����� ��������� �������� ������� ������ ������������
            first_index++;
        }
        while (mas[last_index] > middle) { //� ������ ����� ��������� �������� ������� ������ ������������
            last_index--;
        }
        //����� �������� �������
        if (first_index <= last_index) { //���� ������ ������� �������� ������ ������� ����������
            int tmp = mas[first_index];
            mas[first_index] = mas[last_index];
            mas[last_index] = tmp;
            first_index++; //���������� ������ ������
            last_index--; //�������� ������ �����
        }
    } while (first_index <= last_index);

    //���� �������� ��� ����������� - ��������
    if (last_index > 0) {
        Quick_Sort(mas, last_index + 1); //����� �����
    }
    if (first_index < size) {
        Quick_Sort(&mas[first_index], size - first_index); //������ �����
    }
}

void Sort_by_Count(int* A_mas, int mas_size) { //���������� ���������
    int max_index = 0, min_index = 0;
    for (int i = 0; i < mas_size; i++) { //������ ������������ � ����������� ��������
        if (A_mas[i] > max_index)
            max_index = A_mas[i]; //������ ������������� ��������
        if (A_mas[i] < min_index)
            min_index = A_mas[i]; //������ ������������ ��������
    }
    int number_of_different_values = max_index - min_index + 1; //����������� ��������� ���������� ������ �������� � �������
    int* B_mas = new int[number_of_different_values]; //������ ��� �������� ���������� ������ �������� � �������� �������
    for (int i = 0; i < number_of_different_values; i++) { //�������� 0 ����� ������
        B_mas[i] = 0;
    }
    for (int i = 0; i < mas_size; i++) { //������� ���������� ������� ��������
        B_mas[A_mas[i] - min_index]++;
    }
    int counter = 0; //������� ������� ��� ��������� �������
    for (int i = 0; i < number_of_different_values; i++) { //������ �� ������� ��������
        for (int j = 0; j < B_mas[i]; j++) { //������ �������� ����������� ����� ���
            A_mas[counter++] = i + min_index; //������ �������� � �������� ������
        }
    }
    delete[] B_mas; //������ ������
}

void Block_Sort(int* mas, int size_mas) { //������� ����������

    int max_element = mas[0]; //������������ �������
    int min_element = mas[0]; //����������� �������

    for (int i = 1; i < size_mas; i++) {
        if (mas[i] > max_element) { //������ ������������ �������
            max_element = mas[i];
        }
        if (mas[i] < min_element) { //������ ����������� �������
            min_element = mas[i];
        }
    }

    int the_numbers_in_the_block = 5; //������� ����� �������� ������ � ���� ����
    int total_blocks = ((max_element - min_element) / the_numbers_in_the_block); //���������� ������
    int** blocks{ new int* [total_blocks] }; //��������� ������ ������

    for (int i = 0; i < total_blocks; i++) { //������������� �������
        blocks[i] = new int[size_mas];
    }

    for (int i = 0; i < size_mas; i++) { //������������� ����� �� ������
        int bucket_index = ((mas[i] - min_element) / total_blocks); //� ����� ���� ���������� �������
        blocks[bucket_index][i] = mas[i]; //��������� ����� � ����
    }
    //���������� ������� ����� ������� ������
    for (int i = 0; i < total_blocks; i++) { //������ �� ������
        for (int j = 0; j < size_mas; j++) { //������ ����� ��� ���������
            for (int k = j + 1; k < size_mas; k++) { //������ ����� ��� ���������
                if (blocks[i][j] > blocks[i][k]) { //���� ���������� �������� ��������
                    int memory = blocks[i][j]; //��������� ���������� ��� �����������
                    blocks[i][j] = blocks[i][k];
                    blocks[i][k] = memory;
                }
            }
        }
    }

    int counter = 0; //������� ��� ��������� �������
    for (int i = 0; i < total_blocks; i++) { //������� �� ������
        for (int j = 0; j < size_mas; j++) { //������� �� ��������� � �����
            if (blocks[i][j] > -1) { //���� ������� - �� �����
                mas[counter++] = blocks[i][j]; //������ ��������
            }
        }
    }

    for (int i = 0; i < total_blocks; i++) { //������������ ������
        delete[] blocks[i]; //�������� �������� � �����
    }
    delete[] blocks; //�������� �������
}

void Shell_Sort(int* mas, int size_mas) { //��������� �����
    int tmp, j;
    for (int step = size_mas / 2; step > 0; step /= 2) { //���� ����� ���� ������ 0. ����� ������ �������� ��� �����������
        for (int i = step; i < size_mas; i++) { //������� �� ������� � ����� step
            tmp = mas[i]; //��������� �������� �������� ��������
            for (j = i; j >= step; j -= step) { //������� � ����� step
                if (tmp < mas[j - step]) { //���� tmp ������, �� ������ ������� tmp � ������� ������� �� j - step
                    mas[j] = mas[j - step];
                }
                else { //���� tmp ������ ��� ����� �������� ������� �� j - step, �� ��������� ����
                    break;
                }
            }
            mas[j] = tmp; //����� �������� �������� ��������
        }
    }
}

void Khoar_Sort(int* mas, int left, int right, int N) { //���������� �����
    int i, j, support_element, tmp; // tmp - ��������� ���������� ��� ������
    i = left; // ����� �������
    j = right; // ������ �������
    support_element = mas[(left + right) / 2]; //������� ������� ��� ����������
    do {
        while ((mas[i] < support_element) && (i < right)) i++; //���� ������� ������� �� ������� i �� ������ ������ ��� ����� �������� � i �� ������ ������ ������ �������
        while ((support_element < mas[j]) && (j > left)) j--; //���� ������� ������� �� ������� j �� ������ ������ ��� ����� �������� � j �� ������ ������ ����� �������
        if (i <= j) { //������ ������� �������� ������� �� �������� i � j � ������� ���������� tmp
            tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;
            i++; //���������� ����� �������
            j--; //�������� ������ �������

        }
    } while (i <= j);
    //���������, �� ������� �� ������� i � j �� ������� �������
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