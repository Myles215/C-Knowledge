#include <benchmark/benchmark.h>

#include <set>
#include <vector>
#include <numeric>
#include <algorithm>

static void escape(void* p)
{
    asm volatile("" : : "g"(p) : "memory");
}

static void clobber()
{
    asm volatile("" : : : "memory");
}

static void BM_vector_insert_128(benchmark::State& state)
{
    srand(1);
    std::vector<int> nums(128);
    std::iota(nums.begin(), nums.end(), 0);
    std::sort(nums.begin(), nums.end(), [](int l, int r){
        return rand()%2 == 0;
    });

    while (state.KeepRunning())
    {
        std::vector<int> s;
        int ind = 0;

        for (int i = 0;i<128;i++)
        {
            s.insert(std::lower_bound(s.begin(), s.end(), nums[i]), nums[i]);
            if (i > 0 && i % 4 == 0) s.erase(std::lower_bound(s.begin(), s.end(), nums[ind++]));
        }
    }
}

static void BM_set_insert_128(benchmark::State& state)
{
    srand(1);
    std::vector<int> nums(128);
    std::iota(nums.begin(), nums.end(), 0);
    std::sort(nums.begin(), nums.end(), [](int l, int r){
        return rand()%2 == 0;
    });

    while (state.KeepRunning())
    {
        std::set<int> s;
        int ind = 0;

        for (int i = 0;i<128;i++)
        {
            s.insert(nums[i]);
            if (i > 0 && i % 4 == 0) s.erase(nums[ind++]);
        }
    }
}

static void BM_vector_insert_256(benchmark::State& state)
{
    srand(1);
    std::vector<int> nums(256);
    std::iota(nums.begin(), nums.end(), 0);
    std::sort(nums.begin(), nums.end(), [](int l, int r){
        return rand()%2 == 0;
    });

    while (state.KeepRunning())
    {
        std::vector<int> s;
        int ind = 0;

        for (int i = 0;i<256;i++)
        {
            s.insert(std::lower_bound(s.begin(), s.end(), nums[i]), nums[i]);
            if (i > 0 && i % 4 == 0) s.erase(std::lower_bound(s.begin(), s.end(), nums[ind++]));
        }
    }
}

static void BM_set_insert_256(benchmark::State& state)
{
    srand(1);
    std::vector<int> nums(256);
    std::iota(nums.begin(), nums.end(), 0);
    std::sort(nums.begin(), nums.end(), [](int l, int r){
        return rand()%2 == 0;
    });

    while (state.KeepRunning())
    {
        std::set<int> s;
        int ind = 0;

        for (int i = 0;i<256;i++)
        {
            s.insert(nums[i]);
            if (i > 0 && i % 4 == 0) s.erase(nums[ind++]);
        }
    }
}

static void BM_vector_insert_512(benchmark::State& state)
{
    srand(1);
    std::vector<int> nums(384);
    std::iota(nums.begin(), nums.end(), 0);
    std::sort(nums.begin(), nums.end(), [](int l, int r){
        return rand()%2 == 0;
    });

    while (state.KeepRunning())
    {
        std::vector<int> s;
        int ind = 0;

        for (int i = 0;i<384;i++)
        {
            s.insert(std::lower_bound(s.begin(), s.end(), nums[i]), nums[i]);
            if (i > 0 && i % 4 == 0) s.erase(std::lower_bound(s.begin(), s.end(), nums[ind++]));
        }
    }
}

static void BM_set_insert_512(benchmark::State& state)
{
    srand(1);
    std::vector<int> nums(384);
    std::iota(nums.begin(), nums.end(), 0);
    std::sort(nums.begin(), nums.end(), [](int l, int r){
        return rand()%2 == 0;
    });

    while (state.KeepRunning())
    {
        std::set<int> s;
        int ind = 0;

        for (int i = 0;i<384;i++)
        {
            s.insert(nums[i]);
            if (i > 0 && i % 4 == 0) s.erase(nums[ind++]);
        }
    }
}

// Register the function as a benchmark
BENCHMARK(BM_vector_insert_128);
BENCHMARK(BM_set_insert_128);
BENCHMARK(BM_vector_insert_256);
BENCHMARK(BM_set_insert_256);
BENCHMARK(BM_vector_insert_512);
BENCHMARK(BM_set_insert_512);

// Run the benchmark
BENCHMARK_MAIN();