#ifndef RADIXSORT_H
#define RADIXSORT_H

#include <algorithm>
#include <climits>
#include <type_traits>
#include <vector>

static constexpr size_t BUCKET_AMOUNT = 256;
static constexpr size_t QUICKSORT_THRESHOLD = 256;

template<class T>
size_t getBucketIndexUnsigned(T element, size_t byteIndex)
{
    return static_cast<size_t>((element >> (byteIndex * CHAR_BIT)) & 0xff);
}

template<class RandomIt1, class RandomIt2>
void unsigned_radix_sort(RandomIt1 firstSource, RandomIt1 lastSource,
                         RandomIt2 firstTarget, RandomIt2 lastTarget,
                         size_t byteIndex)
{
    auto rangeLength = std::distance(firstSource, lastSource);
    
    if (rangeLength < QUICKSORT_THRESHOLD)
    {
        std::sort(firstSource, lastSource);
        
        if ((byteIndex & 1) == 0)
        {
            // We had to sort [firstSource, lastSource) because it contains
            // all the elements belonging to that very range. However,
            // that range does not reside in the argument vector, so we have
            // to copy it into the argument vector.
            std::copy(firstSource, lastSource, firstTarget);
        }
        
        return;
    }
    
    using value_type = typename std::iterator_traits<RandomIt1>::value_type;
    
    size_t bucketSizeMap[BUCKET_AMOUNT] = {0};
    size_t startIndexMap[BUCKET_AMOUNT] = {0};
    size_t processedMap [BUCKET_AMOUNT] = {0};
    
    for (RandomIt1 it = firstSource; it != lastSource; ++it)
    {
        bucketSizeMap[getBucketIndexUnsigned(*it, byteIndex)]++;
    }
    
    for (size_t i = 1; i < BUCKET_AMOUNT; ++i)
    {
        startIndexMap[i] = startIndexMap[i - 1] + bucketSizeMap[i - 1];
    }
    
    for (RandomIt1 it = firstSource; it != lastSource; ++it)
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

template<class RandomIt1, class RandomIt2>
void signed_radix_sort(RandomIt1 firstSource, RandomIt1 lastSource,
                       RandomIt2 firstTarget, RandomIt2 lastTarget,
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
    
    using value_type = typename std::iterator_traits<RandomIt1>::value_type;
    
    size_t bucketSizeMap[BUCKET_AMOUNT] = {0};
    size_t startIndexMap[BUCKET_AMOUNT] = {0};
    size_t processedMap [BUCKET_AMOUNT] = {0};
    
    for (RandomIt1 it = firstSource; it != lastSource; ++it)
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
    
    for (RandomIt1 it = firstSource; it != lastSource; ++it)
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
    using value_type = typename std::iterator_traits<RandomIt>::value_type;
    
    std::vector<value_type> aux(rangeLength);
    
    unsigned_radix_sort(first,
                        last,
                        aux.begin(),
                        aux.end(),
                        sizeof(value_type) - 1);
}

template<class RandomIt>
void signed_radix_sort(RandomIt first, RandomIt last)
{
    auto rangeLength = std::distance(first, last);
    using value_type = typename std::iterator_traits<RandomIt>::value_type;
    
    std::vector<value_type> aux(rangeLength);
    
    signed_radix_sort(first,
                      last,
                      aux.begin(),
                      aux.end(),
                      sizeof(value_type) - 1);
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
        // The input objects not integers at all; delegate to std::sort.
        std::sort(first, last);
    }
}

#endif // RADIXSORT_H
