#include "Controller.h"
#include "PluginView.h"

Controller::Controller()
{
    resetParameters();
}

void Controller::bindEditor (AudioProcessorEditor& theEditor)
{
    /*
     * We want to access the PluginView* parameters, so we need to cast down to the actual type from our base class
     */
    if (auto* editor = dynamic_cast<PluginView*>(&theEditor))
    {
        editor->filterMode.addItemList (Filter::getModes(), 1);
        editor->distortionMode.addItemList (Distortion::getModes(), 1);
        
        updateControlValues (theEditor);
        
        editor->cutoff.addListener (this);
        editor->resonance.addListener (this);
        editor->drive.addListener (this);
        editor->filterMode.addListener (this);
        editor->distortionMode.addListener (this);
        editor->distortionIsPreFilter.addListener (this);
        
        editor->cutoff.setTooltip (parameterDescriptions[int (Parameter::cutoff)]);
        editor->resonance.setTooltip (parameterDescriptions[int (Parameter::resonance)]);
        editor->drive.setTooltip (parameterDescriptions[int (Parameter::drive)]);
        editor->distortionMode.setTooltip (parameterDescriptions[int (Parameter::distortionMode)]);
        editor->filterMode.setTooltip (parameterDescriptions[int (Parameter::filterMode)]);
        editor->distortionIsPreFilter.setTooltip (parameterDescriptions[int (Parameter::distortionIsPreFilter)]);
        
        editor->cutoff.setComponentID (parameterNames[int (Parameter::cutoff)]);
        editor->resonance.setComponentID (parameterNames[int (Parameter::resonance)]);
        editor->drive.setComponentID (parameterNames[int (Parameter::drive)]);
        editor->distortionMode.setComponentID (parameterNames[int (Parameter::distortionMode)]);
        editor->filterMode.setComponentID (parameterNames[int (Parameter::filterMode)]);
        editor->distortionIsPreFilter.setComponentID (parameterNames[int (Parameter::distortionIsPreFilter)]);
    }
}

void Controller::unbindEditor (AudioProcessorEditor& theEditor)
{
    /**
     * And we have to remember to remove these listeners because the editor may be deleted
     * out of order from our plugin...
     */
    if (auto* editor = dynamic_cast<PluginView*>(&theEditor))
    {
        editor->cutoff.removeListener (this);
        editor->resonance.removeListener (this);
        editor->drive.removeListener (this);
        editor->filterMode.removeListener (this);
        editor->distortionMode.removeListener (this);
        editor->distortionIsPreFilter.removeListener (this);
    }
}

void Controller::setSampleRate (float fs)
{
    filter[0].setSampleRate (fs);
    filter[1].setSampleRate (fs);
    distortion[0].setSampleRate (fs);
    distortion[1].setSampleRate (fs);
}

void Controller::setParameter (Parameter param, var value)
{
    /**
     * Here we are setting the parameter values. Essentially, we just store the parameter, but we should confirm that
     * the values are in a sensible range...
     */
    if (param == Parameter::drive)
    {
        jassert (float (value) >= 0.0f && float (value) <= 1.0f);
    }

    if (param == Parameter::cutoff)
    {
        jassert (float (value) >= 0.0f && float (value) <= 22050.0f);
    }

    if (param == Parameter::resonance)
    {
        jassert (float (value) >= 0.0f && float (value) <= 1.0f);
    }

    if (param == Parameter::distortionMode)
    {
        jassert (value.isInt());
        jassert (int (value) >= 0 && int (value) <= int (Distortion::Mode::bitReducer));
    }

    if (param == Parameter::filterMode)
    {
        jassert (value.isInt());
        jassert (int (value) >= 0 && int (value) <= int (Filter::Mode::highPass));
    }

    if (param == Parameter::distortionIsPreFilter)
        jassert (value.isBool());

    /**
     * the actual store for the parameter is here. 
     * Notice that almost all of this function is boiler plate checking value ranges!
     */
    parameters[int (param)] = value;
}

