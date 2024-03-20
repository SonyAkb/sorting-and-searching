#include <iostream>
#include <vector>
#include <string>
using namespace std;

void creature_mas_rand(vector<int>& ptr); //������ ������ ����� ������ ��������� �����
void creature_mas_hands(vector<int>& ptr); //�������� ������� � ����������
void print(vector<int>& ptr); //����� �������� �������
void Quick_Sort(vector<int>& vect, int start_Index, int pivot_Index); //������� ����������
int linear_search(vector<int>& vect, int element); //�������� �����
int Binary_search(vector<int>& vect, int key_el); //�������� �����
int Interpolation_search(vector<int>& vect, int key_el); //���������������� �����
int Direct_search(string str, string key_sub_str); //������ ����� ��������� � ������

int main() {
    system("chcp 1251 > Null");
    srand(time(0));

    int choice_1, choice_2, index_find = -1, mas_size, desired_element;
    vector<int> vect;
    string all_str, sub_str;

    do { //����� ������
        cout << "����� �������� �� ������ ��������� �����? " << endl;
        cout << "1 - �������� �����" << endl;
        cout << "2 - �������� �����" << endl;
        cout << "3 - ���������������� �����" << endl;
        cout << "4 - ������ ����� ���������" << endl;
        cin >> choice_1;
    } while (choice_1 < 1 || choice_1 > 4);

    cout << endl;

    if (choice_1 != 4) {
        do {
            cout << "������� ������ ������� (������ ������ 0): ";
            cin >> mas_size; //���� ������� �������
        } while (mas_size < 1);

        vect.reserve(mas_size); //���������� ������

        do {
            cout << endl << "����� �������� �� ������ ������� ������? " << endl;
            cout << "1 - ������ �������" << endl;
            cout << "2 - ������� ��������" << endl;
            cin >> choice_2;
        } while (choice_2 < 1 || choice_2 > 2);

        switch (choice_2) { //����� ������� �������� �������
        case 1: {
            creature_mas_hands(vect);
            break;
        }
        default: {
            creature_mas_rand(vect); //�������� ������� ��������
            break;
        }
        }

        if (choice_1 == 2 || choice_1 == 3) { //���� ���� �������������
            Quick_Sort(vect, 0, vect.size() - 1);
        }
        
        print(vect);
        cout << "������� �������, ������� ���������� �����: ";
        cin >> desired_element;
    }
    else {
        cout << "������� ������: ";
        cin.ignore();
        getline(cin, all_str);
        cout << "������� ���������, ������� ���������� �����: ";
        getline(cin, sub_str);
    }
    
    if (choice_1 == 1) { //�������� �����
        index_find = linear_search(vect, desired_element);
    }
    else if (choice_1 == 2) { //�������� �����
        index_find = Binary_search(vect, desired_element);
    }
    else if (choice_1 == 3) { //���������������� �����
        index_find = Interpolation_search(vect, desired_element);
    }
    else { //������ ����� ���������
        index_find = Direct_search(all_str, sub_str);
    }
    
    if (index_find == -1) {
        cout << endl << "������ �������� ���!";
    }
    else {
        cout << endl << "����� �������� - " << index_find + 1;
    }

    return 0;
}

void creature_mas_rand(vector<int>& ptr) { //������ ������ ����� ������ ��������� �����
    for (int i = 0; i < ptr.capacity(); i++) {
        ptr.push_back(rand() % 1000 + 1); //��������� ����� �� 1 �� 1000
    }
}

void creature_mas_hands(vector<int>& ptr) { //�������� ������� � ����������
    cout << endl;
    int pointer;
    for (int i = 0; i < ptr.capacity(); i++) {
        cout << "������� ������� " << i + 1 << ": ";
        cin >> pointer;
        ptr.push_back(pointer);
    }
}

void print(vector<int>& ptr) { //����� �������� �������
    cout << endl << "������� ������:" << endl;
    for (int i = 0; i < ptr.size(); i++) { //������� �� �������
        cout << ptr[i] << ' ';
    }
    cout << endl << endl;
}

void Quick_Sort(vector<int>& vect, int start_Index, int pivot_Index) { //������� ����������
    if (start_Index < pivot_Index) {
        int current_Index = start_Index;
        for (int i = current_Index; i < pivot_Index; i++) { //��� �� �������� ��������
            if (vect[i] <= vect[pivot_Index]) {
                swap(vect[i], vect[current_Index++]); //����� �������� �������
            }
        }
        swap(vect[current_Index], vect[pivot_Index]); //����� �������� �������
        Quick_Sort(vect, start_Index, current_Index - 1);
        Quick_Sort(vect, current_Index + 1, pivot_Index);
    }
}

int linear_search(vector<int>& vect, int element) { //�������� �����
    int index_el = -1;
    for (int i = 0; i < vect.size() && index_el == -1; i++) {
        if (vect[i] == element) { //���� ������� ������
            index_el = i;
        }
    }
    return index_el;
}

int Binary_search(vector<int>& vect, int key_el) { //�������� �����
    int index_el = -1, middle_index, the_left_border = 0, the_right_border = vect.size() - 1;
    while (the_left_border <= the_right_border && index_el == -1) {
        middle_index = (the_left_border + the_right_border) / 2; //������� ������� ������������ ������� ������
        if (vect[middle_index] == key_el) { //���� ������� ������
            index_el = middle_index;
        }
        else {
            if (vect[middle_index] < key_el) { //���� ������� ������� ������ ���������
                the_left_border = middle_index + 1; //����� ����� �������
            }
            else { //���� ������� ������� ������ ���������
                the_right_border = middle_index - 1; //����� ������ �������
            }
        }
    }
    return  index_el;
}

int Interpolation_search(vector<int>& vect, int key_el) { //���������������� �����
    int index_el = -1, middle_index, the_left_border = 0, the_right_border = vect.size() - 1;
    while (the_left_border <= the_right_border && index_el == -1) {
        middle_index = the_left_border + (((key_el - vect[the_left_border]) * (the_right_border - the_left_border)) /
            (vect[the_right_border] - vect[the_left_border])); //������� ������� ������������ ������� ������
        if (vect[middle_index] == key_el) { //���� ������� ������
            index_el = middle_index;
        }
        else {
            if (vect[middle_index] < key_el) { //���� ������� ������� ������ ���������
                the_left_border = middle_index + 1; //����� ����� �������
            }
            else { //���� ������� ������� ������ ���������
                the_right_border = middle_index - 1; //����� ������ �������
            }
        }
    }
    return  index_el;
}

int Direct_search(string str, string key_sub_str) { //������ ����� ��������� � ������
    int index_el = -1, len_sub_str = key_sub_str.size();
    for (int i = 0; i < str.size() - len_sub_str && index_el == -1; i++) { //��� �� ������
        bool found = true; //������ ���������� ��������� � ������
        int j = 0; //����� ����������� �����
        while (j < len_sub_str && found) { //��� �� ���������
            found = (str[i + j] == key_sub_str[j]); //���������� ������� ������ � ���������
            j++; //����� ����������� �����
        }
        if (found) { //���� ��� �������� �������
            index_el = i; //������ ������� ��������
        }
    }
    return index_el;
}