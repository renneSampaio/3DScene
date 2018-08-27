#ifndef _OBJLOADER_HEADER__
#define _OBJLOADER_HEADER__

#include "Mesh.hpp"
#include <vector>

namespace ModelLoader {
    Mesh* LoadMeshFromOBJ(const char* filename);
}

#endif

