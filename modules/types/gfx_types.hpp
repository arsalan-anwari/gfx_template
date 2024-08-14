#pragma once

#include <string_view>
#include "fundamental_types.hpp"

enum class gfx_api_t { opengl, vulkan, dx11 };
enum class gfx_compute_t { cuda, opencl, hip, none };

template<gfx_api_t Gfx_Api, gfx_compute_t Compute_Api = gfx_compute_t::none>
struct gfx_canvas_t;

template<gfx_api_t Gfx_Api>
struct gfx_window_manager_t;

struct gfx_canvas_dim_t { 
    u16 width = 800, height = 600; 

    bool operator==(const gfx_canvas_dim_t& other) const {
        return width == other.width && height == other.height;
    }
};

struct gfx_canvas_settings_t {
    gfx_canvas_dim_t size;
    std::string_view name;
    f32 frame_rate_hz;
    f32 update_delay_ms;

    bool operator==(const gfx_canvas_settings_t& other) const {
        return size == other.size && frame_rate_hz == other.frame_rate_hz;
    }

};

