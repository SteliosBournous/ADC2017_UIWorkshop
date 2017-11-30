#include "Controller.h"
#include "PluginView.h"

Controller::Controller (AudioProcessor& audioProcessor)
            : parameters (audioProcessor, nullptr)
{
    constructParameters();
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
        
        using APVTS = AudioProcessorValueTreeState;
        
        editor->sliders.add (new APVTS::SliderAttachment (  parameters, parameterKeys[int (Parameter::cutoff)],                editor->cutoff));
        editor->sliders.add (new APVTS::SliderAttachment (  parameters, parameterKeys[int (Parameter::resonance)],             editor->resonance));
        editor->sliders.add (new APVTS::SliderAttachment (  parameters, parameterKeys[int (Parameter::drive)],                 editor->drive));
        editor->combos.add ( new APVTS::ComboBoxAttachment (parameters, parameterKeys[int (Parameter::distortionMode)],        editor->distortionMode));
        editor->combos.add ( new APVTS::ComboBoxAttachment (parameters, parameterKeys[int (Parameter::filterMode)],            editor->filterMode));
        editor->buttons.add (new APVTS::ButtonAttachment (  parameters, parameterKeys[int (Parameter::distortionIsPreFilter)], editor->distortionIsPreFilter));

        editor->cutoff.setTooltip (parameterDescriptions[int (Parameter::cutoff)]);
        editor->resonance.setTooltip (parameterDescriptions[int (Parameter::resonance)]);
        editor->drive.setTooltip (parameterDescriptions[int (Parameter::drive)]);
        editor->distortionMode.setTooltip (parameterDescriptions[int (Parameter::distortionMode)]);
        editor->filterMode.setTooltip (parameterDescriptions[int (Parameter::filterMode)]);
        editor->distortionIsPreFilter.setTooltip (parameterDescriptions[int (Parameter::distortionIsPreFilter)]);
        
        editor->cutoff.setComponentID (parameterKeys[int (Parameter::cutoff)]);
        editor->resonance.setComponentID (parameterKeys[int (Parameter::resonance)]);
        editor->drive.setComponentID (parameterKeys[int (Parameter::drive)]);
        editor->distortionMode.setComponentID (parameterKeys[int (Parameter::distortionMode)]);
        editor->filterMode.setComponentID (parameterKeys[int (Parameter::filterMode)]);
        editor->distortionIsPreFilter.setComponentID (parameterKeys[int (Parameter::distortionIsPreFilter)]);
    }
}

void Controller::constructParameters()
{
    /**
     * All the parameters information is now grouped together here as a collection of calls. There is now a single place to setup these parameters
     * with all the convertors etc being kept together
     */
    
    parameters.createAndAddParameter (parameterKeys[int (Parameter::drive)],
                                      parameterNames[int (Parameter::drive)],
                                      "%",
                                      NormalisableRange<float> (0.0f, 1.0f),
                                      0.25f,
                                      [] (float value) -> String { return String (roundToInt (value * 100.0f)); },
                                      [] (const String& value) -> float { return float (value.getIntValue()) / 100.0f; });
    
    parameters.createAndAddParameter (parameterKeys[int (Parameter::distortionMode)], parameterNames[int (Parameter::distortionMode)],
                                     {}, NormalisableRange<float> (0.0f, float (Distortion::numberOfModes - 1)), float (Distortion::Mode::polyShaper),
                                     [] (float value) -> String {
                                         return Distortion::getModes()[roundToInt (value)];
                                     },
                                     [] (const String& value) -> float {
                                         auto modes = Distortion::getModes();
                                         for (int index = 0, maxIndex = modes.size(); index < maxIndex; ++index)
                                             if (value == modes[index])
                                                 return float (index);
                                         jassertfalse;
                                         return 0.0f;
                                     });
    
    parameters.createAndAddParameter (parameterKeys[int (Parameter::cutoff)], parameterNames[int (Parameter::cutoff)],
                                      {},
                                      NormalisableRange<float> (0.0f, 1.0f),
                                      Filter::getFrequencyRange().convertTo0to1 (10000.0f),
                                      [] (float freq01) -> String {
                                          const auto freqInHz = Filter::getFrequencyRange().convertFrom0to1 (freq01);
                                          return (freqInHz >= 1000.f) ? (String (freqInHz / 1000.0f, 2) + " Khz") : (String (freqInHz, 2) + " Hz");
                                      },
                                      [] (const String& value) -> float {
                                          float freqInHz = 0.0f;
                                          if (value.contains ("Khz"))
                                              freqInHz = value.replace (" KHz", {}).getFloatValue() * 1000.0f;
                                          else
                                              freqInHz = value.replace (" Hz", {}).getFloatValue();
                                          
                                          return Filter::getFrequencyRange().convertTo0to1 (freqInHz);
                                      });
    
    parameters.createAndAddParameter (parameterKeys[int (Parameter::resonance)], parameterNames[int (Parameter::resonance)],
                                     "%", NormalisableRange<float> (0.0f, 1.0f), 0.25f,
                                     [] (float value) -> String { return String (roundToInt (value * 100.0f)); },
                                     [] (const String& value) -> float { return float (value.getIntValue()) / 100.0f; });
    
    parameters.createAndAddParameter (parameterKeys[int (Parameter::filterMode)], parameterNames[int (Parameter::filterMode)],
                                     {}, NormalisableRange<float> (0.0f, float (Filter::numberOfModes - 1)), float (Filter::Mode::lowPass),
                                     [] (float value) -> String {
                                         return Filter::getModes()[roundToInt (value)];
                                     },
                                     [] (const String& value) -> float {
                                         auto modes = Filter::getModes();
                                         for (int index = 0, maxIndex = modes.size(); index < maxIndex; ++index)
                                             if (value == modes[index])
                                                 return float (index);
                                         jassertfalse;
                                         return 0.0f;
                                     });
    
    parameters.createAndAddParameter (parameterKeys[int (Parameter::distortionIsPreFilter)], parameterNames[int (Parameter::distortionIsPreFilter)],
                                     {}, NormalisableRange<float> (0.0f, 1.0f), 1.0f,
                                     [] (float value) -> String { return (value >= 1.0f) ? "Distortion -> Filter" : "Filter -> Distortion"; },
                                     [] (const String& value) -> float { return (value == "Distortion -> Filter") ? 1.0f : 0.0f; });
    
    
    parameters.state = ValueTree (Identifier (JucePlugin_Name));
    jassert (parameters.state.getNumChildren() == numberOfParameters);
}

