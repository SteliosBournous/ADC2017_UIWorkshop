#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class PathDataPanel : public Component
{
public:
    
    PathDataPanel();
    ~PathDataPanel() = default;
    
    void paint (Graphics&) override;
    
private:
    
    void drawPaths (Graphics& g, Rectangle<float> itemBounds, const bool stroke);
    void drawPath (Graphics& g, Rectangle<float> area, Path path, const bool stroke);

    static Path getUSBIcon();
    static Path getBluetoothIcon();
    static Path getTwitterIcon();
    static Path getPhoneIcon();
    static Path getSpeakerIcon();
    static Path getFacebookIcon();
    
    Array<Path> paths;
};
