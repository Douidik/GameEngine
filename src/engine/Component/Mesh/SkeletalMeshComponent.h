#pragma once

#include "MeshComponent.h"
#include "Graphics/Mesh/SkeletalMeshImporter.h"

class SkeletalMeshComponent : public IMeshComponent {
public:
    SkeletalMeshComponent(const std::string &name, const std::string &filePath, int tags = 0);

    virtual void update() override;

private:
    SkeletalMeshData mData;
    VertexBuffer mBoneBuffer;
    SkeletalMeshImporter *mpImporter;

private:
    glm::mat4 mGlobalInverseTransform;

private:
    Animation::Animator mpAnimator;
};