void Controller::setSampleRate (float fs)
{
    filter[0].setSampleRate (fs);
    filter[1].setSampleRate (fs);
    distortion[0].setSampleRate (fs);
    distortion[1].setSampleRate (fs);
}

void Controller::prepareForProcess()
{
    const auto drive      = *parameters.getRawParameterValue (parameterKeys[int (Parameter::drive)]);
    const auto driveMode  = Distortion::Mode (roundToInt (*parameters.getRawParameterValue (parameterKeys[int (Parameter::distortionMode)])));
    const auto cutoff     = Filter::getFrequencyRange().convertFrom0to1 (*parameters.getRawParameterValue (parameterKeys[int (Parameter::cutoff)]));
    const auto resonance  = *parameters.getRawParameterValue (parameterKeys[int (Parameter::resonance)]);
    const auto filterMode = Filter::Mode (roundToInt (*parameters.getRawParameterValue (parameterKeys[int (Parameter::filterMode)])));
    
    distortion[0].setDrive (drive);
    distortion[1].setDrive (drive);
    distortion[0].setMode (driveMode);
    distortion[1].setMode (driveMode);
    
    filter[0].setFrequency (cutoff);
    filter[1].setFrequency (cutoff);
    filter[0].setResonance (resonance);
    filter[1].setResonance (resonance);
    filter[0].setMode (filterMode);
    filter[1].setMode (filterMode);
}

void Controller::process (AudioSampleBuffer& buffer)
{
    prepareForProcess();

    if ((*parameters.getRawParameterValue (parameterKeys[int (Parameter::distortionIsPreFilter)])) > 0.5f)
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
     * Notice that over half of this function is now checking that we have valid values, rather than actual functional implementation
     */
    if (ScopedPointer<XmlElement> parametersXml = parameters.state.createXml())
        return *parametersXml;

    jassertfalse;
    return XmlElement (JucePlugin_Name);
}

void Controller::restoreState (XmlElement& xml)
{
    jassert (xml.hasTagName (parameters.state.getType()));
    
    if (xml.hasTagName (parameters.state.getType()))
        parameters.state = ValueTree::fromXml (xml);
}

String Controller::getParameterInfo (String paramKey) const
{
    if (auto theParameter = parameters.getParameter (paramKey))
        return theParameter->name + ": " + theParameter->getText (theParameter->getValue(), 1024) + " " + theParameter->label;

    jassertfalse;
    return {};
}

constexpr const char* Controller::parameterKeys[Controller::numberOfParameters];
constexpr const char* Controller::parameterNames[Controller::numberOfParameters];
constexpr const char* Controller::parameterDescriptions[Controller::numberOfParameters];
