#ifndef _OBJLOADER_HEADER__
#define _OBJLOADER_HEADER__

#include "Mesh.hpp"
#include <vector>

namespace ModelLoader {
    std::vector<Mesh> LoadMeshesFromOBJ(const char* filename);
}

#endif

