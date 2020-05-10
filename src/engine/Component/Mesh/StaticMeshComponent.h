#pragma once

#include "MeshComponent.h"
#include "Graphics/Mesh/StaticMeshImporter.h"

class StaticMeshComponent : public IMeshComponent {
public:
    StaticMeshComponent(const std::string &name, const std::string &filePath, int tags = 0);

    virtual void update() override;

private:
    StaticMeshData mData;

};

