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

struct heavy
{
    unsigned i1{};
    unsigned i2{};

    std::string aggressorOwner{};
    std::string bookOrderOwner{};

    char a{};
    char b{};
};

template<typename T>
void AllocateOnStack(int n)
{
    std::vector<T> vec;
    vec.reserve(n);
    for (int i = 0; i < n; i++)
    {
        vec[i] = T{};
    }
    
    while (!vec.empty()) 
    {
        vec.erase(vec.begin());
        escape(&vec);
    }

    clobber();
}

template<typename T>
void AllocateOnHeap(int n)
{
    std::vector<T*> vec;
    vec.reserve(n);
    for (int i = 0; i < n; i++)
    {
        vec[i] = new T{};
    }
    escape(&vec);

    while (!vec.empty()) 
    {
        clobber();
        vec.erase(vec.begin());
        escape(&vec);
    }

    clobber();
}

static void BM_stack_int_32(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        AllocateOnStack<int>(32);
    }
}

static void BM_heap_int_32(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        AllocateOnHeap<int>(32);
    }
}

static void BM_stack_int_64(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        AllocateOnStack<int>(64);
    }
}

static void BM_heap_int_64(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        AllocateOnHeap<int>(64);
    }
}

static void BM_stack_int_128(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        AllocateOnStack<int>(128);
    }
}

static void BM_heap_int_128(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        AllocateOnHeap<int>(128);
    }
}

static void BM_stack_heavy_32(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        AllocateOnStack<heavy>(32);
    }
}

static void BM_heap_heavy_32(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        AllocateOnHeap<heavy>(32);
    }
}

static void BM_stack_heavy_64(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        AllocateOnStack<heavy>(64);
    }
}

static void BM_heap_heavy_64(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        AllocateOnHeap<heavy>(64);
    }
}

static void BM_stack_heavy_128(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        AllocateOnStack<heavy>(128);
    }
}

static void BM_heap_heavy_128(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        AllocateOnHeap<heavy>(128);
    }
}

static void simple_stack(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        int t{};
        clobber();
    }
}

static void simple_heap(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        int* t = new int{};
        clobber();
        delete t;
    }
}

static void simple_vec(benchmark::State& state)
{
    std::vector<int> v;
    
    while (state.KeepRunning())
    {
        v.emplace_back();
        v.pop_back();
        clobber();
    }
}

// literally no difference between these
BENCHMARK(BM_stack_int_32);
BENCHMARK(BM_heap_int_32);
BENCHMARK(BM_stack_int_64);
BENCHMARK(BM_heap_int_64);
BENCHMARK(BM_stack_int_128);
BENCHMARK(BM_heap_int_128);

BENCHMARK(BM_stack_heavy_32);
BENCHMARK(BM_heap_heavy_32);
BENCHMARK(BM_stack_heavy_64);
BENCHMARK(BM_heap_heavy_64);
BENCHMARK(BM_stack_heavy_128);
BENCHMARK(BM_heap_heavy_128);

BENCHMARK(simple_stack);
BENCHMARK(simple_heap);
BENCHMARK(simple_vec);
// Run the benchmark
BENCHMARK_MAIN();