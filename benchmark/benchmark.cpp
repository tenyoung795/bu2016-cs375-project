#include <cstdlib>

#include <chrono>
#include <iostream>
#include <random>
#include <ratio>
#include <utility>
#include <unordered_set>
#include <vector>

#include "../linearProbe.h"
#include "../resize.h"
#include "../robinHoodHash.h"

/**
 * Benchmarks an argumentless function.
 *
 * @param r the runnable.
 * @tparam Runnable the runnable's type.
 * @return How long it took.
 */
template <class Runnable>
static std::chrono::duration<double, std::nano> benchmark(Runnable &&r) {
    auto begin = std::chrono::steady_clock::now();
    std::forward<Runnable>(r)();
    return std::chrono::steady_clock::now() - begin;
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " NUMBER_OF_ELEMENTS\n";
        return EXIT_FAILURE;
    }

    const auto num_elements = std::strtoul(argv[1], nullptr, 10);
    const auto capacity = cs375::next_table_size(static_cast<std::size_t>(static_cast<long double>(num_elements) / 0.75l));

    std::random_device rd;
    std::default_random_engine engine(rd());
    using result_type = std::default_random_engine::result_type;

    std::vector<result_type> to_insert, to_find, to_delete;
    to_insert.reserve(num_elements);
    to_find.reserve(num_elements);
    to_delete.reserve(num_elements);
    for (unsigned long i = 0; i < num_elements; ++i) {
        to_insert.emplace_back(engine());
        to_find.emplace_back(engine());
        to_delete.emplace_back(engine());
    }

    std::cout << "robinHoodHash\n";
    {
        cs375::robinHoodHash<result_type> table{capacity};
        auto inserts = benchmark([&] {
            for (auto num : to_insert) {
                table.insertKey(num);
            }
        });
        std::cout << "\tinsert: " << (inserts / num_elements).count() << '\n';
        auto finds = benchmark([&] {
            for (auto num : to_find) {
                table.searchKey(num);
            }
        });
        std::cout << "\tfind: " << (finds / num_elements).count() << '\n';
        auto deletes = benchmark([&] {
            for (auto num : to_delete) {
                table.deleteKey(num);
            }
        });
        std::cout << "\tdelete: " << (deletes / num_elements).count() << '\n';
    }
    std::cout << "linearProbe\n";
    {
        cs375::linearProbe<result_type> table{capacity};
        auto inserts = benchmark([&] {
            for (auto num : to_insert) {
                table.insertKey(num);
            }
        });
        std::cout << "\tinsert: " << (inserts / num_elements).count() << '\n';
        auto finds = benchmark([&] {
            for (auto num : to_find) {
                table.searchKey(num);
            }
        });
        std::cout << "\tfind: " << (finds / num_elements).count() << '\n';
        auto deletes = benchmark([&] {
            for (auto num : to_delete) {
                table.deleteKey(num);
            }
        });
        std::cout << "\tdelete: " << (deletes / num_elements).count() << '\n';
    }
    std::cout << "unordered_set\n";
    {
        std::unordered_set<result_type> table{capacity};
        table.max_load_factor(0.75f);

        auto inserts = benchmark([&] {
            for (auto num : to_insert) {
                table.insert(num);
            }
        });
        std::cout << "\tinsert: " << (inserts / num_elements).count() << '\n';
        auto finds = benchmark([&] {
            for (auto num : to_find) {
                table.count(num);
            }
        });
        std::cout << "\tfind: " << (finds / num_elements).count() << '\n';
        auto deletes = benchmark([&] {
            for (auto num : to_delete) {
                auto iter = table.find(num);
                if (iter != table.end()) {
                    table.erase(iter);
                }
            }
        });
        std::cout << "\tdelete: " << (deletes / num_elements).count() << '\n';
    }

    return 0;
}
