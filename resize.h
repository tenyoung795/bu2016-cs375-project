#ifndef RESIZE_H
#define RESIZE_H

#include <cstddef>
#include <cstdint>

#include <algorithm>
#include <iterator>

namespace cs375 {

/**
 * Determines whether a table should resize, given a maximum load factor,
 * a number of buckets, and a desired number of elements.
 *
 * @param max_load_factor the maximum load factor (number of elements per bucket).
 * @param num_buckets the number of buckets.
 * @param num_elements the (desired) number of elements.
 * @return Whether the table should resize.
 */
constexpr bool should_resize(float max_load_factor, std::size_t num_buckets, std::size_t num_elements) {
   return static_cast<std::size_t>(max_load_factor * static_cast<long double>(num_buckets)) < num_elements;
}

static_assert(!should_resize(0.75f, 4, 3), "No need to resize a table with just the right number of elements");
static_assert(should_resize(0.75f, 4, 4), "Must resize a table with one too many elements");

/**
 * Determine the next table size in buckets, which is at least a given size.
 *
 * @param current_size the current size in buckets.
 * @return The next size in buckets.
 */
static std::size_t next_table_size(std::size_t current_size) {
    // List of primes ripped from libstdc++'s implementation.
    // Includes SIZE_MAX to avoid that edge case.
    // Assumes size_t is either 32- or 64-bit.
    constexpr std::size_t primes[] = {
        2u, 3u, 5u, 7u, 11u, 13u, 17u, 19u, 23u, 29u, 31u,
        37u, 41u, 43u, 47u, 53u, 59u, 61u, 67u, 71u, 73u, 79u,
        83u, 89u, 97u, 103u, 109u, 113u, 127u, 137u, 139u, 149u,
        157u, 167u, 179u, 193u, 199u, 211u, 227u, 241u, 257u,
        277u, 293u, 313u, 337u, 359u, 383u, 409u, 439u, 467u,
        503u, 541u, 577u, 619u, 661u, 709u, 761u, 823u, 887u,
        953u, 1031u, 1109u, 1193u, 1289u, 1381u, 1493u, 1613u,
        1741u, 1879u, 2029u, 2179u, 2357u, 2549u, 2753u, 2971u,
        3209u, 3469u, 3739u, 4027u, 4349u, 4703u, 5087u, 5503u,
        5953u, 6427u, 6949u, 7517u, 8123u, 8783u, 9497u, 10273u,
        11113u, 12011u, 12983u, 14033u, 15173u, 16411u, 17749u,
        19183u, 20753u, 22447u, 24281u, 26267u, 28411u, 30727u,
        33223u, 35933u, 38873u, 42043u, 45481u, 49201u, 53201u,
        57557u, 62233u, 67307u, 72817u, 78779u, 85229u, 92203u,
        99733u, 107897u, 116731u, 126271u, 136607u, 147793u,
        159871u, 172933u, 187091u, 202409u, 218971u, 236897u,
        256279u, 277261u, 299951u, 324503u, 351061u, 379787u,
        410857u, 444487u, 480881u, 520241u, 562841u, 608903u,
        658753u, 712697u, 771049u, 834181u, 902483u, 976369u,
        1056323u, 1142821u, 1236397u, 1337629u, 1447153u, 1565659u,
        1693859u, 1832561u, 1982627u, 2144977u, 2320627u, 2510653u,
        2716249u, 2938679u, 3179303u, 3439651u, 3721303u, 4026031u,
        4355707u, 4712381u, 5098259u, 5515729u, 5967347u, 6456007u,
        6984629u, 7556579u, 8175383u, 8844859u, 9569143u, 10352717u,
        11200489u, 12117689u, 13109983u, 14183539u, 15345007u,
        16601593u, 17961079u, 19431899u, 21023161u, 22744717u,
        24607243u, 26622317u, 28802401u, 31160981u, 33712729u,
        36473443u, 39460231u, 42691603u, 46187573u, 49969847u,
        54061849u, 58488943u, 63278561u, 68460391u, 74066549u,
        80131819u, 86693767u, 93793069u, 101473717u, 109783337u,
        118773397u, 128499677u, 139022417u, 150406843u, 162723577u,
        176048909u, 190465427u, 206062531u, 222936881u, 241193053u,
        260944219u, 282312799u, 305431229u, 330442829u, 357502601u,
        386778277u, 418451333u, 452718089u, 489790921u, 529899637u,
        573292817u, 620239453u, 671030513u, 725980837u, 785430967u,
        849749479u, 919334987u, 994618837u, 1076067617u, 1164186217u,
        1259520799u, 1362662261u, 1474249943u, 1594975441u, 1725587117u,
        1866894511u, 2019773507u, 2185171673u, 2364114217u, 2557710269u,
        2767159799u, 2993761039u, 3238918481u, 3504151727u, 3791104843u,
        4101556399u, 4294967291u,
        #if SIZE_MAX > UINT32_MAX
        6442450933u, 8589934583u, 12884901857u, 17179869143u,
        25769803693u, 34359738337u, 51539607367u, 68719476731u,
        103079215087u, 137438953447u, 206158430123u, 274877906899u,
        412316860387u, 549755813881u, 824633720731u, 1099511627689u,
        1649267441579u, 2199023255531u, 3298534883309u, 4398046511093u,
        6597069766607u, 8796093022151u, 13194139533241u, 17592186044399u,
        26388279066581u, 35184372088777u, 52776558133177u, 70368744177643u,
        105553116266399u, 140737488355213u, 211106232532861u, 281474976710597u,
        562949953421231u, 1125899906842597u, 2251799813685119u,
        4503599627370449u, 9007199254740881u, 18014398509481951u,
        36028797018963913u, 72057594037927931u, 144115188075855859u,
        288230376151711717u, 576460752303423433u,
        1152921504606846883u, 2305843009213693951u,
        4611686018427387847u, 9223372036854775783u,
        18446744073709551557u,
        #endif
        SIZE_MAX
    };
    return *std::lower_bound(std::begin(primes), std::end(primes), 2u * current_size);
}

}

#endif // RESIZE_H
