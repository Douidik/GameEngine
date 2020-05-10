#include "EnginePCH.h"
#include "KeyFrame.h"
#include "Joint.h"

namespace Animation {

    std::pair<KeyFrame *, KeyFrame *>
    KeyFrame::Find(Joint *pJoint, std::vector<KeyFrame *> &keyFrames, float clipTime) {
        KeyFrame *pKeyFrameA = nullptr, *pKeyFrameB = nullptr;
        std::string jointName = pJoint->getName();

        //We find which key frame we need to play
        for (std::vector<KeyFrame *>::iterator nextIt = keyFrames.begin(); nextIt != keyFrames.end(); nextIt++) {
            //We found the key frame
            if (clipTime < (*nextIt)->Time) {
                std::vector<KeyFrame *>::iterator it = std::prev(nextIt);
                pKeyFrameA = *it;
                pKeyFrameB = *nextIt;
                break;
            }
        }

        return {pKeyFrameA, pKeyFrameB};
    }

}