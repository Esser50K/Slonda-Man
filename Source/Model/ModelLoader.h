#ifndef MODELLOADER_H_INCLUDED
#define MODELLOADER_H_INCLUDED

#include <vector>
#include <string>
#include <GL/glew.h>

#include "Mesh.h"

Mesh loadObjModel(const std::string& fileName);

#endif // MODELLOADER_H_INCLUDED
