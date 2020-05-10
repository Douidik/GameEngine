#include "EnginePCH.h"
#include "StaticMeshImporter.h"

StaticMeshImporter::StaticMeshImporter(const std::string &filePath, StaticMeshData &inData) {
    loadAiScene(filePath);
    inData.reserve(mpAiScene);
    int meshIndex = 0;
    parseNode(mpAiScene->mRootNode, inData, meshIndex);
}

void StaticMeshImporter::parseNode(const aiNode *pAiNode, StaticMeshData &inData, int &meshIndex) {
    for (int i = 0; i < pAiNode->mNumMeshes; i++) {
        aiMesh *pAiMesh = mpAiScene->mMeshes[pAiNode->mMeshes[i]];

        parseVertices(pAiMesh, &inData, inData.MeshBases[meshIndex]);
        parseIndices(pAiMesh, &inData, inData.MeshBases[meshIndex]);
        parseTextures(pAiMesh, &inData);

        meshIndex++;
    }

    for (int i = 0; i < pAiNode->mNumChildren; i++) {
        parseNode(pAiNode->mChildren[i], inData, meshIndex);
    }
}
