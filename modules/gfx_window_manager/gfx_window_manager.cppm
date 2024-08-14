module;

import gfx_canvas;

#include <vector>
#include <algorithm>
#include <ranges>

#ifdef SETTING_OPENGL_CUDA_CONTEXT
    #include "opengl_window_manager.hpp"
#endif //SETTING_OPENGL_CUDA_CONTEXT

export module gfx_window_manager;

export enum class gfx_canvas_render_mode {
    single_window_multi_canvas,
    multi_window_single_canvas,
    multi_window_multi_canvas
};

export template<gfx_api_t Gfx_Api>
struct gfx_window_manager {
    using window_manager_type = typename gfx_window_manager_t<Gfx_Api>::type;

    gfx_window_manager(gfx_canvas_render_mode render_mode, std::vector<gfx_canvas<Gfx_Api>> canvas_list) :
        render_mode(render_mode),
        canvas_list(canvas_list)
    {   
        // check if canvas list is not empty
        if (canvas_list.empty()) {
            throw std::domain_error("[gfx_window] : Canvas list cannot be empty!");
        }

        switch (render_mode) {
            case gfx_canvas_render_mode::single_window_multi_canvas: {
                // check if all canvas settings are similar     
                if (!is_same_canvas_settings(canvas_list)) {
                    throw std::domain_error("[gfx_window] : Cannot use render mode single_window_multi_canvas if canvas settings are not the same!");
                }

                // Create single window based of similar canvas settings. 
                gfx_window_manager_internal.create_window(canvas_list[0].settings);

                // Set the only window as active
                gfx_window_manager_internal.set_active_window();

                canvas_list[0].init();
            }
            case gfx_canvas_render_mode::multi_window_single_canvas: {

            }
            case gfx_canvas_render_mode::multi_window_multi_canvas: {

            }
            default: {}
        }

    }

    void start() {

        switch (render_mode) {
            case gfx_canvas_render_mode::single_window_multi_canvas: {

                // Since only a single window is made, use a simple while loop in the main thread   
                const f32 targetFPS = canvas_list[0].settings.frame_rate_hz;
                const f32 targetFrameTime = 1.0 / targetFPS;
                f32 switchTime = canvas_list[0].settings.update_delay_ms;

                f32 previousTime = gfx_window_manager_internal.get_time_now();
                f32 accumulator = 0.0;
                f32 lastSwitchTime = previousTime;

                i32 currentShapeIndex = 0;
            
                while (!gfx_window_manager_internal.is_window_closed()) {
                    f32 currentTime = gfx_window_manager_internal.get_time_now();
                    f32 elapsedTime = currentTime - previousTime;
                    previousTime = currentTime;

                    // Accumulate elapsed time
                    accumulator += elapsedTime;

                    // Switch the shape every `switchTime` seconds
                    if (currentTime - lastSwitchTime >= switchTime) {
                        currentShapeIndex = (currentShapeIndex + 1) % canvas_list.size();
                        lastSwitchTime = currentTime;
                    }

                    // Fixed update logic if enough time has passed
                    while (accumulator >= targetFrameTime) {
                        // Logic updates can go here if needed
                        accumulator -= targetFrameTime;
                    }

                    // Render the scene
                    canvas_list[0].clear();

                    // Call the current render function from the vector
                    canvas_list[currentShapeIndex]();

                    // Swap buffers
                    gfx_window_manager_internal.swap_window_buffers();

                    // Poll for and process events
                    gfx_window_manager_internal.poll_window_events();

                    // Calculate how much time is left until the next frame
                    f32 frameTime = gfx_window_manager_internal.get_time_now() - currentTime;
                    if (frameTime < targetFrameTime) {
                        gfx_window_manager_internal.await_timeout(targetFrameTime - frameTime);
                    }
                }

            }
            case gfx_canvas_render_mode::multi_window_single_canvas: {

            }
            case gfx_canvas_render_mode::multi_window_multi_canvas: {

            }
            default: {}
        }
    }


    

private:
    window_manager_type gfx_window_manager_internal;
    
    gfx_canvas_render_mode render_mode;
    std::vector<gfx_canvas<Gfx_Api>> canvas_list;

    bool is_same_canvas_settings(const std::vector<gfx_canvas<Gfx_Api>>& canvas_list) {
        // Extract the settings of the first canvas
        const auto& reference_settings = canvas_list.front().settings;

        // Use std::ranges::all_of to check if all settings are the same
        return std::ranges::all_of(canvas_list, [&reference_settings](const auto& c) {
            return c.settings == reference_settings;
        });
    }


};




