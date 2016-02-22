#include <algorithm>
#include <cstdint>
#include <iostream>
#include <random>
#include "radixsort.h"

static uint64_t* getRandomUnsignedArray(size_t size)
{
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<uint64_t>
        dist(0, std::numeric_limits<uint64_t>::max());
    
    uint64_t* array = new uint64_t[size];
    
    for (auto i = 0; i < size; ++i)
    {
        array[i] = dist(e);
    }
    
    return array;
}

static int64_t* getRandomSignedArray(size_t size)
{
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<int64_t>
    dist(std::numeric_limits<int64_t>::min(),
         std::numeric_limits<int64_t>::max());
    
    int64_t* array = new int64_t[size];
    
    for (auto i = 0; i < size; ++i)
    {
        array[i] = dist(e);
    }
    
    return array;
}

static void profileUnsignedIntegerArray()
{
    std::cout << "--- Unsigned array ---" << std::endl;
    
    constexpr size_t SIZE = 10 * 1000 * 1000;
    uint64_t* arr1 = getRandomUnsignedArray(SIZE);
    uint64_t* arr2 = new uint64_t[SIZE];
    
    std::copy(arr1, arr1 + SIZE, arr2);
    
    auto begin = std::chrono::high_resolution_clock::now();
    std::sort(arr1, arr1 + SIZE);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout << "std::sort() in "
    << std::chrono::
    duration_cast<std::chrono::milliseconds>(end - begin).count()
    << " milliseconds."
    << std::endl;
    
    begin = std::chrono::high_resolution_clock::now();
    sort(arr2, arr2 + SIZE);
    end = std::chrono::high_resolution_clock::now();
    
    std::cout << "Radix sort in "
    << std::chrono::
    duration_cast<std::chrono::milliseconds>(end - begin).count()
    << " milliseconds."
    << std::endl;
    
    std::cout << "Equal: "
    << std::boolalpha
    << std::equal(arr1, arr1 + SIZE, arr2)
    << std::endl;
}

static void profileSignedIntegerArray()
{
    std::cout << "--- Signed array ---" << std::endl;
    
    constexpr size_t SIZE = 10 * 1000 * 1000;
    int64_t* arr1 = getRandomSignedArray(SIZE);
    int64_t* arr2 = new int64_t[SIZE];
    
    std::copy(arr1, arr1 + SIZE, arr2);
    
    auto begin = std::chrono::high_resolution_clock::now();
    std::sort(arr1, arr1 + SIZE);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout << "std::sort() in "
    << std::chrono::
    duration_cast<std::chrono::milliseconds>(end - begin).count()
    << " milliseconds."
    << std::endl;
    
    begin = std::chrono::high_resolution_clock::now();
    sort(arr2, arr2 + SIZE);
    end = std::chrono::high_resolution_clock::now();
    
    std::cout << "Radix sort in "
    << std::chrono::
    duration_cast<std::chrono::milliseconds>(end - begin).count()
    << " milliseconds."
    << std::endl;
    
    std::cout << "Equal: "
    << std::boolalpha
    << std::equal(arr1, arr1 + SIZE, arr2)
    << std::endl;
}

int main(int argc, const char * argv[]) {
    profileUnsignedIntegerArray();
    profileSignedIntegerArray();

    std::cout << "Bye!\n";
    return 0;
}
