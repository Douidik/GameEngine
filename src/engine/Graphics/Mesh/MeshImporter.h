#pragma once

#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "MeshData.h"
#include "Util/Util.h"

//Declaring texture types handled by the engine
extern const std::map<std::string, aiTextureType> TextureTypes;

#define TEXTURE_PLACEHOLDER "textures/placeholder.png"

class IMeshImporter {
protected:
    virtual void loadAiScene(const std::string &filePath);

    void parseVertices(aiMesh *pAiMesh, IMeshData *data, unsigned int baseVertex);

    void parseIndices(aiMesh *pAiMesh, StaticMeshData *pData, unsigned int baseIndex);

    void parseTextures(aiMesh *pAiMesh, StaticMeshData *pData);

public:
    inline const aiScene *getAiScene() const { return mpAiScene; }

protected:
    const aiScene *mpAiScene;
private:
    Assimp::Importer mAiImporter;
    std::string mDirectory;
    std::vector<Texture *> mpTextureCache;
};

