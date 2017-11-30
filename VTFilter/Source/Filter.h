#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "MathHelpers.h"

class Filter
{
public:

    enum class Mode { lowPass = 0, highPass };
    static StringArray getModes() { return { "Low pass", "High pass" }; }
    static constexpr int numberOfModes = int (Mode::highPass) + 1;
	
    void setSampleRate (const float fs)
    {
        sampleRate        = fs;
        inverseSampleRate = 1.0f / fs;
        dcFilterFrequency = MathHelpers<>::minimum (1.0f, 1.0f - std::expf (-float_Pi * 10.0f * (1.0f / fs)));
        reset();
    }
    
    static NormalisableRange<float> getFrequencyRange()
    {
        static NormalisableRange<float> range (30.0f, 14000.0f,
                                               [] (float currentRangeStart, float currentRangeEnd, float normalisedValue) -> float {
                                                   return currentRangeStart + ((normalisedValue * normalisedValue * normalisedValue) * (currentRangeEnd - currentRangeStart));
                                               },
                                               [] (float currentRangeStart, float currentRangeEnd, float mappedValue) -> float {
                                                   static constexpr float power = 1.0f / 3.0f;
                                                   return std::powf (mappedValue - currentRangeStart, power) / std::powf ((currentRangeEnd - currentRangeStart), power);
                                               },
                                               nullptr);
        
        return range;
        
    }
    
    void setFrequency (const float freqInHz) { frequency = freqInHz; }
    void setResonance (const float res) { resonance = res * 1.01f; }
    void setMode (const Filter::Mode m) { mode = m; }
    
    void process (AudioSampleBuffer& buffer, int channel)
    {
        jassert (buffer.getNumSamples() != 0);
        
        if (auto* channelData = buffer.getWritePointer (channel))
        {
            uint32 numberOfSamples = uint32 (buffer.getNumSamples());
            
            const auto inc = computeFilterIncrement (numberOfSamples);
            const auto q   = MathHelpers<>::clip (16.f, 2.f * std::sqrtf (resonance));
            
            history[0] = MathHelpers<>::minimum (1.0f, q * 0.25f);
            history[1] = 1.0f - history[0];
            
            if (mode == Filter::Mode::lowPass)
                processLowPass (channelData, numberOfSamples, inc, q);
            else
                processHighPass (channelData, numberOfSamples, inc, q);
        }
    }
    
private:
    
    void reset()
    {
        coefficients[0] = 0.0f;
        coefficients[1] = 0.0f;
        alpha           = 0.0f;
        targetFrequency = 0.0f;
        outputLowPass   = 0.0f;
        history[0]      = 0.0f;
        history[1]      = 0.0f;
        mode            = Filter::Mode::lowPass;
    }
    
    void processLowPass (float* buffer, const uint32 numberOfSamples, const float frequencyIncrement, const float q)
    {
        for (uint32 sampleIndex = 0;  sampleIndex < numberOfSamples; ++sampleIndex)
        {
            targetFrequency += frequencyIncrement;
            processSample (buffer[sampleIndex], 0.0f, targetFrequency, q);
            buffer[sampleIndex] = computeNextOutput (alpha);
        }
    }
    
    void processHighPass (float* buffer, const uint32 numberOfSamples, const float frequencyIncrement, const float q)
    {
        for (uint32 sampleIndex = 0;  sampleIndex < numberOfSamples; ++sampleIndex)
        {
            targetFrequency += frequencyIncrement;
            processSample (0.0f, -buffer[sampleIndex], targetFrequency, q);
            buffer[sampleIndex] = computeNextOutput (buffer[sampleIndex] + alpha);
        }
    }
    
    inline void processSample (const float in1, const float in2, const float g, const float k)
	{
		const float ka1 = k * alpha;
		alpha = MathHelpers<>::tanhlimpoly (coefficients[1]);
		const float ka2 = k * alpha;
		coefficients[0] += g * MathHelpers<>::tanhlimpoly (in1 - history[0] * ka2 - history[1] * ka1 - coefficients[0]);
		coefficients[1] += g * MathHelpers<>::tanhlimpoly (in2 + coefficients[0] + ka2 - coefficients[1]);
    }

    inline float computeFilterIncrement (const uint32 numberOfSamples) const
    {
        const float filterFrequency = 1.0f - std::expf (-(2.0f * float_Pi) * (MathHelpers<>::clip (1.f, inverseSampleRate * frequency)));
        return (MathHelpers<>::minimum (1.0f, filterFrequency + filterFrequency * filterFrequency * (0.5f + filterFrequency * (0.3333333333f + filterFrequency * 0.25f))) - targetFrequency) * (1.0f / float (numberOfSamples));
    }

	inline float computeNextOutput (const float in)
	{
		const auto output = MathHelpers<>::tanhlimpoly (in) - outputLowPass;
		outputLowPass += dcFilterFrequency * output;
		return output;
	}
    
    float sampleRate = 44100.0f;
    float inverseSampleRate = 1.0f / 44100.0f;

    float history[2];
    float coefficients[2];
    float alpha = 0.0f;

    float dcFilterFrequency = 0.0f;
    float outputLowPass = 0.0f;
	float targetFrequency = 0.0f;
	
    Filter::Mode mode = Filter::Mode::lowPass;
	float frequency = 0.0f;
    float resonance = 0.25f;
};

