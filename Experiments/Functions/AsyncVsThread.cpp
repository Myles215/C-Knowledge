#include <benchmark/benchmark.h>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <future>
#include <thread>

struct heavy
{
    unsigned i1;
    unsigned i2;

    std::string s1;
    std::string s2;

    char a;
    char b;
};

void func(heavy& heav) 
{
    int l = heav.i1 + heav.i2;
    std::string s3 = heav.s1 + heav.s2;
    s3 += heav.a;
    s3 += heav.b;
}

static void async_func(benchmark::State& state)
{
    heavy h{2, 4, "myles", "watkinson", 'a', 'b'};

    while (state.KeepRunning())
    {
        auto a = std::async(std::launch::async, [&h] 
        {   
            int l = h.i1 + h.i2;
            std::string s3 = h.s1 + h.s2;
            s3 += h.a;
            s3 += h.b;
        });
        a.wait();
    }
}

static void thread_func(benchmark::State& state)
{
    heavy heav{2, 4, "myles", "watkinson", 'a', 'b'};

    while (state.KeepRunning())
    {
        auto a = std::thread([&heav]
        {  
            int l = heav.i1 + heav.i2;
            std::string s3 = heav.s1 + heav.s2;
            s3 += heav.a;
            s3 += heav.b;
        });
        a.join();
    }
}

static void inline_func(benchmark::State& state)
{
    heavy heav{2, 4, "myles", "watkinson", 'a', 'b'};

    while (state.KeepRunning())
    {
        auto a = [&heav]
        {  
            int l = heav.i1 + heav.i2;
            std::string s3 = heav.s1 + heav.s2;
            s3 += heav.a;
            s3 += heav.b;
        };
        a();
    }
}

static void inline_func2(benchmark::State& state)
{
    heavy heav{2, 4, "myles", "watkinson", 'a', 'b'};

    auto a = [&heav]
        {  
            int l = heav.i1 + heav.i2;
            std::string s3 = heav.s1 + heav.s2;
            s3 += heav.a;
            s3 += heav.b;
        };

    while (state.KeepRunning())
    {
        a();
    }
}

BENCHMARK(async_func);
BENCHMARK(thread_func);
BENCHMARK(inline_func);
BENCHMARK(inline_func2);

// Run the benchmark
BENCHMARK_MAIN();