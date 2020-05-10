#include "EnginePCH.h"
#include "Clip.h"

namespace Animation {

    Clip::Clip(const std::string &name, float ticksPerSecond, float duration,
               std::map<Joint *, std::vector<KeyFrame *>> keyFrames)
            : mName(name), mTicksPerSecond(ticksPerSecond), mDuration(duration), mKeyFrames(keyFrames) {}


    std::vector<glm::mat4> Clip::getJointsTransform(float timeInSeconds,
                                                    std::vector<Joint *> &pJoints,
                                                    std::map<std::string, unsigned int> boneMapping,
                                                    glm::mat4 modelMatrix,
                                                    glm::mat4 globalInverseTransform) {
        std::vector<glm::mat4> jointsTransform;
        float timeInTicks = timeInSeconds * mTicksPerSecond;
        float clipTime = std::fmod(timeInTicks, mDuration);
        glm::mat4 parentTransform = modelMatrix;
        parseJointTransform(pJoints[0], parentTransform, globalInverseTransform, clipTime, jointsTransform,
                            boneMapping);

        return jointsTransform;
    }

    void Clip::parseJointTransform(Joint *pJoint,
                                   glm::mat4 &parentTransform,
                                   glm::mat4 globalInverseTransform,
                                   float clipTime,
                                   std::vector<glm::mat4> &jointsTransform,
                                   std::map<std::string, unsigned int> boneMapping) {
        KeyFrame *pKeyFrameA, *pKeyFrameB;
        std::tie(pKeyFrameA, pKeyFrameB) = KeyFrame::Find(pJoint, mKeyFrames[pJoint], clipTime);
        glm::mat4 jointTransform = pJoint->getTransform(clipTime, pKeyFrameA, pKeyFrameB);
        glm::mat4 globalTransform = parentTransform * jointTransform;

        if (boneMapping.find(pJoint->getName()) != boneMapping.end()) {
            glm::mat4 finalTransformation = globalInverseTransform * globalTransform * pJoint->getOffset();
            jointsTransform.push_back(jointTransform);
        }

        for (unsigned int i = 0; i < pJoint->getChildren().size(); i++) {
            parseJointTransform(pJoint->getChildren()[i], globalTransform, globalInverseTransform, clipTime,
                                jointsTransform, boneMapping);
        }
    }

}