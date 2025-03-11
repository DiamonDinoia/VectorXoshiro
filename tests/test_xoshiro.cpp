#include <xoshiro/xoshiro.hpp>

#include <xoshiro256plusplus.c>
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

static constexpr auto tests = 1 << 15;

TEST_CASE("xoshiro256++", "[xoshiro256++]") {
    const auto seed = std::random_device()();
    INFO("SEED: " << seed);
    xoshiro::Xoshiro rng(seed);
    s[0] = rng.getState()[0];
    s[1] = rng.getState()[1];
    s[2] = rng.getState()[2];
    s[3] = rng.getState()[3];
    for (int i = 0; i < tests; ++i) { REQUIRE(rng() == next()); }
    rng.jump();
    jump();
    REQUIRE(rng.getState()[0] == s[0]);
    REQUIRE(rng.getState()[1] == s[1]);
    REQUIRE(rng.getState()[2] == s[2]);
    REQUIRE(rng.getState()[3] == s[3]);
    for (int i = 0; i < tests; ++i) {
        const auto result = rng.uniform();
        REQUIRE(result >= 0);
        REQUIRE(result < 1);
    }
}

