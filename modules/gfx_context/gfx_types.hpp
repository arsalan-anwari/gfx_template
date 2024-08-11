#pragma once

enum class gfx_api_t { opengl, vulkan, cuda };
enum class gfx_vendor_t { nvidia, amd, intel };
enum class gfx_device_t { integrated, dedicated };
enum class gfx_os_t { windows, linux, darwin };

template<gfx_api_t API>
struct gfx_context_t;
