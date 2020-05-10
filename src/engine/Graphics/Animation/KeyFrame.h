#pragma once

namespace Animation {

    class Joint;

    struct KeyFrame {

        static std::pair<KeyFrame *, KeyFrame *>
        Find(Joint *pJoint, std::vector<KeyFrame *> &keyFrames, float clipTime);

        float Time;

        glm::vec3 Position;
        glm::quat Rotation;

        KeyFrame *LastKeyFrame;
        KeyFrame *NextKeyFrame;
        Joint *TargetedJoint;

    };

}