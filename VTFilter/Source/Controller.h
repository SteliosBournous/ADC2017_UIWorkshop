#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#include "Filter.h"
#include "Distortion.h"

/**
 * This is the controller class
 * It is responsible for marshalling the data model classes (Filter and Distortion)
 */
class Controller
{
public:
    
    /** A list of the parameters that we support */
    enum class Parameter { drive = 0, distortionMode, cutoff, resonance, filterMode, distortionIsPreFilter };
    
    Controller (AudioProcessor& audioProcessor);
    
    void bindEditor (AudioProcessorEditor& editor);

    String getParameterInfo (String paramKey) const;
    
    void setSampleRate (float fs);
    /**
     * This is how the controller will be serialized - saving to its own internal Xml format
     */
    XmlElement saveState() const;
    void restoreState (XmlElement& xml);
    
    void process (AudioSampleBuffer& buffer);
    
private:
    
    static constexpr int numberOfParameters = int (Parameter::distortionIsPreFilter) + 1;
    
    static constexpr const char* parameterKeys[numberOfParameters]   =
    { "drive", "distortionMode", "cutoff", "resonance", "filterMode", "order" };
    
    static constexpr const char* parameterNames[numberOfParameters] =
    { "Drive", "Distortion Mode", "Cutoff", "Resonance", "Filter Mode", "Order" };
    
    static constexpr const char* parameterDescriptions[numberOfParameters] =
    {
        "Amount of distortion",
        "Type of distortion",
        "Cutoff frequency of the filter",
        "Resonance of the filter",
        "Type of filter",
        "Order of filter and distortion"
    };
    
    void prepareForProcess();
    void constructParameters();
    
    Filter filter[2];
    Distortion distortion[2];
    
    AudioProcessorValueTreeState parameters;
};




