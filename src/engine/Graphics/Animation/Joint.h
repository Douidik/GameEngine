#pragma once

#include "KeyFrame.h"
#include "assimp/scene.h"

namespace Animation {

    class Joint {
    public:
        Joint(const std::string &name, Joint *pParentJoint, glm::mat4 offset, glm::mat4 defaultTransformation);

        //Node management
    public:
        inline std::string getName() const { return mName; }

        inline std::vector<Joint *> getChildren() const { return mpChildrenJoints; }

        inline Joint *getParent() const { return mpParentJoint; }

        inline glm::mat4 getOffset() const { return mOffset; }

        inline void setOffset(glm::mat4 offset) { mOffset = offset; }

    private:
        void setupAttachment(Joint *pParentJoint);

        //Joint transform computation
    public:
        //Get the current bone transformation based on the current animation time in ticks, the keyframeA and the keyframeB (basically starting key frame and end key frame)
        glm::mat4 getTransform(float clipTime, KeyFrame *pKeyFrameA, KeyFrame *pKeyFrameB);

    private:
        glm::mat4 getPosition(float clipTime, KeyFrame *pKeyFrameA, KeyFrame *pKeyFrameB);

        glm::mat4 getRotation(float clipTime, KeyFrame *pKeyFrameA, KeyFrame *pKeyFrameB);

    private:
        /*If the transformation of the bone is not provided by the clip we set the default transformation provided by default
         It often the case when the joint is only existing for technical reasons */
        glm::mat4 mDefaultTransformation;

        glm::mat4 mOffset;
        std::string mName;

        Joint *mpParentJoint;
        std::vector<Joint *> mpChildrenJoints;

    public:
        static Joint *GetParentByAiNode(const aiNode *pAiParentNode, std::vector<Joint *> &hierarchy);

        static Joint *Find(std::vector<Joint *> &pJoints, std::string &name);
    };
}

