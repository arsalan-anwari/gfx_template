if (DEFINED VCPKG_MANIFEST_FEATURES)

  # For now only one setting is used, but in future multiple can be selected by the user.
  if (VCPKG_MANIFEST_FEATURES STREQUAL "opengl-cuda-context")
      set(SETTING_OPENGL_CUDA_CONTEXT ON CACHE BOOL "OpenGL window context using GLEW and GLFW" FORCE)
      add_compile_definitions(SETTING_OPENGL_CUDA_CONTEXT)
  endif()

else()

  # If no feature flags are used used the default of opengl_window_context
  message(ERROR "VCPKG_MANIFEST_FEATURES is not set in CMakePresets.json!")

endif()