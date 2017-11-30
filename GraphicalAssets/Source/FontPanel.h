#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class FontPanel : public Component
{
public:
    
    FontPanel();
    ~FontPanel() = default;
    
    void paint (Graphics&) override;
    
private:
    
    void drawIcon (Graphics& g, Rectangle<float> area, CharPointer_UTF8 character);
    
    Font drawFont;
    Array<CharPointer_UTF8> icons;
};
