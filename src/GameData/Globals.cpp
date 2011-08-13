#include "Globals.hpp"

#include "../Render/Renderer.hpp"

Globals globals;

#ifndef _BUILD_DATE
#define _BUILD_DATE "UNKNOWN"
#endif /* _BUILD_DATE */
#ifndef _GIT_VERSION
#define _GIT_VERSION "UNKNOWN"
#endif /* _GIT_VERSION */
#ifndef _GIT_SHA1
#define _GIT_SHA1 "UNKNOWN"
#endif /* _GIT_SHA1 */

const string Globals::build_date_ = _BUILD_DATE;
const string Globals::git_version_ = _GIT_VERSION;
const string Globals::git_sha1_ = _GIT_SHA1;
Renderer* Globals::renderer_ = NULL;

Globals g;
