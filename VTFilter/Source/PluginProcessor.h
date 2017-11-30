#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#include "Controller.h"

/**
 * The PluginProcessor is a simple wrapper around our plugin provided by Juce
 * It essentially just holds our controller and our view, and manages the lifetime and 
 * all the generic setup infromation
 */
class PluginProcessor  : public AudioProcessor
{
public:
    
    PluginProcessor();
    ~PluginProcessor() = default;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {}
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override
    {
        if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
            return false;
        if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
            return false;
        return true;
    }
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const String getName() const override { return JucePlugin_Name; }

    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect () const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const String getProgramName (int) override { return {}; }
    void changeProgramName (int, const String&) override {}

    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    const Controller& getController() const { return filter; }
    Controller& getController() { return filter; }

private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)

    Controller filter { *this };
};
