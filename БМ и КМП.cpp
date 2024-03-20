#include <iostream>
#include <string>
using namespace std;

int Boiler_Moore_Search(string all_str, string sub_str);//поиск Бойлера Мура
void prefix_function(string sub_str, int* prefix); //префикс функция
int KMP_search(string all_str, string sub_str); //поиск Кнута Морриса Прата

int main(){
	system("chcp 1251 > Null");
	srand(time(0));
	int choice, index_find = -1;
	string all_str, sub_str;

	do { //выбор поиска
		cout << "Каким способом вы хотите совершить поиск? " << endl;
		cout << "1 - Алгоритм Бойлера Мура" << endl;
		cout << "2 - Алгоритм Кнута Мориса Прата" << endl;
		cin >> choice;
	} while (choice < 1 || choice > 2);

	cout << endl << "Введите строку: ";
	cin.ignore();
	getline(cin, all_str);
	cout << "Введите ПОДстроку, которую необходимо найти: ";
	getline(cin, sub_str);

	switch (choice) { //выбор поиска
	case 1: {
		index_find = Boiler_Moore_Search(all_str, sub_str);
		break;
	}
	default: {
		index_find = KMP_search(all_str, sub_str);
		break;
	}
	}

	if (index_find == -1) {
		cout << endl << "Такого элемента нет!";
	}
	else {
		cout << endl << "Номер элемента - " << index_find + 1;
	}

	return 0;
}

int Boiler_Moore_Search(string all_str, string sub_str) {//поиск Бойлера Мура
	int len_str, len_sub_str, index_el = -1;
	len_str = all_str.size(); //длина строки
	len_sub_str = sub_str.size();//длина подстроки
	bool flag;

	if (len_str != 0 && len_sub_str != 0) { //если строка и подстрока существуют
		int last_char_substr_relative_string;
		int offset_table[256];//массив смещения по таблице ASCII из всех символов таблицы
		for (int i = 0; i < 256; i++) { //заполнение полей символов случайными элементами
			offset_table[i] = len_sub_str;
		}
		for (int i = len_sub_str - 2; i >= 0; i--) { //генерация таблицы смещения для элементов, которые есть в подстроке
			//substr = char (-128 до 127), приводим к unsigned char (от 0 до 255) и приводим к типу int согласно таблице ASCII, чтобы получить нужный индекс
			if (offset_table[int((unsigned char)sub_str[i])] == len_sub_str) { //если, смещение элемента подстроки равно длине подстроки
				offset_table[int((unsigned char)sub_str[i])] = len_sub_str - i - 1;//шаг смещения - "длина подстроки" - "расстояние от конца" - "перевод длины в индекс"
			}
		}
		last_char_substr_relative_string = len_sub_str - 1;//позиция последнего символа подстроки относительно строки
		while (last_char_substr_relative_string < len_str && index_el == -1) {//пока не дойдем до конца строки
			if (sub_str[len_sub_str - 1] != all_str[last_char_substr_relative_string]) {//если последний элемент подстроки НЕ равен элементу строки на позиции last_char_substr_relative_string
				last_char_substr_relative_string += offset_table[int((unsigned char)all_str[last_char_substr_relative_string])];//смещаем подстроку, пользуясь таблицей смещения
			}
			else {//если последний элемент подстроки РАВЕН элементу строки на позиции last_char_substr_relative_string
				flag = true;
				for (int i = len_sub_str - 1; i >= 0 && index_el == -1 && flag; i--) {//проход по подстроке с правого края
					if (sub_str[i] != all_str[last_char_substr_relative_string - len_sub_str + i + 1]) {//если к-л элемент не равен - смещаем по таблице последнего символа строки
						last_char_substr_relative_string += offset_table[int((unsigned char)all_str[last_char_substr_relative_string - len_sub_str + i + 1])];//смещение по строке
						flag = false; //надо сместить подстроку по строке
					}
					else if (i == 0) {//если все равны то возвращаем индекс начала подстроки в строке
						index_el = last_char_substr_relative_string - len_sub_str + 1;//вычисление индекса
					}
				}
			}
		}
	}
	return index_el; //возврат индекса
}

void prefix_function(string sub_str, int* prefix) { //префикс функция
	prefix[0] = 0;
	int i = 1, j = 0;
	while (i < sub_str.size()) {//иду по ПОДстроке
		if (sub_str[i] == sub_str[j]) {//если в подстроке найдены совпадающие элементы
			prefix[i] = j + 1;
			i++;
			j++;
		}
		else {
			if (j == 0) {//если на первом эл подстроки
				prefix[i] = 0;
				i++;
			}
			else {
				j = prefix[j - 1];
			}
		}
	}
}

int KMP_search(string all_str, string sub_str) { //поиск Кнута Морриса Прата
	int* prefix = new int[sub_str.size()]; //префикс
	int str_count = 0, sub_s_count = 0, index_el = -1;
	prefix_function(sub_str, prefix); //префикс функция

	while (str_count < all_str.size() && index_el == -1) {//пока не пройду всю строку или не найду индекс
		if (sub_str[sub_s_count] == all_str[str_count]) {//если совпал эл из строки и подстроки
			str_count++;//увеличиваю счетчик по строке
			sub_s_count++;//увеличиваю счетчик по подстроке
		}
		if (sub_s_count == sub_str.size()) {//если найдена вся подстрока
			index_el = str_count - sub_str.size();
		}
		else if (str_count < all_str.size() && sub_str[sub_s_count] != all_str[str_count]) {//если НЕ найдена вся подстрока
			if (sub_s_count == 0) {//если проверяю с первого символа подстроки
				str_count++;//увеличиваю счетчик по строке
			}
			else {//если проверяю НЕ с первого символа подстроки
				sub_s_count = prefix[sub_s_count - 1];
			}
		}
	}
	delete[] prefix;//освобождаю память
	return index_el;//вощзвращаю индекс
}
