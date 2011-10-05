#include "gl.h"
#include <windows.h>

static int m_initialized = 0;

#ifdef EGL_GL_VERSION_1_2_DEFINED
  EGL_glblendcolor_t glBlendColor = 0;
  EGL_glblendequation_t glBlendEquation = 0;
  EGL_glcopytexsubimage3d_t glCopyTexSubImage3D = 0;
  EGL_gldrawrangeelements_t glDrawRangeElements = 0;
  EGL_glteximage3d_t glTexImage3D = 0;
  EGL_gltexsubimage3d_t glTexSubImage3D = 0;
#endif

#ifdef EGL_GL_VERSION_1_3_DEFINED
  EGL_glActiveTexture_t glActiveTexture = 0;
  EGL_glClientActiveTexture_t glClientActiveTexture = 0;
  EGL_glCompressedTexImage1D_t glCompressedTexImage1D = 0;
  EGL_glCompressedTexImage2D_t glCompressedTexImage2D = 0;
  EGL_glCompressedTexImage3D_t glCompressedTexImage3D = 0;
  EGL_glCompressedTexSubImage1D_t glCompressedTexSubImage1D = 0;
  EGL_glCompressedTexSubImage2D_t glCompressedTexSubImage2D = 0;
  EGL_glCompressedTexSubImage3D_t glCompressedTexSubImage3D = 0;
  EGL_glGetCompressedTexImage_t glGetCompressedTexImage = 0;
  EGL_glLoadTransposeMatrixd_t glLoadTransposeMatrixd = 0;
  EGL_glLoadTransposeMatrixf_t glLoadTransposeMatrixf = 0;
  EGL_glMultTransposeMatrixd_t glMultTransposeMatrixd = 0;
  EGL_glMultTransposeMatrixf_t glMultTransposeMatrixf = 0;
  EGL_glMultiTexCoord1d_t glMultiTexCoord1d = 0;
  EGL_glMultiTexCoord1dv_t glMultiTexCoord1dv = 0;
  EGL_glMultiTexCoord1f_t glMultiTexCoord1f = 0;
  EGL_glMultiTexCoord1fv_t glMultiTexCoord1fv = 0;
  EGL_glMultiTexCoord1i_t glMultiTexCoord1i = 0;
  EGL_glMultiTexCoord1iv_t glMultiTexCoord1iv = 0;
  EGL_glMultiTexCoord1s_t glMultiTexCoord1s = 0;
  EGL_glMultiTexCoord1sv_t glMultiTexCoord1sv = 0;
  EGL_glMultiTexCoord2d_t glMultiTexCoord2d = 0;
  EGL_glMultiTexCoord2dv_t glMultiTexCoord2dv = 0;
  EGL_glMultiTexCoord2f_t glMultiTexCoord2f = 0;
  EGL_glMultiTexCoord2fv_t glMultiTexCoord2fv = 0;
  EGL_glMultiTexCoord2i_t glMultiTexCoord2i = 0;
  EGL_glMultiTexCoord2iv_t glMultiTexCoord2iv = 0;
  EGL_glMultiTexCoord2s_t glMultiTexCoord2s = 0;
  EGL_glMultiTexCoord2sv_t glMultiTexCoord2sv = 0;
  EGL_glMultiTexCoord3d_t glMultiTexCoord3d = 0;
  EGL_glMultiTexCoord3dv_t glMultiTexCoord3dv = 0;
  EGL_glMultiTexCoord3f_t glMultiTexCoord3f = 0;
  EGL_glMultiTexCoord3fv_t glMultiTexCoord3fv = 0;
  EGL_glMultiTexCoord3i_t glMultiTexCoord3i = 0;
  EGL_glMultiTexCoord3iv_t glMultiTexCoord3iv = 0;
  EGL_glMultiTexCoord3s_t glMultiTexCoord3s = 0;
  EGL_glMultiTexCoord3sv_t glMultiTexCoord3sv = 0;
  EGL_glMultiTexCoord4d_t glMultiTexCoord4d = 0;
  EGL_glMultiTexCoord4dv_t glMultiTexCoord4dv = 0;
  EGL_glMultiTexCoord4f_t glMultiTexCoord4f = 0;
  EGL_glMultiTexCoord4fv_t glMultiTexCoord4fv = 0;
  EGL_glMultiTexCoord4i_t glMultiTexCoord4i = 0;
  EGL_glMultiTexCoord4iv_t glMultiTexCoord4iv = 0;
  EGL_glMultiTexCoord4s_t glMultiTexCoord4s = 0;
  EGL_glMultiTexCoord4sv_t glMultiTexCoord4sv = 0;
  EGL_glSampleCoverage_t glSampleCoverage = 0;
#endif

