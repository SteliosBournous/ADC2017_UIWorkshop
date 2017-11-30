#include "PluginProcessor.h"
#include "PluginView.h"

void PluginProcessor::prepareToPlay (double sampleRate, int)
{
    filter.setSampleRate (float (sampleRate));
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer&)
{
    ScopedNoDenormals noDenormals;
    filter.process (buffer);
}

void PluginProcessor::getStateInformation (MemoryBlock& destData)
{
    MemoryOutputStream stream (destData, false);
    filter.saveState().writeToStream (stream, {});
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (ScopedPointer<XmlElement> xml = XmlDocument::parse (String ((const char *)(data), size_t (sizeInBytes))))
        filter.restoreState (*xml, *this);
}

PluginProcessor::PluginProcessor()
                       : AudioProcessor (BusesProperties().withInput  ("Input",  AudioChannelSet::stereo(), true).withOutput ("Output", AudioChannelSet::stereo(), true))
{
}

AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginView (*this);
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}
