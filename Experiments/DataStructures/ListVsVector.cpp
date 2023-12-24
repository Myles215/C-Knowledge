#include <benchmark/benchmark.h>

#include <list>
#include <vector>

static void escape(void* p)
{
    asm volatile("" : : "g"(p) : "memory");
}

static void clobber()
{
    asm volatile("" : : : "memory");
}

static void BM_list_build_128(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        std::list<int> lis(128, 0);
    }
}

static void BM_vec_build_128(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        std::vector<int> vec(128, 0);
        escape(vec.data());
    }
}

static void BM_list_insertion_128(benchmark::State& state) 
{
    srand(0);

    while (state.KeepRunning())
    {
        std::list<int> lis(128, 0);

        auto startit = lis.begin();
        int s = rand()%lis.size();
        while (--s > 0) startit++;

        lis.erase(startit);
    }
}

static void BM_vector_insertion_128(benchmark::State& state) 
{
    srand(0);

    while (state.KeepRunning())
    {
        std::vector<int> vec(128, 0);
        escape(&vec);

        auto startit = vec.begin();
        int s = rand()%vec.size();
        while (--s > 0) startit++;

        vec.erase(startit);
        clobber();
    }
}

static void BM_list_build_512(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        std::list<int> lis(512, 0);
    }
}

static void BM_vec_build_512(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        std::vector<int> vec(512, 0);
        escape(vec.data());
    }
}

static void BM_list_insertion_512(benchmark::State& state) 
{
    srand(0);

    while (state.KeepRunning())
    {
        std::list<int> lis(512, 0);

        auto startit = lis.begin();
        int s = rand()%lis.size();
        while (--s > 0) startit++;

        lis.erase(startit);
    }
}

static void BM_vector_insertion_512(benchmark::State& state) 
{
    srand(0);

    while (state.KeepRunning())
    {
        std::vector<int> vec(512, 0);
        escape(&vec);

        auto startit = vec.begin();
        int s = rand()%vec.size();
        while (--s > 0) startit++;

        vec.erase(startit);
        clobber();
    }
}

// Register the function as a benchmark
BENCHMARK(BM_vector_insertion_128);
BENCHMARK(BM_vec_build_128);
BENCHMARK(BM_list_insertion_128);
BENCHMARK(BM_list_build_128);

BENCHMARK(BM_vector_insertion_512);
BENCHMARK(BM_vec_build_512);
BENCHMARK(BM_list_insertion_512);
BENCHMARK(BM_list_build_512);
// Run the benchmark
BENCHMARK_MAIN();