#ifdef EGL_GL_VERSION_1_4_DEFINED
  EGL_glBlendFuncSeparate_t glBlendFuncSeparate = 0;
  EGL_glFogCoordd_t glFogCoordd = 0;
  EGL_glFogCoorddv_t glFogCoorddv = 0;
  EGL_glFogCoordf_t glFogCoordf = 0;
  EGL_glFogCoordfv_t glFogCoordfv = 0;
  EGL_glFogCoordPointer_t glFogCoordPointer = 0;
  EGL_glMultiDrawArrays_t glMultiDrawArrays = 0;
  EGL_glMultiDrawElements_t glMultiDrawElements = 0;
  EGL_glPointParameterf_t glPointParameterf = 0;
  EGL_glPointParameterfv_t glPointParameterfv = 0;
  EGL_glPointParameteri_t glPointParameteri = 0;
  EGL_glPointParameteriv_t glPointParameteriv = 0;
  EGL_glSecondaryColor3b_t glSecondaryColor3b = 0;
  EGL_glSecondaryColor3bv_t glSecondaryColor3bv = 0;
  EGL_glSecondaryColor3d_t glSecondaryColor3d = 0;
  EGL_glSecondaryColor3dv_t glSecondaryColor3dv = 0;
  EGL_glSecondaryColor3f_t glSecondaryColor3f = 0;
  EGL_glSecondaryColor3fv_t glSecondaryColor3fv = 0;
  EGL_glSecondaryColor3i_t glSecondaryColor3i = 0;
  EGL_glSecondaryColor3iv_t glSecondaryColor3iv = 0;
  EGL_glSecondaryColor3s_t glSecondaryColor3s = 0;
  EGL_glSecondaryColor3sv_t glSecondaryColor3sv = 0;
  EGL_glSecondaryColor3ub_t glSecondaryColor3ub = 0;
  EGL_glSecondaryColor3ubv_t glSecondaryColor3ubv = 0;
  EGL_glSecondaryColor3ui_t glSecondaryColor3ui = 0;
  EGL_glSecondaryColor3uiv_t glSecondaryColor3uiv = 0;
  EGL_glSecondaryColor3us_t glSecondaryColor3us = 0;
  EGL_glSecondaryColor3usv_t glSecondaryColor3usv = 0;
  EGL_glSecondaryColorPointer_t glSecondaryColorPointer = 0;
  EGL_glWindowPos2d_t glWindowPos2d = 0;
  EGL_glWindowPos2dv_t glWindowPos2dv = 0;
  EGL_glWindowPos2f_t glWindowPos2f = 0;
  EGL_glWindowPos2fv_t glWindowPos2fv = 0;
  EGL_glWindowPos2i_t glWindowPos2i = 0;
  EGL_glWindowPos2iv_t glWindowPos2iv = 0;
  EGL_glWindowPos2s_t glWindowPos2s = 0;
  EGL_glWindowPos2sv_t glWindowPos2sv = 0;
  EGL_glWindowPos3d_t glWindowPos3d = 0;
  EGL_glWindowPos3dv_t glWindowPos3dv = 0;
  EGL_glWindowPos3f_t glWindowPos3f = 0;
  EGL_glWindowPos3fv_t glWindowPos3fv = 0;
  EGL_glWindowPos3i_t glWindowPos3i = 0;
  EGL_glWindowPos3iv_t glWindowPos3iv = 0;
  EGL_glWindowPos3s_t glWindowPos3s = 0;
  EGL_glWindowPos3sv_t glWindowPos3sv = 0;
#endif

#ifdef EGL_GL_VERSION_1_5_DEFINED
  EGL_glBeginQuery_t glBeginQuery = 0;
  EGL_glBindBuffer_t glBindBuffer = 0;
  EGL_glBufferData_t glBufferData = 0;
  EGL_glBufferSubData_t glBufferSubData = 0;
  EGL_glDeleteBuffers_t glDeleteBuffers = 0;
  EGL_glDeleteQueries_t glDeleteQueries = 0;
  EGL_glEndQuery_t glEndQuery = 0;
  EGL_glGenBuffers_t glGenBuffers = 0;
  EGL_glGenQueries_t glGenQueries = 0;
  EGL_glGetBufferParameteriv_t glGetBufferParameteriv = 0;
  EGL_glGetBufferPointerv_t glGetBufferPointerv = 0;
  EGL_glGetBufferSubData_t glGetBufferSubData = 0;
  EGL_glGetQueryObjectiv_t glGetQueryObjectiv = 0;
  EGL_glGetQueryObjectuiv_t glGetQueryObjectuiv = 0;
  EGL_glGetQueryiv_t glGetQueryiv = 0;
  EGL_glIsBuffer_t glIsBuffer = 0;
  EGL_glIsQuery_t glIsQuery = 0;
  EGL_glMapBuffer_t glMapBuffer = 0;
  EGL_glUnmapBuffer_t glUnmapBuffer = 0;
#endif

