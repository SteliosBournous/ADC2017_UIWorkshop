#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class VectorPanel : public Component
{
public:
    
    VectorPanel();
    ~VectorPanel() = default;
    
    void paint (Graphics&) override;
    
private:
    
    void paintJuceLogo (Graphics& g, Rectangle<float> logoBounds);
};
