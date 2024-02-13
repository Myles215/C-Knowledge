#include <benchmark/benchmark.h>
#include <string>
#include <vector>

static void escape(const void* p)
{
    asm volatile("" : : "g"(p) : "memory");
}

static void clobber()
{
    asm volatile("" : : : "memory");
}

static void simple_stack(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        int t{};
        escape(&t);
    }
}

static void simple_heap(benchmark::State& state)
{
    int* t = nullptr;

    while (state.KeepRunning())
    {
        t = new int{};
        escape(t);
        delete t;
    }
}

static void simple_vec_emplace(benchmark::State& state)
{
    std::vector<int> v;
    
    while (state.KeepRunning())
    {
        v.emplace_back();
        v.pop_back();
        escape(&v);
    }
}

static void simple_vec_push(benchmark::State& state)
{
    std::vector<int> v;
    
    while (state.KeepRunning())
    {
        v.push_back(int{});
        v.pop_back();
        escape(&v);
    }
}

BENCHMARK(simple_stack);
BENCHMARK(simple_heap);
BENCHMARK(simple_vec_emplace);
BENCHMARK(simple_vec_push);
// Run the benchmark
BENCHMARK_MAIN();