#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class DCFilter
{
public:

    void setSampleRate (float fs)
    {
        dcFrequency = 1.0f - std::expf (-float_Pi * 10.0f * (1.0f / fs));
        reset();
    }
    
    void reset()
    {
        dcFilter = 0.0f;
    }
    
    float process (float in)
    {
        const float filtOut = in - dcFilter;
        dcFilter           += dcFrequency * filtOut;
        return filtOut;
    }
    
private:

    float dcFrequency = 0.0f;
    float dcFilter = 0.0f;
};