var Controller::getParameter (Parameter param) const
{
    return parameters[int (param)];
}

void Controller::resetParameters()
{
    /**
     * Our parameter defaults are stored here, one thing to notice is how spread
     * out all of the parameter infomration is. Constants in the header, parameters here etc etc
     */
    static const var defaultParameters[numberOfParameters] =
    {
        0.15f,
        int (Distortion::Mode::polyShaper),
        10000.0f,
        0.25f,
        int (Filter::Mode::lowPass),
        true
    };
    
    for (int param = 0; param < numberOfParameters; ++param)
        setParameter (Parameter (param), defaultParameters[param]);
}

void Controller::setParameterWithStringValue (Parameter param, String value)
{
    /**
     * Yep more code spread out to deal with changing parameters
     */
    
    if (param == Parameter::drive || param == Parameter::resonance)
        setParameter (param, value.replace (" %", {}).getFloatValue() / 100.0f);
    
    if (param == Parameter::distortionMode)
    {
        auto modes = Distortion::getModes();
        for (int index = 0, maxIndex = modes.size(); index < maxIndex; ++index)
            if (value == modes[index])
                setParameter (param, index);
    }
    
    if (param == Parameter::cutoff)
    {
        if (value.contains ("Khz"))
            setParameter (param, value.replace (" KHz", {}).getFloatValue() * 1000.0f);
        else
            setParameter (param, value.replace (" Hz", {}).getFloatValue());
    }
    
    if (param == Parameter::filterMode)
    {
        auto modes = Filter::getModes();
        for (int index = 0, maxIndex = modes.size(); index < maxIndex; ++index)
            if (value == modes[index])
                setParameter (param, index);
    }
    
    if (param == Parameter::distortionIsPreFilter)
        setParameter (param, value == "Distortion -> Filter");
}

String Controller::getParameterValue (Parameter param) const
{
    /**
     * And even more spread to the parameters, here we are converting to a string-ized parameter 
     */
    
    if (param == Parameter::drive || param == Parameter::resonance)
        return String (roundToInt (float (parameters[int (param)]) * 100.0f)) + "%";

    if (param == Parameter::distortionMode)
        return Distortion::getModes()[roundToInt (parameters[int (param)])];

    if (param == Parameter::cutoff)
    {
        auto freqInHz = float (parameters[int (param)]);
        if (freqInHz >= 1000.f)
            return String (freqInHz / 1000.0f, 2) + " Khz";

        return String (freqInHz, 2) + " Hz";
    }

    if (param == Parameter::filterMode)
        return Filter::getModes()[roundToInt (parameters[int (param)])];

    if (param == Parameter::distortionIsPreFilter)
        return (parameters[int (param)]) ? "Distortion -> Filter" : "Filter -> Distortion";


    jassertfalse;
    return {};
}

void Controller::prepareForProcess()
{
    distortion[0].setDrive (parameters[int (Parameter::drive)]);
    distortion[1].setDrive (parameters[int (Parameter::drive)]);
    distortion[0].setMode (Distortion::Mode (int (parameters[int (Parameter::distortionMode)])));
    distortion[1].setMode (Distortion::Mode (int (parameters[int (Parameter::distortionMode)])));
    
    filter[0].setFrequency (parameters[int (Parameter::cutoff)]);
    filter[1].setFrequency (parameters[int (Parameter::cutoff)]);
    filter[0].setResonance (parameters[int (Parameter::resonance)]);
    filter[1].setResonance (parameters[int (Parameter::resonance)]);
    filter[0].setMode (Filter::Mode (int (parameters[int (Parameter::filterMode)])));
    filter[1].setMode (Filter::Mode (int (parameters[int (Parameter::filterMode)])));
}

void Controller::process (AudioSampleBuffer& buffer)
{
    prepareForProcess();
    
    if (parameters[int (Parameter::distortionIsPreFilter)])
    {
        distortion[0].process (buffer, 0);
        distortion[1].process (buffer, 1);

        filter[0].process (buffer, 0);
        filter[1].process (buffer, 1);
    }
    else
    {
        filter[0].process (buffer, 0);
        filter[1].process (buffer, 1);

        distortion[0].process (buffer, 0);
        distortion[1].process (buffer, 1);
    }
}

