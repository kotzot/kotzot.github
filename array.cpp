#include <iostream>
#include <string>
#include <sycl/sycl.hpp>
using namespace sycl;

int main(int argc, char** argv) {
    std::string operacao = argv[1];
    std::string num = argv[2];
    std::string texto = argv[3];
    int sz = texto.size();
    int inval = stoi(num);
    queue q;
    char* result = malloc_shared<char>(sz, q);
    std::memcpy(result, texto.data(), sz);
    
    if (operacao == "soma") {
        q.parallel_for(sz, [=](auto& i) {
        result[i] += inval;
        }).wait();
        std::cout << "resultado:" << result << "\n";
    } else
    if (operacao == "subtrai") {
        q.parallel_for(sz, [=](auto& i) {
        result[i] -= inval;
        }).wait();
        std::cout << "resultado:" << result << "\n"; 
    } else
    if (operacao == "multiplica") {
        q.parallel_for(sz, [=](auto& i) {
        result[i] *= inval;
        }).wait();
        std::cout << "resultado:" << result << "\n";
    } else
    if (operacao == "divide") {
        q.parallel_for(sz, [=](auto& i) {
        result[i] /= inval;
        }).wait();
        std::cout << "resultado:" << result << "\n";
    } else std::cout << "operacao invalida";
    
    
    free(result, q);
    return 0;
    }