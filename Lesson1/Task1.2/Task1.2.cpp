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

void Sum1(std::vector<int> v1, std::vector<int> v2, std::vector<int> v3) {
    std::vector<int> V1(1'000);
    std::vector<int> V2(1'000);
    std::vector<int> V3(1'000);
    std::mt19937 gen;
    std::uniform_int_distribution<int> dis(0, 1'000);
    auto rand_num([=]() mutable {return dis(gen); });
    generate(V1.begin(), V1.end(), rand_num);
    generate(V2.begin(), V2.end(), rand_num);
    
    for (int i = 0; i < v1.size(); i++)
    {
        v3[i] = v1[i] + v2[i];
    }
   

}

int main ()
{
   setlocale(LC_ALL, "Russian");
   std::cout <<"Количество аппаратных ядер "<< std::thread::hardware_concurrency() << std::endl;
   std::vector<int> V1;
   std::vector<int> V2;
   std::vector<int> V3;
       
    const int num_threads = 2;
   std::thread t[num_threads];
   auto start1 = std::chrono::steady_clock::now();
    for (int i = 0; i < num_threads; ++i) {
        t[i] = std::thread(Sum1, V1, V2, V3);
     }

    for (int i = 0; i < num_threads; ++i) {
        t[i].join();
    }
    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed1_seconds = end1 - start1;
    std::cout << "            1000" << std::endl;
    std::cout << "2 потока = " << elapsed1_seconds.count() << std::endl;

   std::vector<std::thread> ts;
   auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < 4; i++) {
       
        ts.push_back (std::thread(Sum1, V1, V2, V3));
}
    for (auto& th : ts)
        th.join();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "4 потока = " << elapsed_seconds.count() << std::endl;
  
   
    
    return 0;
}