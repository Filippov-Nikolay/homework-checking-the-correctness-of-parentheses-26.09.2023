#include <iostream>
#include <string.h>
#include <time.h>
using namespace std;

class Stack
{
	// Нижняя и верхняя границы стека
	enum { EMPTY = -1, FULL = 20 };

	// Массив для хранения данных
	char st[FULL + 1];

	// Указатель на вершину стека
	int top;

public:
	// Конструктор
	Stack();

	// Добавление элемента
	void Push(char c);

	// Извлечение элемента
	char Pop();

	// Очистка стека
	void Clear();

	// Проверка существования элементов в стеке
	bool IsEmpty();

	// Проверка на переполнение стека
	bool IsFull();

	// Количество элементов в стеке
	int GetCount();

	// Получение последнего элемента
	char GetLastElement();

	// Получение последнего элемента
	void PrintLastElement();

	// Вывод всех элементов
	void Print();

	bool checkCorrectness(char*);
};


Stack::Stack()
{
	// Изначально стек пуст
	top = EMPTY;
}

void Stack::Clear()
{
	// Эффективная "очистка" стека 
	// (данные в массиве все еще существуют, 
	// но функции класса, ориентированные на работу с вершиной стека,
	// будут их игнорировать)
	top = EMPTY;
}

bool Stack::IsEmpty()
{
	// Пуст?
	return top == EMPTY;
}

bool Stack::IsFull()
{
	// Полон?
	return top == FULL;
}

int Stack::GetCount()
{
	// Количество присутствующих в стеке элементов
	return top + 1;
}

char Stack::GetLastElement() {
	return st[top];
}

void Stack::PrintLastElement() {
	cout << st[top];
}


void Stack::Print() {
	for (int i = 0; i < top + 1; i++)
		cout << st[i];
}

bool Stack::checkCorrectness(char* buff) {
	Stack T;

	int index = 0, j = 0;
	char* tempSumbol = new char[strlen(buff)];

	for (int i = 0; i < strlen(buff); i++) {
		char correct = buff[i];

		if (correct == '(' || correct == '{' || correct == '[') {
			tempSumbol[index++] = correct; // ( { 
			T.Push(correct);
		}
		else if (correct == ')' || correct == '}' || correct == ']') {
			if (T.IsEmpty())
				return 0;
			else {
				T.Push(correct);
				char temp = T.GetLastElement();

				// cout << "tempSumbol: " << tempSumbol[index - 1] << endl;
				// cout << "TEMP: " << temp << endl;

				if ((tempSumbol[index - 1] != '(' && temp == ')') ||
					(tempSumbol[index - 1] != '{' && temp == '}') ||
					(tempSumbol[index - 1] != '[' && temp == ']')) {
					return 0;
				}
				index--;
			}
		}
		else
			T.Push(correct);
	}

	return 1;
}

void Stack::Push(char c)
{
	// Если в стеке есть место, то увеличиваем указатель
	// на вершину стека и вставляем новый элемент
	if (!IsFull())
		st[++top] = c;
}

char Stack::Pop()
{
	// Если в стеке есть элементы, то возвращаем верхний и
	// уменьшаем указатель на вершину стека
	if (!IsEmpty())
		return st[top--];
	else // Если в стеке элементов нет
		return 0;
}

void main() {
	setlocale(0, "");
	srand(time(0));
	Stack ST;
	char c;
	char buff[100];

	cin.getline(buff, strlen(buff) + 1, ';');

	if (ST.checkCorrectness(buff)) {
		cout << "Всё верно!" << endl;

		for (int i = 0; i < strlen(buff); i++) {
			c = buff[i];
			ST.Push(c);
		}
	}
	else
		cout << "Не верно!" << endl;


	ST.Print();
	cout << endl;

	ST.PrintLastElement();
}

