#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#include "Filter.h"
#include "Distortion.h"

/**
 * This is the controller class
 * It is responsible for marshalling the data model classes (Filter and Distortion)
 */
class Controller : private Slider::Listener
                 , private ComboBox::Listener
                 , private Button::Listener
{
public:

    /** A list of the parameters that we support */
    enum class Parameter { drive = 0, distortionMode, cutoff, resonance, filterMode, distortionIsPreFilter };

    Controller();

    /** 
     * These functions are used to connect editor components and parameters. Make sure that you call them symetrically
     * i.e. a call to bindEditor must also have a matched unbindEditor
     */
    void bindEditor (AudioProcessorEditor& editor);
    void unbindEditor (AudioProcessorEditor& editor);

    String getParameterInfo (Parameter param) const;

    void setSampleRate (float fs);

    /**
     * This is how the controller will be serialized - saving to its own internal Xml format
     */
    XmlElement saveState() const;
    void restoreState (XmlElement& xml, AudioProcessor& audioProcessor);
    
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
    
    /**
     * These parameter functions are simple boiler plate for setting and getting
     * variables using a param index, rather than by accessing the array directly
     */
    void setParameter (Parameter param, var value);
    var getParameter (Parameter param) const;
    void setParameterWithStringValue (Parameter param, String value);
    String getParameterValue (Parameter param) const;
    void resetParameters();
    
    /**
     * Editor callbacks for when component change
     */
    void updateControlValues (AudioProcessorEditor& theEditor);
    void sliderValueChanged (Slider* slider) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (Button*) override;
    
    Filter filter[2];
    Distortion distortion[2];

    /**
     * These are the actual parameters - they are represented by values that
     * match the actual values (i.e. Cutoff is a float, processor order is a bool etc)
     */
    var parameters[numberOfParameters];
};
