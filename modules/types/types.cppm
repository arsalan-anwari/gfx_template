module;

#include "exceptions_types.hpp"
#include "gfx_types.hpp"

export module types;

export using gfx_api = ::gfx_api_t;
export using gfx_compute = ::gfx_compute_t;
export using gfx_canvas_dim = ::gfx_canvas_dim_t;
export using gfx_canvas_settings = ::gfx_canvas_settings_t;

export using i8 = ::i8;
export using i16 = ::i16;
export using i32 = ::i32;
export using i64 = ::i64;
export using isize = ::isize;
// using i128 = int64_t;

export using u8 = ::u8;
export using u16 = ::u16;
export using u32 = ::u32;
export using u64 = ::u64;
export using usize = ::usize;

export using f16 = ::f16;
export using f32 = ::f32;
