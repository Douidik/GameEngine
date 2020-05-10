#include "EnginePCH.h"
#include "StaticMeshComponent.h"

StaticMeshComponent::StaticMeshComponent(const std::string &name, const std::string &filePath, int tags)
        : IMeshComponent(name, ComponentTag::StaticMesh | tags) {
    StaticMeshImporter *tmpImporter = new StaticMeshImporter(filePath, mData);

    mVertexBuffer = VertexBuffer(&mData.Vertices[0], Util::GetSizeOfVector(mData.Vertices));
    mElementBuffer = ElementBuffer(&mData.Indices[0], mData.Indices.size());

    mVertexArray.addBuffer(mVertexBuffer, mData.StaticMeshLayoutArray, *Renderer::GetShader<StaticMeshComponent>());

    delete tmpImporter;
}

void StaticMeshComponent::update() {
    Renderer::DrawMesh<StaticMeshComponent>(this);
    mVertexArray.bind();
    mElementBuffer.bind();

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


