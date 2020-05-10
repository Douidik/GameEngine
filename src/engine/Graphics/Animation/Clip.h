#pragma once

#include "Joint.h"

namespace Animation {

    class Clip {
    public:
        Clip(const std::string &name, float ticksPerSecond, float duration,
             std::map<Joint *, std::vector<KeyFrame *>> keyFrames);

        std::vector<glm::mat4> getJointsTransform(float timeInSeconds,
                                                  std::vector<Joint *> &pJoints,
                                                  std::map<std::string,
                                                          unsigned int> boneMapping,
                                                  glm::mat4 modelMatrix,
                                                  glm::mat4 globalInverseMatrix);

        inline std::string getName() const { return mName; }

    private:
        void parseJointTransform(Joint *pJoint,
                                 glm::mat4 &parentTransform,
                                 glm::mat4 globalInverseTransform,
                                 float clipTime,
                                 std::vector<glm::mat4> &jointsTransform,
                                 std::map<std::string, unsigned int> boneMapping);

    private:
        std::map<Joint *, std::vector<KeyFrame *>> mKeyFrames;
        float mTicksPerSecond, mDuration;
        std::string mName;
    };

}

