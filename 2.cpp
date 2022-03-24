#include <iostream>
#include <ctime>
#include <random>

using namespace std;



extern "C" {
        /* Создаем переменные которые нам нужны */
        const int size = 5;
        int size_asm = size;
        int arr[size];
        int sum;
};


int main()
{
	/* Для того, чтобы работал рандом */
    srand(time(0));

	/* Заполняем массив случайными числами */
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 10;
    }

	/* Выводим на экран каждый элемент массива через пробел */
    for (int i = 0; i < size; i++)
    {
        cout<<arr[i]<<" ";
    }

    //Код на ассемблере
        __asm
        (
        R"(
                .intel_syntax noprefix ; //используем синтаксис intel

                mov esi, 0 ; //Регистр где будем хранить адреса элементов одномерного массива
                mov dl, 0  ; //Регистр где считаем количество пройденных элемент>
                        Start:
                mov ecx, arr[esi] ; // кладем в регистр ecx, адрес элемента массива
                imul ecx, ecx ; // умножаем значение в регистре ecx, на значение ecx, то есть ecx=ecx*ecx
                add sum, ecx ; // результат умножения  кладем в sum
                add esi, 4 ; // Переход к другому элементу массива
                        CheckEnd:
                add dl, 1 
                cmp dl, BYTE PTR size_asm ; // Сравнение, есть ли ещё строки
                jl Start ; // Если есть, опять идем к функции Start

                .att_syntax
        )"
        );

	/* С новой строки выводим на экран значение суммы */
   cout << "\n" << sum << endl;
   return 0;
}
