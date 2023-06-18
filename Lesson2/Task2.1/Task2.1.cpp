// Task2.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <Windows.h>
#include <chrono>
#include<mutex>
#include<atomic>



thread_local int n;
void Client()
{
	n = 0;
	for (int i = 0; i < 10; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "Клиент  " << n++ << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Operator()
{
	n = 10;
	for (int i = 0; i < 10; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		std::cout << "Оператор " << n-- << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main()
{
	std::cout << std::thread::hardware_concurrency() << std::endl;
	setlocale(LC_ALL, "Russian");
	//int n = 10;
	std::thread t1(Client);
	std::thread t2(Operator);
	t1.join();
	t2.join();

	return 0;
}