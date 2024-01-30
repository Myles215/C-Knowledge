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

template <class DerivedClass>
class StaticInterface
{
public:
    void DoSomething()
    {
        static_cast<DerivedClass*>(this)->DoSomethingImp();
    }
};

class StaticDerived : public StaticInterface<StaticDerived>
{
public:
    void DoSomethingImp()
    {
        int x = 1;
        int y = x + 2;
        int z = x * y;
    }
};

class DynamicInterface
{
public:
    virtual void DoSomething() = 0;
};

class DynamicDerived : public DynamicInterface
{
public:
    void DoSomething() override
    {
        int x = 1;
        int y = x + 2;
        int z = x * y;
    }
};

static void BM_static_inheritance(benchmark::State& state)
{
    StaticDerived* interface = new StaticDerived;

    while (state.KeepRunning())
    {
        interface->DoSomething();
    }
}

static void BM_dynamic_inheritance(benchmark::State& state)
{
    DynamicDerived* interface = new DynamicDerived;

    while (state.KeepRunning())
    {
        interface->DoSomething();
    }
}

static void BM_static_inheritance_virtual(benchmark::State& state)
{
    StaticInterface<StaticDerived>* interface = new StaticDerived;

    while (state.KeepRunning())
    {
        interface->DoSomething();
    }
}

static void BM_dynamic_inheritance_virtual(benchmark::State& state)
{
    DynamicInterface* interface = new DynamicDerived;

    while (state.KeepRunning())
    {
        interface->DoSomething();
    }
}

BENCHMARK(BM_static_inheritance);
BENCHMARK(BM_dynamic_inheritance);
BENCHMARK(BM_static_inheritance_virtual);
BENCHMARK(BM_dynamic_inheritance_virtual);

// Run the benchmark
BENCHMARK_MAIN();