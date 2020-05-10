#include "EnginePCH.h"
#include "MeshImporter.h"
#include "Util/Util.h"
#include "Util/Vfs.h"

void IMeshImporter::loadAiScene(const std::string &filePath) {
   
    Util::Vfs virtualPath(filePath);
    std::cout << virtualPath.get() << std::endl;

    mpAiScene = mAiImporter.ReadFile(virutalPath.get(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (!mpAiScene || mpAiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !mpAiScene->mRootNode) {
        std::cerr << "Assimp fails to parse model at " << filePath << ":\n" << mAiImporter.GetErrorString()
                  << std::endl;
        assert(0);
    }

    mDirectory = filePath.substr(0, filePath.find_last_of('/') + 1);
}

void IMeshImporter::parseVertices(aiMesh *paiMesh, IMeshData *pData, unsigned int baseVertex) {
    for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
        pData->Vertices[baseVertex + i].Position = Util::Math::AiVec3ToGlm(paiMesh->mVertices[i]);
        pData->Vertices[baseVertex + i].TexCoords = Util::Math::AiVec2ToGlm(paiMesh->mTextureCoords[0][i]);
        pData->Vertices[baseVertex + i].Normals = Util::Math::AiVec3ToGlm(paiMesh->mNormals[i]);
    }
}

void IMeshImporter::parseIndices(aiMesh *pAiMesh, StaticMeshData *pData, unsigned int baseIndex) {

    for (unsigned int i = 0; i < pAiMesh->mNumFaces; i++) {
        aiFace face = pAiMesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            pData->Indices[baseIndex + (i * 3 + j)] = face.mIndices[j];
        }
    }
}

void IMeshImporter::parseTextures(aiMesh *pAiMesh, StaticMeshData *pData) {
    const aiMaterial *pAiMaterial = mpAiScene->mMaterials[pAiMesh->mMaterialIndex];

    if (pAiMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
        aiString path;
        if (pAiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
            std::string fullpath = mDirectory + path.C_Str();
            pData->Textures.push_back(Texture(fullpath, "DIFFUSE", 0));
        }
    }
    else {
        pData->Textures.push_back(Texture(RESOURCE_PATH(std::string(TEXTURE_PLACEHOLDER)), "DIFFUSE", 0));
    }
}
