#pragma once

#include "EnginePCH.h"
#include "Graphics/Texture.h"
#include <assimp/material.h>
#include <assimp/scene.h>
#include "Graphics/VertexArray.h"
#include "Graphics/Mesh/MeshData.h"
#include "Util/Math.h"
#include "Graphics/Animation/Clip.h"
#include "Graphics/Animation/Animator.h"

#define BONES_PER_VERTEX 4

using namespace Animation;

const std::map<std::string, aiTextureType> TextureTypes =
        {
                {"DIFFUSE", aiTextureType_DIFFUSE}
                //TODO: ,
                //{"HEIGHT", aiTextureType_HEIGHT},
                //{"SPECULAR", aiTextureType_SPECULAR},
                //{"NORMALS", aiTextureType_NORMALS}
        };


struct MeshVertex {
    glm::vec3 Position;
    glm::vec2 TexCoords;
    glm::vec3 Normals;
};

const LayoutArray StaticMeshLayoutArraySample = {{{"inPosition", 3, GL_FLOAT}, {"inTexCoords", 2, GL_FLOAT}, {"inNormals", 3, GL_FLOAT}}};
const LayoutArray SkeletalMeshLayoutArraySample = {{{"inBoneIDs", BONES_PER_VERTEX, GL_INT}, {"inBoneWeights", BONES_PER_VERTEX, GL_FLOAT}}};

struct IMeshData {
    virtual void reserve(const aiScene *paiScene) {
        NumMeshes = paiScene->mNumMeshes;

        unsigned int verticesSize = 0;
        for (int i = 0; i < NumMeshes; i++) {
            MeshBases[i] = verticesSize;
            verticesSize += paiScene->mMeshes[i]->mNumVertices;
            MeshCount[i] = paiScene->mMeshes[i]->mNumVertices;
        }

        Vertices.resize(verticesSize);
        Indices.resize(verticesSize);

        std::for_each(TextureTypes.begin(), TextureTypes.end(),
                      [this](const auto pair) { this->TextureTypeCount[pair.first] = 0; });
    }

    std::vector<MeshVertex> Vertices;
    std::vector<Texture> Textures;
    std::vector<GLuint> Indices;

    unsigned int NumMeshes;
    std::map<int, int> MeshBases;
    std::map<int, int> MeshCount;
    std::map<std::string, int> TextureTypeCount;

};

struct StaticMeshData : public IMeshData {
    StaticMeshData() = default;

    StaticMeshData(const aiScene *pAiScene) {
        StaticMeshLayoutArray = StaticMeshLayoutArraySample;
        GlobalInverseTransform = Util::Math::AiMat4x4ToGlm(pAiScene->mRootNode->mTransformation);
        reserve(pAiScene);
    }

    LayoutArray StaticMeshLayoutArray;
    glm::mat4 GlobalInverseTransform;
};

struct BoneVertex {
    BoneVertex() {
        memset(IDs, 0, sizeof(unsigned int) * BONES_PER_VERTEX);
        memset(Weights, 0, sizeof(float) * BONES_PER_VERTEX);
    }

    void addBoneData(unsigned int id, float weight) {
        for (int i = 0; i < BONES_PER_VERTEX; i++) {
            if (IDs[i] == 0U && Weights[i] == 0.0f) {
                IDs[i] = id;
                Weights[i] = weight;

                return;
            }
        }
    }

    unsigned int IDs[BONES_PER_VERTEX];
    float Weights[BONES_PER_VERTEX];
};

struct SkeletalMeshData : public StaticMeshData {
    SkeletalMeshData() = default;

    SkeletalMeshData(const aiScene *pAiScene)
            : StaticMeshData(pAiScene), NumJoints(0), SkeletalMeshLayoutArray(SkeletalMeshLayoutArraySample) {
        reserve(pAiScene);
    }

    virtual void reserve(const aiScene *pAiScene) override {
        NumMeshes = pAiScene->mNumMeshes;

        unsigned int verticesSize = 0;

        for (int i = 0; i < NumMeshes; i++) {
            MeshBases[i] = verticesSize;
            verticesSize += pAiScene->mMeshes[i]->mNumVertices;
            MeshCount[i] = pAiScene->mMeshes[i]->mNumVertices;
        }

        Bones.resize(verticesSize);
        Vertices.resize(verticesSize);
        Indices.resize(verticesSize);
    }

    std::vector<BoneVertex> Bones;
    std::vector<Joint *> pJoints;
    std::vector<Clip> Clips;
    std::map<std::string, unsigned int> BoneMapping;
    unsigned int NumJoints;
    LayoutArray SkeletalMeshLayoutArray;
};
