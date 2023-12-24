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

struct Heavy
{
    int p{};
    int id{};
    int v{};

    std::string o = "owner";
};

static void BM_list_delete_128(benchmark::State& state)
{
    srand(1);
    std::vector<Heavy> input;

    for (int i = 0;i<128;i++)
    {   
        input.emplace_back();
        input.back().id = i;
    }

    while (state.KeepRunning())
    {
        std::list<Heavy> s;

        for (int i = 0;i<128;i++)
        {
            s.emplace_back(input[i]);

            if (i > 0 && i % 4 == 0)
            {
                auto it = std::find_if(s.begin(), s.end(), [i](Heavy& h){
                    return h.id == rand() % (i+1);
                });
 
                if (it != s.end()) s.erase(it);
            }
        }
    }
}

static void BM_vec_delete_128(benchmark::State& state)
{
    srand(1);
    std::vector<Heavy> input;

    for (int i = 0;i<128;i++)
    {   
        input.emplace_back();
        input.back().id = i;
    }

    while (state.KeepRunning())
    {
        std::vector<Heavy> s;

        for (int i = 0;i<128;i++)
        {
            s.emplace_back(input[i]);

            if (i > 0 && i % 4 == 0)
            {
                auto it = std::lower_bound(s.begin(), s.end(), 0, [i](Heavy& h, int a){
                    return h.id == rand() % (i+1);
                });
 
                if (it != s.end()) s.erase(it);
            }
        }
    }
}

// Register the function as a benchmark
BENCHMARK(BM_list_delete_128);
BENCHMARK(BM_vec_delete_128);

// Run the benchmark
BENCHMARK_MAIN();