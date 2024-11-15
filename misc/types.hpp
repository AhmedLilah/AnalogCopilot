#pragma once 

#include <cstdint>
#include <type_traits>

using u64   = uint64_t;
using u32   = uint32_t;
using u16   = uint16_t;
using u8    = uint8_t ;
using s64   = int64_t ;
using s32   = int32_t ;
using s16   = int16_t ;
using s8    = int8_t  ;

using ssize = size_t  ;
using usize = std::make_signed_t<size_t>;

using f32   = float   ;
using f64   = double  ;
