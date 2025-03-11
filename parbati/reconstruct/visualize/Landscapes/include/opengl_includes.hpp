// opengl_includes.hpp
#pragma once

// First include GLAD with proper inclusion guards
#ifndef GLAD_INCLUDED
#define GLAD_INCLUDED

//Tell glad.h not to use extern "C" by defining
#define GLAD_NO_EXTERN_C
#ifdef __cplusplus
extern "C" {
#endif
#include "../extern/glad/glad.h" //glad_wrapper.hpp"
#ifdef __cplusplus
}
#endif
#endif

// Then include GLFW
#include "GLFW/glfw3.h"
