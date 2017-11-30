#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class DrawablesPanel : public Component
{
public:
    
    DrawablesPanel();
    ~DrawablesPanel() = default;
    
    void paint (Graphics&) override;
    
private:
    
    ScopedPointer<Drawable> svg;
};
