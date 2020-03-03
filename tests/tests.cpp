#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <bitflags.h>


namespace Test {


enum class Flags {
    kFlagA,
    kFlagB,
    kFlagC,

    kLastElement_  // there should be no flags after this element
};  // enum class Flags


enum class Flags2 {
    kFlagX,
    kFlagY,
    kFlagZ,

    kLastElement_  // there should be no flags after this element
};  // enum class Flags2


using bf::operator|;
using bf::operator&;
using bf::operator~;


}  // namespace Test


using bf::bitflags;

template<class T> struct sink { typedef void type; };
template<class T> using sink_t = typename sink<T>::type;

template<typename T, typename = void> struct accept_Flags : std::false_type {};
template<typename T> struct accept_Flags <T, sink_t<decltype( T() | Test::Flags::kFlagA )>> : std::true_type {};

template<typename T, typename = void> struct accept_int : std::false_type {};
template<typename T> struct accept_int <T, sink_t<decltype(T() | 10)>> : std::true_type {};


TEST_CASE("testing bitflags")
{
    auto f = bitflags<Test::Flags>{};

    REQUIRE("000" == f.to_string());

    SUBCASE("testing constr(ENUMERATION)") {
        CHECK("001" == bitflags<Test::Flags>(Test::Flags::kFlagA).to_string());
    }

    SUBCASE("testing set()") {
        CHECK("111" == f.set().to_string());
    }

    SUBCASE("testing set(ENUMERATION)") {
        CHECK("001" == f.set(Test::Flags::kFlagA).to_string());
        CHECK("101" == f.set(Test::Flags::kFlagC).to_string());
    }

    SUBCASE("testing reset()") {
        CHECK("001" == f.set(Test::Flags::kFlagA).to_string());
        CHECK("000" == f.reset().to_string());
        CHECK("111" == f.set().to_string());
        CHECK("000" == f.reset().to_string());
    }

    SUBCASE("testing reset(ENUMERATION)") {
        CHECK("001" == f.set(Test::Flags::kFlagA).to_string());
        CHECK("011" == f.set(Test::Flags::kFlagB).to_string());
        CHECK("010" == f.reset(Test::Flags::kFlagA).to_string());
        CHECK("000" == f.reset(Test::Flags::kFlagB).to_string());
        CHECK("111" == f.set().to_string());
        CHECK("011" == f.reset(Test::Flags::kFlagC).to_string());
    }

    SUBCASE("testing flip()") {
        CHECK("001" == f.set(Test::Flags::kFlagA).to_string());
        CHECK("110" == f.flip().to_string());
        CHECK("111" == f.set().to_string());
        CHECK("000" == f.flip().to_string());
    }

    SUBCASE("testing flip(ENUMERATION)") {
        CHECK("001" == f.set(Test::Flags::kFlagA).to_string());
        CHECK("011" == f.set(Test::Flags::kFlagB).to_string());
        CHECK("010" == f.flip(Test::Flags::kFlagA).to_string());
        CHECK("000" == f.flip(Test::Flags::kFlagB).to_string());
        CHECK("111" == f.set().to_string());
        CHECK("011" == f.flip(Test::Flags::kFlagC).to_string());
    }

    SUBCASE("testing f[ENUMERATION]") {
        CHECK_FALSE(f[Test::Flags::kFlagA]);
        CHECK(f.set(Test::Flags::kFlagA)[Test::Flags::kFlagA]);
        CHECK_FALSE(f[Test::Flags::kFlagB]);
    }

    SUBCASE("testing f |= ENUMERATION") {
        CHECK("100" == (f |= Test::Flags::kFlagC).to_string());
        CHECK("101" == (f |= Test::Flags::kFlagA).to_string());
    }

    SUBCASE("testing f |= bitflags") {
        CHECK("010" == (f |= bitflags<Test::Flags>(Test::Flags::kFlagB)).to_string());
    }

    SUBCASE("testing f | ENUMERATION") {
        CHECK("100" == (f | Test::Flags::kFlagC).to_string());
        CHECK("000" == f.to_string());
    }

    SUBCASE("testing ENUMERATION | ENUMERATION") {
        CHECK("101" == (Test::Flags::kFlagA | Test::Flags::kFlagC).to_string());
    }

    SUBCASE("testing f &= ENUMERATION") {
        CHECK("000" == (f &= Test::Flags::kFlagC).to_string());
        CHECK("001" == (f.set() &= Test::Flags::kFlagA).to_string());
    }

    SUBCASE("testing f &= bitflags") {
        CHECK("010" == (f.set() &= bitflags<Test::Flags>(Test::Flags::kFlagB)).to_string());
    }

    SUBCASE("testing f & ENUMERATION") {
        CHECK("100" == (f.set() & Test::Flags::kFlagC).to_string());
        CHECK("111" == f.to_string());
    }

    SUBCASE("testing ENUMERATION & ENUMERATION") {
        CHECK("000" == (Test::Flags::kFlagA & Test::Flags::kFlagC).to_string());
        CHECK("100" == ((Test::Flags::kFlagA | Test::Flags::kFlagC) & Test::Flags::kFlagC).to_string());
        CHECK("000" == ((Test::Flags::kFlagA | Test::Flags::kFlagB) & Test::Flags::kFlagC).to_string());
    }

    SUBCASE("testing ~ ENUMERATION") {
        CHECK("110" == (~ Test::Flags::kFlagA).to_string());
        CHECK("010" == (~ (Test::Flags::kFlagA | Test::Flags::kFlagC)).to_string());
        CHECK("111" == (~ Test::Flags::kFlagA | ~ Test::Flags::kFlagB).to_string());
    }

    SUBCASE("testing ~ f") {
        CHECK("111" == (~ f).to_string());
        CHECK("000" == f.to_string());
        CHECK("110" == (~ f.set(Test::Flags::kFlagA)).to_string());
        CHECK("001" == f.to_string());
        CHECK("100" == (~ f.set(Test::Flags::kFlagB)).to_string());
        CHECK("011" == f.to_string());
    }

    SUBCASE("testing complex flag set/reset") {
        CHECK("111" == (f |= Test::Flags::kFlagA | Test::Flags::kFlagB | Test::Flags::kFlagC).to_string());
        CHECK("010" == (f &= Test::Flags::kFlagB).to_string());
        CHECK("111" == (f |= ~ Test::Flags::kFlagB).to_string());
    }

    SUBCASE("testing compile-time type checks") {
        CHECK(accept_Flags<bitflags<Test::Flags>>::value);
        CHECK_FALSE(accept_Flags<bitflags<Test::Flags2>>::value);
        CHECK_FALSE(accept_int<bitflags<Test::Flags>>::value);
    }

    SUBCASE("testing eq") {
        auto f2 = bitflags<Test::Flags>{ Test::Flags::kFlagA };
        CHECK(f == bitflags<Test::Flags>{});
        CHECK_FALSE(f != bitflags<Test::Flags>{});
        CHECK(f2 == f.set(Test::Flags::kFlagA));
        CHECK_FALSE(f2 == f.set(Test::Flags::kFlagB));
    }

    SUBCASE("testing bits") {
        CHECK(f.none());
        CHECK_FALSE(f.all());
        CHECK_FALSE(f.any());

        CHECK(f.set(Test::Flags::kFlagA).any());
        CHECK_FALSE(f.none());
        CHECK_FALSE(f.all());
        CHECK(f.any());
        CHECK_FALSE(f.none(Test::Flags::kFlagA));
        CHECK(f.none(Test::Flags::kFlagB));
        CHECK(f.all(Test::Flags::kFlagA));
        CHECK(f.any(Test::Flags::kFlagA));
        CHECK(f.none(Test::Flags::kFlagB));
        CHECK_FALSE(f.all(Test::Flags::kFlagB));
        CHECK_FALSE(f.all(Test::Flags::kFlagB));

        CHECK(f.set(Test::Flags::kFlagB).all(Test::Flags::kFlagB));
        CHECK(f.all(Test::Flags::kFlagA));
        CHECK(f.any(Test::Flags::kFlagB));
        CHECK(f.any(Test::Flags::kFlagA));
        CHECK_FALSE(f.none(Test::Flags::kFlagB));
        CHECK_FALSE(f.none(Test::Flags::kFlagA));
        CHECK(f.none(Test::Flags::kFlagC));
        CHECK(f.all(Test::Flags::kFlagA | Test::Flags::kFlagB));
        CHECK(f.any(Test::Flags::kFlagA | Test::Flags::kFlagB));
        CHECK_FALSE(f.none(Test::Flags::kFlagA | Test::Flags::kFlagB));
        CHECK_FALSE(f.none());
        CHECK_FALSE(f.all());
        CHECK(f.any());

        CHECK(f.set().all());
        CHECK_FALSE(f.none());
        CHECK(f.any());

        CHECK(f.reset().none());
        CHECK_FALSE(f.all());
        CHECK_FALSE(f.any());
    }
}
