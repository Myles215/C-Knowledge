#include <benchmark/benchmark.h>
#include <string>
#include <map>
#include <vector>
#include <functional>

#include <coroutine>

struct heavy
{
    unsigned i1;
    unsigned i2;

    std::string aggressorOwner;
    std::string bookOrderOwner;

    char a;
    char b;
};

template<typename T>
struct Generator
{
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
 
    struct promise_type // required
    {
        T value_;
        std::exception_ptr exception_;
 
        Generator get_return_object()
        {
            return Generator(handle_type::from_promise(*this));
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { exception_ = std::current_exception(); } // saving
                                                                              // exception
 
        template<std::convertible_to<T> From> // C++20 concept
        std::suspend_always yield_value(From&& from)
        {
            value_ = std::forward<From>(from); // caching the result in promise
            return {};
        }
        void return_void() {}
    };
 
    handle_type h_;
 
    Generator(handle_type h) : h_(h) {}
    ~Generator() { h_.destroy(); }
    explicit operator bool()
    {
        fill(); // The only way to reliably find out whether or not we finished coroutine,
                // whether or not there is going to be a next value generated (co_yield)
                // in coroutine via C++ getter (operator () below) is to execute/resume
                // coroutine until the next co_yield point (or let it fall off end).
                // Then we store/cache result in promise to allow getter (operator() below
                // to grab it without executing coroutine).
        return !h_.done();
    }
    T operator()()
    {
        fill();
        full_ = false; // we are going to move out previously cached
                       // result to make promise empty again
        return std::move(h_.promise().value_);
    }
 
private:
    bool full_ = false;
 
    void fill()
    {
        if (!full_)
        {
            h_();
            if (h_.promise().exception_)
                std::rethrow_exception(h_.promise().exception_);
            // propagate coroutine exception in called context
 
            full_ = true;
        }
    }
};

static void escape(const void* p)
{
    asm volatile("" : : "g"(p) : "memory");
}

static void clobber()
{
    asm volatile("" : : : "memory");
}
 
Generator<heavy>
coro_heavy(unsigned n)
{
    for (unsigned i = 0; i < n; i++)
    {
        co_yield heavy{i, i, "hello", "world", 'a', 'b'};
    }

    co_return;
}

std::vector<heavy> func_heavy(unsigned n)
{
    std::vector<heavy> ret(n);

    for (unsigned i = 0; i < n; i++)
    {
        ret[i] = heavy{i, i, "hello", "world", 'a', 'b'};
    }

    return ret;
}

void operate_on(const heavy& h)
{
    const auto [i, j, s1, s2, c1, c2] = h;
    int k = i * j;
    std::string lo = s1 + s2;
    char p = c1 + c2;
    clobber();
}

static void BM_coroutine_return_8(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        auto gen =  coro_heavy(8);

        while (gen) operate_on(gen());
    }
}

static void BM_func_return_8(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        for (const auto h : func_heavy(8))
        {
            operate_on(h);
        }
    }
}

static void BM_coroutine_return_16(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        auto gen =  coro_heavy(16);

        while (gen) operate_on(gen());
    }
}

static void BM_func_return_16(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        for (const auto h : func_heavy(16))
        {
            operate_on(h);
        }
    }
}

static void BM_coroutine_return_32(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        auto gen =  coro_heavy(32);

        while (gen) operate_on(gen());
    }
}

static void BM_func_return_32(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        for (const auto h : func_heavy(32))
        {
            operate_on(h);
        }
    }
}

static void BM_coroutine_return_64(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        auto gen =  coro_heavy(64);

        while (gen) operate_on(gen());
    }
}

static void BM_func_return_64(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        for (const auto& h : func_heavy(64))
        {
            operate_on(h);
        }
    }
}

// Register the function as a benchmark
BENCHMARK(BM_coroutine_return_8);
BENCHMARK(BM_func_return_8);
BENCHMARK(BM_coroutine_return_16);
BENCHMARK(BM_func_return_16);
BENCHMARK(BM_coroutine_return_32);
BENCHMARK(BM_func_return_32);
BENCHMARK(BM_coroutine_return_64);
BENCHMARK(BM_func_return_64);

// Run the benchmark
BENCHMARK_MAIN();