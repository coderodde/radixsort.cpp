#ifndef RADIXSORT_H
#define RADIXSORT_H

#include <algorithm>
#include <iostream>
#include <type_traits>

static constexpr size_t BITS_PER_BYTE = 8;
static constexpr size_t BUCKET_AMOUNT = 256;
static constexpr size_t QUICKSORT_THRESHOLD = 128;

template<class T>
static size_t getBucketIndexUnsigned(T element, size_t byteIndex)
{
    return static_cast<size_t>((element >> (byteIndex * BITS_PER_BYTE)) & 0xff);
}

/*template<class T>
static size_t getBucketIndexUnsigned(T element, size_t byteIndex)
{
    return static_cast<size_t>();
}*/

template<class RandomIt>
void unsigned_radix_sort(RandomIt firstSource, RandomIt lastSource,
                         RandomIt firstTarget, RandomIt lastTarget,
                         size_t byteIndex)
{
    auto rangeLength = std::distance(firstSource, lastSource);
    
    if (rangeLength < QUICKSORT_THRESHOLD)
    {
        std::sort(firstSource, lastSource);
        
        if ((byteIndex & 1) == 0)
        {
            std::copy(firstSource, lastSource, firstTarget);
        }
        
        return;
    }
    
    typedef typename std::iterator_traits<RandomIt>::value_type value_type;
    
    size_t bucketSizeMap[BUCKET_AMOUNT];
    size_t startIndexMap[BUCKET_AMOUNT];
    size_t processedMap [BUCKET_AMOUNT];
    
    for (size_t i = 0; i < BUCKET_AMOUNT; ++i)
    {
        bucketSizeMap[i] = 0;
        startIndexMap[i] = 0;
        processedMap[i]  = 0;
    }
    
    for (RandomIt it = firstSource; it != lastSource; ++it)
    {
        bucketSizeMap[getBucketIndexUnsigned(*it, byteIndex)]++;
    }
    
    for (size_t i = 1; i < BUCKET_AMOUNT; ++i)
    {
        startIndexMap[i] = startIndexMap[i - 1] + bucketSizeMap[i - 1];
    }
    
    for (RandomIt it = firstSource; it != lastSource; ++it)
    {
        value_type element = *it;
        size_t bucket = getBucketIndexUnsigned(element, byteIndex);
        *(firstTarget + startIndexMap[bucket]
          + processedMap[bucket]++) = element;
    }
    
    if (byteIndex > 0)
    {
        for (size_t i = 0; i < BUCKET_AMOUNT; ++i)
        {
            if (bucketSizeMap[i] != 0)
            {
                unsigned_radix_sort(firstTarget + startIndexMap[i],
                                    firstTarget + startIndexMap[i]
                                    + bucketSizeMap[i],
                                    firstSource + startIndexMap[i],
                                    firstSource + startIndexMap[i]
                                    + bucketSizeMap[i],
                                    byteIndex - 1);
            }
        }
    }
}

template<class RandomIt>
void signed_radix_sort(RandomIt firstSource, RandomIt lastSource,
                       RandomIt firstTarget, RandomIt lastTarget,
                       size_t byteIndex)
{
    auto rangeLength = std::distance(firstSource, lastSource);
    
    if (rangeLength < QUICKSORT_THRESHOLD)
    {
        std::sort(firstSource, lastSource);
        
        if ((byteIndex & 1) == 0)
        {
            std::copy(firstSource, lastSource, firstTarget);
        }
        
        return;
    }
    
    typedef typename std::iterator_traits<RandomIt>::value_type value_type;
    
    size_t bucketSizeMap[BUCKET_AMOUNT];
    size_t startIndexMap[BUCKET_AMOUNT];
    size_t processedMap [BUCKET_AMOUNT];
    
    for (size_t i = 0; i < BUCKET_AMOUNT; ++i)
    {
        bucketSizeMap[i] = 0;
        startIndexMap[i] = 0;
        processedMap[i]  = 0;
    }
    
    for (RandomIt it = firstSource; it != lastSource; ++it)
    {
        bucketSizeMap[getBucketIndexUnsigned(*it, byteIndex)]++;
    }
    
    startIndexMap[BUCKET_AMOUNT >> 1] = 0;
    
    for (size_t i = (BUCKET_AMOUNT >> 1) + 1; i < BUCKET_AMOUNT; ++i)
    {
        startIndexMap[i] = startIndexMap[i - 1] + bucketSizeMap[i - 1];
    }
    
    startIndexMap[0] = startIndexMap[BUCKET_AMOUNT - 1] +
                       bucketSizeMap[BUCKET_AMOUNT - 1];
    
    for (size_t i = 1; i < BUCKET_AMOUNT >> 1; ++i)
    {
        startIndexMap[i] = startIndexMap[i - 1] + bucketSizeMap[i - 1];
    }
    
    for (RandomIt it = firstSource; it != lastSource; ++it)
    {
        value_type element = *it;
        size_t bucket = getBucketIndexUnsigned(element, byteIndex);
        *(firstTarget + startIndexMap[bucket]
          + processedMap[bucket]++) = element;
    }
    
    if (byteIndex > 0)
    {
        for (size_t i = 0; i < BUCKET_AMOUNT; ++i)
        {
            if (bucketSizeMap[i] != 0)
            {
                unsigned_radix_sort(firstTarget + startIndexMap[i],
                                    firstTarget + startIndexMap[i]
                                    + bucketSizeMap[i],
                                    firstSource + startIndexMap[i],
                                    firstSource + startIndexMap[i]
                                    + bucketSizeMap[i],
                                    byteIndex - 1);
            }
        }
    }
}

template<class RandomIt>
void unsigned_radix_sort(RandomIt first, RandomIt last)
{
    auto rangeLength = std::distance(first, last);
    typedef typename std::iterator_traits<RandomIt>::value_type value_type;
    value_type* aux = new value_type[rangeLength];
    
    unsigned_radix_sort(first,
                        last,
                        aux,
                        aux + rangeLength,
                        sizeof(value_type) - 1);
    delete[] aux;
}

template<class RandomIt>
void signed_radix_sort(RandomIt first, RandomIt last)
{
    auto rangeLength = std::distance(first, last);
    typedef typename std::iterator_traits<RandomIt>::value_type value_type;
    value_type* aux = new value_type[rangeLength];
    
    signed_radix_sort(first,
                      last,
                      aux,
                      aux + rangeLength,
                      sizeof(value_type) - 1);
    delete[] aux;
}

template<class RandomIt>
void sort(RandomIt first, RandomIt last)
{
    if (std::distance(first, last) < 2)
    {
        // Nothing to sort.
        return;
    }
    
    typedef typename std::iterator_traits<RandomIt>::value_type value_type;
    
    if (std::is_unsigned<value_type>::value)
    {
        // The input integers are unsigned.
        unsigned_radix_sort(first, last);
    }
    else if (std::is_signed<value_type>::value)
    {
        // The input integers are signed.
        signed_radix_sort(first, last);
    }
    else
    {
        // The input objects not integers at all; delegate to stable_sort.
        std::stable_sort(first, last);
    }
}

#endif // RADIXSORT_H
