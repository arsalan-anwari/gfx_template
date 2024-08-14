#pragma once

// #include <string>
#include <vector>
#include <memory>

#include <GLFW/glfw3.h>

#include "../types/gfx_types.hpp"
#include "../types/exceptions_types.hpp"

namespace {
    struct GLFWwindowDeleter {
        void operator()(GLFWwindow* ptr) {
            glfwDestroyWindow(ptr);
        }
    };
}

struct opengl_window_manager{

    opengl_window_manager() {
        if (!glfwInit()) {
            throw std::runtime_error("[opengl_window_manager::opengl_window_manager] : Could not initialzie GLFW!");
            return;
        }
    }

    ~opengl_window_manager() {
        windows.clear();
        //glfwDestroyWindow(window);
        glfwTerminate();
    }

    void create_window(const gfx_canvas_settings_t& settings) {
        std::unique_ptr<GLFWwindow, GLFWwindowDeleter> window{
            glfwCreateWindow(settings.size.width, settings.size.height, settings.name.data(), nullptr, nullptr), 
            GLFWwindowDeleter{}
        };
        //window = glfwCreateWindow(settings.size.width, settings.size.height, settings.name.data(), nullptr, nullptr);
        if (!window) { throw std::runtime_error("[opengl_window_manager::create_window] : Could not create new window context!"); }
        windows.push_back(std::move(window));
    }

    void set_active_window(const u8 window_num = 0){
        glfwMakeContextCurrent(get_raw_window(window_num));
    }

    bool is_window_closed(const u8 window_num = 0) {
        return glfwWindowShouldClose(get_raw_window(window_num));
    }

    f32 get_time_now() {
        return glfwGetTime();
    }

    void swap_window_buffers(const u8 window_num = 0) {
        glfwSwapBuffers(get_raw_window(window_num));
    }

    void poll_window_events(const u8 window_num = 0) {
        glfwPollEvents();
    }

    void await_timeout(f32 time_ms) {
        glfwWaitEventsTimeout(time_ms);
    }


private:


    std::vector<std::unique_ptr<GLFWwindow, GLFWwindowDeleter>> windows;
    //GLFWwindow* window;

    GLFWwindow* get_raw_window(const u8 window_num = 0) {
        if (window_num >= windows.size() || !windows[window_num]) {
            throw std::out_of_range("[opengl_window_manager::set_active_window] : Invalid window to set active!");
        }
        return windows[window_num].get();
    }

};

template<> struct gfx_window_manager_t<gfx_api_t::opengl>{ 
    using type = opengl_window_manager;
};
