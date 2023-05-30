// Task1.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <Windows.h>
#include <chrono>

void Client()
{
	for (int i = 0; i < 10; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "Клиент  " << (i+1) << " ";
		std::cout << std::endl;
	}
}

void Operator()
{
	int n = 10;
	for (int i = n; i >= 1 ; i--)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		std::cout << "Оператор " << i << " ";
		std::cout << std::endl;
	}
}

int main()
{
	std::cout << std::thread::hardware_concurrency() << std::endl;
	setlocale(LC_ALL, "Russian");
	std::thread t1 (Client);
	std::thread t2 (Operator);
	
	t1.join();
	t2.join();

	return 0;
}