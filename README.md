# bitflags
C++ class for storing bit flags. Flag names are taken from 'enum class'. Type-safe bit operations (prevents using flags from different enums).

```c++
#include <iostream>

#include "bitflags.h"

using bf::bitflags;


namespace my {


enum class Flags {
    kFlagA,
    kFlagB,
    kFlagC,

    kLastElement_  // there should be no flags after this element
};  // enum class Flags


enum class OtherFlags {
    kFlagX,
    kFlagY,
    kFlagZ,

    kLastElement_  // there should be no flags after this element
};  // enum class OtherFlags


using bf::operator|;
using bf::operator&;
using bf::operator~;


}  // namespace my


int main()
{
    auto f = bitflags<my::Flags>{};

    f.set(my::Flags::kFlagA);
    std::cout << "Flags: " << f.to_string() << std::endl;

    if (f.any(my::Flags::kFlagA | my::Flags::kFlagB)) {
        std::cout << "Flags: any..." << f.to_string() << std::endl;
    }

    f |= my::Flags::kFlagB | my::Flags::kFlagC;
    if (f.all()) {
        std::cout << "Flags: all..." << f.to_string() << std::endl;
    }

    f.reset();
    if (f.none()) {
        std::cout << "Flags: none..." << f.to_string() << std::endl;
    }

    // Compile error:
    // f |= my::Flags::kFlagA | my::OtherFlags::kFlagX

    return 0;
}
```
