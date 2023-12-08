// Task1.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <iomanip>

float Sum = 0;
void Sum1(std::vector<int> V1, std::vector<int> V2) {
    
     
    for (int i = 0; i < V1.size(); i++)
    {
       Sum += V1[i] + V2[i];
    }
   

}

int main ()
{
   SetConsoleCP(1251);
   SetConsoleOutputCP(1251);
   std::cout <<"Количество аппаратных ядер "<< std::thread::hardware_concurrency() << std::endl;
   std::vector<int> V1;
   std::vector<int> V2;
   std::vector<int> VECSizes{ 1000, 10000, 100000, 1000000 };
   std::vector<int> CountThreads{ 1, 2, 4, 8, 16 };
   
   std::cout << std::endl;

   for (const auto& count : CountThreads)
   {
       std::cout << count << " потоков\t";
       for (const auto& VECSize : VECSizes)
       {
           V1.resize(VECSize, 1);
           V2.resize(VECSize, 2);
           std::vector<std::thread> ts;
           int VECSize=1;
           VECSize = VECSize / count;
           auto start = std::chrono::steady_clock::now();
           for (int i = 0; i < count; i++)
           {
               std::vector<int> newV1;
               std::vector<int> newV2;
               int rightBorder = (i != count - 1) ? VECSize * (i + 1) : VECSize;
               for (int j = VECSize * i; j < rightBorder; ++j)
               {
                   newV1.push_back(V1.at(j));
                   newV2.push_back(V2.at(j));
               }
               ts.push_back(std::thread(Sum1, newV1, newV2));
           }
           for (auto& V : ts)
           {
               V.join();
           }
           auto stop = std::chrono::steady_clock::now();
           auto duration = std::chrono::duration_cast<std::chrono::microseconds> (stop - start);
           std::cout << static_cast<double>(duration.count()) / 1e6 << "s\t";

           Sum = 0;
       }
       std::cout << std::endl;

   }
    
    return 0;
}