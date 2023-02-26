// Copyright (C) 2022 Rowan Cruse Howse
// 
// This file is part of Alder.
// 
// Alder is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Alder is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Alder.  If not, see <http://www.gnu.org/licenses/>.

#ifndef GLUTIL_H
#define GLUTIL_H
#include <string>
#include "GL/glew.h"
inline std::string getGLErrorStr(GLenum err)
{
	switch (err)
	{
		case GL_NO_ERROR:
			return "GL_NO_ERROR";
		case GL_INVALID_ENUM:
			return "GL_INVALID_ENUM";
		case GL_INVALID_VALUE:
			return "GL_INVALID_VALUE";
		case GL_INVALID_OPERATION:
			return "GL_INVALID_OPERATION";
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			return "GL_INVALID_FRAMEBUFFER_OPERATION";
		case GL_OUT_OF_MEMORY:
			return "GL_OUT_OF_MEMORY";
		case GL_STACK_UNDERFLOW:
			return "GL_STACK_UNDERFLOW";
		case GL_STACK_OVERFLOW:
			return "GL_STACK_OVERFLOW";
		default:
			return "UNKNOWN_ERROR";
	}
}

void GLAPIENTRY
inline glMessageCallback( [[maybe_unused]]GLenum source,
                 [[maybe_unused]]GLenum type,
                 [[maybe_unused]]GLuint id,
                 [[maybe_unused]]GLenum severity,
                 [[maybe_unused]]GLsizei length,
                 [[maybe_unused]]const GLchar* message,
                 [[maybe_unused]]const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

#endif // GLUTIL_H
