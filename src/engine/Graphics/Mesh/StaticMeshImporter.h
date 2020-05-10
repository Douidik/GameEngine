#pragma once

#include "MeshImporter.h"

class StaticMeshImporter : public IMeshImporter {
public:
    StaticMeshImporter(const std::string &filePath, StaticMeshData &inData);

private:
    void parseNode(const aiNode *node, StaticMeshData &inData, int &meshIndex);

};