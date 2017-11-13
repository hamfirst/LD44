/*

    This file was generated with gl3w_gen.py, part of gl3w
    (hosted at https://github.com/skaslev/gl3w)

    This is free and unencumbered software released into the public domain.

    Anyone is free to copy, modify, publish, use, compile, sell, or
    distribute this software, either in source code form or as a compiled
    binary, for any purpose, commercial or non-commercial, and by any
    means.

    In jurisdictions that recognize copyright laws, the author or authors
    of this software dedicate any and all copyright interest in the
    software to the public domain. We make this dedication for the benefit
    of the public at large and to the detriment of our heirs and
    successors. We intend this dedication to be an overt act of
    relinquishment in perpetuity of all present and future rights to this
    software under copyright law.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
    OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/

#include <gl3w/gl3w.h>

#if defined(_WEB)

int gl3wInit(int egl_mode)
{
  return 1;
}

int gl3wIsSupported(int major, int minor)
{
  return 1;
}

GL3WglProc gl3wGetProcAddress(const char *proc)
{
  return 0;
}

#elif defined(_ANDROID)

#define _GNU_SOURCE
#include <dlfcn.h>

PFNGLBINDVERTEXARRAYOESPROC glBindVertexArray;
PFNGLGENVERTEXARRAYSOESPROC glGenVertexArrays;
PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArrays;

int gl3wInit(int egl_mode)
{
  void *libhandle = dlopen("libGLESv2.so", RTLD_LAZY);
  if (libhandle == 0)
  {
    return 0;
  }

  glBindVertexArray = (PFNGLBINDVERTEXARRAYOESPROC)dlsym(libhandle,
    "glBindVertexArrayOES");
  glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSOESPROC)dlsym(libhandle,
    "glDeleteVertexArraysOES");
  glGenVertexArrays = (PFNGLGENVERTEXARRAYSOESPROC)dlsym(libhandle,
    "glGenVertexArraysOES");

  dlclose(libhandle);
  return glBindVertexArray && glDeleteVertexArrays && glGenVertexArrays ? 1 : 0;
}

int gl3wIsSupported(int major, int minor)
{
  return 1;
}

GL3WglProc gl3wGetProcAddress(const char *proc)
{
  return 0;
}

#else

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>

#include <EGL/egl.h>

static HMODULE libgl;
static int use_egl = 0;

static void open_libgl(int egl_mode)
{
  use_egl = egl_mode;
  if (!use_egl)
  {
    libgl = LoadLibraryA("opengl32.dll");
  }
}

static void close_libgl(void)
{
  if (!use_egl)
  {
    FreeLibrary(libgl);
  }
}

static GL3WglProc get_proc(const char *proc)
{
  if (use_egl)
  {
    return (GL3WglProc)eglGetProcAddress(proc);
  }

	GL3WglProc res;

	res = (GL3WglProc) wglGetProcAddress(proc);
	if (!res)
		res = (GL3WglProc) GetProcAddress(libgl, proc);
	return res;
}

#elif defined(__APPLE__) || defined(__APPLE_CC__)
#include <Carbon/Carbon.h>

CFBundleRef bundle;
CFURLRef bundleURL;

static void open_libgl(int egl_mode)
{
	bundleURL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
		CFSTR("/System/Library/Frameworks/OpenGL.framework"),
		kCFURLPOSIXPathStyle, true);

	bundle = CFBundleCreate(kCFAllocatorDefault, bundleURL);
	assert(bundle != NULL);
}

static void close_libgl(void)
{
	CFRelease(bundle);
	CFRelease(bundleURL);
}

static GL3WglProc get_proc(const char *proc)
{
	GL3WglProc res;

	CFStringRef procname = CFStringCreateWithCString(kCFAllocatorDefault, proc,
		kCFStringEncodingASCII);
	res = (GL3WglProc) CFBundleGetFunctionPointerForName(bundle, procname);
	CFRelease(procname);
	return res;
}

#else

#include <dlfcn.h>
#include <GL/glx.h>

static void *libgl;
static PFNGLXGETPROCADDRESSPROC glx_get_proc_address;

static void open_libgl(int egl_mode)
{
	libgl = dlopen("libGL.so.1", RTLD_LAZY | RTLD_GLOBAL);
	glx_get_proc_address = (PFNGLXGETPROCADDRESSPROC) dlsym(libgl, "glXGetProcAddressARB");
}

static void close_libgl(void)
{
	dlclose(libgl);
}

static GL3WglProc get_proc(const char *proc)
{
	GL3WglProc res;

	res = (GL3WglProc) glx_get_proc_address((const GLubyte *) proc);
	if (!res)
		res = (GL3WglProc) dlsym(libgl, proc);
	return res;
}

#endif

static struct {
	int major, minor;
} version;

static int parse_version(void)
{
	//if (!glGetIntegerv)
	//	return -1;

	//glGetIntegerv(GL_MAJOR_VERSION, &version.major);
	//glGetIntegerv(GL_MINOR_VERSION, &version.minor);

	//if (version.major < 3)
	//	return -1;
	//return 0;

  return 0;
}

static void load_procs(void);

int gl3wInit(int egl_mode)
{
	open_libgl(egl_mode);
	load_procs();
	close_libgl();
	return parse_version();
}

int gl3wIsSupported(int major, int minor)
{
	if (major < 3)
		return 0;
	if (version.major == major)
		return version.minor >= minor;
	return version.major >= major;
}

GL3WglProc gl3wGetProcAddress(const char *proc)
{
	return get_proc(proc);
}

PFNGLACTIVESHADERPROGRAMPROC                         gl3wActiveShaderProgram;
PFNGLACTIVETEXTUREPROC                               gl3wActiveTexture;
PFNGLATTACHSHADERPROC                                gl3wAttachShader;
PFNGLBEGINCONDITIONALRENDERPROC                      gl3wBeginConditionalRender;
PFNGLBEGINQUERYPROC                                  gl3wBeginQuery;
PFNGLBEGINQUERYINDEXEDPROC                           gl3wBeginQueryIndexed;
PFNGLBEGINTRANSFORMFEEDBACKPROC                      gl3wBeginTransformFeedback;
PFNGLBINDATTRIBLOCATIONPROC                          gl3wBindAttribLocation;
PFNGLBINDBUFFERPROC                                  gl3wBindBuffer;
PFNGLBINDBUFFERBASEPROC                              gl3wBindBufferBase;
PFNGLBINDBUFFERRANGEPROC                             gl3wBindBufferRange;
PFNGLBINDBUFFERSBASEPROC                             gl3wBindBuffersBase;
PFNGLBINDBUFFERSRANGEPROC                            gl3wBindBuffersRange;
PFNGLBINDFRAGDATALOCATIONPROC                        gl3wBindFragDataLocation;
PFNGLBINDFRAGDATALOCATIONINDEXEDPROC                 gl3wBindFragDataLocationIndexed;
PFNGLBINDFRAMEBUFFERPROC                             gl3wBindFramebuffer;
PFNGLBINDIMAGETEXTUREPROC                            gl3wBindImageTexture;
PFNGLBINDIMAGETEXTURESPROC                           gl3wBindImageTextures;
PFNGLBINDPROGRAMPIPELINEPROC                         gl3wBindProgramPipeline;
PFNGLBINDRENDERBUFFERPROC                            gl3wBindRenderbuffer;
PFNGLBINDSAMPLERPROC                                 gl3wBindSampler;
PFNGLBINDSAMPLERSPROC                                gl3wBindSamplers;
PFNGLBINDTEXTUREPROC                                 gl3wBindTexture;
PFNGLBINDTEXTUREUNITPROC                             gl3wBindTextureUnit;
PFNGLBINDTEXTURESPROC                                gl3wBindTextures;
PFNGLBINDTRANSFORMFEEDBACKPROC                       gl3wBindTransformFeedback;
PFNGLBINDVERTEXARRAYPROC                             gl3wBindVertexArray;
PFNGLBINDVERTEXBUFFERPROC                            gl3wBindVertexBuffer;
PFNGLBINDVERTEXBUFFERSPROC                           gl3wBindVertexBuffers;
PFNGLBLENDCOLORPROC                                  gl3wBlendColor;
PFNGLBLENDEQUATIONPROC                               gl3wBlendEquation;
PFNGLBLENDEQUATIONSEPARATEPROC                       gl3wBlendEquationSeparate;
PFNGLBLENDEQUATIONSEPARATEIPROC                      gl3wBlendEquationSeparatei;
PFNGLBLENDEQUATIONSEPARATEIARBPROC                   gl3wBlendEquationSeparateiARB;
PFNGLBLENDEQUATIONIPROC                              gl3wBlendEquationi;
PFNGLBLENDEQUATIONIARBPROC                           gl3wBlendEquationiARB;
PFNGLBLENDFUNCPROC                                   gl3wBlendFunc;
PFNGLBLENDFUNCSEPARATEPROC                           gl3wBlendFuncSeparate;
PFNGLBLENDFUNCSEPARATEIPROC                          gl3wBlendFuncSeparatei;
PFNGLBLENDFUNCSEPARATEIARBPROC                       gl3wBlendFuncSeparateiARB;
PFNGLBLENDFUNCIPROC                                  gl3wBlendFunci;
PFNGLBLENDFUNCIARBPROC                               gl3wBlendFunciARB;
PFNGLBLITFRAMEBUFFERPROC                             gl3wBlitFramebuffer;
PFNGLBLITNAMEDFRAMEBUFFERPROC                        gl3wBlitNamedFramebuffer;
PFNGLBUFFERDATAPROC                                  gl3wBufferData;
PFNGLBUFFERPAGECOMMITMENTARBPROC                     gl3wBufferPageCommitmentARB;
PFNGLBUFFERSTORAGEPROC                               gl3wBufferStorage;
PFNGLBUFFERSUBDATAPROC                               gl3wBufferSubData;
PFNGLCHECKFRAMEBUFFERSTATUSPROC                      gl3wCheckFramebufferStatus;
PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC                 gl3wCheckNamedFramebufferStatus;
PFNGLCLAMPCOLORPROC                                  gl3wClampColor;
PFNGLCLEARPROC                                       gl3wClear;
PFNGLCLEARBUFFERDATAPROC                             gl3wClearBufferData;
PFNGLCLEARBUFFERSUBDATAPROC                          gl3wClearBufferSubData;
PFNGLCLEARBUFFERFIPROC                               gl3wClearBufferfi;
PFNGLCLEARBUFFERFVPROC                               gl3wClearBufferfv;
PFNGLCLEARBUFFERIVPROC                               gl3wClearBufferiv;
PFNGLCLEARBUFFERUIVPROC                              gl3wClearBufferuiv;
PFNGLCLEARCOLORPROC                                  gl3wClearColor;
PFNGLCLEARDEPTHPROC                                  gl3wClearDepth;
PFNGLCLEARDEPTHFPROC                                 gl3wClearDepthf;
PFNGLCLEARNAMEDBUFFERDATAPROC                        gl3wClearNamedBufferData;
PFNGLCLEARNAMEDBUFFERSUBDATAPROC                     gl3wClearNamedBufferSubData;
PFNGLCLEARNAMEDFRAMEBUFFERFIPROC                     gl3wClearNamedFramebufferfi;
PFNGLCLEARNAMEDFRAMEBUFFERFVPROC                     gl3wClearNamedFramebufferfv;
PFNGLCLEARNAMEDFRAMEBUFFERIVPROC                     gl3wClearNamedFramebufferiv;
PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC                    gl3wClearNamedFramebufferuiv;
PFNGLCLEARSTENCILPROC                                gl3wClearStencil;
PFNGLCLEARTEXIMAGEPROC                               gl3wClearTexImage;
PFNGLCLEARTEXSUBIMAGEPROC                            gl3wClearTexSubImage;
PFNGLCLIENTWAITSYNCPROC                              gl3wClientWaitSync;
PFNGLCLIPCONTROLPROC                                 gl3wClipControl;
PFNGLCOLORMASKPROC                                   gl3wColorMask;
PFNGLCOLORMASKIPROC                                  gl3wColorMaski;
PFNGLCOMPILESHADERPROC                               gl3wCompileShader;
PFNGLCOMPILESHADERINCLUDEARBPROC                     gl3wCompileShaderIncludeARB;
PFNGLCOMPRESSEDTEXIMAGE1DPROC                        gl3wCompressedTexImage1D;
PFNGLCOMPRESSEDTEXIMAGE2DPROC                        gl3wCompressedTexImage2D;
PFNGLCOMPRESSEDTEXIMAGE3DPROC                        gl3wCompressedTexImage3D;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC                     gl3wCompressedTexSubImage1D;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC                     gl3wCompressedTexSubImage2D;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC                     gl3wCompressedTexSubImage3D;
PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC                 gl3wCompressedTextureSubImage1D;
PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC                 gl3wCompressedTextureSubImage2D;
PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC                 gl3wCompressedTextureSubImage3D;
PFNGLCOPYBUFFERSUBDATAPROC                           gl3wCopyBufferSubData;
PFNGLCOPYIMAGESUBDATAPROC                            gl3wCopyImageSubData;
PFNGLCOPYNAMEDBUFFERSUBDATAPROC                      gl3wCopyNamedBufferSubData;
PFNGLCOPYTEXIMAGE1DPROC                              gl3wCopyTexImage1D;
PFNGLCOPYTEXIMAGE2DPROC                              gl3wCopyTexImage2D;
PFNGLCOPYTEXSUBIMAGE1DPROC                           gl3wCopyTexSubImage1D;
PFNGLCOPYTEXSUBIMAGE2DPROC                           gl3wCopyTexSubImage2D;
PFNGLCOPYTEXSUBIMAGE3DPROC                           gl3wCopyTexSubImage3D;
PFNGLCOPYTEXTURESUBIMAGE1DPROC                       gl3wCopyTextureSubImage1D;
PFNGLCOPYTEXTURESUBIMAGE2DPROC                       gl3wCopyTextureSubImage2D;
PFNGLCOPYTEXTURESUBIMAGE3DPROC                       gl3wCopyTextureSubImage3D;
PFNGLCREATEBUFFERSPROC                               gl3wCreateBuffers;
PFNGLCREATEFRAMEBUFFERSPROC                          gl3wCreateFramebuffers;
PFNGLCREATEPROGRAMPROC                               gl3wCreateProgram;
PFNGLCREATEPROGRAMPIPELINESPROC                      gl3wCreateProgramPipelines;
PFNGLCREATEQUERIESPROC                               gl3wCreateQueries;
PFNGLCREATERENDERBUFFERSPROC                         gl3wCreateRenderbuffers;
PFNGLCREATESAMPLERSPROC                              gl3wCreateSamplers;
PFNGLCREATESHADERPROC                                gl3wCreateShader;
PFNGLCREATESHADERPROGRAMVPROC                        gl3wCreateShaderProgramv;
PFNGLCREATESYNCFROMCLEVENTARBPROC                    gl3wCreateSyncFromCLeventARB;
PFNGLCREATETEXTURESPROC                              gl3wCreateTextures;
PFNGLCREATETRANSFORMFEEDBACKSPROC                    gl3wCreateTransformFeedbacks;
PFNGLCREATEVERTEXARRAYSPROC                          gl3wCreateVertexArrays;
PFNGLCULLFACEPROC                                    gl3wCullFace;
PFNGLDEBUGMESSAGECALLBACKPROC                        gl3wDebugMessageCallback;
PFNGLDEBUGMESSAGECALLBACKARBPROC                     gl3wDebugMessageCallbackARB;
PFNGLDEBUGMESSAGECONTROLPROC                         gl3wDebugMessageControl;
PFNGLDEBUGMESSAGECONTROLARBPROC                      gl3wDebugMessageControlARB;
PFNGLDEBUGMESSAGEINSERTPROC                          gl3wDebugMessageInsert;
PFNGLDEBUGMESSAGEINSERTARBPROC                       gl3wDebugMessageInsertARB;
PFNGLDELETEBUFFERSPROC                               gl3wDeleteBuffers;
PFNGLDELETEFRAMEBUFFERSPROC                          gl3wDeleteFramebuffers;
PFNGLDELETENAMEDSTRINGARBPROC                        gl3wDeleteNamedStringARB;
PFNGLDELETEPROGRAMPROC                               gl3wDeleteProgram;
PFNGLDELETEPROGRAMPIPELINESPROC                      gl3wDeleteProgramPipelines;
PFNGLDELETEQUERIESPROC                               gl3wDeleteQueries;
PFNGLDELETERENDERBUFFERSPROC                         gl3wDeleteRenderbuffers;
PFNGLDELETESAMPLERSPROC                              gl3wDeleteSamplers;
PFNGLDELETESHADERPROC                                gl3wDeleteShader;
PFNGLDELETESYNCPROC                                  gl3wDeleteSync;
PFNGLDELETETEXTURESPROC                              gl3wDeleteTextures;
PFNGLDELETETRANSFORMFEEDBACKSPROC                    gl3wDeleteTransformFeedbacks;
PFNGLDELETEVERTEXARRAYSPROC                          gl3wDeleteVertexArrays;
PFNGLDEPTHFUNCPROC                                   gl3wDepthFunc;
PFNGLDEPTHMASKPROC                                   gl3wDepthMask;
PFNGLDEPTHRANGEPROC                                  gl3wDepthRange;
PFNGLDEPTHRANGEARRAYVPROC                            gl3wDepthRangeArrayv;
PFNGLDEPTHRANGEINDEXEDPROC                           gl3wDepthRangeIndexed;
PFNGLDEPTHRANGEFPROC                                 gl3wDepthRangef;
PFNGLDETACHSHADERPROC                                gl3wDetachShader;
PFNGLDISABLEPROC                                     gl3wDisable;
PFNGLDISABLEVERTEXARRAYATTRIBPROC                    gl3wDisableVertexArrayAttrib;
PFNGLDISABLEVERTEXATTRIBARRAYPROC                    gl3wDisableVertexAttribArray;
PFNGLDISABLEIPROC                                    gl3wDisablei;
PFNGLDISPATCHCOMPUTEPROC                             gl3wDispatchCompute;
PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC                 gl3wDispatchComputeGroupSizeARB;
PFNGLDISPATCHCOMPUTEINDIRECTPROC                     gl3wDispatchComputeIndirect;
PFNGLDRAWARRAYSPROC                                  gl3wDrawArrays;
PFNGLDRAWARRAYSINDIRECTPROC                          gl3wDrawArraysIndirect;
PFNGLDRAWARRAYSINSTANCEDPROC                         gl3wDrawArraysInstanced;
PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC             gl3wDrawArraysInstancedBaseInstance;
PFNGLDRAWBUFFERPROC                                  gl3wDrawBuffer;
PFNGLDRAWBUFFERSPROC                                 gl3wDrawBuffers;
PFNGLDRAWELEMENTSPROC                                gl3wDrawElements;
PFNGLDRAWELEMENTSBASEVERTEXPROC                      gl3wDrawElementsBaseVertex;
PFNGLDRAWELEMENTSINDIRECTPROC                        gl3wDrawElementsIndirect;
PFNGLDRAWELEMENTSINSTANCEDPROC                       gl3wDrawElementsInstanced;
PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC           gl3wDrawElementsInstancedBaseInstance;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC             gl3wDrawElementsInstancedBaseVertex;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC gl3wDrawElementsInstancedBaseVertexBaseInstance;
PFNGLDRAWRANGEELEMENTSPROC                           gl3wDrawRangeElements;
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC                 gl3wDrawRangeElementsBaseVertex;
PFNGLDRAWTRANSFORMFEEDBACKPROC                       gl3wDrawTransformFeedback;
PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC              gl3wDrawTransformFeedbackInstanced;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC                 gl3wDrawTransformFeedbackStream;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC        gl3wDrawTransformFeedbackStreamInstanced;
PFNGLENABLEPROC                                      gl3wEnable;
PFNGLENABLEVERTEXARRAYATTRIBPROC                     gl3wEnableVertexArrayAttrib;
PFNGLENABLEVERTEXATTRIBARRAYPROC                     gl3wEnableVertexAttribArray;
PFNGLENABLEIPROC                                     gl3wEnablei;
PFNGLENDCONDITIONALRENDERPROC                        gl3wEndConditionalRender;
PFNGLENDQUERYPROC                                    gl3wEndQuery;
PFNGLENDQUERYINDEXEDPROC                             gl3wEndQueryIndexed;
PFNGLENDTRANSFORMFEEDBACKPROC                        gl3wEndTransformFeedback;
PFNGLFENCESYNCPROC                                   gl3wFenceSync;
PFNGLFINISHPROC                                      gl3wFinish;
PFNGLFLUSHPROC                                       gl3wFlush;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC                      gl3wFlushMappedBufferRange;
PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC                 gl3wFlushMappedNamedBufferRange;
PFNGLFRAMEBUFFERPARAMETERIPROC                       gl3wFramebufferParameteri;
PFNGLFRAMEBUFFERRENDERBUFFERPROC                     gl3wFramebufferRenderbuffer;
PFNGLFRAMEBUFFERTEXTUREPROC                          gl3wFramebufferTexture;
PFNGLFRAMEBUFFERTEXTURE1DPROC                        gl3wFramebufferTexture1D;
PFNGLFRAMEBUFFERTEXTURE2DPROC                        gl3wFramebufferTexture2D;
PFNGLFRAMEBUFFERTEXTURE3DPROC                        gl3wFramebufferTexture3D;
PFNGLFRAMEBUFFERTEXTURELAYERPROC                     gl3wFramebufferTextureLayer;
PFNGLFRONTFACEPROC                                   gl3wFrontFace;
PFNGLGENBUFFERSPROC                                  gl3wGenBuffers;
PFNGLGENFRAMEBUFFERSPROC                             gl3wGenFramebuffers;
PFNGLGENPROGRAMPIPELINESPROC                         gl3wGenProgramPipelines;
PFNGLGENQUERIESPROC                                  gl3wGenQueries;
PFNGLGENRENDERBUFFERSPROC                            gl3wGenRenderbuffers;
PFNGLGENSAMPLERSPROC                                 gl3wGenSamplers;
PFNGLGENTEXTURESPROC                                 gl3wGenTextures;
PFNGLGENTRANSFORMFEEDBACKSPROC                       gl3wGenTransformFeedbacks;
PFNGLGENVERTEXARRAYSPROC                             gl3wGenVertexArrays;
PFNGLGENERATEMIPMAPPROC                              gl3wGenerateMipmap;
PFNGLGENERATETEXTUREMIPMAPPROC                       gl3wGenerateTextureMipmap;
PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC              gl3wGetActiveAtomicCounterBufferiv;
PFNGLGETACTIVEATTRIBPROC                             gl3wGetActiveAttrib;
PFNGLGETACTIVESUBROUTINENAMEPROC                     gl3wGetActiveSubroutineName;
PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC              gl3wGetActiveSubroutineUniformName;
PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC                gl3wGetActiveSubroutineUniformiv;
PFNGLGETACTIVEUNIFORMPROC                            gl3wGetActiveUniform;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC                   gl3wGetActiveUniformBlockName;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC                     gl3wGetActiveUniformBlockiv;
PFNGLGETACTIVEUNIFORMNAMEPROC                        gl3wGetActiveUniformName;
PFNGLGETACTIVEUNIFORMSIVPROC                         gl3wGetActiveUniformsiv;
PFNGLGETATTACHEDSHADERSPROC                          gl3wGetAttachedShaders;
PFNGLGETATTRIBLOCATIONPROC                           gl3wGetAttribLocation;
PFNGLGETBOOLEANI_VPROC                               gl3wGetBooleani_v;
PFNGLGETBOOLEANVPROC                                 gl3wGetBooleanv;
PFNGLGETBUFFERPARAMETERI64VPROC                      gl3wGetBufferParameteri64v;
PFNGLGETBUFFERPARAMETERIVPROC                        gl3wGetBufferParameteriv;
PFNGLGETBUFFERPOINTERVPROC                           gl3wGetBufferPointerv;
PFNGLGETBUFFERSUBDATAPROC                            gl3wGetBufferSubData;
PFNGLGETCOMPRESSEDTEXIMAGEPROC                       gl3wGetCompressedTexImage;
PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC                   gl3wGetCompressedTextureImage;
PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC                gl3wGetCompressedTextureSubImage;
PFNGLGETDEBUGMESSAGELOGPROC                          gl3wGetDebugMessageLog;
PFNGLGETDEBUGMESSAGELOGARBPROC                       gl3wGetDebugMessageLogARB;
PFNGLGETDOUBLEI_VPROC                                gl3wGetDoublei_v;
PFNGLGETDOUBLEVPROC                                  gl3wGetDoublev;
PFNGLGETERRORPROC                                    gl3wGetError;
PFNGLGETFLOATI_VPROC                                 gl3wGetFloati_v;
PFNGLGETFLOATVPROC                                   gl3wGetFloatv;
PFNGLGETFRAGDATAINDEXPROC                            gl3wGetFragDataIndex;
PFNGLGETFRAGDATALOCATIONPROC                         gl3wGetFragDataLocation;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC         gl3wGetFramebufferAttachmentParameteriv;
PFNGLGETFRAMEBUFFERPARAMETERIVPROC                   gl3wGetFramebufferParameteriv;
PFNGLGETGRAPHICSRESETSTATUSPROC                      gl3wGetGraphicsResetStatus;
PFNGLGETGRAPHICSRESETSTATUSARBPROC                   gl3wGetGraphicsResetStatusARB;
PFNGLGETIMAGEHANDLEARBPROC                           gl3wGetImageHandleARB;
PFNGLGETINTEGER64I_VPROC                             gl3wGetInteger64i_v;
PFNGLGETINTEGER64VPROC                               gl3wGetInteger64v;
PFNGLGETINTEGERI_VPROC                               gl3wGetIntegeri_v;
PFNGLGETINTEGERVPROC                                 gl3wGetIntegerv;
PFNGLGETINTERNALFORMATI64VPROC                       gl3wGetInternalformati64v;
PFNGLGETINTERNALFORMATIVPROC                         gl3wGetInternalformativ;
PFNGLGETMULTISAMPLEFVPROC                            gl3wGetMultisamplefv;
PFNGLGETNAMEDBUFFERPARAMETERI64VPROC                 gl3wGetNamedBufferParameteri64v;
PFNGLGETNAMEDBUFFERPARAMETERIVPROC                   gl3wGetNamedBufferParameteriv;
PFNGLGETNAMEDBUFFERPOINTERVPROC                      gl3wGetNamedBufferPointerv;
PFNGLGETNAMEDBUFFERSUBDATAPROC                       gl3wGetNamedBufferSubData;
PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC    gl3wGetNamedFramebufferAttachmentParameteriv;
PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC              gl3wGetNamedFramebufferParameteriv;
PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC             gl3wGetNamedRenderbufferParameteriv;
PFNGLGETNAMEDSTRINGARBPROC                           gl3wGetNamedStringARB;
PFNGLGETNAMEDSTRINGIVARBPROC                         gl3wGetNamedStringivARB;
PFNGLGETOBJECTLABELPROC                              gl3wGetObjectLabel;
PFNGLGETOBJECTPTRLABELPROC                           gl3wGetObjectPtrLabel;
PFNGLGETPOINTERVPROC                                 gl3wGetPointerv;
PFNGLGETPROGRAMBINARYPROC                            gl3wGetProgramBinary;
PFNGLGETPROGRAMINFOLOGPROC                           gl3wGetProgramInfoLog;
PFNGLGETPROGRAMINTERFACEIVPROC                       gl3wGetProgramInterfaceiv;
PFNGLGETPROGRAMPIPELINEINFOLOGPROC                   gl3wGetProgramPipelineInfoLog;
PFNGLGETPROGRAMPIPELINEIVPROC                        gl3wGetProgramPipelineiv;
PFNGLGETPROGRAMRESOURCEINDEXPROC                     gl3wGetProgramResourceIndex;
PFNGLGETPROGRAMRESOURCELOCATIONPROC                  gl3wGetProgramResourceLocation;
PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC             gl3wGetProgramResourceLocationIndex;
PFNGLGETPROGRAMRESOURCENAMEPROC                      gl3wGetProgramResourceName;
PFNGLGETPROGRAMRESOURCEIVPROC                        gl3wGetProgramResourceiv;
PFNGLGETPROGRAMSTAGEIVPROC                           gl3wGetProgramStageiv;
PFNGLGETPROGRAMIVPROC                                gl3wGetProgramiv;
PFNGLGETQUERYBUFFEROBJECTI64VPROC                    gl3wGetQueryBufferObjecti64v;
PFNGLGETQUERYBUFFEROBJECTIVPROC                      gl3wGetQueryBufferObjectiv;
PFNGLGETQUERYBUFFEROBJECTUI64VPROC                   gl3wGetQueryBufferObjectui64v;
PFNGLGETQUERYBUFFEROBJECTUIVPROC                     gl3wGetQueryBufferObjectuiv;
PFNGLGETQUERYINDEXEDIVPROC                           gl3wGetQueryIndexediv;
PFNGLGETQUERYOBJECTI64VPROC                          gl3wGetQueryObjecti64v;
PFNGLGETQUERYOBJECTIVPROC                            gl3wGetQueryObjectiv;
PFNGLGETQUERYOBJECTUI64VPROC                         gl3wGetQueryObjectui64v;
PFNGLGETQUERYOBJECTUIVPROC                           gl3wGetQueryObjectuiv;
PFNGLGETQUERYIVPROC                                  gl3wGetQueryiv;
PFNGLGETRENDERBUFFERPARAMETERIVPROC                  gl3wGetRenderbufferParameteriv;
PFNGLGETSAMPLERPARAMETERIIVPROC                      gl3wGetSamplerParameterIiv;
PFNGLGETSAMPLERPARAMETERIUIVPROC                     gl3wGetSamplerParameterIuiv;
PFNGLGETSAMPLERPARAMETERFVPROC                       gl3wGetSamplerParameterfv;
PFNGLGETSAMPLERPARAMETERIVPROC                       gl3wGetSamplerParameteriv;
PFNGLGETSHADERINFOLOGPROC                            gl3wGetShaderInfoLog;
PFNGLGETSHADERPRECISIONFORMATPROC                    gl3wGetShaderPrecisionFormat;
PFNGLGETSHADERSOURCEPROC                             gl3wGetShaderSource;
PFNGLGETSHADERIVPROC                                 gl3wGetShaderiv;
PFNGLGETSTRINGPROC                                   gl3wGetString;
PFNGLGETSTRINGIPROC                                  gl3wGetStringi;
PFNGLGETSUBROUTINEINDEXPROC                          gl3wGetSubroutineIndex;
PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC                gl3wGetSubroutineUniformLocation;
PFNGLGETSYNCIVPROC                                   gl3wGetSynciv;
PFNGLGETTEXIMAGEPROC                                 gl3wGetTexImage;
PFNGLGETTEXLEVELPARAMETERFVPROC                      gl3wGetTexLevelParameterfv;
PFNGLGETTEXLEVELPARAMETERIVPROC                      gl3wGetTexLevelParameteriv;
PFNGLGETTEXPARAMETERIIVPROC                          gl3wGetTexParameterIiv;
PFNGLGETTEXPARAMETERIUIVPROC                         gl3wGetTexParameterIuiv;
PFNGLGETTEXPARAMETERFVPROC                           gl3wGetTexParameterfv;
PFNGLGETTEXPARAMETERIVPROC                           gl3wGetTexParameteriv;
PFNGLGETTEXTUREHANDLEARBPROC                         gl3wGetTextureHandleARB;
PFNGLGETTEXTUREIMAGEPROC                             gl3wGetTextureImage;
PFNGLGETTEXTURELEVELPARAMETERFVPROC                  gl3wGetTextureLevelParameterfv;
PFNGLGETTEXTURELEVELPARAMETERIVPROC                  gl3wGetTextureLevelParameteriv;
PFNGLGETTEXTUREPARAMETERIIVPROC                      gl3wGetTextureParameterIiv;
PFNGLGETTEXTUREPARAMETERIUIVPROC                     gl3wGetTextureParameterIuiv;
PFNGLGETTEXTUREPARAMETERFVPROC                       gl3wGetTextureParameterfv;
PFNGLGETTEXTUREPARAMETERIVPROC                       gl3wGetTextureParameteriv;
PFNGLGETTEXTURESAMPLERHANDLEARBPROC                  gl3wGetTextureSamplerHandleARB;
PFNGLGETTEXTURESUBIMAGEPROC                          gl3wGetTextureSubImage;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC                 gl3wGetTransformFeedbackVarying;
PFNGLGETTRANSFORMFEEDBACKI64_VPROC                   gl3wGetTransformFeedbacki64_v;
PFNGLGETTRANSFORMFEEDBACKI_VPROC                     gl3wGetTransformFeedbacki_v;
PFNGLGETTRANSFORMFEEDBACKIVPROC                      gl3wGetTransformFeedbackiv;
PFNGLGETUNIFORMBLOCKINDEXPROC                        gl3wGetUniformBlockIndex;
PFNGLGETUNIFORMINDICESPROC                           gl3wGetUniformIndices;
PFNGLGETUNIFORMLOCATIONPROC                          gl3wGetUniformLocation;
PFNGLGETUNIFORMSUBROUTINEUIVPROC                     gl3wGetUniformSubroutineuiv;
PFNGLGETUNIFORMDVPROC                                gl3wGetUniformdv;
PFNGLGETUNIFORMFVPROC                                gl3wGetUniformfv;
PFNGLGETUNIFORMIVPROC                                gl3wGetUniformiv;
PFNGLGETUNIFORMUIVPROC                               gl3wGetUniformuiv;
PFNGLGETVERTEXARRAYINDEXED64IVPROC                   gl3wGetVertexArrayIndexed64iv;
PFNGLGETVERTEXARRAYINDEXEDIVPROC                     gl3wGetVertexArrayIndexediv;
PFNGLGETVERTEXARRAYIVPROC                            gl3wGetVertexArrayiv;
PFNGLGETVERTEXATTRIBIIVPROC                          gl3wGetVertexAttribIiv;
PFNGLGETVERTEXATTRIBIUIVPROC                         gl3wGetVertexAttribIuiv;
PFNGLGETVERTEXATTRIBLDVPROC                          gl3wGetVertexAttribLdv;
PFNGLGETVERTEXATTRIBLUI64VARBPROC                    gl3wGetVertexAttribLui64vARB;
PFNGLGETVERTEXATTRIBPOINTERVPROC                     gl3wGetVertexAttribPointerv;
PFNGLGETVERTEXATTRIBDVPROC                           gl3wGetVertexAttribdv;
PFNGLGETVERTEXATTRIBFVPROC                           gl3wGetVertexAttribfv;
PFNGLGETVERTEXATTRIBIVPROC                           gl3wGetVertexAttribiv;
PFNGLGETNCOMPRESSEDTEXIMAGEPROC                      gl3wGetnCompressedTexImage;
PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC                   gl3wGetnCompressedTexImageARB;
PFNGLGETNTEXIMAGEPROC                                gl3wGetnTexImage;
PFNGLGETNTEXIMAGEARBPROC                             gl3wGetnTexImageARB;
PFNGLGETNUNIFORMDVPROC                               gl3wGetnUniformdv;
PFNGLGETNUNIFORMDVARBPROC                            gl3wGetnUniformdvARB;
PFNGLGETNUNIFORMFVPROC                               gl3wGetnUniformfv;
PFNGLGETNUNIFORMFVARBPROC                            gl3wGetnUniformfvARB;
PFNGLGETNUNIFORMIVPROC                               gl3wGetnUniformiv;
PFNGLGETNUNIFORMIVARBPROC                            gl3wGetnUniformivARB;
PFNGLGETNUNIFORMUIVPROC                              gl3wGetnUniformuiv;
PFNGLGETNUNIFORMUIVARBPROC                           gl3wGetnUniformuivARB;
PFNGLHINTPROC                                        gl3wHint;
PFNGLINVALIDATEBUFFERDATAPROC                        gl3wInvalidateBufferData;
PFNGLINVALIDATEBUFFERSUBDATAPROC                     gl3wInvalidateBufferSubData;
PFNGLINVALIDATEFRAMEBUFFERPROC                       gl3wInvalidateFramebuffer;
PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC              gl3wInvalidateNamedFramebufferData;
PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC           gl3wInvalidateNamedFramebufferSubData;
PFNGLINVALIDATESUBFRAMEBUFFERPROC                    gl3wInvalidateSubFramebuffer;
PFNGLINVALIDATETEXIMAGEPROC                          gl3wInvalidateTexImage;
PFNGLINVALIDATETEXSUBIMAGEPROC                       gl3wInvalidateTexSubImage;
PFNGLISBUFFERPROC                                    gl3wIsBuffer;
PFNGLISENABLEDPROC                                   gl3wIsEnabled;
PFNGLISENABLEDIPROC                                  gl3wIsEnabledi;
PFNGLISFRAMEBUFFERPROC                               gl3wIsFramebuffer;
PFNGLISIMAGEHANDLERESIDENTARBPROC                    gl3wIsImageHandleResidentARB;
PFNGLISNAMEDSTRINGARBPROC                            gl3wIsNamedStringARB;
PFNGLISPROGRAMPROC                                   gl3wIsProgram;
PFNGLISPROGRAMPIPELINEPROC                           gl3wIsProgramPipeline;
PFNGLISQUERYPROC                                     gl3wIsQuery;
PFNGLISRENDERBUFFERPROC                              gl3wIsRenderbuffer;
PFNGLISSAMPLERPROC                                   gl3wIsSampler;
PFNGLISSHADERPROC                                    gl3wIsShader;
PFNGLISSYNCPROC                                      gl3wIsSync;
PFNGLISTEXTUREPROC                                   gl3wIsTexture;
PFNGLISTEXTUREHANDLERESIDENTARBPROC                  gl3wIsTextureHandleResidentARB;
PFNGLISTRANSFORMFEEDBACKPROC                         gl3wIsTransformFeedback;
PFNGLISVERTEXARRAYPROC                               gl3wIsVertexArray;
PFNGLLINEWIDTHPROC                                   gl3wLineWidth;
PFNGLLINKPROGRAMPROC                                 gl3wLinkProgram;
PFNGLLOGICOPPROC                                     gl3wLogicOp;
PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC               gl3wMakeImageHandleNonResidentARB;
PFNGLMAKEIMAGEHANDLERESIDENTARBPROC                  gl3wMakeImageHandleResidentARB;
PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC             gl3wMakeTextureHandleNonResidentARB;
PFNGLMAKETEXTUREHANDLERESIDENTARBPROC                gl3wMakeTextureHandleResidentARB;
PFNGLMAPBUFFERPROC                                   gl3wMapBuffer;
PFNGLMAPBUFFERRANGEPROC                              gl3wMapBufferRange;
PFNGLMAPNAMEDBUFFERPROC                              gl3wMapNamedBuffer;
PFNGLMAPNAMEDBUFFERRANGEPROC                         gl3wMapNamedBufferRange;
PFNGLMEMORYBARRIERPROC                               gl3wMemoryBarrier;
PFNGLMEMORYBARRIERBYREGIONPROC                       gl3wMemoryBarrierByRegion;
PFNGLMINSAMPLESHADINGPROC                            gl3wMinSampleShading;
PFNGLMINSAMPLESHADINGARBPROC                         gl3wMinSampleShadingARB;
PFNGLMULTIDRAWARRAYSPROC                             gl3wMultiDrawArrays;
PFNGLMULTIDRAWARRAYSINDIRECTPROC                     gl3wMultiDrawArraysIndirect;
PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC             gl3wMultiDrawArraysIndirectCountARB;
PFNGLMULTIDRAWELEMENTSPROC                           gl3wMultiDrawElements;
PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC                 gl3wMultiDrawElementsBaseVertex;
PFNGLMULTIDRAWELEMENTSINDIRECTPROC                   gl3wMultiDrawElementsIndirect;
PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC           gl3wMultiDrawElementsIndirectCountARB;
PFNGLNAMEDBUFFERDATAPROC                             gl3wNamedBufferData;
PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC                gl3wNamedBufferPageCommitmentARB;
PFNGLNAMEDBUFFERPAGECOMMITMENTEXTPROC                gl3wNamedBufferPageCommitmentEXT;
PFNGLNAMEDBUFFERSTORAGEPROC                          gl3wNamedBufferStorage;
PFNGLNAMEDBUFFERSUBDATAPROC                          gl3wNamedBufferSubData;
PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC                  gl3wNamedFramebufferDrawBuffer;
PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC                 gl3wNamedFramebufferDrawBuffers;
PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC                  gl3wNamedFramebufferParameteri;
PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC                  gl3wNamedFramebufferReadBuffer;
PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC                gl3wNamedFramebufferRenderbuffer;
PFNGLNAMEDFRAMEBUFFERTEXTUREPROC                     gl3wNamedFramebufferTexture;
PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC                gl3wNamedFramebufferTextureLayer;
PFNGLNAMEDRENDERBUFFERSTORAGEPROC                    gl3wNamedRenderbufferStorage;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC         gl3wNamedRenderbufferStorageMultisample;
PFNGLNAMEDSTRINGARBPROC                              gl3wNamedStringARB;
PFNGLOBJECTLABELPROC                                 gl3wObjectLabel;
PFNGLOBJECTPTRLABELPROC                              gl3wObjectPtrLabel;
PFNGLPATCHPARAMETERFVPROC                            gl3wPatchParameterfv;
PFNGLPATCHPARAMETERIPROC                             gl3wPatchParameteri;
PFNGLPAUSETRANSFORMFEEDBACKPROC                      gl3wPauseTransformFeedback;
PFNGLPIXELSTOREFPROC                                 gl3wPixelStoref;
PFNGLPIXELSTOREIPROC                                 gl3wPixelStorei;
PFNGLPOINTPARAMETERFPROC                             gl3wPointParameterf;
PFNGLPOINTPARAMETERFVPROC                            gl3wPointParameterfv;
PFNGLPOINTPARAMETERIPROC                             gl3wPointParameteri;
PFNGLPOINTPARAMETERIVPROC                            gl3wPointParameteriv;
PFNGLPOINTSIZEPROC                                   gl3wPointSize;
PFNGLPOLYGONMODEPROC                                 gl3wPolygonMode;
PFNGLPOLYGONOFFSETPROC                               gl3wPolygonOffset;
PFNGLPOPDEBUGGROUPPROC                               gl3wPopDebugGroup;
PFNGLPRIMITIVERESTARTINDEXPROC                       gl3wPrimitiveRestartIndex;
PFNGLPROGRAMBINARYPROC                               gl3wProgramBinary;
PFNGLPROGRAMPARAMETERIPROC                           gl3wProgramParameteri;
PFNGLPROGRAMUNIFORM1DPROC                            gl3wProgramUniform1d;
PFNGLPROGRAMUNIFORM1DVPROC                           gl3wProgramUniform1dv;
PFNGLPROGRAMUNIFORM1FPROC                            gl3wProgramUniform1f;
PFNGLPROGRAMUNIFORM1FVPROC                           gl3wProgramUniform1fv;
PFNGLPROGRAMUNIFORM1IPROC                            gl3wProgramUniform1i;
PFNGLPROGRAMUNIFORM1IVPROC                           gl3wProgramUniform1iv;
PFNGLPROGRAMUNIFORM1UIPROC                           gl3wProgramUniform1ui;
PFNGLPROGRAMUNIFORM1UIVPROC                          gl3wProgramUniform1uiv;
PFNGLPROGRAMUNIFORM2DPROC                            gl3wProgramUniform2d;
PFNGLPROGRAMUNIFORM2DVPROC                           gl3wProgramUniform2dv;
PFNGLPROGRAMUNIFORM2FPROC                            gl3wProgramUniform2f;
PFNGLPROGRAMUNIFORM2FVPROC                           gl3wProgramUniform2fv;
PFNGLPROGRAMUNIFORM2IPROC                            gl3wProgramUniform2i;
PFNGLPROGRAMUNIFORM2IVPROC                           gl3wProgramUniform2iv;
PFNGLPROGRAMUNIFORM2UIPROC                           gl3wProgramUniform2ui;
PFNGLPROGRAMUNIFORM2UIVPROC                          gl3wProgramUniform2uiv;
PFNGLPROGRAMUNIFORM3DPROC                            gl3wProgramUniform3d;
PFNGLPROGRAMUNIFORM3DVPROC                           gl3wProgramUniform3dv;
PFNGLPROGRAMUNIFORM3FPROC                            gl3wProgramUniform3f;
PFNGLPROGRAMUNIFORM3FVPROC                           gl3wProgramUniform3fv;
PFNGLPROGRAMUNIFORM3IPROC                            gl3wProgramUniform3i;
PFNGLPROGRAMUNIFORM3IVPROC                           gl3wProgramUniform3iv;
PFNGLPROGRAMUNIFORM3UIPROC                           gl3wProgramUniform3ui;
PFNGLPROGRAMUNIFORM3UIVPROC                          gl3wProgramUniform3uiv;
PFNGLPROGRAMUNIFORM4DPROC                            gl3wProgramUniform4d;
PFNGLPROGRAMUNIFORM4DVPROC                           gl3wProgramUniform4dv;
PFNGLPROGRAMUNIFORM4FPROC                            gl3wProgramUniform4f;
PFNGLPROGRAMUNIFORM4FVPROC                           gl3wProgramUniform4fv;
PFNGLPROGRAMUNIFORM4IPROC                            gl3wProgramUniform4i;
PFNGLPROGRAMUNIFORM4IVPROC                           gl3wProgramUniform4iv;
PFNGLPROGRAMUNIFORM4UIPROC                           gl3wProgramUniform4ui;
PFNGLPROGRAMUNIFORM4UIVPROC                          gl3wProgramUniform4uiv;
PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC                 gl3wProgramUniformHandleui64ARB;
PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC                gl3wProgramUniformHandleui64vARB;
PFNGLPROGRAMUNIFORMMATRIX2DVPROC                     gl3wProgramUniformMatrix2dv;
PFNGLPROGRAMUNIFORMMATRIX2FVPROC                     gl3wProgramUniformMatrix2fv;
PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC                   gl3wProgramUniformMatrix2x3dv;
PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC                   gl3wProgramUniformMatrix2x3fv;
PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC                   gl3wProgramUniformMatrix2x4dv;
PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC                   gl3wProgramUniformMatrix2x4fv;
PFNGLPROGRAMUNIFORMMATRIX3DVPROC                     gl3wProgramUniformMatrix3dv;
PFNGLPROGRAMUNIFORMMATRIX3FVPROC                     gl3wProgramUniformMatrix3fv;
PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC                   gl3wProgramUniformMatrix3x2dv;
PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC                   gl3wProgramUniformMatrix3x2fv;
PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC                   gl3wProgramUniformMatrix3x4dv;
PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC                   gl3wProgramUniformMatrix3x4fv;
PFNGLPROGRAMUNIFORMMATRIX4DVPROC                     gl3wProgramUniformMatrix4dv;
PFNGLPROGRAMUNIFORMMATRIX4FVPROC                     gl3wProgramUniformMatrix4fv;
PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC                   gl3wProgramUniformMatrix4x2dv;
PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC                   gl3wProgramUniformMatrix4x2fv;
PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC                   gl3wProgramUniformMatrix4x3dv;
PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC                   gl3wProgramUniformMatrix4x3fv;
PFNGLPROVOKINGVERTEXPROC                             gl3wProvokingVertex;
PFNGLPUSHDEBUGGROUPPROC                              gl3wPushDebugGroup;
PFNGLQUERYCOUNTERPROC                                gl3wQueryCounter;
PFNGLREADBUFFERPROC                                  gl3wReadBuffer;
PFNGLREADPIXELSPROC                                  gl3wReadPixels;
PFNGLREADNPIXELSPROC                                 gl3wReadnPixels;
PFNGLREADNPIXELSARBPROC                              gl3wReadnPixelsARB;
PFNGLRELEASESHADERCOMPILERPROC                       gl3wReleaseShaderCompiler;
PFNGLRENDERBUFFERSTORAGEPROC                         gl3wRenderbufferStorage;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC              gl3wRenderbufferStorageMultisample;
PFNGLRESUMETRANSFORMFEEDBACKPROC                     gl3wResumeTransformFeedback;
PFNGLSAMPLECOVERAGEPROC                              gl3wSampleCoverage;
PFNGLSAMPLEMASKIPROC                                 gl3wSampleMaski;
PFNGLSAMPLERPARAMETERIIVPROC                         gl3wSamplerParameterIiv;
PFNGLSAMPLERPARAMETERIUIVPROC                        gl3wSamplerParameterIuiv;
PFNGLSAMPLERPARAMETERFPROC                           gl3wSamplerParameterf;
PFNGLSAMPLERPARAMETERFVPROC                          gl3wSamplerParameterfv;
PFNGLSAMPLERPARAMETERIPROC                           gl3wSamplerParameteri;
PFNGLSAMPLERPARAMETERIVPROC                          gl3wSamplerParameteriv;
PFNGLSCISSORPROC                                     gl3wScissor;
PFNGLSCISSORARRAYVPROC                               gl3wScissorArrayv;
PFNGLSCISSORINDEXEDPROC                              gl3wScissorIndexed;
PFNGLSCISSORINDEXEDVPROC                             gl3wScissorIndexedv;
PFNGLSHADERBINARYPROC                                gl3wShaderBinary;
PFNGLSHADERSOURCEPROC                                gl3wShaderSource;
PFNGLSHADERSTORAGEBLOCKBINDINGPROC                   gl3wShaderStorageBlockBinding;
PFNGLSTENCILFUNCPROC                                 gl3wStencilFunc;
PFNGLSTENCILFUNCSEPARATEPROC                         gl3wStencilFuncSeparate;
PFNGLSTENCILMASKPROC                                 gl3wStencilMask;
PFNGLSTENCILMASKSEPARATEPROC                         gl3wStencilMaskSeparate;
PFNGLSTENCILOPPROC                                   gl3wStencilOp;
PFNGLSTENCILOPSEPARATEPROC                           gl3wStencilOpSeparate;
PFNGLTEXBUFFERPROC                                   gl3wTexBuffer;
PFNGLTEXBUFFERRANGEPROC                              gl3wTexBufferRange;
PFNGLTEXIMAGE1DPROC                                  gl3wTexImage1D;
PFNGLTEXIMAGE2DPROC                                  gl3wTexImage2D;
PFNGLTEXIMAGE2DMULTISAMPLEPROC                       gl3wTexImage2DMultisample;
PFNGLTEXIMAGE3DPROC                                  gl3wTexImage3D;
PFNGLTEXIMAGE3DMULTISAMPLEPROC                       gl3wTexImage3DMultisample;
PFNGLTEXPAGECOMMITMENTARBPROC                        gl3wTexPageCommitmentARB;
PFNGLTEXPARAMETERIIVPROC                             gl3wTexParameterIiv;
PFNGLTEXPARAMETERIUIVPROC                            gl3wTexParameterIuiv;
PFNGLTEXPARAMETERFPROC                               gl3wTexParameterf;
PFNGLTEXPARAMETERFVPROC                              gl3wTexParameterfv;
PFNGLTEXPARAMETERIPROC                               gl3wTexParameteri;
PFNGLTEXPARAMETERIVPROC                              gl3wTexParameteriv;
PFNGLTEXSTORAGE1DPROC                                gl3wTexStorage1D;
PFNGLTEXSTORAGE2DPROC                                gl3wTexStorage2D;
PFNGLTEXSTORAGE2DMULTISAMPLEPROC                     gl3wTexStorage2DMultisample;
PFNGLTEXSTORAGE3DPROC                                gl3wTexStorage3D;
PFNGLTEXSTORAGE3DMULTISAMPLEPROC                     gl3wTexStorage3DMultisample;
PFNGLTEXSUBIMAGE1DPROC                               gl3wTexSubImage1D;
PFNGLTEXSUBIMAGE2DPROC                               gl3wTexSubImage2D;
PFNGLTEXSUBIMAGE3DPROC                               gl3wTexSubImage3D;
PFNGLTEXTUREBARRIERPROC                              gl3wTextureBarrier;
PFNGLTEXTUREBUFFERPROC                               gl3wTextureBuffer;
PFNGLTEXTUREBUFFERRANGEPROC                          gl3wTextureBufferRange;
PFNGLTEXTUREPARAMETERIIVPROC                         gl3wTextureParameterIiv;
PFNGLTEXTUREPARAMETERIUIVPROC                        gl3wTextureParameterIuiv;
PFNGLTEXTUREPARAMETERFPROC                           gl3wTextureParameterf;
PFNGLTEXTUREPARAMETERFVPROC                          gl3wTextureParameterfv;
PFNGLTEXTUREPARAMETERIPROC                           gl3wTextureParameteri;
PFNGLTEXTUREPARAMETERIVPROC                          gl3wTextureParameteriv;
PFNGLTEXTURESTORAGE1DPROC                            gl3wTextureStorage1D;
PFNGLTEXTURESTORAGE2DPROC                            gl3wTextureStorage2D;
PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC                 gl3wTextureStorage2DMultisample;
PFNGLTEXTURESTORAGE3DPROC                            gl3wTextureStorage3D;
PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC                 gl3wTextureStorage3DMultisample;
PFNGLTEXTURESUBIMAGE1DPROC                           gl3wTextureSubImage1D;
PFNGLTEXTURESUBIMAGE2DPROC                           gl3wTextureSubImage2D;
PFNGLTEXTURESUBIMAGE3DPROC                           gl3wTextureSubImage3D;
PFNGLTEXTUREVIEWPROC                                 gl3wTextureView;
PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC                 gl3wTransformFeedbackBufferBase;
PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC                gl3wTransformFeedbackBufferRange;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC                   gl3wTransformFeedbackVaryings;
PFNGLUNIFORM1DPROC                                   gl3wUniform1d;
PFNGLUNIFORM1DVPROC                                  gl3wUniform1dv;
PFNGLUNIFORM1FPROC                                   gl3wUniform1f;
PFNGLUNIFORM1FVPROC                                  gl3wUniform1fv;
PFNGLUNIFORM1IPROC                                   gl3wUniform1i;
PFNGLUNIFORM1IVPROC                                  gl3wUniform1iv;
PFNGLUNIFORM1UIPROC                                  gl3wUniform1ui;
PFNGLUNIFORM1UIVPROC                                 gl3wUniform1uiv;
PFNGLUNIFORM2DPROC                                   gl3wUniform2d;
PFNGLUNIFORM2DVPROC                                  gl3wUniform2dv;
PFNGLUNIFORM2FPROC                                   gl3wUniform2f;
PFNGLUNIFORM2FVPROC                                  gl3wUniform2fv;
PFNGLUNIFORM2IPROC                                   gl3wUniform2i;
PFNGLUNIFORM2IVPROC                                  gl3wUniform2iv;
PFNGLUNIFORM2UIPROC                                  gl3wUniform2ui;
PFNGLUNIFORM2UIVPROC                                 gl3wUniform2uiv;
PFNGLUNIFORM3DPROC                                   gl3wUniform3d;
PFNGLUNIFORM3DVPROC                                  gl3wUniform3dv;
PFNGLUNIFORM3FPROC                                   gl3wUniform3f;
PFNGLUNIFORM3FVPROC                                  gl3wUniform3fv;
PFNGLUNIFORM3IPROC                                   gl3wUniform3i;
PFNGLUNIFORM3IVPROC                                  gl3wUniform3iv;
PFNGLUNIFORM3UIPROC                                  gl3wUniform3ui;
PFNGLUNIFORM3UIVPROC                                 gl3wUniform3uiv;
PFNGLUNIFORM4DPROC                                   gl3wUniform4d;
PFNGLUNIFORM4DVPROC                                  gl3wUniform4dv;
PFNGLUNIFORM4FPROC                                   gl3wUniform4f;
PFNGLUNIFORM4FVPROC                                  gl3wUniform4fv;
PFNGLUNIFORM4IPROC                                   gl3wUniform4i;
PFNGLUNIFORM4IVPROC                                  gl3wUniform4iv;
PFNGLUNIFORM4UIPROC                                  gl3wUniform4ui;
PFNGLUNIFORM4UIVPROC                                 gl3wUniform4uiv;
PFNGLUNIFORMBLOCKBINDINGPROC                         gl3wUniformBlockBinding;
PFNGLUNIFORMHANDLEUI64ARBPROC                        gl3wUniformHandleui64ARB;
PFNGLUNIFORMHANDLEUI64VARBPROC                       gl3wUniformHandleui64vARB;
PFNGLUNIFORMMATRIX2DVPROC                            gl3wUniformMatrix2dv;
PFNGLUNIFORMMATRIX2FVPROC                            gl3wUniformMatrix2fv;
PFNGLUNIFORMMATRIX2X3DVPROC                          gl3wUniformMatrix2x3dv;
PFNGLUNIFORMMATRIX2X3FVPROC                          gl3wUniformMatrix2x3fv;
PFNGLUNIFORMMATRIX2X4DVPROC                          gl3wUniformMatrix2x4dv;
PFNGLUNIFORMMATRIX2X4FVPROC                          gl3wUniformMatrix2x4fv;
PFNGLUNIFORMMATRIX3DVPROC                            gl3wUniformMatrix3dv;
PFNGLUNIFORMMATRIX3FVPROC                            gl3wUniformMatrix3fv;
PFNGLUNIFORMMATRIX3X2DVPROC                          gl3wUniformMatrix3x2dv;
PFNGLUNIFORMMATRIX3X2FVPROC                          gl3wUniformMatrix3x2fv;
PFNGLUNIFORMMATRIX3X4DVPROC                          gl3wUniformMatrix3x4dv;
PFNGLUNIFORMMATRIX3X4FVPROC                          gl3wUniformMatrix3x4fv;
PFNGLUNIFORMMATRIX4DVPROC                            gl3wUniformMatrix4dv;
PFNGLUNIFORMMATRIX4FVPROC                            gl3wUniformMatrix4fv;
PFNGLUNIFORMMATRIX4X2DVPROC                          gl3wUniformMatrix4x2dv;
PFNGLUNIFORMMATRIX4X2FVPROC                          gl3wUniformMatrix4x2fv;
PFNGLUNIFORMMATRIX4X3DVPROC                          gl3wUniformMatrix4x3dv;
PFNGLUNIFORMMATRIX4X3FVPROC                          gl3wUniformMatrix4x3fv;
PFNGLUNIFORMSUBROUTINESUIVPROC                       gl3wUniformSubroutinesuiv;
PFNGLUNMAPBUFFERPROC                                 gl3wUnmapBuffer;
PFNGLUNMAPNAMEDBUFFERPROC                            gl3wUnmapNamedBuffer;
PFNGLUSEPROGRAMPROC                                  gl3wUseProgram;
PFNGLUSEPROGRAMSTAGESPROC                            gl3wUseProgramStages;
PFNGLVALIDATEPROGRAMPROC                             gl3wValidateProgram;
PFNGLVALIDATEPROGRAMPIPELINEPROC                     gl3wValidateProgramPipeline;
PFNGLVERTEXARRAYATTRIBBINDINGPROC                    gl3wVertexArrayAttribBinding;
PFNGLVERTEXARRAYATTRIBFORMATPROC                     gl3wVertexArrayAttribFormat;
PFNGLVERTEXARRAYATTRIBIFORMATPROC                    gl3wVertexArrayAttribIFormat;
PFNGLVERTEXARRAYATTRIBLFORMATPROC                    gl3wVertexArrayAttribLFormat;
PFNGLVERTEXARRAYBINDINGDIVISORPROC                   gl3wVertexArrayBindingDivisor;
PFNGLVERTEXARRAYELEMENTBUFFERPROC                    gl3wVertexArrayElementBuffer;
PFNGLVERTEXARRAYVERTEXBUFFERPROC                     gl3wVertexArrayVertexBuffer;
PFNGLVERTEXARRAYVERTEXBUFFERSPROC                    gl3wVertexArrayVertexBuffers;
PFNGLVERTEXATTRIB1DPROC                              gl3wVertexAttrib1d;
PFNGLVERTEXATTRIB1DVPROC                             gl3wVertexAttrib1dv;
PFNGLVERTEXATTRIB1FPROC                              gl3wVertexAttrib1f;
PFNGLVERTEXATTRIB1FVPROC                             gl3wVertexAttrib1fv;
PFNGLVERTEXATTRIB1SPROC                              gl3wVertexAttrib1s;
PFNGLVERTEXATTRIB1SVPROC                             gl3wVertexAttrib1sv;
PFNGLVERTEXATTRIB2DPROC                              gl3wVertexAttrib2d;
PFNGLVERTEXATTRIB2DVPROC                             gl3wVertexAttrib2dv;
PFNGLVERTEXATTRIB2FPROC                              gl3wVertexAttrib2f;
PFNGLVERTEXATTRIB2FVPROC                             gl3wVertexAttrib2fv;
PFNGLVERTEXATTRIB2SPROC                              gl3wVertexAttrib2s;
PFNGLVERTEXATTRIB2SVPROC                             gl3wVertexAttrib2sv;
PFNGLVERTEXATTRIB3DPROC                              gl3wVertexAttrib3d;
PFNGLVERTEXATTRIB3DVPROC                             gl3wVertexAttrib3dv;
PFNGLVERTEXATTRIB3FPROC                              gl3wVertexAttrib3f;
PFNGLVERTEXATTRIB3FVPROC                             gl3wVertexAttrib3fv;
PFNGLVERTEXATTRIB3SPROC                              gl3wVertexAttrib3s;
PFNGLVERTEXATTRIB3SVPROC                             gl3wVertexAttrib3sv;
PFNGLVERTEXATTRIB4NBVPROC                            gl3wVertexAttrib4Nbv;
PFNGLVERTEXATTRIB4NIVPROC                            gl3wVertexAttrib4Niv;
PFNGLVERTEXATTRIB4NSVPROC                            gl3wVertexAttrib4Nsv;
PFNGLVERTEXATTRIB4NUBPROC                            gl3wVertexAttrib4Nub;
PFNGLVERTEXATTRIB4NUBVPROC                           gl3wVertexAttrib4Nubv;
PFNGLVERTEXATTRIB4NUIVPROC                           gl3wVertexAttrib4Nuiv;
PFNGLVERTEXATTRIB4NUSVPROC                           gl3wVertexAttrib4Nusv;
PFNGLVERTEXATTRIB4BVPROC                             gl3wVertexAttrib4bv;
PFNGLVERTEXATTRIB4DPROC                              gl3wVertexAttrib4d;
PFNGLVERTEXATTRIB4DVPROC                             gl3wVertexAttrib4dv;
PFNGLVERTEXATTRIB4FPROC                              gl3wVertexAttrib4f;
PFNGLVERTEXATTRIB4FVPROC                             gl3wVertexAttrib4fv;
PFNGLVERTEXATTRIB4IVPROC                             gl3wVertexAttrib4iv;
PFNGLVERTEXATTRIB4SPROC                              gl3wVertexAttrib4s;
PFNGLVERTEXATTRIB4SVPROC                             gl3wVertexAttrib4sv;
PFNGLVERTEXATTRIB4UBVPROC                            gl3wVertexAttrib4ubv;
PFNGLVERTEXATTRIB4UIVPROC                            gl3wVertexAttrib4uiv;
PFNGLVERTEXATTRIB4USVPROC                            gl3wVertexAttrib4usv;
PFNGLVERTEXATTRIBBINDINGPROC                         gl3wVertexAttribBinding;
PFNGLVERTEXATTRIBDIVISORPROC                         gl3wVertexAttribDivisor;
PFNGLVERTEXATTRIBFORMATPROC                          gl3wVertexAttribFormat;
PFNGLVERTEXATTRIBI1IPROC                             gl3wVertexAttribI1i;
PFNGLVERTEXATTRIBI1IVPROC                            gl3wVertexAttribI1iv;
PFNGLVERTEXATTRIBI1UIPROC                            gl3wVertexAttribI1ui;
PFNGLVERTEXATTRIBI1UIVPROC                           gl3wVertexAttribI1uiv;
PFNGLVERTEXATTRIBI2IPROC                             gl3wVertexAttribI2i;
PFNGLVERTEXATTRIBI2IVPROC                            gl3wVertexAttribI2iv;
PFNGLVERTEXATTRIBI2UIPROC                            gl3wVertexAttribI2ui;
PFNGLVERTEXATTRIBI2UIVPROC                           gl3wVertexAttribI2uiv;
PFNGLVERTEXATTRIBI3IPROC                             gl3wVertexAttribI3i;
PFNGLVERTEXATTRIBI3IVPROC                            gl3wVertexAttribI3iv;
PFNGLVERTEXATTRIBI3UIPROC                            gl3wVertexAttribI3ui;
PFNGLVERTEXATTRIBI3UIVPROC                           gl3wVertexAttribI3uiv;
PFNGLVERTEXATTRIBI4BVPROC                            gl3wVertexAttribI4bv;
PFNGLVERTEXATTRIBI4IPROC                             gl3wVertexAttribI4i;
PFNGLVERTEXATTRIBI4IVPROC                            gl3wVertexAttribI4iv;
PFNGLVERTEXATTRIBI4SVPROC                            gl3wVertexAttribI4sv;
PFNGLVERTEXATTRIBI4UBVPROC                           gl3wVertexAttribI4ubv;
PFNGLVERTEXATTRIBI4UIPROC                            gl3wVertexAttribI4ui;
PFNGLVERTEXATTRIBI4UIVPROC                           gl3wVertexAttribI4uiv;
PFNGLVERTEXATTRIBI4USVPROC                           gl3wVertexAttribI4usv;
PFNGLVERTEXATTRIBIFORMATPROC                         gl3wVertexAttribIFormat;
PFNGLVERTEXATTRIBIPOINTERPROC                        gl3wVertexAttribIPointer;
PFNGLVERTEXATTRIBL1DPROC                             gl3wVertexAttribL1d;
PFNGLVERTEXATTRIBL1DVPROC                            gl3wVertexAttribL1dv;
PFNGLVERTEXATTRIBL1UI64ARBPROC                       gl3wVertexAttribL1ui64ARB;
PFNGLVERTEXATTRIBL1UI64VARBPROC                      gl3wVertexAttribL1ui64vARB;
PFNGLVERTEXATTRIBL2DPROC                             gl3wVertexAttribL2d;
PFNGLVERTEXATTRIBL2DVPROC                            gl3wVertexAttribL2dv;
PFNGLVERTEXATTRIBL3DPROC                             gl3wVertexAttribL3d;
PFNGLVERTEXATTRIBL3DVPROC                            gl3wVertexAttribL3dv;
PFNGLVERTEXATTRIBL4DPROC                             gl3wVertexAttribL4d;
PFNGLVERTEXATTRIBL4DVPROC                            gl3wVertexAttribL4dv;
PFNGLVERTEXATTRIBLFORMATPROC                         gl3wVertexAttribLFormat;
PFNGLVERTEXATTRIBLPOINTERPROC                        gl3wVertexAttribLPointer;
PFNGLVERTEXATTRIBP1UIPROC                            gl3wVertexAttribP1ui;
PFNGLVERTEXATTRIBP1UIVPROC                           gl3wVertexAttribP1uiv;
PFNGLVERTEXATTRIBP2UIPROC                            gl3wVertexAttribP2ui;
PFNGLVERTEXATTRIBP2UIVPROC                           gl3wVertexAttribP2uiv;
PFNGLVERTEXATTRIBP3UIPROC                            gl3wVertexAttribP3ui;
PFNGLVERTEXATTRIBP3UIVPROC                           gl3wVertexAttribP3uiv;
PFNGLVERTEXATTRIBP4UIPROC                            gl3wVertexAttribP4ui;
PFNGLVERTEXATTRIBP4UIVPROC                           gl3wVertexAttribP4uiv;
PFNGLVERTEXATTRIBPOINTERPROC                         gl3wVertexAttribPointer;
PFNGLVERTEXBINDINGDIVISORPROC                        gl3wVertexBindingDivisor;
PFNGLVIEWPORTPROC                                    gl3wViewport;
PFNGLVIEWPORTARRAYVPROC                              gl3wViewportArrayv;
PFNGLVIEWPORTINDEXEDFPROC                            gl3wViewportIndexedf;
PFNGLVIEWPORTINDEXEDFVPROC                           gl3wViewportIndexedfv;
PFNGLWAITSYNCPROC                                    gl3wWaitSync;

static void load_procs(void)
{
	gl3wActiveShaderProgram = (PFNGLACTIVESHADERPROGRAMPROC) get_proc("glActiveShaderProgram");
	gl3wActiveTexture = (PFNGLACTIVETEXTUREPROC) get_proc("glActiveTexture");
	gl3wAttachShader = (PFNGLATTACHSHADERPROC) get_proc("glAttachShader");
	gl3wBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC) get_proc("glBeginConditionalRender");
	gl3wBeginQuery = (PFNGLBEGINQUERYPROC) get_proc("glBeginQuery");
	gl3wBeginQueryIndexed = (PFNGLBEGINQUERYINDEXEDPROC) get_proc("glBeginQueryIndexed");
	gl3wBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC) get_proc("glBeginTransformFeedback");
	gl3wBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC) get_proc("glBindAttribLocation");
	gl3wBindBuffer = (PFNGLBINDBUFFERPROC) get_proc("glBindBuffer");
	gl3wBindBufferBase = (PFNGLBINDBUFFERBASEPROC) get_proc("glBindBufferBase");
	gl3wBindBufferRange = (PFNGLBINDBUFFERRANGEPROC) get_proc("glBindBufferRange");
	gl3wBindBuffersBase = (PFNGLBINDBUFFERSBASEPROC) get_proc("glBindBuffersBase");
	gl3wBindBuffersRange = (PFNGLBINDBUFFERSRANGEPROC) get_proc("glBindBuffersRange");
	gl3wBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC) get_proc("glBindFragDataLocation");
	gl3wBindFragDataLocationIndexed = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC) get_proc("glBindFragDataLocationIndexed");
	gl3wBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) get_proc("glBindFramebuffer");
	gl3wBindImageTexture = (PFNGLBINDIMAGETEXTUREPROC) get_proc("glBindImageTexture");
	gl3wBindImageTextures = (PFNGLBINDIMAGETEXTURESPROC) get_proc("glBindImageTextures");
	gl3wBindProgramPipeline = (PFNGLBINDPROGRAMPIPELINEPROC) get_proc("glBindProgramPipeline");
	gl3wBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) get_proc("glBindRenderbuffer");
	gl3wBindSampler = (PFNGLBINDSAMPLERPROC) get_proc("glBindSampler");
	gl3wBindSamplers = (PFNGLBINDSAMPLERSPROC) get_proc("glBindSamplers");
	gl3wBindTexture = (PFNGLBINDTEXTUREPROC) get_proc("glBindTexture");
	gl3wBindTextureUnit = (PFNGLBINDTEXTUREUNITPROC) get_proc("glBindTextureUnit");
	gl3wBindTextures = (PFNGLBINDTEXTURESPROC) get_proc("glBindTextures");
	gl3wBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC) get_proc("glBindTransformFeedback");
	gl3wBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) get_proc("glBindVertexArray");
	gl3wBindVertexBuffer = (PFNGLBINDVERTEXBUFFERPROC) get_proc("glBindVertexBuffer");
	gl3wBindVertexBuffers = (PFNGLBINDVERTEXBUFFERSPROC) get_proc("glBindVertexBuffers");
	gl3wBlendColor = (PFNGLBLENDCOLORPROC) get_proc("glBlendColor");
	gl3wBlendEquation = (PFNGLBLENDEQUATIONPROC) get_proc("glBlendEquation");
	gl3wBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC) get_proc("glBlendEquationSeparate");
	gl3wBlendEquationSeparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC) get_proc("glBlendEquationSeparatei");
	gl3wBlendEquationSeparateiARB = (PFNGLBLENDEQUATIONSEPARATEIARBPROC) get_proc("glBlendEquationSeparateiARB");
	gl3wBlendEquationi = (PFNGLBLENDEQUATIONIPROC) get_proc("glBlendEquationi");
	gl3wBlendEquationiARB = (PFNGLBLENDEQUATIONIARBPROC) get_proc("glBlendEquationiARB");
	gl3wBlendFunc = (PFNGLBLENDFUNCPROC) get_proc("glBlendFunc");
	gl3wBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC) get_proc("glBlendFuncSeparate");
	gl3wBlendFuncSeparatei = (PFNGLBLENDFUNCSEPARATEIPROC) get_proc("glBlendFuncSeparatei");
	gl3wBlendFuncSeparateiARB = (PFNGLBLENDFUNCSEPARATEIARBPROC) get_proc("glBlendFuncSeparateiARB");
	gl3wBlendFunci = (PFNGLBLENDFUNCIPROC) get_proc("glBlendFunci");
	gl3wBlendFunciARB = (PFNGLBLENDFUNCIARBPROC) get_proc("glBlendFunciARB");
	gl3wBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC) get_proc("glBlitFramebuffer");
	gl3wBlitNamedFramebuffer = (PFNGLBLITNAMEDFRAMEBUFFERPROC) get_proc("glBlitNamedFramebuffer");
	gl3wBufferData = (PFNGLBUFFERDATAPROC) get_proc("glBufferData");
	gl3wBufferPageCommitmentARB = (PFNGLBUFFERPAGECOMMITMENTARBPROC) get_proc("glBufferPageCommitmentARB");
	gl3wBufferStorage = (PFNGLBUFFERSTORAGEPROC) get_proc("glBufferStorage");
	gl3wBufferSubData = (PFNGLBUFFERSUBDATAPROC) get_proc("glBufferSubData");
	gl3wCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) get_proc("glCheckFramebufferStatus");
	gl3wCheckNamedFramebufferStatus = (PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC) get_proc("glCheckNamedFramebufferStatus");
	gl3wClampColor = (PFNGLCLAMPCOLORPROC) get_proc("glClampColor");
	gl3wClear = (PFNGLCLEARPROC) get_proc("glClear");
	gl3wClearBufferData = (PFNGLCLEARBUFFERDATAPROC) get_proc("glClearBufferData");
	gl3wClearBufferSubData = (PFNGLCLEARBUFFERSUBDATAPROC) get_proc("glClearBufferSubData");
	gl3wClearBufferfi = (PFNGLCLEARBUFFERFIPROC) get_proc("glClearBufferfi");
	gl3wClearBufferfv = (PFNGLCLEARBUFFERFVPROC) get_proc("glClearBufferfv");
	gl3wClearBufferiv = (PFNGLCLEARBUFFERIVPROC) get_proc("glClearBufferiv");
	gl3wClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC) get_proc("glClearBufferuiv");
	gl3wClearColor = (PFNGLCLEARCOLORPROC) get_proc("glClearColor");
	gl3wClearDepth = (PFNGLCLEARDEPTHPROC) get_proc("glClearDepth");
	gl3wClearDepthf = (PFNGLCLEARDEPTHFPROC) get_proc("glClearDepthf");
	gl3wClearNamedBufferData = (PFNGLCLEARNAMEDBUFFERDATAPROC) get_proc("glClearNamedBufferData");
	gl3wClearNamedBufferSubData = (PFNGLCLEARNAMEDBUFFERSUBDATAPROC) get_proc("glClearNamedBufferSubData");
	gl3wClearNamedFramebufferfi = (PFNGLCLEARNAMEDFRAMEBUFFERFIPROC) get_proc("glClearNamedFramebufferfi");
	gl3wClearNamedFramebufferfv = (PFNGLCLEARNAMEDFRAMEBUFFERFVPROC) get_proc("glClearNamedFramebufferfv");
	gl3wClearNamedFramebufferiv = (PFNGLCLEARNAMEDFRAMEBUFFERIVPROC) get_proc("glClearNamedFramebufferiv");
	gl3wClearNamedFramebufferuiv = (PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC) get_proc("glClearNamedFramebufferuiv");
	gl3wClearStencil = (PFNGLCLEARSTENCILPROC) get_proc("glClearStencil");
	gl3wClearTexImage = (PFNGLCLEARTEXIMAGEPROC) get_proc("glClearTexImage");
	gl3wClearTexSubImage = (PFNGLCLEARTEXSUBIMAGEPROC) get_proc("glClearTexSubImage");
	gl3wClientWaitSync = (PFNGLCLIENTWAITSYNCPROC) get_proc("glClientWaitSync");
	gl3wClipControl = (PFNGLCLIPCONTROLPROC) get_proc("glClipControl");
	gl3wColorMask = (PFNGLCOLORMASKPROC) get_proc("glColorMask");
	gl3wColorMaski = (PFNGLCOLORMASKIPROC) get_proc("glColorMaski");
	gl3wCompileShader = (PFNGLCOMPILESHADERPROC) get_proc("glCompileShader");
	gl3wCompileShaderIncludeARB = (PFNGLCOMPILESHADERINCLUDEARBPROC) get_proc("glCompileShaderIncludeARB");
	gl3wCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC) get_proc("glCompressedTexImage1D");
	gl3wCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC) get_proc("glCompressedTexImage2D");
	gl3wCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC) get_proc("glCompressedTexImage3D");
	gl3wCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) get_proc("glCompressedTexSubImage1D");
	gl3wCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) get_proc("glCompressedTexSubImage2D");
	gl3wCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) get_proc("glCompressedTexSubImage3D");
	gl3wCompressedTextureSubImage1D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC) get_proc("glCompressedTextureSubImage1D");
	gl3wCompressedTextureSubImage2D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC) get_proc("glCompressedTextureSubImage2D");
	gl3wCompressedTextureSubImage3D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC) get_proc("glCompressedTextureSubImage3D");
	gl3wCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC) get_proc("glCopyBufferSubData");
	gl3wCopyImageSubData = (PFNGLCOPYIMAGESUBDATAPROC) get_proc("glCopyImageSubData");
	gl3wCopyNamedBufferSubData = (PFNGLCOPYNAMEDBUFFERSUBDATAPROC) get_proc("glCopyNamedBufferSubData");
	gl3wCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC) get_proc("glCopyTexImage1D");
	gl3wCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC) get_proc("glCopyTexImage2D");
	gl3wCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC) get_proc("glCopyTexSubImage1D");
	gl3wCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC) get_proc("glCopyTexSubImage2D");
	gl3wCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC) get_proc("glCopyTexSubImage3D");
	gl3wCopyTextureSubImage1D = (PFNGLCOPYTEXTURESUBIMAGE1DPROC) get_proc("glCopyTextureSubImage1D");
	gl3wCopyTextureSubImage2D = (PFNGLCOPYTEXTURESUBIMAGE2DPROC) get_proc("glCopyTextureSubImage2D");
	gl3wCopyTextureSubImage3D = (PFNGLCOPYTEXTURESUBIMAGE3DPROC) get_proc("glCopyTextureSubImage3D");
	gl3wCreateBuffers = (PFNGLCREATEBUFFERSPROC) get_proc("glCreateBuffers");
	gl3wCreateFramebuffers = (PFNGLCREATEFRAMEBUFFERSPROC) get_proc("glCreateFramebuffers");
	gl3wCreateProgram = (PFNGLCREATEPROGRAMPROC) get_proc("glCreateProgram");
	gl3wCreateProgramPipelines = (PFNGLCREATEPROGRAMPIPELINESPROC) get_proc("glCreateProgramPipelines");
	gl3wCreateQueries = (PFNGLCREATEQUERIESPROC) get_proc("glCreateQueries");
	gl3wCreateRenderbuffers = (PFNGLCREATERENDERBUFFERSPROC) get_proc("glCreateRenderbuffers");
	gl3wCreateSamplers = (PFNGLCREATESAMPLERSPROC) get_proc("glCreateSamplers");
	gl3wCreateShader = (PFNGLCREATESHADERPROC) get_proc("glCreateShader");
	gl3wCreateShaderProgramv = (PFNGLCREATESHADERPROGRAMVPROC) get_proc("glCreateShaderProgramv");
	gl3wCreateSyncFromCLeventARB = (PFNGLCREATESYNCFROMCLEVENTARBPROC) get_proc("glCreateSyncFromCLeventARB");
	gl3wCreateTextures = (PFNGLCREATETEXTURESPROC) get_proc("glCreateTextures");
	gl3wCreateTransformFeedbacks = (PFNGLCREATETRANSFORMFEEDBACKSPROC) get_proc("glCreateTransformFeedbacks");
	gl3wCreateVertexArrays = (PFNGLCREATEVERTEXARRAYSPROC) get_proc("glCreateVertexArrays");
	gl3wCullFace = (PFNGLCULLFACEPROC) get_proc("glCullFace");
	gl3wDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC) get_proc("glDebugMessageCallback");
	gl3wDebugMessageCallbackARB = (PFNGLDEBUGMESSAGECALLBACKARBPROC) get_proc("glDebugMessageCallbackARB");
	gl3wDebugMessageControl = (PFNGLDEBUGMESSAGECONTROLPROC) get_proc("glDebugMessageControl");
	gl3wDebugMessageControlARB = (PFNGLDEBUGMESSAGECONTROLARBPROC) get_proc("glDebugMessageControlARB");
	gl3wDebugMessageInsert = (PFNGLDEBUGMESSAGEINSERTPROC) get_proc("glDebugMessageInsert");
	gl3wDebugMessageInsertARB = (PFNGLDEBUGMESSAGEINSERTARBPROC) get_proc("glDebugMessageInsertARB");
	gl3wDeleteBuffers = (PFNGLDELETEBUFFERSPROC) get_proc("glDeleteBuffers");
	gl3wDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) get_proc("glDeleteFramebuffers");
	gl3wDeleteNamedStringARB = (PFNGLDELETENAMEDSTRINGARBPROC) get_proc("glDeleteNamedStringARB");
	gl3wDeleteProgram = (PFNGLDELETEPROGRAMPROC) get_proc("glDeleteProgram");
	gl3wDeleteProgramPipelines = (PFNGLDELETEPROGRAMPIPELINESPROC) get_proc("glDeleteProgramPipelines");
	gl3wDeleteQueries = (PFNGLDELETEQUERIESPROC) get_proc("glDeleteQueries");
	gl3wDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) get_proc("glDeleteRenderbuffers");
	gl3wDeleteSamplers = (PFNGLDELETESAMPLERSPROC) get_proc("glDeleteSamplers");
	gl3wDeleteShader = (PFNGLDELETESHADERPROC) get_proc("glDeleteShader");
	gl3wDeleteSync = (PFNGLDELETESYNCPROC) get_proc("glDeleteSync");
	gl3wDeleteTextures = (PFNGLDELETETEXTURESPROC) get_proc("glDeleteTextures");
	gl3wDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC) get_proc("glDeleteTransformFeedbacks");
	gl3wDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) get_proc("glDeleteVertexArrays");
	gl3wDepthFunc = (PFNGLDEPTHFUNCPROC) get_proc("glDepthFunc");
	gl3wDepthMask = (PFNGLDEPTHMASKPROC) get_proc("glDepthMask");
	gl3wDepthRange = (PFNGLDEPTHRANGEPROC) get_proc("glDepthRange");
	gl3wDepthRangeArrayv = (PFNGLDEPTHRANGEARRAYVPROC) get_proc("glDepthRangeArrayv");
	gl3wDepthRangeIndexed = (PFNGLDEPTHRANGEINDEXEDPROC) get_proc("glDepthRangeIndexed");
	gl3wDepthRangef = (PFNGLDEPTHRANGEFPROC) get_proc("glDepthRangef");
	gl3wDetachShader = (PFNGLDETACHSHADERPROC) get_proc("glDetachShader");
	gl3wDisable = (PFNGLDISABLEPROC) get_proc("glDisable");
	gl3wDisableVertexArrayAttrib = (PFNGLDISABLEVERTEXARRAYATTRIBPROC) get_proc("glDisableVertexArrayAttrib");
	gl3wDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) get_proc("glDisableVertexAttribArray");
	gl3wDisablei = (PFNGLDISABLEIPROC) get_proc("glDisablei");
	gl3wDispatchCompute = (PFNGLDISPATCHCOMPUTEPROC) get_proc("glDispatchCompute");
	gl3wDispatchComputeGroupSizeARB = (PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC) get_proc("glDispatchComputeGroupSizeARB");
	gl3wDispatchComputeIndirect = (PFNGLDISPATCHCOMPUTEINDIRECTPROC) get_proc("glDispatchComputeIndirect");
	gl3wDrawArrays = (PFNGLDRAWARRAYSPROC) get_proc("glDrawArrays");
	gl3wDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC) get_proc("glDrawArraysIndirect");
	gl3wDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC) get_proc("glDrawArraysInstanced");
	gl3wDrawArraysInstancedBaseInstance = (PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC) get_proc("glDrawArraysInstancedBaseInstance");
	gl3wDrawBuffer = (PFNGLDRAWBUFFERPROC) get_proc("glDrawBuffer");
	gl3wDrawBuffers = (PFNGLDRAWBUFFERSPROC) get_proc("glDrawBuffers");
	gl3wDrawElements = (PFNGLDRAWELEMENTSPROC) get_proc("glDrawElements");
	gl3wDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC) get_proc("glDrawElementsBaseVertex");
	gl3wDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC) get_proc("glDrawElementsIndirect");
	gl3wDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC) get_proc("glDrawElementsInstanced");
	gl3wDrawElementsInstancedBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC) get_proc("glDrawElementsInstancedBaseInstance");
	gl3wDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) get_proc("glDrawElementsInstancedBaseVertex");
	gl3wDrawElementsInstancedBaseVertexBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC) get_proc("glDrawElementsInstancedBaseVertexBaseInstance");
	gl3wDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC) get_proc("glDrawRangeElements");
	gl3wDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) get_proc("glDrawRangeElementsBaseVertex");
	gl3wDrawTransformFeedback = (PFNGLDRAWTRANSFORMFEEDBACKPROC) get_proc("glDrawTransformFeedback");
	gl3wDrawTransformFeedbackInstanced = (PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC) get_proc("glDrawTransformFeedbackInstanced");
	gl3wDrawTransformFeedbackStream = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC) get_proc("glDrawTransformFeedbackStream");
	gl3wDrawTransformFeedbackStreamInstanced = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC) get_proc("glDrawTransformFeedbackStreamInstanced");
	gl3wEnable = (PFNGLENABLEPROC) get_proc("glEnable");
	gl3wEnableVertexArrayAttrib = (PFNGLENABLEVERTEXARRAYATTRIBPROC) get_proc("glEnableVertexArrayAttrib");
	gl3wEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) get_proc("glEnableVertexAttribArray");
	gl3wEnablei = (PFNGLENABLEIPROC) get_proc("glEnablei");
	gl3wEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC) get_proc("glEndConditionalRender");
	gl3wEndQuery = (PFNGLENDQUERYPROC) get_proc("glEndQuery");
	gl3wEndQueryIndexed = (PFNGLENDQUERYINDEXEDPROC) get_proc("glEndQueryIndexed");
	gl3wEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC) get_proc("glEndTransformFeedback");
	gl3wFenceSync = (PFNGLFENCESYNCPROC) get_proc("glFenceSync");
	gl3wFinish = (PFNGLFINISHPROC) get_proc("glFinish");
	gl3wFlush = (PFNGLFLUSHPROC) get_proc("glFlush");
	gl3wFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC) get_proc("glFlushMappedBufferRange");
	gl3wFlushMappedNamedBufferRange = (PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC) get_proc("glFlushMappedNamedBufferRange");
	gl3wFramebufferParameteri = (PFNGLFRAMEBUFFERPARAMETERIPROC) get_proc("glFramebufferParameteri");
	gl3wFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) get_proc("glFramebufferRenderbuffer");
	gl3wFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC) get_proc("glFramebufferTexture");
	gl3wFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) get_proc("glFramebufferTexture1D");
	gl3wFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) get_proc("glFramebufferTexture2D");
	gl3wFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) get_proc("glFramebufferTexture3D");
	gl3wFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC) get_proc("glFramebufferTextureLayer");
	gl3wFrontFace = (PFNGLFRONTFACEPROC) get_proc("glFrontFace");
	gl3wGenBuffers = (PFNGLGENBUFFERSPROC) get_proc("glGenBuffers");
	gl3wGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) get_proc("glGenFramebuffers");
	gl3wGenProgramPipelines = (PFNGLGENPROGRAMPIPELINESPROC) get_proc("glGenProgramPipelines");
	gl3wGenQueries = (PFNGLGENQUERIESPROC) get_proc("glGenQueries");
	gl3wGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) get_proc("glGenRenderbuffers");
	gl3wGenSamplers = (PFNGLGENSAMPLERSPROC) get_proc("glGenSamplers");
	gl3wGenTextures = (PFNGLGENTEXTURESPROC) get_proc("glGenTextures");
	gl3wGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC) get_proc("glGenTransformFeedbacks");
	gl3wGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) get_proc("glGenVertexArrays");
	gl3wGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) get_proc("glGenerateMipmap");
	gl3wGenerateTextureMipmap = (PFNGLGENERATETEXTUREMIPMAPPROC) get_proc("glGenerateTextureMipmap");
	gl3wGetActiveAtomicCounterBufferiv = (PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC) get_proc("glGetActiveAtomicCounterBufferiv");
	gl3wGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC) get_proc("glGetActiveAttrib");
	gl3wGetActiveSubroutineName = (PFNGLGETACTIVESUBROUTINENAMEPROC) get_proc("glGetActiveSubroutineName");
	gl3wGetActiveSubroutineUniformName = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC) get_proc("glGetActiveSubroutineUniformName");
	gl3wGetActiveSubroutineUniformiv = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC) get_proc("glGetActiveSubroutineUniformiv");
	gl3wGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC) get_proc("glGetActiveUniform");
	gl3wGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) get_proc("glGetActiveUniformBlockName");
	gl3wGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC) get_proc("glGetActiveUniformBlockiv");
	gl3wGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC) get_proc("glGetActiveUniformName");
	gl3wGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC) get_proc("glGetActiveUniformsiv");
	gl3wGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC) get_proc("glGetAttachedShaders");
	gl3wGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC) get_proc("glGetAttribLocation");
	gl3wGetBooleani_v = (PFNGLGETBOOLEANI_VPROC) get_proc("glGetBooleani_v");
	gl3wGetBooleanv = (PFNGLGETBOOLEANVPROC) get_proc("glGetBooleanv");
	gl3wGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC) get_proc("glGetBufferParameteri64v");
	gl3wGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC) get_proc("glGetBufferParameteriv");
	gl3wGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC) get_proc("glGetBufferPointerv");
	gl3wGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC) get_proc("glGetBufferSubData");
	gl3wGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC) get_proc("glGetCompressedTexImage");
	gl3wGetCompressedTextureImage = (PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC) get_proc("glGetCompressedTextureImage");
	gl3wGetCompressedTextureSubImage = (PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC) get_proc("glGetCompressedTextureSubImage");
	gl3wGetDebugMessageLog = (PFNGLGETDEBUGMESSAGELOGPROC) get_proc("glGetDebugMessageLog");
	gl3wGetDebugMessageLogARB = (PFNGLGETDEBUGMESSAGELOGARBPROC) get_proc("glGetDebugMessageLogARB");
	gl3wGetDoublei_v = (PFNGLGETDOUBLEI_VPROC) get_proc("glGetDoublei_v");
	gl3wGetDoublev = (PFNGLGETDOUBLEVPROC) get_proc("glGetDoublev");
	gl3wGetError = (PFNGLGETERRORPROC) get_proc("glGetError");
	gl3wGetFloati_v = (PFNGLGETFLOATI_VPROC) get_proc("glGetFloati_v");
	gl3wGetFloatv = (PFNGLGETFLOATVPROC) get_proc("glGetFloatv");
	gl3wGetFragDataIndex = (PFNGLGETFRAGDATAINDEXPROC) get_proc("glGetFragDataIndex");
	gl3wGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC) get_proc("glGetFragDataLocation");
	gl3wGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) get_proc("glGetFramebufferAttachmentParameteriv");
	gl3wGetFramebufferParameteriv = (PFNGLGETFRAMEBUFFERPARAMETERIVPROC) get_proc("glGetFramebufferParameteriv");
	gl3wGetGraphicsResetStatus = (PFNGLGETGRAPHICSRESETSTATUSPROC) get_proc("glGetGraphicsResetStatus");
	gl3wGetGraphicsResetStatusARB = (PFNGLGETGRAPHICSRESETSTATUSARBPROC) get_proc("glGetGraphicsResetStatusARB");
	gl3wGetImageHandleARB = (PFNGLGETIMAGEHANDLEARBPROC) get_proc("glGetImageHandleARB");
	gl3wGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC) get_proc("glGetInteger64i_v");
	gl3wGetInteger64v = (PFNGLGETINTEGER64VPROC) get_proc("glGetInteger64v");
	gl3wGetIntegeri_v = (PFNGLGETINTEGERI_VPROC) get_proc("glGetIntegeri_v");
	gl3wGetIntegerv = (PFNGLGETINTEGERVPROC) get_proc("glGetIntegerv");
	gl3wGetInternalformati64v = (PFNGLGETINTERNALFORMATI64VPROC) get_proc("glGetInternalformati64v");
	gl3wGetInternalformativ = (PFNGLGETINTERNALFORMATIVPROC) get_proc("glGetInternalformativ");
	gl3wGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC) get_proc("glGetMultisamplefv");
	gl3wGetNamedBufferParameteri64v = (PFNGLGETNAMEDBUFFERPARAMETERI64VPROC) get_proc("glGetNamedBufferParameteri64v");
	gl3wGetNamedBufferParameteriv = (PFNGLGETNAMEDBUFFERPARAMETERIVPROC) get_proc("glGetNamedBufferParameteriv");
	gl3wGetNamedBufferPointerv = (PFNGLGETNAMEDBUFFERPOINTERVPROC) get_proc("glGetNamedBufferPointerv");
	gl3wGetNamedBufferSubData = (PFNGLGETNAMEDBUFFERSUBDATAPROC) get_proc("glGetNamedBufferSubData");
	gl3wGetNamedFramebufferAttachmentParameteriv = (PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC) get_proc("glGetNamedFramebufferAttachmentParameteriv");
	gl3wGetNamedFramebufferParameteriv = (PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC) get_proc("glGetNamedFramebufferParameteriv");
	gl3wGetNamedRenderbufferParameteriv = (PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC) get_proc("glGetNamedRenderbufferParameteriv");
	gl3wGetNamedStringARB = (PFNGLGETNAMEDSTRINGARBPROC) get_proc("glGetNamedStringARB");
	gl3wGetNamedStringivARB = (PFNGLGETNAMEDSTRINGIVARBPROC) get_proc("glGetNamedStringivARB");
	gl3wGetObjectLabel = (PFNGLGETOBJECTLABELPROC) get_proc("glGetObjectLabel");
	gl3wGetObjectPtrLabel = (PFNGLGETOBJECTPTRLABELPROC) get_proc("glGetObjectPtrLabel");
	gl3wGetPointerv = (PFNGLGETPOINTERVPROC) get_proc("glGetPointerv");
	gl3wGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC) get_proc("glGetProgramBinary");
	gl3wGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) get_proc("glGetProgramInfoLog");
	gl3wGetProgramInterfaceiv = (PFNGLGETPROGRAMINTERFACEIVPROC) get_proc("glGetProgramInterfaceiv");
	gl3wGetProgramPipelineInfoLog = (PFNGLGETPROGRAMPIPELINEINFOLOGPROC) get_proc("glGetProgramPipelineInfoLog");
	gl3wGetProgramPipelineiv = (PFNGLGETPROGRAMPIPELINEIVPROC) get_proc("glGetProgramPipelineiv");
	gl3wGetProgramResourceIndex = (PFNGLGETPROGRAMRESOURCEINDEXPROC) get_proc("glGetProgramResourceIndex");
	gl3wGetProgramResourceLocation = (PFNGLGETPROGRAMRESOURCELOCATIONPROC) get_proc("glGetProgramResourceLocation");
	gl3wGetProgramResourceLocationIndex = (PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC) get_proc("glGetProgramResourceLocationIndex");
	gl3wGetProgramResourceName = (PFNGLGETPROGRAMRESOURCENAMEPROC) get_proc("glGetProgramResourceName");
	gl3wGetProgramResourceiv = (PFNGLGETPROGRAMRESOURCEIVPROC) get_proc("glGetProgramResourceiv");
	gl3wGetProgramStageiv = (PFNGLGETPROGRAMSTAGEIVPROC) get_proc("glGetProgramStageiv");
	gl3wGetProgramiv = (PFNGLGETPROGRAMIVPROC) get_proc("glGetProgramiv");
	gl3wGetQueryBufferObjecti64v = (PFNGLGETQUERYBUFFEROBJECTI64VPROC) get_proc("glGetQueryBufferObjecti64v");
	gl3wGetQueryBufferObjectiv = (PFNGLGETQUERYBUFFEROBJECTIVPROC) get_proc("glGetQueryBufferObjectiv");
	gl3wGetQueryBufferObjectui64v = (PFNGLGETQUERYBUFFEROBJECTUI64VPROC) get_proc("glGetQueryBufferObjectui64v");
	gl3wGetQueryBufferObjectuiv = (PFNGLGETQUERYBUFFEROBJECTUIVPROC) get_proc("glGetQueryBufferObjectuiv");
	gl3wGetQueryIndexediv = (PFNGLGETQUERYINDEXEDIVPROC) get_proc("glGetQueryIndexediv");
	gl3wGetQueryObjecti64v = (PFNGLGETQUERYOBJECTI64VPROC) get_proc("glGetQueryObjecti64v");
	gl3wGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC) get_proc("glGetQueryObjectiv");
	gl3wGetQueryObjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC) get_proc("glGetQueryObjectui64v");
	gl3wGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC) get_proc("glGetQueryObjectuiv");
	gl3wGetQueryiv = (PFNGLGETQUERYIVPROC) get_proc("glGetQueryiv");
	gl3wGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) get_proc("glGetRenderbufferParameteriv");
	gl3wGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC) get_proc("glGetSamplerParameterIiv");
	gl3wGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC) get_proc("glGetSamplerParameterIuiv");
	gl3wGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC) get_proc("glGetSamplerParameterfv");
	gl3wGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC) get_proc("glGetSamplerParameteriv");
	gl3wGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) get_proc("glGetShaderInfoLog");
	gl3wGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC) get_proc("glGetShaderPrecisionFormat");
	gl3wGetShaderSource = (PFNGLGETSHADERSOURCEPROC) get_proc("glGetShaderSource");
	gl3wGetShaderiv = (PFNGLGETSHADERIVPROC) get_proc("glGetShaderiv");
	gl3wGetString = (PFNGLGETSTRINGPROC) get_proc("glGetString");
	gl3wGetStringi = (PFNGLGETSTRINGIPROC) get_proc("glGetStringi");
	gl3wGetSubroutineIndex = (PFNGLGETSUBROUTINEINDEXPROC) get_proc("glGetSubroutineIndex");
	gl3wGetSubroutineUniformLocation = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC) get_proc("glGetSubroutineUniformLocation");
	gl3wGetSynciv = (PFNGLGETSYNCIVPROC) get_proc("glGetSynciv");
	gl3wGetTexImage = (PFNGLGETTEXIMAGEPROC) get_proc("glGetTexImage");
	gl3wGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC) get_proc("glGetTexLevelParameterfv");
	gl3wGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC) get_proc("glGetTexLevelParameteriv");
	gl3wGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC) get_proc("glGetTexParameterIiv");
	gl3wGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC) get_proc("glGetTexParameterIuiv");
	gl3wGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC) get_proc("glGetTexParameterfv");
	gl3wGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC) get_proc("glGetTexParameteriv");
	gl3wGetTextureHandleARB = (PFNGLGETTEXTUREHANDLEARBPROC) get_proc("glGetTextureHandleARB");
	gl3wGetTextureImage = (PFNGLGETTEXTUREIMAGEPROC) get_proc("glGetTextureImage");
	gl3wGetTextureLevelParameterfv = (PFNGLGETTEXTURELEVELPARAMETERFVPROC) get_proc("glGetTextureLevelParameterfv");
	gl3wGetTextureLevelParameteriv = (PFNGLGETTEXTURELEVELPARAMETERIVPROC) get_proc("glGetTextureLevelParameteriv");
	gl3wGetTextureParameterIiv = (PFNGLGETTEXTUREPARAMETERIIVPROC) get_proc("glGetTextureParameterIiv");
	gl3wGetTextureParameterIuiv = (PFNGLGETTEXTUREPARAMETERIUIVPROC) get_proc("glGetTextureParameterIuiv");
	gl3wGetTextureParameterfv = (PFNGLGETTEXTUREPARAMETERFVPROC) get_proc("glGetTextureParameterfv");
	gl3wGetTextureParameteriv = (PFNGLGETTEXTUREPARAMETERIVPROC) get_proc("glGetTextureParameteriv");
	gl3wGetTextureSamplerHandleARB = (PFNGLGETTEXTURESAMPLERHANDLEARBPROC) get_proc("glGetTextureSamplerHandleARB");
	gl3wGetTextureSubImage = (PFNGLGETTEXTURESUBIMAGEPROC) get_proc("glGetTextureSubImage");
	gl3wGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) get_proc("glGetTransformFeedbackVarying");
	gl3wGetTransformFeedbacki64_v = (PFNGLGETTRANSFORMFEEDBACKI64_VPROC) get_proc("glGetTransformFeedbacki64_v");
	gl3wGetTransformFeedbacki_v = (PFNGLGETTRANSFORMFEEDBACKI_VPROC) get_proc("glGetTransformFeedbacki_v");
	gl3wGetTransformFeedbackiv = (PFNGLGETTRANSFORMFEEDBACKIVPROC) get_proc("glGetTransformFeedbackiv");
	gl3wGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC) get_proc("glGetUniformBlockIndex");
	gl3wGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC) get_proc("glGetUniformIndices");
	gl3wGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) get_proc("glGetUniformLocation");
	gl3wGetUniformSubroutineuiv = (PFNGLGETUNIFORMSUBROUTINEUIVPROC) get_proc("glGetUniformSubroutineuiv");
	gl3wGetUniformdv = (PFNGLGETUNIFORMDVPROC) get_proc("glGetUniformdv");
	gl3wGetUniformfv = (PFNGLGETUNIFORMFVPROC) get_proc("glGetUniformfv");
	gl3wGetUniformiv = (PFNGLGETUNIFORMIVPROC) get_proc("glGetUniformiv");
	gl3wGetUniformuiv = (PFNGLGETUNIFORMUIVPROC) get_proc("glGetUniformuiv");
	gl3wGetVertexArrayIndexed64iv = (PFNGLGETVERTEXARRAYINDEXED64IVPROC) get_proc("glGetVertexArrayIndexed64iv");
	gl3wGetVertexArrayIndexediv = (PFNGLGETVERTEXARRAYINDEXEDIVPROC) get_proc("glGetVertexArrayIndexediv");
	gl3wGetVertexArrayiv = (PFNGLGETVERTEXARRAYIVPROC) get_proc("glGetVertexArrayiv");
	gl3wGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC) get_proc("glGetVertexAttribIiv");
	gl3wGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC) get_proc("glGetVertexAttribIuiv");
	gl3wGetVertexAttribLdv = (PFNGLGETVERTEXATTRIBLDVPROC) get_proc("glGetVertexAttribLdv");
	gl3wGetVertexAttribLui64vARB = (PFNGLGETVERTEXATTRIBLUI64VARBPROC) get_proc("glGetVertexAttribLui64vARB");
	gl3wGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC) get_proc("glGetVertexAttribPointerv");
	gl3wGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC) get_proc("glGetVertexAttribdv");
	gl3wGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC) get_proc("glGetVertexAttribfv");
	gl3wGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC) get_proc("glGetVertexAttribiv");
	gl3wGetnCompressedTexImage = (PFNGLGETNCOMPRESSEDTEXIMAGEPROC) get_proc("glGetnCompressedTexImage");
	gl3wGetnCompressedTexImageARB = (PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC) get_proc("glGetnCompressedTexImageARB");
	gl3wGetnTexImage = (PFNGLGETNTEXIMAGEPROC) get_proc("glGetnTexImage");
	gl3wGetnTexImageARB = (PFNGLGETNTEXIMAGEARBPROC) get_proc("glGetnTexImageARB");
	gl3wGetnUniformdv = (PFNGLGETNUNIFORMDVPROC) get_proc("glGetnUniformdv");
	gl3wGetnUniformdvARB = (PFNGLGETNUNIFORMDVARBPROC) get_proc("glGetnUniformdvARB");
	gl3wGetnUniformfv = (PFNGLGETNUNIFORMFVPROC) get_proc("glGetnUniformfv");
	gl3wGetnUniformfvARB = (PFNGLGETNUNIFORMFVARBPROC) get_proc("glGetnUniformfvARB");
	gl3wGetnUniformiv = (PFNGLGETNUNIFORMIVPROC) get_proc("glGetnUniformiv");
	gl3wGetnUniformivARB = (PFNGLGETNUNIFORMIVARBPROC) get_proc("glGetnUniformivARB");
	gl3wGetnUniformuiv = (PFNGLGETNUNIFORMUIVPROC) get_proc("glGetnUniformuiv");
	gl3wGetnUniformuivARB = (PFNGLGETNUNIFORMUIVARBPROC) get_proc("glGetnUniformuivARB");
	gl3wHint = (PFNGLHINTPROC) get_proc("glHint");
	gl3wInvalidateBufferData = (PFNGLINVALIDATEBUFFERDATAPROC) get_proc("glInvalidateBufferData");
	gl3wInvalidateBufferSubData = (PFNGLINVALIDATEBUFFERSUBDATAPROC) get_proc("glInvalidateBufferSubData");
	gl3wInvalidateFramebuffer = (PFNGLINVALIDATEFRAMEBUFFERPROC) get_proc("glInvalidateFramebuffer");
	gl3wInvalidateNamedFramebufferData = (PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC) get_proc("glInvalidateNamedFramebufferData");
	gl3wInvalidateNamedFramebufferSubData = (PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC) get_proc("glInvalidateNamedFramebufferSubData");
	gl3wInvalidateSubFramebuffer = (PFNGLINVALIDATESUBFRAMEBUFFERPROC) get_proc("glInvalidateSubFramebuffer");
	gl3wInvalidateTexImage = (PFNGLINVALIDATETEXIMAGEPROC) get_proc("glInvalidateTexImage");
	gl3wInvalidateTexSubImage = (PFNGLINVALIDATETEXSUBIMAGEPROC) get_proc("glInvalidateTexSubImage");
	gl3wIsBuffer = (PFNGLISBUFFERPROC) get_proc("glIsBuffer");
	gl3wIsEnabled = (PFNGLISENABLEDPROC) get_proc("glIsEnabled");
	gl3wIsEnabledi = (PFNGLISENABLEDIPROC) get_proc("glIsEnabledi");
	gl3wIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) get_proc("glIsFramebuffer");
	gl3wIsImageHandleResidentARB = (PFNGLISIMAGEHANDLERESIDENTARBPROC) get_proc("glIsImageHandleResidentARB");
	gl3wIsNamedStringARB = (PFNGLISNAMEDSTRINGARBPROC) get_proc("glIsNamedStringARB");
	gl3wIsProgram = (PFNGLISPROGRAMPROC) get_proc("glIsProgram");
	gl3wIsProgramPipeline = (PFNGLISPROGRAMPIPELINEPROC) get_proc("glIsProgramPipeline");
	gl3wIsQuery = (PFNGLISQUERYPROC) get_proc("glIsQuery");
	gl3wIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) get_proc("glIsRenderbuffer");
	gl3wIsSampler = (PFNGLISSAMPLERPROC) get_proc("glIsSampler");
	gl3wIsShader = (PFNGLISSHADERPROC) get_proc("glIsShader");
	gl3wIsSync = (PFNGLISSYNCPROC) get_proc("glIsSync");
	gl3wIsTexture = (PFNGLISTEXTUREPROC) get_proc("glIsTexture");
	gl3wIsTextureHandleResidentARB = (PFNGLISTEXTUREHANDLERESIDENTARBPROC) get_proc("glIsTextureHandleResidentARB");
	gl3wIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC) get_proc("glIsTransformFeedback");
	gl3wIsVertexArray = (PFNGLISVERTEXARRAYPROC) get_proc("glIsVertexArray");
	gl3wLineWidth = (PFNGLLINEWIDTHPROC) get_proc("glLineWidth");
	gl3wLinkProgram = (PFNGLLINKPROGRAMPROC) get_proc("glLinkProgram");
	gl3wLogicOp = (PFNGLLOGICOPPROC) get_proc("glLogicOp");
	gl3wMakeImageHandleNonResidentARB = (PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC) get_proc("glMakeImageHandleNonResidentARB");
	gl3wMakeImageHandleResidentARB = (PFNGLMAKEIMAGEHANDLERESIDENTARBPROC) get_proc("glMakeImageHandleResidentARB");
	gl3wMakeTextureHandleNonResidentARB = (PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC) get_proc("glMakeTextureHandleNonResidentARB");
	gl3wMakeTextureHandleResidentARB = (PFNGLMAKETEXTUREHANDLERESIDENTARBPROC) get_proc("glMakeTextureHandleResidentARB");
	gl3wMapBuffer = (PFNGLMAPBUFFERPROC) get_proc("glMapBuffer");
	gl3wMapBufferRange = (PFNGLMAPBUFFERRANGEPROC) get_proc("glMapBufferRange");
	gl3wMapNamedBuffer = (PFNGLMAPNAMEDBUFFERPROC) get_proc("glMapNamedBuffer");
	gl3wMapNamedBufferRange = (PFNGLMAPNAMEDBUFFERRANGEPROC) get_proc("glMapNamedBufferRange");
	gl3wMemoryBarrier = (PFNGLMEMORYBARRIERPROC) get_proc("glMemoryBarrier");
	gl3wMemoryBarrierByRegion = (PFNGLMEMORYBARRIERBYREGIONPROC) get_proc("glMemoryBarrierByRegion");
	gl3wMinSampleShading = (PFNGLMINSAMPLESHADINGPROC) get_proc("glMinSampleShading");
	gl3wMinSampleShadingARB = (PFNGLMINSAMPLESHADINGARBPROC) get_proc("glMinSampleShadingARB");
	gl3wMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC) get_proc("glMultiDrawArrays");
	gl3wMultiDrawArraysIndirect = (PFNGLMULTIDRAWARRAYSINDIRECTPROC) get_proc("glMultiDrawArraysIndirect");
	gl3wMultiDrawArraysIndirectCountARB = (PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC) get_proc("glMultiDrawArraysIndirectCountARB");
	gl3wMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC) get_proc("glMultiDrawElements");
	gl3wMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC) get_proc("glMultiDrawElementsBaseVertex");
	gl3wMultiDrawElementsIndirect = (PFNGLMULTIDRAWELEMENTSINDIRECTPROC) get_proc("glMultiDrawElementsIndirect");
	gl3wMultiDrawElementsIndirectCountARB = (PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC) get_proc("glMultiDrawElementsIndirectCountARB");
	gl3wNamedBufferData = (PFNGLNAMEDBUFFERDATAPROC) get_proc("glNamedBufferData");
	gl3wNamedBufferPageCommitmentARB = (PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC) get_proc("glNamedBufferPageCommitmentARB");
	gl3wNamedBufferPageCommitmentEXT = (PFNGLNAMEDBUFFERPAGECOMMITMENTEXTPROC) get_proc("glNamedBufferPageCommitmentEXT");
	gl3wNamedBufferStorage = (PFNGLNAMEDBUFFERSTORAGEPROC) get_proc("glNamedBufferStorage");
	gl3wNamedBufferSubData = (PFNGLNAMEDBUFFERSUBDATAPROC) get_proc("glNamedBufferSubData");
	gl3wNamedFramebufferDrawBuffer = (PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC) get_proc("glNamedFramebufferDrawBuffer");
	gl3wNamedFramebufferDrawBuffers = (PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC) get_proc("glNamedFramebufferDrawBuffers");
	gl3wNamedFramebufferParameteri = (PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC) get_proc("glNamedFramebufferParameteri");
	gl3wNamedFramebufferReadBuffer = (PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC) get_proc("glNamedFramebufferReadBuffer");
	gl3wNamedFramebufferRenderbuffer = (PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC) get_proc("glNamedFramebufferRenderbuffer");
	gl3wNamedFramebufferTexture = (PFNGLNAMEDFRAMEBUFFERTEXTUREPROC) get_proc("glNamedFramebufferTexture");
	gl3wNamedFramebufferTextureLayer = (PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC) get_proc("glNamedFramebufferTextureLayer");
	gl3wNamedRenderbufferStorage = (PFNGLNAMEDRENDERBUFFERSTORAGEPROC) get_proc("glNamedRenderbufferStorage");
	gl3wNamedRenderbufferStorageMultisample = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC) get_proc("glNamedRenderbufferStorageMultisample");
	gl3wNamedStringARB = (PFNGLNAMEDSTRINGARBPROC) get_proc("glNamedStringARB");
	gl3wObjectLabel = (PFNGLOBJECTLABELPROC) get_proc("glObjectLabel");
	gl3wObjectPtrLabel = (PFNGLOBJECTPTRLABELPROC) get_proc("glObjectPtrLabel");
	gl3wPatchParameterfv = (PFNGLPATCHPARAMETERFVPROC) get_proc("glPatchParameterfv");
	gl3wPatchParameteri = (PFNGLPATCHPARAMETERIPROC) get_proc("glPatchParameteri");
	gl3wPauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC) get_proc("glPauseTransformFeedback");
	gl3wPixelStoref = (PFNGLPIXELSTOREFPROC) get_proc("glPixelStoref");
	gl3wPixelStorei = (PFNGLPIXELSTOREIPROC) get_proc("glPixelStorei");
	gl3wPointParameterf = (PFNGLPOINTPARAMETERFPROC) get_proc("glPointParameterf");
	gl3wPointParameterfv = (PFNGLPOINTPARAMETERFVPROC) get_proc("glPointParameterfv");
	gl3wPointParameteri = (PFNGLPOINTPARAMETERIPROC) get_proc("glPointParameteri");
	gl3wPointParameteriv = (PFNGLPOINTPARAMETERIVPROC) get_proc("glPointParameteriv");
	gl3wPointSize = (PFNGLPOINTSIZEPROC) get_proc("glPointSize");
	gl3wPolygonMode = (PFNGLPOLYGONMODEPROC) get_proc("glPolygonMode");
	gl3wPolygonOffset = (PFNGLPOLYGONOFFSETPROC) get_proc("glPolygonOffset");
	gl3wPopDebugGroup = (PFNGLPOPDEBUGGROUPPROC) get_proc("glPopDebugGroup");
	gl3wPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC) get_proc("glPrimitiveRestartIndex");
	gl3wProgramBinary = (PFNGLPROGRAMBINARYPROC) get_proc("glProgramBinary");
	gl3wProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC) get_proc("glProgramParameteri");
	gl3wProgramUniform1d = (PFNGLPROGRAMUNIFORM1DPROC) get_proc("glProgramUniform1d");
	gl3wProgramUniform1dv = (PFNGLPROGRAMUNIFORM1DVPROC) get_proc("glProgramUniform1dv");
	gl3wProgramUniform1f = (PFNGLPROGRAMUNIFORM1FPROC) get_proc("glProgramUniform1f");
	gl3wProgramUniform1fv = (PFNGLPROGRAMUNIFORM1FVPROC) get_proc("glProgramUniform1fv");
	gl3wProgramUniform1i = (PFNGLPROGRAMUNIFORM1IPROC) get_proc("glProgramUniform1i");
	gl3wProgramUniform1iv = (PFNGLPROGRAMUNIFORM1IVPROC) get_proc("glProgramUniform1iv");
	gl3wProgramUniform1ui = (PFNGLPROGRAMUNIFORM1UIPROC) get_proc("glProgramUniform1ui");
	gl3wProgramUniform1uiv = (PFNGLPROGRAMUNIFORM1UIVPROC) get_proc("glProgramUniform1uiv");
	gl3wProgramUniform2d = (PFNGLPROGRAMUNIFORM2DPROC) get_proc("glProgramUniform2d");
	gl3wProgramUniform2dv = (PFNGLPROGRAMUNIFORM2DVPROC) get_proc("glProgramUniform2dv");
	gl3wProgramUniform2f = (PFNGLPROGRAMUNIFORM2FPROC) get_proc("glProgramUniform2f");
	gl3wProgramUniform2fv = (PFNGLPROGRAMUNIFORM2FVPROC) get_proc("glProgramUniform2fv");
	gl3wProgramUniform2i = (PFNGLPROGRAMUNIFORM2IPROC) get_proc("glProgramUniform2i");
	gl3wProgramUniform2iv = (PFNGLPROGRAMUNIFORM2IVPROC) get_proc("glProgramUniform2iv");
	gl3wProgramUniform2ui = (PFNGLPROGRAMUNIFORM2UIPROC) get_proc("glProgramUniform2ui");
	gl3wProgramUniform2uiv = (PFNGLPROGRAMUNIFORM2UIVPROC) get_proc("glProgramUniform2uiv");
	gl3wProgramUniform3d = (PFNGLPROGRAMUNIFORM3DPROC) get_proc("glProgramUniform3d");
	gl3wProgramUniform3dv = (PFNGLPROGRAMUNIFORM3DVPROC) get_proc("glProgramUniform3dv");
	gl3wProgramUniform3f = (PFNGLPROGRAMUNIFORM3FPROC) get_proc("glProgramUniform3f");
	gl3wProgramUniform3fv = (PFNGLPROGRAMUNIFORM3FVPROC) get_proc("glProgramUniform3fv");
	gl3wProgramUniform3i = (PFNGLPROGRAMUNIFORM3IPROC) get_proc("glProgramUniform3i");
	gl3wProgramUniform3iv = (PFNGLPROGRAMUNIFORM3IVPROC) get_proc("glProgramUniform3iv");
	gl3wProgramUniform3ui = (PFNGLPROGRAMUNIFORM3UIPROC) get_proc("glProgramUniform3ui");
	gl3wProgramUniform3uiv = (PFNGLPROGRAMUNIFORM3UIVPROC) get_proc("glProgramUniform3uiv");
	gl3wProgramUniform4d = (PFNGLPROGRAMUNIFORM4DPROC) get_proc("glProgramUniform4d");
	gl3wProgramUniform4dv = (PFNGLPROGRAMUNIFORM4DVPROC) get_proc("glProgramUniform4dv");
	gl3wProgramUniform4f = (PFNGLPROGRAMUNIFORM4FPROC) get_proc("glProgramUniform4f");
	gl3wProgramUniform4fv = (PFNGLPROGRAMUNIFORM4FVPROC) get_proc("glProgramUniform4fv");
	gl3wProgramUniform4i = (PFNGLPROGRAMUNIFORM4IPROC) get_proc("glProgramUniform4i");
	gl3wProgramUniform4iv = (PFNGLPROGRAMUNIFORM4IVPROC) get_proc("glProgramUniform4iv");
	gl3wProgramUniform4ui = (PFNGLPROGRAMUNIFORM4UIPROC) get_proc("glProgramUniform4ui");
	gl3wProgramUniform4uiv = (PFNGLPROGRAMUNIFORM4UIVPROC) get_proc("glProgramUniform4uiv");
	gl3wProgramUniformHandleui64ARB = (PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC) get_proc("glProgramUniformHandleui64ARB");
	gl3wProgramUniformHandleui64vARB = (PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC) get_proc("glProgramUniformHandleui64vARB");
	gl3wProgramUniformMatrix2dv = (PFNGLPROGRAMUNIFORMMATRIX2DVPROC) get_proc("glProgramUniformMatrix2dv");
	gl3wProgramUniformMatrix2fv = (PFNGLPROGRAMUNIFORMMATRIX2FVPROC) get_proc("glProgramUniformMatrix2fv");
	gl3wProgramUniformMatrix2x3dv = (PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC) get_proc("glProgramUniformMatrix2x3dv");
	gl3wProgramUniformMatrix2x3fv = (PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) get_proc("glProgramUniformMatrix2x3fv");
	gl3wProgramUniformMatrix2x4dv = (PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC) get_proc("glProgramUniformMatrix2x4dv");
	gl3wProgramUniformMatrix2x4fv = (PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) get_proc("glProgramUniformMatrix2x4fv");
	gl3wProgramUniformMatrix3dv = (PFNGLPROGRAMUNIFORMMATRIX3DVPROC) get_proc("glProgramUniformMatrix3dv");
	gl3wProgramUniformMatrix3fv = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC) get_proc("glProgramUniformMatrix3fv");
	gl3wProgramUniformMatrix3x2dv = (PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC) get_proc("glProgramUniformMatrix3x2dv");
	gl3wProgramUniformMatrix3x2fv = (PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) get_proc("glProgramUniformMatrix3x2fv");
	gl3wProgramUniformMatrix3x4dv = (PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC) get_proc("glProgramUniformMatrix3x4dv");
	gl3wProgramUniformMatrix3x4fv = (PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) get_proc("glProgramUniformMatrix3x4fv");
	gl3wProgramUniformMatrix4dv = (PFNGLPROGRAMUNIFORMMATRIX4DVPROC) get_proc("glProgramUniformMatrix4dv");
	gl3wProgramUniformMatrix4fv = (PFNGLPROGRAMUNIFORMMATRIX4FVPROC) get_proc("glProgramUniformMatrix4fv");
	gl3wProgramUniformMatrix4x2dv = (PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC) get_proc("glProgramUniformMatrix4x2dv");
	gl3wProgramUniformMatrix4x2fv = (PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) get_proc("glProgramUniformMatrix4x2fv");
	gl3wProgramUniformMatrix4x3dv = (PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC) get_proc("glProgramUniformMatrix4x3dv");
	gl3wProgramUniformMatrix4x3fv = (PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) get_proc("glProgramUniformMatrix4x3fv");
	gl3wProvokingVertex = (PFNGLPROVOKINGVERTEXPROC) get_proc("glProvokingVertex");
	gl3wPushDebugGroup = (PFNGLPUSHDEBUGGROUPPROC) get_proc("glPushDebugGroup");
	gl3wQueryCounter = (PFNGLQUERYCOUNTERPROC) get_proc("glQueryCounter");
	gl3wReadBuffer = (PFNGLREADBUFFERPROC) get_proc("glReadBuffer");
	gl3wReadPixels = (PFNGLREADPIXELSPROC) get_proc("glReadPixels");
	gl3wReadnPixels = (PFNGLREADNPIXELSPROC) get_proc("glReadnPixels");
	gl3wReadnPixelsARB = (PFNGLREADNPIXELSARBPROC) get_proc("glReadnPixelsARB");
	gl3wReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC) get_proc("glReleaseShaderCompiler");
	gl3wRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) get_proc("glRenderbufferStorage");
	gl3wRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) get_proc("glRenderbufferStorageMultisample");
	gl3wResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC) get_proc("glResumeTransformFeedback");
	gl3wSampleCoverage = (PFNGLSAMPLECOVERAGEPROC) get_proc("glSampleCoverage");
	gl3wSampleMaski = (PFNGLSAMPLEMASKIPROC) get_proc("glSampleMaski");
	gl3wSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC) get_proc("glSamplerParameterIiv");
	gl3wSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC) get_proc("glSamplerParameterIuiv");
	gl3wSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC) get_proc("glSamplerParameterf");
	gl3wSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC) get_proc("glSamplerParameterfv");
	gl3wSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC) get_proc("glSamplerParameteri");
	gl3wSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC) get_proc("glSamplerParameteriv");
	gl3wScissor = (PFNGLSCISSORPROC) get_proc("glScissor");
	gl3wScissorArrayv = (PFNGLSCISSORARRAYVPROC) get_proc("glScissorArrayv");
	gl3wScissorIndexed = (PFNGLSCISSORINDEXEDPROC) get_proc("glScissorIndexed");
	gl3wScissorIndexedv = (PFNGLSCISSORINDEXEDVPROC) get_proc("glScissorIndexedv");
	gl3wShaderBinary = (PFNGLSHADERBINARYPROC) get_proc("glShaderBinary");
	gl3wShaderSource = (PFNGLSHADERSOURCEPROC) get_proc("glShaderSource");
	gl3wShaderStorageBlockBinding = (PFNGLSHADERSTORAGEBLOCKBINDINGPROC) get_proc("glShaderStorageBlockBinding");
	gl3wStencilFunc = (PFNGLSTENCILFUNCPROC) get_proc("glStencilFunc");
	gl3wStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC) get_proc("glStencilFuncSeparate");
	gl3wStencilMask = (PFNGLSTENCILMASKPROC) get_proc("glStencilMask");
	gl3wStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC) get_proc("glStencilMaskSeparate");
	gl3wStencilOp = (PFNGLSTENCILOPPROC) get_proc("glStencilOp");
	gl3wStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC) get_proc("glStencilOpSeparate");
	gl3wTexBuffer = (PFNGLTEXBUFFERPROC) get_proc("glTexBuffer");
	gl3wTexBufferRange = (PFNGLTEXBUFFERRANGEPROC) get_proc("glTexBufferRange");
	gl3wTexImage1D = (PFNGLTEXIMAGE1DPROC) get_proc("glTexImage1D");
	gl3wTexImage2D = (PFNGLTEXIMAGE2DPROC) get_proc("glTexImage2D");
	gl3wTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC) get_proc("glTexImage2DMultisample");
	gl3wTexImage3D = (PFNGLTEXIMAGE3DPROC) get_proc("glTexImage3D");
	gl3wTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC) get_proc("glTexImage3DMultisample");
	gl3wTexPageCommitmentARB = (PFNGLTEXPAGECOMMITMENTARBPROC) get_proc("glTexPageCommitmentARB");
	gl3wTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC) get_proc("glTexParameterIiv");
	gl3wTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC) get_proc("glTexParameterIuiv");
	gl3wTexParameterf = (PFNGLTEXPARAMETERFPROC) get_proc("glTexParameterf");
	gl3wTexParameterfv = (PFNGLTEXPARAMETERFVPROC) get_proc("glTexParameterfv");
	gl3wTexParameteri = (PFNGLTEXPARAMETERIPROC) get_proc("glTexParameteri");
	gl3wTexParameteriv = (PFNGLTEXPARAMETERIVPROC) get_proc("glTexParameteriv");
	gl3wTexStorage1D = (PFNGLTEXSTORAGE1DPROC) get_proc("glTexStorage1D");
	gl3wTexStorage2D = (PFNGLTEXSTORAGE2DPROC) get_proc("glTexStorage2D");
	gl3wTexStorage2DMultisample = (PFNGLTEXSTORAGE2DMULTISAMPLEPROC) get_proc("glTexStorage2DMultisample");
	gl3wTexStorage3D = (PFNGLTEXSTORAGE3DPROC) get_proc("glTexStorage3D");
	gl3wTexStorage3DMultisample = (PFNGLTEXSTORAGE3DMULTISAMPLEPROC) get_proc("glTexStorage3DMultisample");
	gl3wTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC) get_proc("glTexSubImage1D");
	gl3wTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC) get_proc("glTexSubImage2D");
	gl3wTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC) get_proc("glTexSubImage3D");
	gl3wTextureBarrier = (PFNGLTEXTUREBARRIERPROC) get_proc("glTextureBarrier");
	gl3wTextureBuffer = (PFNGLTEXTUREBUFFERPROC) get_proc("glTextureBuffer");
	gl3wTextureBufferRange = (PFNGLTEXTUREBUFFERRANGEPROC) get_proc("glTextureBufferRange");
	gl3wTextureParameterIiv = (PFNGLTEXTUREPARAMETERIIVPROC) get_proc("glTextureParameterIiv");
	gl3wTextureParameterIuiv = (PFNGLTEXTUREPARAMETERIUIVPROC) get_proc("glTextureParameterIuiv");
	gl3wTextureParameterf = (PFNGLTEXTUREPARAMETERFPROC) get_proc("glTextureParameterf");
	gl3wTextureParameterfv = (PFNGLTEXTUREPARAMETERFVPROC) get_proc("glTextureParameterfv");
	gl3wTextureParameteri = (PFNGLTEXTUREPARAMETERIPROC) get_proc("glTextureParameteri");
	gl3wTextureParameteriv = (PFNGLTEXTUREPARAMETERIVPROC) get_proc("glTextureParameteriv");
	gl3wTextureStorage1D = (PFNGLTEXTURESTORAGE1DPROC) get_proc("glTextureStorage1D");
	gl3wTextureStorage2D = (PFNGLTEXTURESTORAGE2DPROC) get_proc("glTextureStorage2D");
	gl3wTextureStorage2DMultisample = (PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC) get_proc("glTextureStorage2DMultisample");
	gl3wTextureStorage3D = (PFNGLTEXTURESTORAGE3DPROC) get_proc("glTextureStorage3D");
	gl3wTextureStorage3DMultisample = (PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC) get_proc("glTextureStorage3DMultisample");
	gl3wTextureSubImage1D = (PFNGLTEXTURESUBIMAGE1DPROC) get_proc("glTextureSubImage1D");
	gl3wTextureSubImage2D = (PFNGLTEXTURESUBIMAGE2DPROC) get_proc("glTextureSubImage2D");
	gl3wTextureSubImage3D = (PFNGLTEXTURESUBIMAGE3DPROC) get_proc("glTextureSubImage3D");
	gl3wTextureView = (PFNGLTEXTUREVIEWPROC) get_proc("glTextureView");
	gl3wTransformFeedbackBufferBase = (PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC) get_proc("glTransformFeedbackBufferBase");
	gl3wTransformFeedbackBufferRange = (PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC) get_proc("glTransformFeedbackBufferRange");
	gl3wTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC) get_proc("glTransformFeedbackVaryings");
	gl3wUniform1d = (PFNGLUNIFORM1DPROC) get_proc("glUniform1d");
	gl3wUniform1dv = (PFNGLUNIFORM1DVPROC) get_proc("glUniform1dv");
	gl3wUniform1f = (PFNGLUNIFORM1FPROC) get_proc("glUniform1f");
	gl3wUniform1fv = (PFNGLUNIFORM1FVPROC) get_proc("glUniform1fv");
	gl3wUniform1i = (PFNGLUNIFORM1IPROC) get_proc("glUniform1i");
	gl3wUniform1iv = (PFNGLUNIFORM1IVPROC) get_proc("glUniform1iv");
	gl3wUniform1ui = (PFNGLUNIFORM1UIPROC) get_proc("glUniform1ui");
	gl3wUniform1uiv = (PFNGLUNIFORM1UIVPROC) get_proc("glUniform1uiv");
	gl3wUniform2d = (PFNGLUNIFORM2DPROC) get_proc("glUniform2d");
	gl3wUniform2dv = (PFNGLUNIFORM2DVPROC) get_proc("glUniform2dv");
	gl3wUniform2f = (PFNGLUNIFORM2FPROC) get_proc("glUniform2f");
	gl3wUniform2fv = (PFNGLUNIFORM2FVPROC) get_proc("glUniform2fv");
	gl3wUniform2i = (PFNGLUNIFORM2IPROC) get_proc("glUniform2i");
	gl3wUniform2iv = (PFNGLUNIFORM2IVPROC) get_proc("glUniform2iv");
	gl3wUniform2ui = (PFNGLUNIFORM2UIPROC) get_proc("glUniform2ui");
	gl3wUniform2uiv = (PFNGLUNIFORM2UIVPROC) get_proc("glUniform2uiv");
	gl3wUniform3d = (PFNGLUNIFORM3DPROC) get_proc("glUniform3d");
	gl3wUniform3dv = (PFNGLUNIFORM3DVPROC) get_proc("glUniform3dv");
	gl3wUniform3f = (PFNGLUNIFORM3FPROC) get_proc("glUniform3f");
	gl3wUniform3fv = (PFNGLUNIFORM3FVPROC) get_proc("glUniform3fv");
	gl3wUniform3i = (PFNGLUNIFORM3IPROC) get_proc("glUniform3i");
	gl3wUniform3iv = (PFNGLUNIFORM3IVPROC) get_proc("glUniform3iv");
	gl3wUniform3ui = (PFNGLUNIFORM3UIPROC) get_proc("glUniform3ui");
	gl3wUniform3uiv = (PFNGLUNIFORM3UIVPROC) get_proc("glUniform3uiv");
	gl3wUniform4d = (PFNGLUNIFORM4DPROC) get_proc("glUniform4d");
	gl3wUniform4dv = (PFNGLUNIFORM4DVPROC) get_proc("glUniform4dv");
	gl3wUniform4f = (PFNGLUNIFORM4FPROC) get_proc("glUniform4f");
	gl3wUniform4fv = (PFNGLUNIFORM4FVPROC) get_proc("glUniform4fv");
	gl3wUniform4i = (PFNGLUNIFORM4IPROC) get_proc("glUniform4i");
	gl3wUniform4iv = (PFNGLUNIFORM4IVPROC) get_proc("glUniform4iv");
	gl3wUniform4ui = (PFNGLUNIFORM4UIPROC) get_proc("glUniform4ui");
	gl3wUniform4uiv = (PFNGLUNIFORM4UIVPROC) get_proc("glUniform4uiv");
	gl3wUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC) get_proc("glUniformBlockBinding");
	gl3wUniformHandleui64ARB = (PFNGLUNIFORMHANDLEUI64ARBPROC) get_proc("glUniformHandleui64ARB");
	gl3wUniformHandleui64vARB = (PFNGLUNIFORMHANDLEUI64VARBPROC) get_proc("glUniformHandleui64vARB");
	gl3wUniformMatrix2dv = (PFNGLUNIFORMMATRIX2DVPROC) get_proc("glUniformMatrix2dv");
	gl3wUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC) get_proc("glUniformMatrix2fv");
	gl3wUniformMatrix2x3dv = (PFNGLUNIFORMMATRIX2X3DVPROC) get_proc("glUniformMatrix2x3dv");
	gl3wUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC) get_proc("glUniformMatrix2x3fv");
	gl3wUniformMatrix2x4dv = (PFNGLUNIFORMMATRIX2X4DVPROC) get_proc("glUniformMatrix2x4dv");
	gl3wUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC) get_proc("glUniformMatrix2x4fv");
	gl3wUniformMatrix3dv = (PFNGLUNIFORMMATRIX3DVPROC) get_proc("glUniformMatrix3dv");
	gl3wUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC) get_proc("glUniformMatrix3fv");
	gl3wUniformMatrix3x2dv = (PFNGLUNIFORMMATRIX3X2DVPROC) get_proc("glUniformMatrix3x2dv");
	gl3wUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC) get_proc("glUniformMatrix3x2fv");
	gl3wUniformMatrix3x4dv = (PFNGLUNIFORMMATRIX3X4DVPROC) get_proc("glUniformMatrix3x4dv");
	gl3wUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC) get_proc("glUniformMatrix3x4fv");
	gl3wUniformMatrix4dv = (PFNGLUNIFORMMATRIX4DVPROC) get_proc("glUniformMatrix4dv");
	gl3wUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) get_proc("glUniformMatrix4fv");
	gl3wUniformMatrix4x2dv = (PFNGLUNIFORMMATRIX4X2DVPROC) get_proc("glUniformMatrix4x2dv");
	gl3wUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC) get_proc("glUniformMatrix4x2fv");
	gl3wUniformMatrix4x3dv = (PFNGLUNIFORMMATRIX4X3DVPROC) get_proc("glUniformMatrix4x3dv");
	gl3wUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC) get_proc("glUniformMatrix4x3fv");
	gl3wUniformSubroutinesuiv = (PFNGLUNIFORMSUBROUTINESUIVPROC) get_proc("glUniformSubroutinesuiv");
	gl3wUnmapBuffer = (PFNGLUNMAPBUFFERPROC) get_proc("glUnmapBuffer");
	gl3wUnmapNamedBuffer = (PFNGLUNMAPNAMEDBUFFERPROC) get_proc("glUnmapNamedBuffer");
	gl3wUseProgram = (PFNGLUSEPROGRAMPROC) get_proc("glUseProgram");
	gl3wUseProgramStages = (PFNGLUSEPROGRAMSTAGESPROC) get_proc("glUseProgramStages");
	gl3wValidateProgram = (PFNGLVALIDATEPROGRAMPROC) get_proc("glValidateProgram");
	gl3wValidateProgramPipeline = (PFNGLVALIDATEPROGRAMPIPELINEPROC) get_proc("glValidateProgramPipeline");
	gl3wVertexArrayAttribBinding = (PFNGLVERTEXARRAYATTRIBBINDINGPROC) get_proc("glVertexArrayAttribBinding");
	gl3wVertexArrayAttribFormat = (PFNGLVERTEXARRAYATTRIBFORMATPROC) get_proc("glVertexArrayAttribFormat");
	gl3wVertexArrayAttribIFormat = (PFNGLVERTEXARRAYATTRIBIFORMATPROC) get_proc("glVertexArrayAttribIFormat");
	gl3wVertexArrayAttribLFormat = (PFNGLVERTEXARRAYATTRIBLFORMATPROC) get_proc("glVertexArrayAttribLFormat");
	gl3wVertexArrayBindingDivisor = (PFNGLVERTEXARRAYBINDINGDIVISORPROC) get_proc("glVertexArrayBindingDivisor");
	gl3wVertexArrayElementBuffer = (PFNGLVERTEXARRAYELEMENTBUFFERPROC) get_proc("glVertexArrayElementBuffer");
	gl3wVertexArrayVertexBuffer = (PFNGLVERTEXARRAYVERTEXBUFFERPROC) get_proc("glVertexArrayVertexBuffer");
	gl3wVertexArrayVertexBuffers = (PFNGLVERTEXARRAYVERTEXBUFFERSPROC) get_proc("glVertexArrayVertexBuffers");
	gl3wVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC) get_proc("glVertexAttrib1d");
	gl3wVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC) get_proc("glVertexAttrib1dv");
	gl3wVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC) get_proc("glVertexAttrib1f");
	gl3wVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC) get_proc("glVertexAttrib1fv");
	gl3wVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC) get_proc("glVertexAttrib1s");
	gl3wVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC) get_proc("glVertexAttrib1sv");
	gl3wVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC) get_proc("glVertexAttrib2d");
	gl3wVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC) get_proc("glVertexAttrib2dv");
	gl3wVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC) get_proc("glVertexAttrib2f");
	gl3wVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC) get_proc("glVertexAttrib2fv");
	gl3wVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC) get_proc("glVertexAttrib2s");
	gl3wVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC) get_proc("glVertexAttrib2sv");
	gl3wVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC) get_proc("glVertexAttrib3d");
	gl3wVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC) get_proc("glVertexAttrib3dv");
	gl3wVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC) get_proc("glVertexAttrib3f");
	gl3wVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC) get_proc("glVertexAttrib3fv");
	gl3wVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC) get_proc("glVertexAttrib3s");
	gl3wVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC) get_proc("glVertexAttrib3sv");
	gl3wVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC) get_proc("glVertexAttrib4Nbv");
	gl3wVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC) get_proc("glVertexAttrib4Niv");
	gl3wVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC) get_proc("glVertexAttrib4Nsv");
	gl3wVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC) get_proc("glVertexAttrib4Nub");
	gl3wVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC) get_proc("glVertexAttrib4Nubv");
	gl3wVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC) get_proc("glVertexAttrib4Nuiv");
	gl3wVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC) get_proc("glVertexAttrib4Nusv");
	gl3wVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC) get_proc("glVertexAttrib4bv");
	gl3wVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC) get_proc("glVertexAttrib4d");
	gl3wVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC) get_proc("glVertexAttrib4dv");
	gl3wVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC) get_proc("glVertexAttrib4f");
	gl3wVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC) get_proc("glVertexAttrib4fv");
	gl3wVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC) get_proc("glVertexAttrib4iv");
	gl3wVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC) get_proc("glVertexAttrib4s");
	gl3wVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC) get_proc("glVertexAttrib4sv");
	gl3wVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC) get_proc("glVertexAttrib4ubv");
	gl3wVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC) get_proc("glVertexAttrib4uiv");
	gl3wVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC) get_proc("glVertexAttrib4usv");
	gl3wVertexAttribBinding = (PFNGLVERTEXATTRIBBINDINGPROC) get_proc("glVertexAttribBinding");
	gl3wVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC) get_proc("glVertexAttribDivisor");
	gl3wVertexAttribFormat = (PFNGLVERTEXATTRIBFORMATPROC) get_proc("glVertexAttribFormat");
	gl3wVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC) get_proc("glVertexAttribI1i");
	gl3wVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC) get_proc("glVertexAttribI1iv");
	gl3wVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC) get_proc("glVertexAttribI1ui");
	gl3wVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC) get_proc("glVertexAttribI1uiv");
	gl3wVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC) get_proc("glVertexAttribI2i");
	gl3wVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC) get_proc("glVertexAttribI2iv");
	gl3wVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC) get_proc("glVertexAttribI2ui");
	gl3wVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC) get_proc("glVertexAttribI2uiv");
	gl3wVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC) get_proc("glVertexAttribI3i");
	gl3wVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC) get_proc("glVertexAttribI3iv");
	gl3wVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC) get_proc("glVertexAttribI3ui");
	gl3wVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC) get_proc("glVertexAttribI3uiv");
	gl3wVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC) get_proc("glVertexAttribI4bv");
	gl3wVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC) get_proc("glVertexAttribI4i");
	gl3wVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC) get_proc("glVertexAttribI4iv");
	gl3wVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC) get_proc("glVertexAttribI4sv");
	gl3wVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC) get_proc("glVertexAttribI4ubv");
	gl3wVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC) get_proc("glVertexAttribI4ui");
	gl3wVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC) get_proc("glVertexAttribI4uiv");
	gl3wVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC) get_proc("glVertexAttribI4usv");
	gl3wVertexAttribIFormat = (PFNGLVERTEXATTRIBIFORMATPROC) get_proc("glVertexAttribIFormat");
	gl3wVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC) get_proc("glVertexAttribIPointer");
	gl3wVertexAttribL1d = (PFNGLVERTEXATTRIBL1DPROC) get_proc("glVertexAttribL1d");
	gl3wVertexAttribL1dv = (PFNGLVERTEXATTRIBL1DVPROC) get_proc("glVertexAttribL1dv");
	gl3wVertexAttribL1ui64ARB = (PFNGLVERTEXATTRIBL1UI64ARBPROC) get_proc("glVertexAttribL1ui64ARB");
	gl3wVertexAttribL1ui64vARB = (PFNGLVERTEXATTRIBL1UI64VARBPROC) get_proc("glVertexAttribL1ui64vARB");
	gl3wVertexAttribL2d = (PFNGLVERTEXATTRIBL2DPROC) get_proc("glVertexAttribL2d");
	gl3wVertexAttribL2dv = (PFNGLVERTEXATTRIBL2DVPROC) get_proc("glVertexAttribL2dv");
	gl3wVertexAttribL3d = (PFNGLVERTEXATTRIBL3DPROC) get_proc("glVertexAttribL3d");
	gl3wVertexAttribL3dv = (PFNGLVERTEXATTRIBL3DVPROC) get_proc("glVertexAttribL3dv");
	gl3wVertexAttribL4d = (PFNGLVERTEXATTRIBL4DPROC) get_proc("glVertexAttribL4d");
	gl3wVertexAttribL4dv = (PFNGLVERTEXATTRIBL4DVPROC) get_proc("glVertexAttribL4dv");
	gl3wVertexAttribLFormat = (PFNGLVERTEXATTRIBLFORMATPROC) get_proc("glVertexAttribLFormat");
	gl3wVertexAttribLPointer = (PFNGLVERTEXATTRIBLPOINTERPROC) get_proc("glVertexAttribLPointer");
	gl3wVertexAttribP1ui = (PFNGLVERTEXATTRIBP1UIPROC) get_proc("glVertexAttribP1ui");
	gl3wVertexAttribP1uiv = (PFNGLVERTEXATTRIBP1UIVPROC) get_proc("glVertexAttribP1uiv");
	gl3wVertexAttribP2ui = (PFNGLVERTEXATTRIBP2UIPROC) get_proc("glVertexAttribP2ui");
	gl3wVertexAttribP2uiv = (PFNGLVERTEXATTRIBP2UIVPROC) get_proc("glVertexAttribP2uiv");
	gl3wVertexAttribP3ui = (PFNGLVERTEXATTRIBP3UIPROC) get_proc("glVertexAttribP3ui");
	gl3wVertexAttribP3uiv = (PFNGLVERTEXATTRIBP3UIVPROC) get_proc("glVertexAttribP3uiv");
	gl3wVertexAttribP4ui = (PFNGLVERTEXATTRIBP4UIPROC) get_proc("glVertexAttribP4ui");
	gl3wVertexAttribP4uiv = (PFNGLVERTEXATTRIBP4UIVPROC) get_proc("glVertexAttribP4uiv");
	gl3wVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) get_proc("glVertexAttribPointer");
	gl3wVertexBindingDivisor = (PFNGLVERTEXBINDINGDIVISORPROC) get_proc("glVertexBindingDivisor");
	gl3wViewport = (PFNGLVIEWPORTPROC) get_proc("glViewport");
	gl3wViewportArrayv = (PFNGLVIEWPORTARRAYVPROC) get_proc("glViewportArrayv");
	gl3wViewportIndexedf = (PFNGLVIEWPORTINDEXEDFPROC) get_proc("glViewportIndexedf");
	gl3wViewportIndexedfv = (PFNGLVIEWPORTINDEXEDFVPROC) get_proc("glViewportIndexedfv");
	gl3wWaitSync = (PFNGLWAITSYNCPROC) get_proc("glWaitSync");
}

#endif
