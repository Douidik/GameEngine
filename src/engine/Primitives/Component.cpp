#include "EnginePCH.h"
#include "Component.h"

int operator|(ComponentTag tag, int tag2) {
    return (int) tag | tag2;
}

int operator&(ComponentTag tag, int tag2) {
    return (int) tag & tag2;
}