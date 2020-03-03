#ifndef BITFLAGS__337779E0_704E_483E_AC2D_49623E8191DB
#define BITFLAGS__337779E0_704E_483E_AC2D_49623E8191DB

#include <bitset>


namespace bf {


template<typename ENUMERATION>
constexpr std::size_t bits_count(const ENUMERATION kLastElement_)
{
    return static_cast<std::size_t>(kLastElement_);
}


template<typename ENUMERATION>
class BitFlags {
public:
    BitFlags() = default;
    BitFlags(const BitFlags&) = default;
    BitFlags(BitFlags&&) = default;

    BitFlags& operator =(const BitFlags&) = default;
    BitFlags& operator =(BitFlags&&) = default;

    ~BitFlags() = default;

    BitFlags(const ENUMERATION flag)                    { set(flag); }

    BitFlags& set()                                     { flags_.set(); return *this; }

    BitFlags& set(const ENUMERATION flag)               { flags_.set(static_cast<std::size_t>(flag)); return *this; }

    BitFlags& reset()                                   { flags_.reset(); return *this; }

    BitFlags& reset(const ENUMERATION flag)             { flags_.reset(static_cast<std::size_t>(flag)); return *this; }

    BitFlags& flip()                                    { flags_.flip(); return *this; }

    BitFlags& flip(const ENUMERATION flag)              { flags_.flip(static_cast<std::size_t>(flag)); return *this; }

    BitFlags& operator |=(const ENUMERATION flag)       { return set(flag); }

    BitFlags& operator |=(const BitFlags& other)        { flags_ |= other.flags_; return *this; }

    BitFlags& operator &=(const ENUMERATION flag)       { return *this &= BitFlags{ flag }; }

    BitFlags& operator &=(const BitFlags& other)        { flags_ &= other.flags_; return *this; }

    BitFlags operator |(const ENUMERATION flag) const   { return BitFlags{ *this } |= flag; }

    BitFlags operator |(const BitFlags& other) const    { return BitFlags{ *this } |= other; }

    BitFlags operator &(const ENUMERATION flag) const   { return BitFlags{ *this } &= flag; }

    BitFlags operator &(const BitFlags& other) const    { return BitFlags{ *this } &= other; }

    BitFlags operator ~() const                         { return BitFlags{ *this }.flip(); }

    bool operator ==(const BitFlags& other) const       { return flags_ == other.flags_ ; }

    bool operator !=(const BitFlags& other) const       { return !(*this == other); }

    bool none() const                                   { return flags_.none(); }

    bool all() const                                    { return flags_.all(); }

    bool any() const                                    { return flags_.any(); }

    bool none(const ENUMERATION flag) const             { return ! flags_[static_cast<std::size_t>(flag)]; }

    bool all(const ENUMERATION flag) const              { return flags_[static_cast<std::size_t>(flag)]; }

    bool any(const ENUMERATION flag) const              { return flags_[static_cast<std::size_t>(flag)]; }

    bool none(const BitFlags& other) const
    {
        for (std::size_t i = 0, sz = flags_.size(); i < sz; i += 1) {
            if (other.flags_[i]) {
                if (flags_[i]) { return false; }
            }
        }
        return true;
    }

    bool all(const BitFlags& other) const
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

    bool any(const BitFlags& other) const
    {
        for (std::size_t i = 0, sz = flags_.size(); i < sz; i += 1) {
            if (other.flags_[i] && flags_[i]) { return true; }
        }
        return false;
    }

    std::string to_string() const                       { return flags_.to_string(); }

private:
    std::bitset<bits_count(ENUMERATION::kLastElement_)> flags_;
};  // class BitFlags


template<typename ENUMERATION>
bf::BitFlags<ENUMERATION> operator |(const ENUMERATION left, const ENUMERATION right)
{
    return bf::BitFlags<ENUMERATION>{left} | right;
}


template<typename ENUMERATION>
bf::BitFlags<ENUMERATION> operator &(const ENUMERATION left, const ENUMERATION right)
{
    return bf::BitFlags<ENUMERATION>{left} & right;
}


template<typename ENUMERATION>
bf::BitFlags<ENUMERATION> operator ~(const ENUMERATION flag)
{
    return ~ bf::BitFlags<ENUMERATION>{flag};
}


template<typename ENUMERATION>
std::ostream& operator <<(std::ostream& stream, const bf::BitFlags<ENUMERATION>& flags)
{
    return stream << flags.to_string();
}


}  // namespace bf


#endif // !BITFLAGS__337779E0_704E_483E_AC2D_49623E8191DB
