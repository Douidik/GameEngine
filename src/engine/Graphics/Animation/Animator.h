#pragma once

#include "Clip.h"

namespace Animation {

    class Animator {
    public:
        Animator(std::vector<Clip> clips);

        Animator() = default;

        void play(const std::string &clipName, std::vector<Joint *> &pJoints, glm::mat4 modelMatrix,
                  glm::mat4 globalInverseTransform, std::map<std::string, unsigned int> boneMapping);

    private:
        std::vector<Clip> mClips;
    };

}