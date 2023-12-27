#include <benchmark/benchmark.h>
#include <string>
#include <map>
#include <vector>
#include <functional>

struct Trade
{
    int tradedVolume;
    int tradedPrice;

    enum class side 
    {
        Buy,
        Sell
    };

    side aggressorSide;
    std::string aggressorOwner;
    std::string bookOrderOwner;
};

struct Order 
{
    int price;
    int volume;

    Trade::side side;

    std::string owner;
};

static void BM_order_order(benchmark::State& state)
{
    std::vector<Order> orders;

    orders.emplace_back(Order{10, 10, Trade::side::Buy, "myles"});

    auto trade = [] (const Order& agg, const Order& other)
    {
        int vol = std::min(agg.volume, other.volume);

        std::string ret = std::to_string(agg.price) + " " + std::to_string(vol) + " " + agg.owner + " " + other.owner;
    };

    Order o{10, 20, Trade::side::Sell, "other"};

    while (state.KeepRunning())
    {
        trade(o, orders.back());
    }
}

static void BM_make_trade(benchmark::State& state)
{
    std::vector<Order> orders;

    orders.emplace_back(Order{10, 10, Trade::side::Buy, "myles"});

    auto trade = [] (const Trade t)
    {
        std::string ret = std::to_string(t.tradedPrice) + " " + std::to_string(t.tradedVolume) + " " + t.aggressorOwner + " " + t.bookOrderOwner;
    };

    Order o{10, 20, Trade::side::Sell, "other"};

    while (state.KeepRunning())
    {
        trade(Trade{std::min(o.volume, orders.back().volume), o.price, o.side, o.owner, orders.back().owner});
    }
}

static void BM_trade_func(benchmark::State& state)
{
    std::vector<Order> orders;

    orders.emplace_back(Order{10, 10, Trade::side::Buy, "myles"});

    auto trade = [] (const int tradedVolume, const int tradedPrice, const Trade::side aggressorSide, const std::string aggressorOwner, const std::string bookOrderOwner)
    {
        std::string ret = std::to_string(tradedPrice) + " " + std::to_string(tradedVolume) + " " + aggressorOwner + " " + bookOrderOwner;
    };

    Order o{10, 20, Trade::side::Sell, "other"};

    while (state.KeepRunning())
    {
        trade(std::min(o.volume, orders.back().volume), o.price, o.side, o.owner, orders.back().owner);
    }
}

// Register the function as a benchmark
BENCHMARK(BM_order_order);
BENCHMARK(BM_make_trade);
BENCHMARK(BM_trade_func);

// Run the benchmark
BENCHMARK_MAIN();