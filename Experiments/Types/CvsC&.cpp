#include <benchmark/benchmark.h>
#include <string>
#include <map>
#include <vector>

static void escape(const void* p)
{
    asm volatile("" : : "g"(p) : "memory");
}

static void clobber()
{
    asm volatile("" : : : "memory");
}

void ConstIteration(std::string& s)
{
    for (const auto c : s)
    {
        //escape(&c);
        clobber();
    }
}

void Iteration(std::string& s)
{
    for (auto c : s)
    {
        //escape(&c);
        clobber();
    }
}

void ConstRefIteration(std::string& s)
{
    for (const auto& c : s)
    {
        //escape(&c);
        clobber();
    }
}

static void BM_const_string_loop_64(benchmark::State& state)
{
    std::string s(64, ' ');

    while (state.KeepRunning())
    {
        ConstIteration(s);
    }
}

static void BM_constref_string_loop_64(benchmark::State& state)
{
    std::string s(64, ' ');

    while (state.KeepRunning())
    {
        ConstRefIteration(s);
    }
}

static void BM_string_loop_64(benchmark::State& state)
{
    std::string s(64, ' ');

    while (state.KeepRunning())
    {
        Iteration(s);
    }
}

static void BM_const_string_loop_256(benchmark::State& state)
{
    std::string s(256, ' ');

    while (state.KeepRunning())
    {
        ConstIteration(s);
    }
}

static void BM_constref_string_loop_256(benchmark::State& state)
{
    std::string s(256, ' ');

    while (state.KeepRunning())
    {
        ConstRefIteration(s);
    }
}

static void BM_string_loop_256(benchmark::State& state)
{
    std::string s(256, ' ');

    while (state.KeepRunning())
    {
        Iteration(s);
    }
}

static void BM_const_string_loop_1024(benchmark::State& state)
{
    std::string s(1024, ' ');

    while (state.KeepRunning())
    {
        ConstIteration(s);
    }
}

static void BM_constref_string_loop_1024(benchmark::State& state)
{
    std::string s(1024, ' ');

    while (state.KeepRunning())
    {
        ConstRefIteration(s);
    }
}

static void BM_string_loop_1024(benchmark::State& state)
{
    std::string s(1024, ' ');

    while (state.KeepRunning())
    {
        Iteration(s);
    }
}

// literally no difference between these
BENCHMARK(BM_const_string_loop_64);
BENCHMARK(BM_constref_string_loop_64);
BENCHMARK(BM_string_loop_64);

BENCHMARK(BM_const_string_loop_256);
BENCHMARK(BM_constref_string_loop_256);
BENCHMARK(BM_string_loop_256);

BENCHMARK(BM_const_string_loop_1024);
BENCHMARK(BM_constref_string_loop_1024);
BENCHMARK(BM_string_loop_1024);

// Run the benchmark
BENCHMARK_MAIN();