#ifdef EGL_GL_VERSION_2_0_DEFINED
  EGL_glAttachShader_t glAttachShader = 0;
  EGL_glBindAttribLocation_t glBindAttribLocation = 0;
  EGL_glBlendEquationSeparate_t glBlendEquationSeparate = 0;
  EGL_glCompileShader_t glCompileShader = 0;
  EGL_glCreateProgram_t glCreateProgram = 0;
  EGL_glCreateShader_t glCreateShader = 0;
  EGL_glDeleteProgram_t glDeleteProgram = 0;
  EGL_glDeleteShader_t glDeleteShader = 0;
  EGL_glDetachShader_t glDetachShader = 0;
  EGL_glDisableVertexAttribArray_t glDisableVertexAttribArray = 0;
  EGL_glDrawBuffers_t glDrawBuffers = 0;
  EGL_glEnableVertexAttribArray_t glEnableVertexAttribArray = 0;
  EGL_glGetActiveAttrib_t glGetActiveAttrib = 0;
  EGL_glGetActiveUniform_t glGetActiveUniform = 0;
  EGL_glGetAttachedShaders_t glGetAttachedShaders = 0;
  EGL_glGetAttribLocation_t glGetAttribLocation = 0;
  EGL_glGetProgramInfoLog_t glGetProgramInfoLog = 0;
  EGL_glGetProgramiv_t glGetProgramiv = 0;
  EGL_glGetShaderInfoLog_t glGetShaderInfoLog = 0;
  EGL_glGetShaderiv_t glGetShaderiv = 0;
  EGL_glGetShaderSource_t glGetShaderSource = 0;
  EGL_glGetUniformLocation_t glGetUniformLocation = 0;
  EGL_glGetUniformfv_t glGetUniformfv = 0;
  EGL_glGetUniformiv_t glGetUniformiv = 0;
  EGL_glGetVertexAttribdv_t glGetVertexAttribdv = 0;
  EGL_glGetVertexAttribfv_t glGetVertexAttribfv = 0;
  EGL_glGetVertexAttribiv_t glGetVertexAttribiv = 0;
  EGL_glGetVertexAttribPointerv_t glGetVertexAttribPointerv = 0;
  EGL_glIsProgram_t glIsProgram = 0;
  EGL_glIsShader_t glIsShader = 0;
  EGL_glLinkProgram_t glLinkProgram = 0;
  EGL_glShaderSource_t glShaderSource = 0;
  EGL_glStencilFuncSeparate_t glStencilFuncSeparate = 0;
  EGL_glStencilMaskSeparate_t glStencilMaskSeparate = 0;
  EGL_glStencilOpSeparate_t glStencilOpSeparate = 0;
  EGL_glUniform1f_t glUniform1f = 0;
  EGL_glUniform1fv_t glUniform1fv = 0;
  EGL_glUniform1i_t glUniform1i = 0;
  EGL_glUniform1iv_t glUniform1iv = 0;
  EGL_glUniform2f_t glUniform2f = 0;
  EGL_glUniform2fv_t glUniform2fv = 0;
  EGL_glUniform2i_t glUniform2i = 0;
  EGL_glUniform2iv_t glUniform2iv = 0;
  EGL_glUniform3f_t glUniform3f = 0;
  EGL_glUniform3fv_t glUniform3fv = 0;
  EGL_glUniform3i_t glUniform3i = 0;
  EGL_glUniform3iv_t glUniform3iv = 0;
  EGL_glUniform4f_t glUniform4f = 0;
  EGL_glUniform4fv_t glUniform4fv = 0;
  EGL_glUniform4i_t glUniform4i = 0;
  EGL_glUniform4iv_t glUniform4iv = 0;
  EGL_glUniformMatrix2fv_t glUniformMatrix2fv = 0;
  EGL_glUniformMatrix3fv_t glUniformMatrix3fv = 0;
  EGL_glUniformMatrix4fv_t glUniformMatrix4fv = 0;
  EGL_glUseProgram_t glUseProgram = 0;
  EGL_glValidateProgram_t glValidateProgram = 0;
  EGL_glVertexAttrib1d_t glVertexAttrib1d = 0;
  EGL_glVertexAttrib1dv_t glVertexAttrib1dv = 0;
  EGL_glVertexAttrib1f_t glVertexAttrib1f = 0;
  EGL_glVertexAttrib1fv_t glVertexAttrib1fv = 0;
  EGL_glVertexAttrib1s_t glVertexAttrib1s = 0;
  EGL_glVertexAttrib1sv_t glVertexAttrib1sv = 0;
  EGL_glVertexAttrib2d_t glVertexAttrib2d = 0;
  EGL_glVertexAttrib2dv_t glVertexAttrib2dv = 0;
  EGL_glVertexAttrib2f_t glVertexAttrib2f = 0;
  EGL_glVertexAttrib2fv_t glVertexAttrib2fv = 0;
  EGL_glVertexAttrib2s_t glVertexAttrib2s = 0;
  EGL_glVertexAttrib2sv_t glVertexAttrib2sv = 0;
  EGL_glVertexAttrib3d_t glVertexAttrib3d = 0;
  EGL_glVertexAttrib3dv_t glVertexAttrib3dv = 0;
  EGL_glVertexAttrib3f_t glVertexAttrib3f = 0;
  EGL_glVertexAttrib3fv_t glVertexAttrib3fv = 0;
  EGL_glVertexAttrib3s_t glVertexAttrib3s = 0;
  EGL_glVertexAttrib3sv_t glVertexAttrib3sv = 0;
  EGL_glVertexAttrib4Nbv_t glVertexAttrib4Nbv = 0;
  EGL_glVertexAttrib4Niv_t glVertexAttrib4Niv = 0;
  EGL_glVertexAttrib4Nsv_t glVertexAttrib4Nsv = 0;
  EGL_glVertexAttrib4Nub_t glVertexAttrib4Nub = 0;
  EGL_glVertexAttrib4Nubv_t glVertexAttrib4Nubv = 0;
  EGL_glVertexAttrib4Nuiv_t glVertexAttrib4Nuiv = 0;
  EGL_glVertexAttrib4Nusv_t glVertexAttrib4Nusv = 0;
  EGL_glVertexAttrib4bv_t glVertexAttrib4bv = 0;
  EGL_glVertexAttrib4d_t glVertexAttrib4d = 0;
  EGL_glVertexAttrib4dv_t glVertexAttrib4dv = 0;
  EGL_glVertexAttrib4f_t glVertexAttrib4f = 0;
  EGL_glVertexAttrib4fv_t glVertexAttrib4fv = 0;
  EGL_glVertexAttrib4iv_t glVertexAttrib4iv = 0;
  EGL_glVertexAttrib4s_t glVertexAttrib4s = 0;
  EGL_glVertexAttrib4sv_t glVertexAttrib4sv = 0;
  EGL_glVertexAttrib4ubv_t glVertexAttrib4ubv = 0;
  EGL_glVertexAttrib4uiv_t glVertexAttrib4uiv = 0;
  EGL_glVertexAttrib4usv_t glVertexAttrib4usv = 0;
  EGL_glVertexAttribPointer_t glVertexAttribPointer = 0;
#endif

#ifdef EGL_GL_VERSION_2_1_DEFINED
  EGL_glUniformMatrix2x3fv_t glUniformMatrix2x3fv = 0;
  EGL_glUniformMatrix2x4fv_t glUniformMatrix2x4fv = 0;
  EGL_glUniformMatrix3x2fv_t glUniformMatrix3x2fv = 0;
  EGL_glUniformMatrix3x4fv_t glUniformMatrix3x4fv = 0;
  EGL_glUniformMatrix4x2fv_t glUniformMatrix4x2fv = 0;
  EGL_glUniformMatrix4x3fv_t glUniformMatrix4x3fv = 0;
#endif

int EGL_getglversion()
{
  const char* buffer = 0;
  unsigned int major = 0;
  unsigned int minor = 0;
  unsigned int version = 0;

  if ( !( buffer = (const char*)glGetString( GL_VERSION ) ) ) {
    return 0;
  }
  major = buffer[0] - '0';
  minor = buffer[2] - '0';
  version = ( major * 10 ) + minor;

  if ( version > 21 ) {
    return 99;
  }
  switch ( version )  {
    case 11: 
    case 12:
    case 13:
    case 14:
    case 15:
    case 20:
    case 21: 
    return version;
  }
  return 0;
}

