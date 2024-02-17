#include <benchmark/benchmark.h>
#include <string>
#include <fstream>

void print_cpp_string(const std::string& s, std::ofstream& out)
{
    out << s;
}

void print_c_string(const char* s, FILE* fp)
{
    fputs(s, fp);
}

void print_c_string(const char* s, size_t size, FILE* fp)
{
    fwrite(s, size, 1, fp);
}

void print_c_string_(const char* s, FILE* fp)
{
    fprintf(fp, s);
}

static void cpp_string_write(benchmark::State& state)
{
    std::ofstream of("test.kv");

    while (state.KeepRunning())
    {
        print_cpp_string("welp", of);
    }

    std::remove("test.kv");
}

static void c_string_write(benchmark::State& state)
{
    FILE* fp = fopen("test.txt", "w");

    while (state.KeepRunning())
    {
        print_c_string("welp", fp);
    }

    fclose(fp);
    std::remove("test.txt");
}

static void c_string_write_fwrite(benchmark::State& state)
{
    FILE* fp = fopen("test.txt", "w");

    while (state.KeepRunning())
    {
        print_c_string("welp", 4, fp);
    }

    fclose(fp);
    std::remove("test.txt");
}

static void cpp_string_write_fo(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        std::ofstream of("test.txt");
        print_cpp_string("welp", of);
    }

    std::remove("test.txt");
}

static void c_string_write_fo(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        FILE* fp = fopen("test.txt", "w");
        print_c_string("welp", fp);
        fclose(fp);
    }

    std::remove("test.txt");
}


static void c_string_write_fo_fwrite(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        FILE* fp = fopen("test.txt", "w");
        print_c_string("welp", 4, fp);
        fclose(fp);
    }

    std::remove("test.txt");
}

static void c_string_write_fo_fprint(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        FILE* fp = fopen("test.txt", "w");
        print_c_string_("welp", fp);
        fclose(fp);
    }

    std::remove("test.txt");
}

static void cpp_string_read_getline(benchmark::State& state)
{
    std::ofstream of("test.txt");
    of << "test string 1";

    while (state.KeepRunning())
    {
        std::ifstream file("test.txt");
        std::string line;
        std::getline(file, line);
        file.close();
    }

    std::remove("test.txt");
}

static void cpp_string_read_buffer(benchmark::State& state)
{
    std::ofstream of("test.txt");
    of << "test string 1";

    while (state.KeepRunning())
    {
        std::ifstream file("test.txt");
        std::string line((std::istream_iterator<char>(file)), std::istream_iterator<char>());
        file.close();
    }

    std::remove("test.txt");
}

static void c_string_read(benchmark::State& state)
{
    std::ofstream of("test.txt");
    of << "test string 1";

    while (state.KeepRunning())
    {
        FILE* fp = fopen("test.txt", "r");
        char* line = NULL;
        size_t len = 0;
        getline(&line, &len, fp);
        fclose(fp);
    }

    std::remove("test.txt");
}

static void c_string_read_convert(benchmark::State& state)
{
    std::ofstream of("test.txt");
    of << "test string 1";

    while (state.KeepRunning())
    {
        FILE* fp = fopen("test.txt", "r");
        char* line = NULL;
        size_t len = 0;
        getline(&line, &len, fp);
        std::string s(line);
        fclose(fp);
    }

    std::remove("test.txt");
}

static void c_string_read_fread(benchmark::State& state)
{
    std::ofstream of("test.txt");
    of << "test string 1";

    while (state.KeepRunning())
    {
        FILE* fp = fopen("test.txt", "r");
        char* line = NULL;
        fread(line, 4, 1, fp);
        fclose(fp);
    }

    std::remove("test.txt");
}

static void cpp_string_cheat(benchmark::State& state)
{
    std::filesystem::create_directory(std::string("./testDir"));
    std::ofstream of("./testDir/test.txt");
    of << "test string 1";

    while (state.KeepRunning())
    {
        for (const auto& dirEntry : std::filesystem::directory_iterator{std::string("./testDir")})
        {
            //if  != "testDir/test") throw std::runtime_error(dirEntry.path().generic_string());
            //std::string s{dirEntry.path().generic_string().substr(2, 12)};
            FILE* fp = fopen(dirEntry.path().generic_string().c_str(), "r");
            char* line = NULL;
            size_t len = 0;
            getline(&line, &len, fp);
            std::string s(line);
            fclose(fp);
        }
    }

    std::filesystem::remove_all(std::string("./testDir"));
}

BENCHMARK(cpp_string_write);
BENCHMARK(c_string_write);
BENCHMARK(c_string_write_fwrite);

BENCHMARK(cpp_string_write_fo);
BENCHMARK(c_string_write_fo);
BENCHMARK(c_string_write_fo_fwrite);
BENCHMARK(c_string_write_fo_fprint);

BENCHMARK(cpp_string_read_getline);
BENCHMARK(cpp_string_read_buffer);
BENCHMARK(c_string_read);
BENCHMARK(c_string_read_convert);
BENCHMARK(c_string_read_fread);

BENCHMARK(cpp_string_cheat);

// Run the benchmark
BENCHMARK_MAIN();