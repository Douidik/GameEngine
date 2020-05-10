#include "EnginePCH.h"
#include "SkeletalMeshComponent.h"
#include "Graphics/Animation/Animator.h"

SkeletalMeshComponent::SkeletalMeshComponent(const std::string &name, const std::string &filePath, int tags)
        : IMeshComponent(name, ComponentTag::SkeletalMesh | tags) {
    mpImporter = new SkeletalMeshImporter(filePath, mData);

    mVertexBuffer = VertexBuffer(&mData.Vertices[0], Util::GetSizeOfVector(mData.Vertices));
    mBoneBuffer = VertexBuffer(&mData.Bones[0], Util::GetSizeOfVector(mData.Bones));
    mElementBuffer = ElementBuffer(&mData.Indices[0], mData.Indices.size());

    mVertexArray.addBuffer(mVertexBuffer, mData.StaticMeshLayoutArray, *Renderer::GetShader<SkeletalMeshComponent>());
    mVertexArray.addBuffer(mBoneBuffer, mData.SkeletalMeshLayoutArray, *Renderer::GetShader<SkeletalMeshComponent>());

    mpAnimator = Animator(mData.Clips);
    mGlobalInverseTransform = mData.GlobalInverseTransform;
}

void SkeletalMeshComponent::update() {
    Renderer::DrawMesh<SkeletalMeshComponent>(this);
    mVertexArray.bind();
    mVertexBuffer.bind();
    mBoneBuffer.bind();
    mElementBuffer.bind();

    mpAnimator.play("Animation0", mData.pJoints, CreateTransformMatrix(), mGlobalInverseTransform, mData.BoneMapping);

    for (int i = 0; i < mData.NumMeshes; i++) {
        mData.Textures[i].bind();
        Renderer::GetShader<StaticMeshComponent>()->setUniform(mData.Textures[i].getUniformName(),mData.Textures[i].getSlot());

        glDrawElementsBaseVertex(
                GL_TRIANGLES,
                mData.MeshCount[i],
                GL_UNSIGNED_INT,
                (void *) (Util::GetSizeOfGLType(GL_UNSIGNED_INT) * mData.MeshBases[i]),
                mData.MeshBases[i]
        );
    }
}