module;

#include <functional>
#include <utility>
#include <string_view>

#ifdef SETTING_OPENGL_CUDA_CONTEXT

#include "opengl_canvas.hpp"

#endif //SETTING_OPENGL_CUDA_CONTEXT

export module gfx_canvas;

export template<gfx_api_t Gfx_Api>
struct gfx_canvas{
    using canvas_type = typename gfx_canvas_t<Gfx_Api>::type;

    gfx_canvas(gfx_canvas_settings_t settings, const std::function<void()>&& render_task) :
        settings(settings),
        render_task(std::move(render_task))
    {
        /*gfx_canvas_internal.init();*/
    }

    void init() { gfx_canvas_internal.init(); }

    void operator()() { render_task(); }

    void clear() { gfx_canvas_internal.clear(); }

    gfx_canvas_settings_t settings;

private:
    canvas_type gfx_canvas_internal;
    std::function<void()> render_task;
};



// export template<gfx_api_t Gfx_Api, gfx_compute_t Compute_Api, gfx_vendor_t Vendor, gfx_device_t Device>
// struct gfx_context {
//     using context_type = typename gfx_context_t<Gfx_Api, Compute_Api, Vendor, Device>::type;
    
//     template<typename... Args>
//     gfx_context(Args&&... args) {
//         gfx_context_internal.init(std::forward<Args>(args)...);
//     }
// private:
//     context_type gfx_context_internal;
// };


