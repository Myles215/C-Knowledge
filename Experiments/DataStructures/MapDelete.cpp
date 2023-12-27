#include <benchmark/benchmark.h>
#include <string>
#include <map>
#include <vector>

struct Heavy
{
    int a{};
    int b{};
    std::string s = "hmm";
    double p{};
};

static void BM_iterator_delete(benchmark::State& state)
{
    std::vector<Heavy> input;

    for (int i = 0;i<128;i++) input.emplace_back();

    while (state.KeepRunning())
    {
        std::map<int, std::vector<Heavy>> s;

        int j = 0;

        for (int i = 0;i<32;i++)
        {
            for (int k = 0;k<4;k++) s[i].push_back(input[j++]);
        }

        for (auto outer = s.begin(); outer != s.end();)
        {
            for (auto inner = outer->second.begin(); inner != outer->second.end();)
            {
                outer->second.erase(inner++);
            }

            s.erase(outer++);
        }

    }
}

static void BM_begin_delete(benchmark::State& state)
{
    std::vector<Heavy> input;

    for (int i = 0;i<128;i++) input.emplace_back();

    while (state.KeepRunning())
    {
        std::map<int, std::vector<Heavy>> s;

        int j = 0;

        for (int i = 0;i<32;i++)
        {
            for (int k = 0;k<4;k++) s[i].push_back(input[j++]);
        }

        while (!s.empty())
        {
            auto& level = s.begin()->second;

            while (!level.empty())
            {   
                level.erase(level.begin());
            }

            s.erase(s.begin());
        }

    }
}

// Register the function as a benchmark
BENCHMARK(BM_iterator_delete);
BENCHMARK(BM_begin_delete);

// Run the benchmark
BENCHMARK_MAIN();