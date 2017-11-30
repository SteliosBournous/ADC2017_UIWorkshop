#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class RasterPanel : public Component
                  , private Slider::Listener
                  , private ComboBox::Listener
{
public:
    
    RasterPanel();
    ~RasterPanel() = default;
    
    void paint (Graphics&) override;
    void resized() override;
    
private:
    
    struct RasterImage
    {
        Image image;
        int dimension;
    };
    
    enum ScalingMode
    {
        scaledMax = 1,
        scaledClosest,
        raw,
        resize,
    };
    
    void sliderValueChanged (Slider*) override;
    void comboBoxChanged (ComboBox*) override;
    
    void loadImages();
    RasterImage getImageForDimension();
    int getDimension() const;
    
    void updateInfoLabel();
    
    void paintImageScaled (Graphics& g, RasterImage image);
    void paintImageNotScaled (Graphics& g, RasterImage image);
    void paintImageResized (Graphics& g, RasterImage image);
    
    
    static constexpr float boundsInset = 20.0f;
    
    Rectangle<float> imageArea;
    Slider dimensionSlider;
    ComboBox scalingMode;
    ComboBox resamplingMode;
    Label sliderLabel { "", "Image dimension" };
    Label infoLabel;
    
    Array<RasterImage> images;
};
