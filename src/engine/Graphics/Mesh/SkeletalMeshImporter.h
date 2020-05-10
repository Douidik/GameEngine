#pragma once

#include "MeshImporter.h"

class SkeletalMeshImporter :
        public IMeshImporter {
public:
    SkeletalMeshImporter(const std::string &filePath, SkeletalMeshData &inData);

private:
    void parseNode(const aiNode *pAiNode, SkeletalMeshData &inData, int &meshIndex);

    void parseJoints(SkeletalMeshData &pData);

    void parseBones(aiMesh *pAiMesh, const aiNode *pAiNode, SkeletalMeshData *pData, int baseVertex);

    void parseAnimations(SkeletalMeshData &pData);
};

