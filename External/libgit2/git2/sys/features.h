#ifndef INCLUDE_features_h__
#define INCLUDE_features_h__

/* #undef GIT_DEBUG_POOL */
/* #undef GIT_TRACE */
#define GIT_THREADS 1
/* #undef GIT_MSVC_CRTDBG */

#define GIT_ARCH_64 1
/* #undef GIT_ARCH_32 */

/* #undef GIT_USE_ICONV */
#define GIT_USE_NSEC 1
/* #undef GIT_USE_STAT_MTIM */
/* #undef GIT_USE_STAT_MTIMESPEC */
/* #undef GIT_USE_STAT_MTIME_NSEC */
/* #undef GIT_USE_FUTIMENS */
/* #undef GIT_USE_REGCOMP_L */

/* #undef GIT_SSH */
/* #undef GIT_SSH_MEMORY_CREDENTIALS */

/* #undef GIT_GSSAPI */
#define GIT_WINHTTP 1
/* #undef GIT_CURL */

#define GIT_HTTPS 1
/* #undef GIT_OPENSSL */
/* #undef GIT_SECURE_TRANSPORT */

#define GIT_SHA1_COLLISIONDETECT 1
/* #undef GIT_SHA1_WIN32 */
/* #undef GIT_SHA1_COMMON_CRYPTO */
/* #undef GIT_SHA1_OPENSSL */

#endif
