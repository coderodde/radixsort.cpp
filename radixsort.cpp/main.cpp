#define NDEBUG

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>
#include "radixsort.h"

constexpr size_t SIZE = 50 * 1000 * 1000;

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

static std::vector<uint64_t> getRandomUnsignedVector(size_t size)
{
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<uint64_t>
    dist(0, std::numeric_limits<uint64_t>::max());
    
    std::vector<uint64_t> vector(size);
    
    for (auto i = 0; i < size; ++i)
    {
        vector[i] = dist(e);
    }
    
    return vector;
}

static std::vector<int64_t> getRandomSignedVector(size_t size)
{
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<int64_t>
    dist(std::numeric_limits<int64_t>::min(),
         std::numeric_limits<int64_t>::max());
    
    std::vector<int64_t> vector(size);
    
    for (auto i = 0; i < size; ++i)
    {
        vector[i] = dist(e);
    }
    
    return vector;
}

static void profileUnsignedIntegerArray()
{
    std::cout << "--- Unsigned array ---" << std::endl;
    
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
    
    delete[] arr1;
    delete[] arr2;
}

static void profileUnsignedIntegerVector()
{
    std::cout << "--- Unsigned vector ---" << std::endl;
    
    std::vector<uint64_t> vec1 = getRandomUnsignedVector(SIZE);
    std::vector<uint64_t> vec2(vec1);
    
    auto begin = std::chrono::high_resolution_clock::now();
    std::sort(vec1.begin(), vec1.end());
    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout << "std::sort() in "
    << std::chrono::
    duration_cast<std::chrono::milliseconds>(end - begin).count()
    << " milliseconds."
    << std::endl;
    
    begin = std::chrono::high_resolution_clock::now();
    sort(vec2.begin(), vec2.end());
    end = std::chrono::high_resolution_clock::now();
    
    std::cout << "Radix sort in "
    << std::chrono::
    duration_cast<std::chrono::milliseconds>(end - begin).count()
    << " milliseconds."
    << std::endl;
    
    std::cout << "Equal: "
    << std::boolalpha
    << std::equal(vec1.begin(), vec1.end(), vec2.begin())
    << std::endl;
}

static void profileSignedIntegerVector()
{
    std::cout << "--- Signed vector ---" << std::endl;
    
    std::vector<int64_t> vec1 = getRandomSignedVector(SIZE);
    std::vector<int64_t> vec2(vec1);
    
    auto begin = std::chrono::high_resolution_clock::now();
    std::sort(vec1.begin(), vec1.end());
    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout << "std::sort() in "
    << std::chrono::
    duration_cast<std::chrono::milliseconds>(end - begin).count()
    << " milliseconds."
    << std::endl;
    
    begin = std::chrono::high_resolution_clock::now();
    sort(vec2.begin(), vec2.end());
    end = std::chrono::high_resolution_clock::now();
    
    std::cout << "Radix sort in "
    << std::chrono::
    duration_cast<std::chrono::milliseconds>(end - begin).count()
    << " milliseconds."
    << std::endl;
    
    std::cout << "Equal: "
    << std::boolalpha
    << std::equal(vec1.begin(), vec1.end(), vec2.begin())
    << std::endl;
}

static void profileSignedIntegerArray()
{
    std::cout << "--- Signed array ---" << std::endl;
    
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
    
    delete[] arr1;
    delete[] arr2;
}

int main(int argc, const char * argv[]) {
    profileUnsignedIntegerArray();
    profileSignedIntegerArray();
    profileUnsignedIntegerVector();
    profileSignedIntegerVector();

    std::cout << "Bye!\n";
    return 0;
}