void EGL_loadextensions()
{
  int glversion = 0;
  int error = 0;

  if ( m_initialized ) {
    return;
  }
  m_initialized = 1;

  glversion = EGL_getglversion();

  if ( 12 <= glversion ) {
    error = 0;
    error |= !( glBlendColor = (EGL_glblendcolor_t)wglGetProcAddress( "glBlendColor" ) );
    error |= !( glBlendEquation = (EGL_glblendequation_t)wglGetProcAddress( "glBlendEquation" ) );
    error |= !( glCopyTexSubImage3D = (EGL_glcopytexsubimage3d_t)wglGetProcAddress( "glCopyTexSubImage3D" ) );
    error |= !( glDrawRangeElements = (EGL_gldrawrangeelements_t)wglGetProcAddress( "glDrawRangeElements" ) );
    error |= !( glTexImage3D = (EGL_glteximage3d_t)wglGetProcAddress( "glTexImage3D" ) );
    error |= !( glTexSubImage3D = (EGL_gltexsubimage3d_t)wglGetProcAddress( "glTexSubImage3D" ) );
  }

  if ( 13 <= glversion ) {
    error = 0;
    error |= !( glActiveTexture = (EGL_glActiveTexture_t)wglGetProcAddress( "glActiveTexture" ) );
    error |= !( glClientActiveTexture = (EGL_glClientActiveTexture_t)wglGetProcAddress( "glClientActiveTexture" ) );
    error |= !( glCompressedTexImage1D = (EGL_glCompressedTexImage1D_t)wglGetProcAddress( "glCompressedTexImage1D" ) );
    error |= !( glCompressedTexImage2D = (EGL_glCompressedTexImage2D_t)wglGetProcAddress( "glCompressedTexImage2D" ) );
    error |= !( glCompressedTexImage3D = (EGL_glCompressedTexImage3D_t)wglGetProcAddress( "glCompressedTexImage3D" ) );
    error |= !( glCompressedTexSubImage1D = (EGL_glCompressedTexSubImage1D_t)wglGetProcAddress( "glCompressedTexSubImage1D" ) );
    error |= !( glCompressedTexSubImage2D = (EGL_glCompressedTexSubImage2D_t)wglGetProcAddress( "glCompressedTexSubImage2D" ) );
    error |= !( glCompressedTexSubImage3D = (EGL_glCompressedTexSubImage3D_t)wglGetProcAddress( "glCompressedTexSubImage3D" ) );
    error |= !( glGetCompressedTexImage = (EGL_glGetCompressedTexImage_t)wglGetProcAddress( "glGetCompressedTexImage" ) );
    error |= !( glLoadTransposeMatrixd = (EGL_glLoadTransposeMatrixd_t)wglGetProcAddress( "glLoadTransposeMatrixd" ) );
    error |= !( glLoadTransposeMatrixf = (EGL_glLoadTransposeMatrixf_t)wglGetProcAddress( "glLoadTransposeMatrixf" ) );
    error |= !( glMultTransposeMatrixd = (EGL_glMultTransposeMatrixd_t)wglGetProcAddress( "glMultTransposeMatrixd" ) );
    error |= !( glMultTransposeMatrixf = (EGL_glMultTransposeMatrixf_t)wglGetProcAddress( "glMultTransposeMatrixf" ) );
    error |= !( glMultiTexCoord1d = (EGL_glMultiTexCoord1d_t)wglGetProcAddress( "glMultiTexCoord1d" ) );
    error |= !( glMultiTexCoord1dv = (EGL_glMultiTexCoord1dv_t)wglGetProcAddress( "glMultiTexCoord1dv" ) );
    error |= !( glMultiTexCoord1f = (EGL_glMultiTexCoord1f_t)wglGetProcAddress( "glMultiTexCoord1f" ) );
    error |= !( glMultiTexCoord1fv = (EGL_glMultiTexCoord1fv_t)wglGetProcAddress( "glMultiTexCoord1fv" ) );
    error |= !( glMultiTexCoord1i = (EGL_glMultiTexCoord1i_t)wglGetProcAddress( "glMultiTexCoord1i" ) );
    error |= !( glMultiTexCoord1iv = (EGL_glMultiTexCoord1iv_t)wglGetProcAddress( "glMultiTexCoord1iv" ) );
    error |= !( glMultiTexCoord1s = (EGL_glMultiTexCoord1s_t)wglGetProcAddress( "glMultiTexCoord1s" ) );
    error |= !( glMultiTexCoord1sv = (EGL_glMultiTexCoord1sv_t)wglGetProcAddress( "glMultiTexCoord1sv" ) );
    error |= !( glMultiTexCoord2d = (EGL_glMultiTexCoord2d_t)wglGetProcAddress( "glMultiTexCoord2d" ) );
    error |= !( glMultiTexCoord2dv = (EGL_glMultiTexCoord2dv_t)wglGetProcAddress( "glMultiTexCoord2dv" ) );
    error |= !( glMultiTexCoord2f = (EGL_glMultiTexCoord2f_t)wglGetProcAddress( "glMultiTexCoord2f" ) );
    error |= !( glMultiTexCoord2fv = (EGL_glMultiTexCoord2fv_t)wglGetProcAddress( "glMultiTexCoord2fv" ) );
    error |= !( glMultiTexCoord2i = (EGL_glMultiTexCoord2i_t)wglGetProcAddress( "glMultiTexCoord2i" ) );
    error |= !( glMultiTexCoord2iv = (EGL_glMultiTexCoord2iv_t)wglGetProcAddress( "glMultiTexCoord2iv" ) );
    error |= !( glMultiTexCoord2s = (EGL_glMultiTexCoord2s_t)wglGetProcAddress( "glMultiTexCoord2s" ) );
    error |= !( glMultiTexCoord2sv = (EGL_glMultiTexCoord2sv_t)wglGetProcAddress( "glMultiTexCoord2sv" ) );
    error |= !( glMultiTexCoord3d = (EGL_glMultiTexCoord3d_t)wglGetProcAddress( "glMultiTexCoord3d" ) );
    error |= !( glMultiTexCoord3dv = (EGL_glMultiTexCoord3dv_t)wglGetProcAddress( "glMultiTexCoord3dv" ) );
    error |= !( glMultiTexCoord3f = (EGL_glMultiTexCoord3f_t)wglGetProcAddress( "glMultiTexCoord3f" ) );
    error |= !( glMultiTexCoord3fv = (EGL_glMultiTexCoord3fv_t)wglGetProcAddress( "glMultiTexCoord3fv" ) );
    error |= !( glMultiTexCoord3i = (EGL_glMultiTexCoord3i_t)wglGetProcAddress( "glMultiTexCoord3i" ) );
    error |= !( glMultiTexCoord3iv = (EGL_glMultiTexCoord3iv_t)wglGetProcAddress( "glMultiTexCoord3iv" ) );
    error |= !( glMultiTexCoord3s = (EGL_glMultiTexCoord3s_t)wglGetProcAddress( "glMultiTexCoord3s" ) );
    error |= !( glMultiTexCoord3sv = (EGL_glMultiTexCoord3sv_t)wglGetProcAddress( "glMultiTexCoord3sv" ) );
    error |= !( glMultiTexCoord4d = (EGL_glMultiTexCoord4d_t)wglGetProcAddress( "glMultiTexCoord4d" ) );
    error |= !( glMultiTexCoord4dv = (EGL_glMultiTexCoord4dv_t)wglGetProcAddress( "glMultiTexCoord4dv" ) );
    error |= !( glMultiTexCoord4f = (EGL_glMultiTexCoord4f_t)wglGetProcAddress( "glMultiTexCoord4f" ) );
    error |= !( glMultiTexCoord4fv = (EGL_glMultiTexCoord4fv_t)wglGetProcAddress( "glMultiTexCoord4fv" ) );
    error |= !( glMultiTexCoord4i = (EGL_glMultiTexCoord4i_t)wglGetProcAddress( "glMultiTexCoord4i" ) );
    error |= !( glMultiTexCoord4iv = (EGL_glMultiTexCoord4iv_t)wglGetProcAddress( "glMultiTexCoord4iv" ) );
    error |= !( glMultiTexCoord4s = (EGL_glMultiTexCoord4s_t)wglGetProcAddress( "glMultiTexCoord4s" ) );
    error |= !( glMultiTexCoord4sv = (EGL_glMultiTexCoord4sv_t)wglGetProcAddress( "glMultiTexCoord4sv" ) );
    error |= !( glSampleCoverage = (EGL_glSampleCoverage_t)wglGetProcAddress( "glSampleCoverage" ) );
  }

  if ( 14 <= glversion ) {
    error = 0;
    error |= !( glBlendFuncSeparate = (EGL_glBlendFuncSeparate_t)wglGetProcAddress( "glBlendFuncSeparate" ) );
    error |= !( glFogCoordd = (EGL_glFogCoordd_t)wglGetProcAddress( "glFogCoordd" ) );
    error |= !( glFogCoorddv = (EGL_glFogCoorddv_t)wglGetProcAddress( "glFogCoorddv" ) );
    error |= !( glFogCoordf = (EGL_glFogCoordf_t)wglGetProcAddress( "glFogCoordf" ) );
    error |= !( glFogCoordfv = (EGL_glFogCoordfv_t)wglGetProcAddress( "glFogCoordfv" ) );
    error |= !( glFogCoordPointer = (EGL_glFogCoordPointer_t)wglGetProcAddress( "glFogCoordPointer" ) );
    error |= !( glMultiDrawArrays = (EGL_glMultiDrawArrays_t)wglGetProcAddress( "glMultiDrawArrays" ) );
    error |= !( glMultiDrawElements = (EGL_glMultiDrawElements_t)wglGetProcAddress( "glMultiDrawElements" ) );
    error |= !( glPointParameterf = (EGL_glPointParameterf_t)wglGetProcAddress( "glPointParameterf" ) );
    error |= !( glPointParameterfv = (EGL_glPointParameterfv_t)wglGetProcAddress( "glPointParameterfv" ) );
    error |= !( glPointParameteri = (EGL_glPointParameteri_t)wglGetProcAddress( "glPointParameteri" ) );
    error |= !( glPointParameteriv = (EGL_glPointParameteriv_t)wglGetProcAddress( "glPointParameteriv" ) );
    error |= !( glSecondaryColor3b = (EGL_glSecondaryColor3b_t)wglGetProcAddress( "glSecondaryColor3b" ) );
    error |= !( glSecondaryColor3bv = (EGL_glSecondaryColor3bv_t)wglGetProcAddress( "glSecondaryColor3bv" ) );
    error |= !( glSecondaryColor3d = (EGL_glSecondaryColor3d_t)wglGetProcAddress( "glSecondaryColor3d" ) );
    error |= !( glSecondaryColor3dv = (EGL_glSecondaryColor3dv_t)wglGetProcAddress( "glSecondaryColor3dv" ) );
    error |= !( glSecondaryColor3f = (EGL_glSecondaryColor3f_t)wglGetProcAddress( "glSecondaryColor3f" ) );
    error |= !( glSecondaryColor3fv = (EGL_glSecondaryColor3fv_t)wglGetProcAddress( "glSecondaryColor3fv" ) );
    error |= !( glSecondaryColor3i = (EGL_glSecondaryColor3i_t)wglGetProcAddress( "glSecondaryColor3i" ) );
    error |= !( glSecondaryColor3iv = (EGL_glSecondaryColor3iv_t)wglGetProcAddress( "glSecondaryColor3iv" ) );
    error |= !( glSecondaryColor3s = (EGL_glSecondaryColor3s_t)wglGetProcAddress( "glSecondaryColor3s" ) );
    error |= !( glSecondaryColor3sv = (EGL_glSecondaryColor3sv_t)wglGetProcAddress( "glSecondaryColor3sv" ) );
    error |= !( glSecondaryColor3ub = (EGL_glSecondaryColor3ub_t)wglGetProcAddress( "glSecondaryColor3ub" ) );
    error |= !( glSecondaryColor3ubv = (EGL_glSecondaryColor3ubv_t)wglGetProcAddress( "glSecondaryColor3ubv" ) );
    error |= !( glSecondaryColor3ui = (EGL_glSecondaryColor3ui_t)wglGetProcAddress( "glSecondaryColor3ui" ) );
    error |= !( glSecondaryColor3uiv = (EGL_glSecondaryColor3uiv_t)wglGetProcAddress( "glSecondaryColor3uiv" ) );
    error |= !( glSecondaryColor3us = (EGL_glSecondaryColor3us_t)wglGetProcAddress( "glSecondaryColor3us" ) );
    error |= !( glSecondaryColor3usv = (EGL_glSecondaryColor3usv_t)wglGetProcAddress( "glSecondaryColor3usv" ) );
    error |= !( glSecondaryColorPointer = (EGL_glSecondaryColorPointer_t)wglGetProcAddress( "glSecondaryColorPointer" ) );
    error |= !( glWindowPos2d = (EGL_glWindowPos2d_t)wglGetProcAddress( "glWindowPos2d" ) );
    error |= !( glWindowPos2dv = (EGL_glWindowPos2dv_t)wglGetProcAddress( "glWindowPos2dv" ) );
    error |= !( glWindowPos2f = (EGL_glWindowPos2f_t)wglGetProcAddress( "glWindowPos2f" ) );
    error |= !( glWindowPos2fv = (EGL_glWindowPos2fv_t)wglGetProcAddress( "glWindowPos2fv" ) );
    error |= !( glWindowPos2i = (EGL_glWindowPos2i_t)wglGetProcAddress( "glWindowPos2i" ) );
    error |= !( glWindowPos2iv = (EGL_glWindowPos2iv_t)wglGetProcAddress( "glWindowPos2iv" ) );
    error |= !( glWindowPos2s = (EGL_glWindowPos2s_t)wglGetProcAddress( "glWindowPos2s" ) );
    error |= !( glWindowPos2sv = (EGL_glWindowPos2sv_t)wglGetProcAddress( "glWindowPos2sv" ) );
    error |= !( glWindowPos3d = (EGL_glWindowPos3d_t)wglGetProcAddress( "glWindowPos3d" ) );
    error |= !( glWindowPos3dv = (EGL_glWindowPos3dv_t)wglGetProcAddress( "glWindowPos3dv" ) );
    error |= !( glWindowPos3f = (EGL_glWindowPos3f_t)wglGetProcAddress( "glWindowPos3f" ) );
    error |= !( glWindowPos3fv = (EGL_glWindowPos3fv_t)wglGetProcAddress( "glWindowPos3fv" ) );
    error |= !( glWindowPos3i = (EGL_glWindowPos3i_t)wglGetProcAddress( "glWindowPos3i" ) );
    error |= !( glWindowPos3iv = (EGL_glWindowPos3iv_t)wglGetProcAddress( "glWindowPos3iv" ) );
    error |= !( glWindowPos3s = (EGL_glWindowPos3s_t)wglGetProcAddress( "glWindowPos3s" ) );
    error |= !( glWindowPos3sv = (EGL_glWindowPos3sv_t)wglGetProcAddress( "glWindowPos3sv" ) );
  }

  if ( 15 <= glversion ) {
    error = 0;
    error |= !( glBeginQuery = (EGL_glBeginQuery_t)wglGetProcAddress( "glBeginQuery" ) );
    error |= !( glBindBuffer = (EGL_glBindBuffer_t)wglGetProcAddress( "glBindBuffer" ) );
    error |= !( glBufferData = (EGL_glBufferData_t)wglGetProcAddress( "glBufferData" ) );
    error |= !( glBufferSubData = (EGL_glBufferSubData_t)wglGetProcAddress( "glBufferSubData" ) );
    error |= !( glDeleteBuffers = (EGL_glDeleteBuffers_t)wglGetProcAddress( "glDeleteBuffers" ) );
    error |= !( glDeleteQueries = (EGL_glDeleteQueries_t)wglGetProcAddress( "glDeleteQueries" ) );
    error |= !( glEndQuery = (EGL_glEndQuery_t)wglGetProcAddress( "glEndQuery" ) );
    error |= !( glGenBuffers = (EGL_glGenBuffers_t)wglGetProcAddress( "glGenBuffers" ) );
    error |= !( glGenQueries = (EGL_glGenQueries_t)wglGetProcAddress( "glGenQueries" ) );
    error |= !( glGetBufferParameteriv = (EGL_glGetBufferParameteriv_t)wglGetProcAddress( "glGetBufferParameteriv" ) );
    error |= !( glGetBufferPointerv = (EGL_glGetBufferPointerv_t)wglGetProcAddress( "glGetBufferPointerv" ) );
    error |= !( glGetBufferSubData = (EGL_glGetBufferSubData_t)wglGetProcAddress( "glGetBufferSubData" ) );
    error |= !( glGetQueryObjectiv = (EGL_glGetQueryObjectiv_t)wglGetProcAddress( "glGetQueryObjectiv" ) );
    error |= !( glGetQueryObjectuiv = (EGL_glGetQueryObjectuiv_t)wglGetProcAddress( "glGetQueryObjectuiv" ) );
    error |= !( glGetQueryiv = (EGL_glGetQueryiv_t)wglGetProcAddress( "glGetQueryiv" ) );
    error |= !( glIsBuffer = (EGL_glIsBuffer_t)wglGetProcAddress( "glIsBuffer" ) );
    error |= !( glIsQuery = (EGL_glIsQuery_t)wglGetProcAddress( "glIsQuery" ) );
    error |= !( glMapBuffer = (EGL_glMapBuffer_t)wglGetProcAddress( "glMapBuffer" ) );
    error |= !( glUnmapBuffer = (EGL_glUnmapBuffer_t)wglGetProcAddress( "glUnmapBuffer" ) );
  }

  if ( 20 <= glversion ) {
    error = 0;
    error |= !( glAttachShader = (EGL_glAttachShader_t)wglGetProcAddress( "glAttachShader" ) );
    error |= !( glBindAttribLocation = (EGL_glBindAttribLocation_t)wglGetProcAddress( "glBindAttribLocation" ) );
    error |= !( glBlendEquationSeparate = (EGL_glBlendEquationSeparate_t)wglGetProcAddress( "glBlendEquationSeparate" ) );
    error |= !( glCompileShader = (EGL_glCompileShader_t)wglGetProcAddress( "glCompileShader" ) );
    error |= !( glCreateProgram = (EGL_glCreateProgram_t)wglGetProcAddress( "glCreateProgram" ) );
    error |= !( glCreateShader = (EGL_glCreateShader_t)wglGetProcAddress( "glCreateShader" ) );
    error |= !( glDeleteProgram = (EGL_glDeleteProgram_t)wglGetProcAddress( "glDeleteProgram" ) );
    error |= !( glDeleteShader = (EGL_glDeleteShader_t)wglGetProcAddress( "glDeleteShader" ) );
    error |= !( glDetachShader = (EGL_glDetachShader_t)wglGetProcAddress( "glDetachShader" ) );
    error |= !( glDisableVertexAttribArray = (EGL_glDisableVertexAttribArray_t)wglGetProcAddress( "glDisableVertexAttribArray" ) );
    error |= !( glDrawBuffers = (EGL_glDrawBuffers_t)wglGetProcAddress( "glDrawBuffers" ) );
    error |= !( glEnableVertexAttribArray = (EGL_glEnableVertexAttribArray_t)wglGetProcAddress( "glEnableVertexAttribArray" ) );
    error |= !( glGetActiveAttrib = (EGL_glGetActiveAttrib_t)wglGetProcAddress( "glGetActiveAttrib" ) );
    error |= !( glGetActiveUniform = (EGL_glGetActiveUniform_t)wglGetProcAddress( "glGetActiveUniform" ) );
    error |= !( glGetAttachedShaders = (EGL_glGetAttachedShaders_t)wglGetProcAddress( "glGetAttachedShaders" ) );
    error |= !( glGetAttribLocation = (EGL_glGetAttribLocation_t)wglGetProcAddress( "glGetAttribLocation" ) );
    error |= !( glGetProgramInfoLog = (EGL_glGetProgramInfoLog_t)wglGetProcAddress( "glGetProgramInfoLog" ) );
    error |= !( glGetProgramiv = (EGL_glGetProgramiv_t)wglGetProcAddress( "glGetProgramiv" ) );
    error |= !( glGetShaderInfoLog = (EGL_glGetShaderInfoLog_t)wglGetProcAddress( "glGetShaderInfoLog" ) );
    error |= !( glGetShaderiv = (EGL_glGetShaderiv_t)wglGetProcAddress( "glGetShaderiv" ) );
    error |= !( glGetShaderSource = (EGL_glGetShaderSource_t)wglGetProcAddress( "glGetShaderSource" ) );
    error |= !( glGetUniformLocation = (EGL_glGetUniformLocation_t)wglGetProcAddress( "glGetUniformLocation" ) );
    error |= !( glGetUniformfv = (EGL_glGetUniformfv_t)wglGetProcAddress( "glGetUniformfv" ) );
    error |= !( glGetUniformiv = (EGL_glGetUniformiv_t)wglGetProcAddress( "glGetUniformiv" ) );
    error |= !( glGetVertexAttribdv = (EGL_glGetVertexAttribdv_t)wglGetProcAddress( "glGetVertexAttribdv" ) );
    error |= !( glGetVertexAttribfv = (EGL_glGetVertexAttribfv_t)wglGetProcAddress( "glGetVertexAttribfv" ) );
    error |= !( glGetVertexAttribiv = (EGL_glGetVertexAttribiv_t)wglGetProcAddress( "glGetVertexAttribiv" ) );
    error |= !( glGetVertexAttribPointerv = (EGL_glGetVertexAttribPointerv_t)wglGetProcAddress( "glGetVertexAttribPointerv" ) );
    error |= !( glIsProgram = (EGL_glIsProgram_t)wglGetProcAddress( "glIsProgram" ) );
    error |= !( glIsShader = (EGL_glIsShader_t)wglGetProcAddress( "glIsShader" ) );
    error |= !( glLinkProgram = (EGL_glLinkProgram_t)wglGetProcAddress( "glLinkProgram" ) );
    error |= !( glShaderSource = (EGL_glShaderSource_t)wglGetProcAddress( "glShaderSource" ) );
    error |= !( glStencilFuncSeparate = (EGL_glStencilFuncSeparate_t)wglGetProcAddress( "glStencilFuncSeparate" ) );
    error |= !( glStencilMaskSeparate = (EGL_glStencilMaskSeparate_t)wglGetProcAddress( "glStencilMaskSeparate" ) );
    error |= !( glStencilOpSeparate = (EGL_glStencilOpSeparate_t)wglGetProcAddress( "glStencilOpSeparate" ) );
    error |= !( glUniform1f = (EGL_glUniform1f_t)wglGetProcAddress( "glUniform1f" ) );
    error |= !( glUniform1fv = (EGL_glUniform1fv_t)wglGetProcAddress( "glUniform1fv" ) );
    error |= !( glUniform1i = (EGL_glUniform1i_t)wglGetProcAddress( "glUniform1i" ) );
    error |= !( glUniform1iv = (EGL_glUniform1iv_t)wglGetProcAddress( "glUniform1iv" ) );
    error |= !( glUniform2f = (EGL_glUniform2f_t)wglGetProcAddress( "glUniform2f" ) );
    error |= !( glUniform2fv = (EGL_glUniform2fv_t)wglGetProcAddress( "glUniform2fv" ) );
    error |= !( glUniform2i = (EGL_glUniform2i_t)wglGetProcAddress( "glUniform2i" ) );
    error |= !( glUniform2iv = (EGL_glUniform2iv_t)wglGetProcAddress( "glUniform2iv" ) );
    error |= !( glUniform3f = (EGL_glUniform3f_t)wglGetProcAddress( "glUniform3f" ) );
    error |= !( glUniform3fv = (EGL_glUniform3fv_t)wglGetProcAddress( "glUniform3fv" ) );
    error |= !( glUniform3i = (EGL_glUniform3i_t)wglGetProcAddress( "glUniform3i" ) );
    error |= !( glUniform3iv = (EGL_glUniform3iv_t)wglGetProcAddress( "glUniform3iv" ) );
    error |= !( glUniform4f = (EGL_glUniform4f_t)wglGetProcAddress( "glUniform4f" ) );
    error |= !( glUniform4fv = (EGL_glUniform4fv_t)wglGetProcAddress( "glUniform4fv" ) );
    error |= !( glUniform4i = (EGL_glUniform4i_t)wglGetProcAddress( "glUniform4i" ) );
    error |= !( glUniform4iv = (EGL_glUniform4iv_t)wglGetProcAddress( "glUniform4iv" ) );
    error |= !( glUniformMatrix2fv = (EGL_glUniformMatrix2fv_t)wglGetProcAddress( "glUniformMatrix2fv" ) );
    error |= !( glUniformMatrix3fv = (EGL_glUniformMatrix3fv_t)wglGetProcAddress( "glUniformMatrix3fv" ) );
    error |= !( glUniformMatrix4fv = (EGL_glUniformMatrix4fv_t)wglGetProcAddress( "glUniformMatrix4fv" ) );
    error |= !( glUseProgram = (EGL_glUseProgram_t)wglGetProcAddress( "glUseProgram" ) );
    error |= !( glValidateProgram = (EGL_glValidateProgram_t)wglGetProcAddress( "glValidateProgram" ) );
    error |= !( glVertexAttrib1d = (EGL_glVertexAttrib1d_t)wglGetProcAddress( "glVertexAttrib1d" ) );
    error |= !( glVertexAttrib1dv = (EGL_glVertexAttrib1dv_t)wglGetProcAddress( "glVertexAttrib1dv" ) );
    error |= !( glVertexAttrib1f = (EGL_glVertexAttrib1f_t)wglGetProcAddress( "glVertexAttrib1f" ) );
    error |= !( glVertexAttrib1fv = (EGL_glVertexAttrib1fv_t)wglGetProcAddress( "glVertexAttrib1fv" ) );
    error |= !( glVertexAttrib1s = (EGL_glVertexAttrib1s_t)wglGetProcAddress( "glVertexAttrib1s" ) );
    error |= !( glVertexAttrib1sv = (EGL_glVertexAttrib1sv_t)wglGetProcAddress( "glVertexAttrib1sv" ) );
    error |= !( glVertexAttrib2d = (EGL_glVertexAttrib2d_t)wglGetProcAddress( "glVertexAttrib2d" ) );
    error |= !( glVertexAttrib2dv = (EGL_glVertexAttrib2dv_t)wglGetProcAddress( "glVertexAttrib2dv" ) );
    error |= !( glVertexAttrib2f = (EGL_glVertexAttrib2f_t)wglGetProcAddress( "glVertexAttrib2f" ) );
    error |= !( glVertexAttrib2fv = (EGL_glVertexAttrib2fv_t)wglGetProcAddress( "glVertexAttrib2fv" ) );
    error |= !( glVertexAttrib2s = (EGL_glVertexAttrib2s_t)wglGetProcAddress( "glVertexAttrib2s" ) );
    error |= !( glVertexAttrib2sv = (EGL_glVertexAttrib2sv_t)wglGetProcAddress( "glVertexAttrib2sv" ) );
    error |= !( glVertexAttrib3d = (EGL_glVertexAttrib3d_t)wglGetProcAddress( "glVertexAttrib3d" ) );
    error |= !( glVertexAttrib3dv = (EGL_glVertexAttrib3dv_t)wglGetProcAddress( "glVertexAttrib3dv" ) );
    error |= !( glVertexAttrib3f = (EGL_glVertexAttrib3f_t)wglGetProcAddress( "glVertexAttrib3f" ) );
    error |= !( glVertexAttrib3fv = (EGL_glVertexAttrib3fv_t)wglGetProcAddress( "glVertexAttrib3fv" ) );
    error |= !( glVertexAttrib3s = (EGL_glVertexAttrib3s_t)wglGetProcAddress( "glVertexAttrib3s" ) );
    error |= !( glVertexAttrib3sv = (EGL_glVertexAttrib3sv_t)wglGetProcAddress( "glVertexAttrib3sv" ) );
    error |= !( glVertexAttrib4Nbv = (EGL_glVertexAttrib4Nbv_t)wglGetProcAddress( "glVertexAttrib4Nbv" ) );
    error |= !( glVertexAttrib4Niv = (EGL_glVertexAttrib4Niv_t)wglGetProcAddress( "glVertexAttrib4Niv" ) );
    error |= !( glVertexAttrib4Nsv = (EGL_glVertexAttrib4Nsv_t)wglGetProcAddress( "glVertexAttrib4Nsv" ) );
    error |= !( glVertexAttrib4Nub = (EGL_glVertexAttrib4Nub_t)wglGetProcAddress( "glVertexAttrib4Nub" ) );
    error |= !( glVertexAttrib4Nubv = (EGL_glVertexAttrib4Nubv_t)wglGetProcAddress( "glVertexAttrib4Nubv" ) );
    error |= !( glVertexAttrib4Nuiv = (EGL_glVertexAttrib4Nuiv_t)wglGetProcAddress( "glVertexAttrib4Nuiv" ) );
    error |= !( glVertexAttrib4Nusv = (EGL_glVertexAttrib4Nusv_t)wglGetProcAddress( "glVertexAttrib4Nusv" ) );
    error |= !( glVertexAttrib4bv = (EGL_glVertexAttrib4bv_t)wglGetProcAddress( "glVertexAttrib4bv" ) );
    error |= !( glVertexAttrib4d = (EGL_glVertexAttrib4d_t)wglGetProcAddress( "glVertexAttrib4d" ) );
    error |= !( glVertexAttrib4dv = (EGL_glVertexAttrib4dv_t)wglGetProcAddress( "glVertexAttrib4dv" ) );
    error |= !( glVertexAttrib4f = (EGL_glVertexAttrib4f_t)wglGetProcAddress( "glVertexAttrib4f" ) );
    error |= !( glVertexAttrib4fv = (EGL_glVertexAttrib4fv_t)wglGetProcAddress( "glVertexAttrib4fv" ) );
    error |= !( glVertexAttrib4iv = (EGL_glVertexAttrib4iv_t)wglGetProcAddress( "glVertexAttrib4iv" ) );
    error |= !( glVertexAttrib4s = (EGL_glVertexAttrib4s_t)wglGetProcAddress( "glVertexAttrib4s" ) );
    error |= !( glVertexAttrib4sv = (EGL_glVertexAttrib4sv_t)wglGetProcAddress( "glVertexAttrib4sv" ) );
    error |= !( glVertexAttrib4ubv = (EGL_glVertexAttrib4ubv_t)wglGetProcAddress( "glVertexAttrib4ubv" ) );
    error |= !( glVertexAttrib4uiv = (EGL_glVertexAttrib4uiv_t)wglGetProcAddress( "glVertexAttrib4uiv" ) );
    error |= !( glVertexAttrib4usv = (EGL_glVertexAttrib4usv_t)wglGetProcAddress( "glVertexAttrib4usv" ) );
    error |= !( glVertexAttribPointer = (EGL_glVertexAttribPointer_t)wglGetProcAddress( "glVertexAttribPointer" ) );
  }

  if ( 21 <= glversion ) {
    error = 0;
    error |= !( glUniformMatrix2x3fv = (EGL_glUniformMatrix2x3fv_t)wglGetProcAddress( "glUniformMatrix2x3fv" ) );
    error |= !( glUniformMatrix2x4fv = (EGL_glUniformMatrix2x4fv_t)wglGetProcAddress( "glUniformMatrix2x4fv" ) );
    error |= !( glUniformMatrix3x2fv = (EGL_glUniformMatrix3x2fv_t)wglGetProcAddress( "glUniformMatrix3x2fv" ) );
    error |= !( glUniformMatrix3x4fv = (EGL_glUniformMatrix3x4fv_t)wglGetProcAddress( "glUniformMatrix3x4fv" ) );
    error |= !( glUniformMatrix4x2fv = (EGL_glUniformMatrix4x2fv_t)wglGetProcAddress( "glUniformMatrix4x2fv" ) );
    error |= !( glUniformMatrix4x3fv = (EGL_glUniformMatrix4x3fv_t)wglGetProcAddress( "glUniformMatrix4x3fv" ) );
  }
}

