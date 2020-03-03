#ifndef BITFLAGS__337779E0_704E_483E_AC2D_49623E8191DB
#define BITFLAGS__337779E0_704E_483E_AC2D_49623E8191DB

#include <type_traits>
#include <bitset>


namespace bf {


namespace detail {

template<typename ENUMERATION>
constexpr std::size_t bits_count(const ENUMERATION kLastElement_) { return static_cast<std::size_t>(kLastElement_); }

template<class T> struct sink { typedef void type; };
template<class T> using sink_t = typename sink<T>::type;

template<typename T, typename = void> struct has_kLastElement : std::false_type {};
template<typename T> struct has_kLastElement <T, sink_t<decltype( T::kLastElement_ )>> : std::true_type {};

}  // namespace detail


template<typename ENUMERATION>
class bitflags {

    static_assert(std::is_enum<ENUMERATION>::value, "ENUMERATION must be of 'enum class' type");
    static_assert(detail::has_kLastElement<ENUMERATION>::value, "ENUMERATION must have 'kLastElement_' value");

public:
    bitflags() = default;
    bitflags(const bitflags&) = default;
    bitflags(bitflags&&) = default;

    bitflags& operator =(const bitflags&) = default;
    bitflags& operator =(bitflags&&) = default;

    ~bitflags() = default;

    bitflags(const ENUMERATION flag)                    { set(flag); }

    bitflags& set()                                     { flags_.set(); return *this; }

    bitflags& set(const ENUMERATION flag)               { flags_.set(static_cast<std::size_t>(flag)); return *this; }

    bitflags& reset()                                   { flags_.reset(); return *this; }

    bitflags& reset(const ENUMERATION flag)             { flags_.reset(static_cast<std::size_t>(flag)); return *this; }

    bitflags& flip()                                    { flags_.flip(); return *this; }

    bitflags& flip(const ENUMERATION flag)              { flags_.flip(static_cast<std::size_t>(flag)); return *this; }

    constexpr bool operator [](const ENUMERATION flag) const { return flags_[static_cast<std::size_t>(flag)]; }

    bitflags& operator |=(const ENUMERATION flag)       { return set(flag); }

    bitflags& operator |=(const bitflags& other)        { flags_ |= other.flags_; return *this; }

    bitflags& operator &=(const ENUMERATION flag)       { return *this &= bitflags(flag); }

    bitflags& operator &=(const bitflags& other)        { flags_ &= other.flags_; return *this; }

    bitflags operator |(const ENUMERATION flag) const   { return bitflags(*this) |= flag; }

    bitflags operator |(const bitflags& other) const    { return bitflags(*this) |= other; }

    bitflags operator &(const ENUMERATION flag) const   { return bitflags(*this) &= flag; }

    bitflags operator &(const bitflags& other) const    { return bitflags(*this) &= other; }

    bitflags operator ~() const                         { return bitflags(*this).flip(); }

    bool operator ==(const bitflags& other) const       { return flags_ == other.flags_ ; }

    bool operator !=(const bitflags& other) const       { return !(*this == other); }

    bool none() const                                   { return flags_.none(); }

    bool all() const                                    { return flags_.all(); }

    bool any() const                                    { return flags_.any(); }

    bool none(const ENUMERATION flag) const             { return ! flags_[static_cast<std::size_t>(flag)]; }

    bool all(const ENUMERATION flag) const              { return flags_[static_cast<std::size_t>(flag)]; }

    bool any(const ENUMERATION flag) const              { return flags_[static_cast<std::size_t>(flag)]; }

    bool none(const bitflags& other) const
    {
        for (std::size_t i = 0, sz = flags_.size(); i < sz; i += 1) {
            if (other.flags_[i]) {
                if (flags_[i]) { return false; }
            }
        }
        return true;
    }

    bool all(const bitflags& other) const
    {
        std::size_t other_count = 0;
        for (std::size_t i = 0, sz = flags_.size(); i < sz; i += 1) {
            if (other.flags_[i]) {
                other_count += 1;
                if (! flags_[i]) { return false; }
            }
        }
        return other_count > 0;
    }

    bool any(const bitflags& other) const
    {
        for (std::size_t i = 0, sz = flags_.size(); i < sz; i += 1) {
            if (other.flags_[i] && flags_[i]) { return true; }
        }
        return false;
    }

    std::string to_string() const                       { return flags_.to_string(); }

private:
    std::bitset<detail::bits_count(ENUMERATION::kLastElement_)> flags_;
};  // class bitflags


template<typename ENUMERATION>
bf::bitflags<ENUMERATION> operator |(const ENUMERATION left, const ENUMERATION right)
{
    return bf::bitflags<ENUMERATION>(left) | right;
}


template<typename ENUMERATION>
bf::bitflags<ENUMERATION> operator &(const ENUMERATION left, const ENUMERATION right)
{
    return bf::bitflags<ENUMERATION>(left) & right;
}


template<typename ENUMERATION>
bf::bitflags<ENUMERATION> operator ~(const ENUMERATION flag)
{
    return ~ bf::bitflags<ENUMERATION>(flag);
}


template<typename ENUMERATION>
std::ostream& operator <<(std::ostream& stream, const bf::bitflags<ENUMERATION>& flags)
{
    return stream << flags.to_string();
}


}  // namespace bf


#endif // !BITFLAGS__337779E0_704E_483E_AC2D_49623E8191DB
