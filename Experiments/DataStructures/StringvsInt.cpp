#include <benchmark/benchmark.h>
#include <string>
#include <map>
#include <vector>

static void clobber()
{
    asm volatile("" : : : "memory");
}

std::map<std::string, int> MakeStringMap(int num, int len)
{
    std::map<std::string, int> ret;

    for (int i = 0; i < num; i++)
    {
        std::string em = "";
        for (int j = 0; j < len; j++)
        {
            em += (char(rand()%256));
        }
        ret[em] = 1;
    }

    return ret;
}

std::map<int, int> MakeIntMap(int num)
{
    std::map<int, int> ret;

    for (int i = 0; i < num; i++)
    {
        ret[rand()%256] = 1;
    }

    return ret;
}

std::vector<std::string> MakeStringVec(int num, int len)
{
    std::vector<std::string> ret;

    for (int i = 0; i < num; i++)
    {
        std::string em = "";
        for (int j = 0; j < len; j++)
        {
            em += (char(rand()%256));
        }
        ret.push_back(em);
    }

    return ret;
}

std::vector<int> MakeIntVec(int num)
{
    std::vector<int> ret;

    for (int i = 0; i < num; i++)
    {
        ret.push_back(rand()%256);
    }

    return ret;
}

static void BM_map_find_string_64(benchmark::State& state)
{
    const auto m = MakeStringMap(64, 8);

    std::string search = "aabaevxy";

    while (state.KeepRunning())
    {
        auto it = m.find(search);
        clobber();
    }
}

static void BM_map_find_int_64(benchmark::State& state)
{
    const auto m = MakeIntMap(64);

    int search = 120;

    while (state.KeepRunning())
    {
        auto it = m.find(search);
        clobber();
    }
}

static void BM_vec_find_string_64(benchmark::State& state)
{
    const auto v = MakeStringVec(64, 8);

    std::string search = "aabaevxy";

    while (state.KeepRunning())
    {
        auto it = find(v.begin(), v.end(), search);
        clobber();
    }
}

static void BM_vec_find_int_64(benchmark::State& state)
{
    const auto v = MakeIntVec(64);

    int search = 280;

    while (state.KeepRunning())
    {
        auto it = find(v.begin(), v.end(), search);
        clobber();
    }
}

// Register the function as a benchmark
BENCHMARK(BM_map_find_string_64);
BENCHMARK(BM_map_find_int_64);
BENCHMARK(BM_vec_find_string_64);
BENCHMARK(BM_vec_find_int_64);
// Run the benchmark
BENCHMARK_MAIN();