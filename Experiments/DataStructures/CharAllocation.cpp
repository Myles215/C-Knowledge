#include <benchmark/benchmark.h>

static void escape(void* p)
{
    asm volatile("" : : "g"(p) : "memory");
}

static void clobber()
{
    asm volatile("" : : : "memory");
}

static void BM_char_array_128(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        char* newArray = new char[128];
        escape(newArray);
    }
}

static void BM_char_array_256(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        char* newArray = new char[256];
        escape(newArray);
    }
}

static void BM_char_array_512(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        char* newArray = new char[512];
        escape(newArray);
    }
}

static void BM_char_array_1024(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        char* newArray = new char[1024];
        escape(newArray);
    }
}

// Register the function as a benchmark
BENCHMARK(BM_char_array_128);
BENCHMARK(BM_char_array_256);
BENCHMARK(BM_char_array_512);
BENCHMARK(BM_char_array_1024);
// Run the benchmark
BENCHMARK_MAIN();