XmlElement Controller::saveState() const
{
    /**
     * Saving is pretty simple, but we need to make sure that you are using variables that dont have any spaces,
     * so we need to reduce the parameter names to something Xml valid
     */
    
    XmlElement xml (JucePlugin_Name);
    
    for (int param = 0; param < numberOfParameters; ++param)
        xml.setAttribute (parameterKeys[param], getParameterValue (Parameter (param)));

    return xml;
}

void Controller::restoreState (XmlElement& xml, AudioProcessor& audioProcessor)
{
    /**
     * And one restore we need to do the same... Again, most of this is boiler plate... 
     */
    jassert (xml.hasTagName (JucePlugin_Name));
    if (xml.hasTagName (JucePlugin_Name))
    {
        for (int param = 0; param < numberOfParameters; ++param)
            setParameterWithStringValue (Parameter (param), xml.getStringAttribute (parameterKeys[param]));
        
        /**
         * And even worse we need to force an update to the editor. This assumes we have a known state in the editor,
         * fine for a trivial plugin, but what if its more complex?
         */
        if (auto* editor = audioProcessor.getActiveEditor())
            updateControlValues (*editor);
    }
}

void Controller::updateControlValues (AudioProcessorEditor& theEditor)
{
    if (auto* editor = dynamic_cast<PluginView*>(&theEditor))
    {
        editor->cutoff.setValue (Filter::getFrequencyRange().convertTo0to1 (getParameter (Controller::Parameter::cutoff)), NotificationType::dontSendNotification);
        editor->resonance.setValue (getParameter (Controller::Parameter::resonance), NotificationType::dontSendNotification);
        editor->drive.setValue (getParameter (Controller::Parameter::drive), NotificationType::dontSendNotification);
        editor->filterMode.setSelectedItemIndex (getParameter (Controller::Parameter::filterMode), NotificationType::dontSendNotification);
        editor->distortionMode.setSelectedItemIndex (getParameter (Controller::Parameter::distortionMode), NotificationType::dontSendNotification);
        editor->distortionIsPreFilter.setToggleState (getParameter (Controller::Parameter::distortionIsPreFilter), NotificationType::dontSendNotification);
    }
}

void Controller::buttonClicked (Button* buttonThatWasClicked)
{
    setParameter (Parameter::distortionIsPreFilter, buttonThatWasClicked->getToggleState());
}

void Controller::sliderValueChanged (Slider* slider)
{
    if (slider->getComponentID() == parameterNames [int (Parameter::cutoff)])
        setParameter (Parameter::cutoff, Filter::getFrequencyRange().convertFrom0to1 (float (slider->getValue())));

    if (slider->getComponentID() == parameterNames [int (Parameter::resonance)])
        setParameter (Parameter::resonance, float (slider->getValue()));
    
    if (slider->getComponentID() == parameterNames [int (Parameter::drive)])
        setParameter (Parameter::drive, float (slider->getValue()));
}

void Controller::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged->getComponentID() == parameterNames [int (Parameter::filterMode)])
        setParameter (Parameter::filterMode, comboBoxThatHasChanged->getSelectedItemIndex());
    
    if (comboBoxThatHasChanged->getComponentID() == parameterNames [int (Parameter::distortionMode)])
        setParameter (Parameter::distortionMode, comboBoxThatHasChanged->getSelectedItemIndex());
}

String Controller::getParameterInfo (Parameter param) const
{
    return String (parameterNames [int (param)]) + ": " + getParameterValue (param);
}

constexpr const char* Controller::parameterKeys[Controller::numberOfParameters];
constexpr const char* Controller::parameterNames[Controller::numberOfParameters];
constexpr const char* Controller::parameterDescriptions[Controller::numberOfParameters];
