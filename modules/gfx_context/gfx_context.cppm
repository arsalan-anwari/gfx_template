module;

#ifdef SETTING_OPENGL_CUDA_CONTEXT

#include "opengl_window_context.hpp"

#include <nvapi/nvapi.h>

#endif //SETTING_OPENGL_CUDA_CONTEXT

export module gfx_context;

export using gfx_api = ::gfx_api_t;

export template<gfx_api Gfx_Api>
struct gfx_context {
    using context_type = typename gfx_context_t<Gfx_Api>::type;
    
    template<typename... Args>
    gfx_context(Args&&... args) {
        gfx_context_internal.init(std::forward<Args>(args)...);
    }
private:
    context_type gfx_context_internal;
};


