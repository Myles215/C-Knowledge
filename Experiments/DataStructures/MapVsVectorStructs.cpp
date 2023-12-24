#include <benchmark/benchmark.h>

#include <map>
#include <vector>
#include <numeric>
#include <algorithm>

struct Heavy
{
    int a{};
    int b{};
    std::string s = "hmm";
    double p{};
};

struct Level
{
    int price;
    std::vector<Heavy> data;
};

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

    std::vector<Heavy> in = {Heavy(), Heavy(), Heavy(), Heavy(), Heavy()};
    Level level{0, in};

    while (state.KeepRunning())
    {
        std::vector<Level> s;
        int ind = 0;

        for (int i = 0;i<128;i++)
        {
            level.price = nums[i];
            s.insert(std::lower_bound(s.begin(), s.end(), nums[i], [](Level l, int p){
                return l.price > p;
            }), level);

            if (i > 0 && i % 4 == 0) s.erase(std::lower_bound(s.begin(), s.end(), nums[ind++], [](Level l, int p) {
                                            return l.price > p;
                                            }));
        }
    }
}

static void BM_map_insert_128(benchmark::State& state)
{
    srand(1);
    std::vector<int> nums(128);
    std::iota(nums.begin(), nums.end(), 0);
    std::sort(nums.begin(), nums.end(), [](int l, int r){
        return rand()%2 == 0;
    });

    std::vector<Heavy> in = {Heavy(), Heavy(), Heavy(), Heavy(), Heavy()};

    while (state.KeepRunning())
    {
        std::map<int, std::vector<Heavy>> s;
        int ind = 0;

        for (int i = 0;i<128;i++)
        {
            s[nums[i]] = in;
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

    std::vector<Heavy> in = {Heavy(), Heavy(), Heavy(), Heavy(), Heavy()};
    Level level{0, in};

    while (state.KeepRunning())
    {
        std::vector<Level> s;
        int ind = 0;

        for (int i = 0;i<256;i++)
        {
            level.price = nums[i];
            s.insert(std::lower_bound(s.begin(), s.end(), nums[i], [](Level l, int p){
                return l.price > p;
            }), level);

            if (i > 0 && i % 4 == 0) s.erase(std::lower_bound(s.begin(), s.end(), nums[ind++], [](Level l, int p) {
                                            return l.price > p;
                                            }));
        }
    }
}

static void BM_map_insert_256(benchmark::State& state)
{
    srand(1);
    std::vector<int> nums(256);
    std::iota(nums.begin(), nums.end(), 0);
    std::sort(nums.begin(), nums.end(), [](int l, int r){
        return rand()%2 == 0;
    });

    std::vector<Heavy> in = {Heavy(), Heavy(), Heavy(), Heavy(), Heavy()};

    while (state.KeepRunning())
    {
        std::map<int, std::vector<Heavy>> s;
        int ind = 0;

        for (int i = 0;i<256;i++)
        {
            s[nums[i]] = in;
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

    std::vector<Heavy> in = {Heavy(), Heavy(), Heavy(), Heavy(), Heavy()};
    Level level{0, in};

    while (state.KeepRunning())
    {
        std::vector<Level> s;
        int ind = 0;

        for (int i = 0;i<384;i++)
        {
            level.price = nums[i];
            s.insert(std::lower_bound(s.begin(), s.end(), nums[i], [](Level l, int p){
                return l.price > p;
            }), level);

            if (i > 0 && i % 4 == 0) s.erase(std::lower_bound(s.begin(), s.end(), nums[ind++], [](Level l, int p) {
                                            return l.price > p;
                                            }));
        }
    }
}

static void BM_map_insert_512(benchmark::State& state)
{
    srand(1);
    std::vector<int> nums(384);
    std::iota(nums.begin(), nums.end(), 0);
    std::sort(nums.begin(), nums.end(), [](int l, int r){
        return rand()%2 == 0;
    });

    std::vector<Heavy> in = {Heavy(), Heavy(), Heavy(), Heavy(), Heavy()};

    while (state.KeepRunning())
    {
        std::map<int, std::vector<Heavy>> s;
        int ind = 0;

        for (int i = 0;i<384;i++)
        {
            s[nums[i]] = in;
            if (i > 0 && i % 4 == 0) s.erase(nums[ind++]);
        }
    }
}

// Register the function as a benchmark
BENCHMARK(BM_vector_insert_128);
BENCHMARK(BM_map_insert_128);
BENCHMARK(BM_vector_insert_256);
BENCHMARK(BM_map_insert_256);
BENCHMARK(BM_vector_insert_512);
BENCHMARK(BM_map_insert_512);

// Run the benchmark
BENCHMARK_MAIN();