// Task1.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <execution>
#include <chrono>
#include <thread>
#include <Windows.h>


const int num_threads = 4;
void Sum(std::vector<int> v1, std::vector<int> v2, std::vector<int> v3) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < v1.size(); i++)
    {
        v3[i] = v1[i] + v2[i];
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time = end - start;
    std::cout << "std::sort time = " << time.count() << std::endl;
}

void ParSum(std::vector<int> v1, std::vector<int> v2, std::vector<int> v3) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < v1.size(); i++)
    {
        v3[i] = v1[i] + v2[i];
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time = end - start;
    std::cout << "std::parallel sort time = " << time.count() << std::endl;
}


int main_exec()
{
    std::cout << std::thread::hardware_concurrency() << std::endl;
    setlocale(LC_ALL, "Russian");

    std::vector<int> V1(1'000'000);
    std::vector<int> V2(1'000'000);
    std::vector<int> V3(1'000'000);
    std::mt19937 gen;
    std::uniform_int_distribution<int> dis(0, 1'000'000);
    auto rand_num([=]() mutable {return dis(gen); });
    generate(V1.begin(), V1.end(), rand_num);
    generate(V2.begin(), V2.end(), rand_num);
    
    std::thread t[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        t[i] = std::thread(Sum, V1, V2, V3);
    }

    for (int i = 0; i < num_threads; ++i) {
        t[i].join();
    }

    //Sum(V1, V2, V3);
    //ParSum(V1, V2, V3);
    return 0;
}