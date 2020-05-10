#include "EnginePCH.h"
#include "SkeletalMeshImporter.h"
#include "Util/Math.h"
#include "Graphics/Animation/Joint.h"

using namespace Util::Math;
using namespace Animation;

SkeletalMeshImporter::SkeletalMeshImporter(const std::string &filePath, SkeletalMeshData &inData) {
    loadAiScene(filePath);
    inData = SkeletalMeshData(mpAiScene);
    int meshIndex = 0;
    parseJoints(inData);
    parseNode(mpAiScene->mRootNode, inData, meshIndex);
    parseAnimations(inData);
}

void SkeletalMeshImporter::parseNode(const aiNode *pAiNode, SkeletalMeshData &inData, int &meshIndex) {

    for (int i = 0; i < pAiNode->mNumMeshes; i++) {
        aiMesh *pAiMesh = mpAiScene->mMeshes[pAiNode->mMeshes[i]];

        parseVertices(pAiMesh, &inData, inData.MeshBases[meshIndex]);
        parseIndices(pAiMesh, &inData, inData.MeshBases[meshIndex]);
        parseBones(pAiMesh, pAiNode, &inData, inData.MeshBases[meshIndex]);
        parseTextures(pAiMesh, &inData);

        meshIndex++;
    }

    for (int i = 0; i < pAiNode->mNumChildren; i++) {
        parseNode(pAiNode->mChildren[i], inData, meshIndex);
    }
}

void SkeletalMeshImporter::parseJoints(SkeletalMeshData &pData) {
    std::function<void(const aiNode *)> readJointHierarchy = [&](const aiNode *pAiNode) {
        Joint *pParentJoint = Joint::GetParentByAiNode(pAiNode->mParent, pData.pJoints);
        glm::mat4 defaultTransform = Util::Math::AiMat4x4ToGlm(pAiNode->mTransformation);
        Joint *pJoint = new Joint(pAiNode->mName.C_Str(), pParentJoint, glm::mat4(0.0f), defaultTransform);
        pData.pJoints.push_back(pJoint);

        for (int i = 0; i < pAiNode->mNumChildren; i++) {
            readJointHierarchy(pAiNode->mChildren[i]);
        }
    };
    readJointHierarchy(mpAiScene->mRootNode);
}

void SkeletalMeshImporter::parseBones(aiMesh *pAiMesh, const aiNode *pAiNode, SkeletalMeshData *pData, int baseVertex) {
    for (unsigned int i = 0; i < pAiMesh->mNumBones; i++) {
        unsigned int boneIndex = 0;
        std::string jointName = pAiMesh->mBones[i]->mName.C_Str();

        if (pData->BoneMapping.find(jointName) == pData->BoneMapping.end()) {
            boneIndex = pData->NumJoints;
            pData->BoneMapping[jointName] = boneIndex;

            const aiNode *pAiJoint = mpAiScene->mRootNode->FindNode(jointName.c_str());
            glm::mat4 offset = Util::Math::AiMat4x4ToGlm(pAiMesh->mBones[i]->mOffsetMatrix);
            Joint *pJoint = Joint::Find(pData->pJoints, jointName);
            pJoint->setOffset(offset);

            pData->NumJoints += 1;
        } else {
            boneIndex = pData->BoneMapping[jointName];
        }

        for (unsigned int j = 0; j < pAiMesh->mBones[i]->mNumWeights; j++) {
            unsigned int vertexID = baseVertex + pAiMesh->mBones[i]->mWeights[j].mVertexId;
            float weight = pAiMesh->mBones[i]->mWeights[j].mWeight;
            pData->Bones[vertexID].addBoneData(boneIndex, weight);
        }

    }
}

void SkeletalMeshImporter::parseAnimations(SkeletalMeshData &pData) {
    //The skeletal mesh must have animations
    assert(mpAiScene->HasAnimations());

    //aiAnimation is what we call clip
    for (int clipIndex = 0; clipIndex < mpAiScene->mNumAnimations; clipIndex++) {
        aiAnimation *pAiAnim = mpAiScene->mAnimations[clipIndex];
        float clipDuration = pAiAnim->mDuration;
        float ticksPerSeconds = pAiAnim->mTicksPerSecond != 0.0f ? pAiAnim->mTicksPerSecond : 25.0f;
        std::string clipName = (pAiAnim->mName.C_Str() == "" ? pAiAnim->mName.C_Str() : "Animation" +
                                                                                        std::to_string(clipIndex));

        //The keyFrames related to the current parsed clip
        std::map<Joint *, std::vector<KeyFrame *>> pClipKeyFrames;

        for (int channelIndex = 0; channelIndex < pAiAnim->mNumChannels; channelIndex++) {
            const aiNodeAnim *pAiChannel = pAiAnim->mChannels[channelIndex];
            std::string jointName = pAiChannel->mNodeName.C_Str();

            auto targetedJointIterator = std::find_if(pData.pJoints.begin(), pData.pJoints.end(),
                                                      [&](Joint *pJoint) { return pJoint->getName() == jointName; });

            //Joint has been found in the hierarchy
            if (targetedJointIterator != pData.pJoints.end()) {

                Joint *targetedJoint = *targetedJointIterator;

                KeyFrame *pLastKeyFrame = nullptr;
                //The keyFrames related to the current parsed joint
                std::vector<KeyFrame *> pJointKeyFrames;


                //The number of position keys will also be the number of key frames
                for (int keyFrameIndex = 0; keyFrameIndex < pAiChannel->mNumPositionKeys - 1; keyFrameIndex++) {
                    KeyFrame *pKeyFrame = new KeyFrame();
                    pKeyFrame->TargetedJoint = targetedJoint;

                    pKeyFrame->LastKeyFrame = pLastKeyFrame;
                    if (pLastKeyFrame != nullptr)
                        pLastKeyFrame->NextKeyFrame = pKeyFrame;

                    pKeyFrame->Time = pAiChannel->mPositionKeys[keyFrameIndex].mTime;

                    pKeyFrame->Position = Util::Math::AiVec3ToGlm(pAiChannel->mPositionKeys[keyFrameIndex].mValue);
                    pKeyFrame->Rotation = Util::Math::AiQuatToGlm(pAiChannel->mRotationKeys[keyFrameIndex].mValue);

                    pJointKeyFrames.push_back(pKeyFrame);
                    pLastKeyFrame = pKeyFrame;
                }

                pClipKeyFrames[targetedJoint] = pJointKeyFrames;

            }
        }
        Clip clip(clipName, ticksPerSeconds, clipDuration, pClipKeyFrames);
        pData.Clips.push_back(clip);
    }
}
