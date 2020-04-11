// Parenthesis_analysis.cpp

#include <iostream>
#include<locale.h>  
//структура для возвращения кода и символа из функции одновременно
struct Return_pop
{
	int code;
	char sym;
};
//Свой класс для реализации стека
class My_stack
{
private:
	//указатель на стек
	char* stack_ptr;
	//размер
	int size;
	//номер текущего элемента(вершина)
	int top;
public:
	//конструктор по умолчанию с 20 элементами
	My_stack(int = 20);
	//дестурктор
	~My_stack();
	//функция добавления элемента
	int push(char sym);
	//фунция взятия элемента
	Return_pop pop();
	//вывод стека
	void print_stack();
};


My_stack::My_stack(int Size)
{
	//инициализация начальных параметров
	size = Size;
	stack_ptr = new char[size];
	top = 0;
}

My_stack::~My_stack()
{
	//удаление стека
	delete [] stack_ptr;
}

int My_stack::push(char sym)
{
	if (top < size)
	{
		stack_ptr[top] = sym;
		top++;
		return 0;
	}
	else
	{
		//std::cout << "Не могу добавить еще элемент в стек т.к. он переполнен!";
		return 1;
	}
}
Return_pop My_stack::pop()
{
	Return_pop tmp = Return_pop();
	if (top > 0)
	{
		top--;
		tmp.code = 0;
		tmp.sym = stack_ptr[top];
		return tmp;
	}
	else
	{
		tmp.code = 1;
		tmp.sym = NULL;
		//std::cout << "Стек пуст, не могу вытащить из него значения!";
		return tmp;
	}
}

//вывод стека
void My_stack::print_stack()
{
	std::cout << "stack(вершина тут ->):";
	for (int i = top - 1; i >= 0; i--)
	{
		std::cout <<  stack_ptr[i];
	}
	std::cout << std::endl;
}

//bool функции для будущей проверки на правильность расстановки скобок
bool push_open(My_stack &stack)
{
	int code = 0;
	//std::cout << "ADD    ";
	code = stack.push('(');
	//stack.print_stack();
	if (code == 1)
		return false;
	else return true;
}

bool pop_close(My_stack &stack)
{
	Return_pop tmp = Return_pop();
	//std::cout << "DELETE ";
	tmp = stack.pop();
	//stack.print_stack();
	if (tmp.code == 1)
		return false;
	else return true;

}
int main()
{
	setlocale(LC_ALL, "RUS");
	My_stack Main_stack = My_stack();
	std::cout << "<<<< Программа анализа строки на правильность открытия и закрытия скобок >>>>" << std::endl;
	std::cout << "Для выхода введите символ пробела" << std::endl;
	while (true)
	{
		bool fl = true;
		char str[100];
		std::cout << std::endl << "Напишите строчку:";
		std::cin.getline(str,100);
		if (str[0] == ' ')
			break;
		for (int i = 0; i < strlen(str); i++)
		{
			if (str[i] == '(')
			{
				if (!push_open(Main_stack))
				{

					std::cout << std::endl << "Ошибка в скобках!" << std::endl;
					fl = false;
					break;
				}
			}
			else
				if (str[i] == ')')
					if (!pop_close(Main_stack))
					{
						std::cout << std::endl << "Ошибка в скобках!" << std::endl;
						fl = false;
						break;
					}
					else
						continue;
		}
		if (!fl) continue;
		if (pop_close(Main_stack))
			std::cout << std::endl << "Ошибка в скобках!" << std::endl;
		else 
			std::cout << std::endl << "Все хорошо)" << std::endl;
	}
	std::cout << "Вы вышли из программы" << std::endl;
};