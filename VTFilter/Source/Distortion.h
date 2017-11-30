#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#include "DCFilter.h"
#include "MathHelpers.h"

class Distortion
{
public:

    enum class Mode { polyShaper = 0, bitReducer };
    static StringArray getModes() { return { "Poly", "Bit Reducer" }; }
    static constexpr int numberOfModes = int (Mode::bitReducer) + 1;

    void setSampleRate (float fs) { dcFilter.setSampleRate (fs); }
    void setDrive (const float drive01) { nextDrive = drive01; }
    
    void setMode (const Distortion::Mode distortionMode)
    {
        if (distortionMode != mode) dcFilter.reset();
        mode = distortionMode;
    }
    
    void process (AudioSampleBuffer& buffer, int channel)
    {
        jassert (buffer.getNumSamples() != 0);
        
        if (auto* channelData = buffer.getWritePointer (channel))
        {
            const float driveDelta = (MathHelpers<>::areEqual (nextDrive, drive)) ? 0.0f : ((nextDrive - drive) * (1.0f / buffer.getNumSamples()));
            
            if (mode == Distortion::Mode::polyShaper)
                processPolyShaper (channelData, buffer.getNumSamples(), driveDelta);
            else
                processBitReducer (channelData, buffer.getNumSamples(), driveDelta);
        }
    }
    

private:
    
    void processPolyShaper (float* channelData, const int numberOfSamples, const float driveDelta)
    {
        for (int sampleIndex = 0; sampleIndex < numberOfSamples; ++sampleIndex)
        {
            drive = MathHelpers<>::clip01 (drive + driveDelta);
            channelData[sampleIndex] = dcFilter.process (MathHelpers<float>::tanhlimpoly (MathHelpers<float>::convertRange (drive * drive, 1.0f, 40.0f) * channelData[sampleIndex]));
        }
    }
    
    void processBitReducer (float* channelData, const int numberOfSamples, const float driveDelta)
    {
        for (int sampleIndex = 0; sampleIndex < numberOfSamples; ++sampleIndex)
        {
            drive				 = MathHelpers<>::clip01 (drive + driveDelta);
            const float quantum  = std::powf (2.0f, MathHelpers<float>::convertRange (std::powf (1.0f - drive, 2.5f), 2.0f, 18.0f));
            jassert (! MathHelpers<>::areEqual (quantum, 0.0f));
            const float distOut  = std::floorf (channelData[sampleIndex] * quantum ) / quantum;
            
            channelData[sampleIndex] = dcFilter.process (distOut);
        }
    }

	float nextDrive = 0.0f;
	float drive = 0.0f;
    Distortion::Mode mode = Distortion::Mode::polyShaper;

    DCFilter dcFilter;
};



