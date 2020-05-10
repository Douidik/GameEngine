#include "EnginePCH.h"
#include "Joint.h"

namespace Animation {

    Joint::Joint(const std::string &name, Joint *pParentJoint, glm::mat4 offset, glm::mat4 defaultTransformation)
            : mName(name), mOffset(offset), mDefaultTransformation(defaultTransformation) {
        //If is not the root joint
        if (pParentJoint != nullptr) {
            setupAttachment(pParentJoint);
        }
    }

    void Joint::setupAttachment(Joint *pParentJoint) {
        mpParentJoint = pParentJoint;
        mpParentJoint->mpChildrenJoints.push_back(this);
    }

    glm::mat4 Joint::getTransform(float animationTime, KeyFrame *pKeyFrameA, KeyFrame *pKeyFrameB) {
        if (pKeyFrameA == nullptr && pKeyFrameB == nullptr) {
            return mDefaultTransformation;
        }

        glm::mat4 transform =
                getPosition(animationTime, pKeyFrameA, pKeyFrameB) * getRotation(animationTime, pKeyFrameA, pKeyFrameB);
        return transform;
    }

    glm::mat4 Joint::getPosition(float animationTime, KeyFrame *pKeyFrameA, KeyFrame *pKeyFrameB) {
        float deltaTime = pKeyFrameB->Time - pKeyFrameA->Time;
        float factor = (animationTime - static_cast<float>(pKeyFrameA->Time)) / deltaTime;
        assert(factor >= 0.0f && factor <= 1.0f);
        glm::vec3 interpolatedPosition = pKeyFrameA->Position * factor - (pKeyFrameB->Position - pKeyFrameA->Position);
        glm::mat4 positionMatrix(1.0f);
        positionMatrix = glm::translate(positionMatrix, interpolatedPosition);

        return positionMatrix;
    }

    glm::mat4 Joint::getRotation(float animationTime, KeyFrame *pKeyFrameA, KeyFrame *pKeyFrameB) {
        float deltaTime = pKeyFrameB->Time - pKeyFrameA->Time;
        float factor = (animationTime - static_cast<float>(pKeyFrameA->Time)) / deltaTime;
        assert(factor >= 0.0f && factor <= 1.0f);
        glm::quat interpolatedRotationQ = glm::slerp(pKeyFrameA->Rotation, pKeyFrameB->Rotation, factor);
        glm::mat4 rotationMatrix = glm::mat4_cast(interpolatedRotationQ);

        return rotationMatrix;
    }

    Joint *Joint::GetParentByAiNode(const aiNode *pAiParentNode, std::vector<Joint *> &hierarchy) {
        Joint *pParentJoint = nullptr;

        for (Joint *pJoint : hierarchy) {
            if (pJoint->getName() == pAiParentNode->mName.C_Str()) {
                pParentJoint = pJoint;
            }
        }
        return pParentJoint;
    }

    Joint *Joint::Find(std::vector<Joint *> &pJoints, std::string &name) {
        auto joint = std::find_if(pJoints.begin(), pJoints.end(),
                                  [&](Joint *pJoint) { return pJoint->getName() == name; });
        assert(joint != pJoints.end());
        return *joint;
    }


}