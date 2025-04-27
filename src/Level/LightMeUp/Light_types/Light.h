#ifndef LIGHT_H
#define LIGHT_H

#include<stdint.h>
#include <fmt/core.h>

class Light
{
    public:
    uint8_t r = 1, g = 2, b = 3;

    void init( uint8_t Rd, uint8_t Gn, uint8_t Bu )
    { r = Rd; g = Gn; b = Bu;  }
    Light( uint8_t Rd, uint8_t Gn, uint8_t Bu ){ init( Rd, Gn, Bu ); }
    Light(){}

    bool operator == ( const Light& Lt ) const
    {
        if( r != Lt.r || g != Lt.g || b != Lt.b ) return false;
        return true;
    }
    bool operator != ( const Light& Lt ) const
    {

        return !( *this == Lt );
    }
};

inline auto format_as(const Light &l) {
    return fmt::format("Light({},{},{})", l.r, l.g, l.b);
}

#include <Reflection/GenReflection.h>

// Register Light type
RENGINE_REFLECT_CLASS_BEGIN(Light)
RENGINE_REFLECT_CLASS_MEMBER(Light, r, "r")
RENGINE_REFLECT_CLASS_MEMBER(Light, g, "g")
RENGINE_REFLECT_CLASS_MEMBER(Light, b, "b")
RENGINE_REFLECT_CLASS_END(Light)

#endif // LIGHT_H
