#include "EnginePCH.h"
#include "Animator.h"
#include "Component/Mesh/SkeletalMeshComponent.h"
#include "Core.h"
#include "Graphics/Renderer.h"

namespace Animation {

    Animator::Animator(std::vector<Clip> clips)
            : mClips(clips) {

    }

    void Animator::play(const std::string &clipName,
                        std::vector<Joint *> &pJoints,
                        glm::mat4 modelMatrix,
                        glm::mat4 globalInverseTransform,
                        std::map<std::string, unsigned int> boneMapping) {
        auto clipIterator = std::find_if(mClips.begin(), mClips.end(),
                                         [&](Clip pClip) { return pClip.getName() == clipName; });

        if (clipIterator == mClips.end()) {
            std::cerr << "Animation: " << clipName << " has not been found in animator" << std::endl;
            assert(0);
        }

        float currentTimeInSeconds = 10.0f;
        std::vector<glm::mat4> jointsTransform = clipIterator->getJointsTransform(currentTimeInSeconds, pJoints,
                                                                                  boneMapping, modelMatrix,
                                                                                  globalInverseTransform);

        for (unsigned int i = 0; i < jointsTransform.size(); i++) {
            Renderer::GetShader<SkeletalMeshComponent>()->setUniform("uBones[" + std::to_string(i) + "]",
                                                                     jointsTransform[i]);
        }
    }

}
