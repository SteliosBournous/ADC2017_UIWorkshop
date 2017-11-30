#include "RasterPanel.h"

RasterPanel::RasterPanel()
{
    addAndMakeVisible (dimensionSlider);
    addAndMakeVisible (scalingMode);
    addAndMakeVisible (sliderLabel);
    addAndMakeVisible (infoLabel);
    addAndMakeVisible (resamplingMode);
    
    scalingMode.addItemList ({ "Scaled (Max)", "Scaled (Closest)", "Raw render", "Resize" }, 1);
    scalingMode.setSelectedId (1);
    
    resamplingMode.addItemList ( { "Nearest neighbour", "Bilinear", "Bicubic" }, 1);
    resamplingMode.setSelectedId (2);
    
    dimensionSlider.setRange (16, 1024);
    dimensionSlider.setValue (512);
    dimensionSlider.setSkewFactorFromMidPoint (128);
    
    dimensionSlider.addListener (this);
    scalingMode.addListener (this);
    resamplingMode.addListener (this);
    
    dimensionSlider.setColour (Slider::ColourIds::textBoxTextColourId, Colours::black);
    sliderLabel.setColour (Label::ColourIds::textColourId, Colours::black);
    infoLabel.setColour (Label::ColourIds::textColourId, Colours::red);
    infoLabel.setJustificationType (Justification::centredRight);
    
    loadImages();
    updateInfoLabel();
}

void RasterPanel::loadImages()
{
    images.add ({ juce::ImageCache::getFromMemory (BinaryData::icon16_png,  BinaryData::icon16_pngSize),   16 });
    images.add ({ juce::ImageCache::getFromMemory (BinaryData::icon32_png,  BinaryData::icon32_pngSize),   32 });
    images.add ({ juce::ImageCache::getFromMemory (BinaryData::icon128_png, BinaryData::icon128_pngSize), 128 });
    images.add ({ juce::ImageCache::getFromMemory (BinaryData::icon256_png, BinaryData::icon256_pngSize), 256 });
    images.add ({ juce::ImageCache::getFromMemory (BinaryData::icon512_png, BinaryData::icon512_pngSize), 512 });
}

void RasterPanel::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.drawRect (imageArea.toNearestInt(), 1);
    
    g.setImageResamplingQuality (Graphics::ResamplingQuality (resamplingMode.getSelectedId() - 1));

    if (scalingMode.getSelectedId() == ScalingMode::scaledMax)      paintImageScaled (g, images.getLast());
    if (scalingMode.getSelectedId() == ScalingMode::scaledClosest)  paintImageScaled (g, getImageForDimension());
    if (scalingMode.getSelectedId() == ScalingMode::raw)            paintImageNotScaled (g, getImageForDimension());
    if (scalingMode.getSelectedId() == ScalingMode::resize)         paintImageResized (g, getImageForDimension());
}

void RasterPanel::paintImageScaled (Graphics& g, RasterImage image)
{
    auto minImageAreaDimension = std::min<float> (imageArea.getWidth(), imageArea.getHeight());
    auto dimension = std::min<float> (minImageAreaDimension, getDimension());
    
    auto drawBounds  = imageArea.withSizeKeepingCentre (dimension, dimension).toNearestInt();
    auto imageBounds = image.image.getBounds();
    
    g.drawImage (image.image,
                 drawBounds.getX(),
                 drawBounds.getY(),
                 drawBounds.getWidth(),
                 drawBounds.getHeight(),
                 imageBounds.getX(),
                 imageBounds.getY(),
                 imageBounds.getWidth(),
                 imageBounds.getHeight());
}

void RasterPanel::paintImageNotScaled (Graphics& g, RasterImage image)
{
    auto minImageAreaDimension = std::min<float> (imageArea.getWidth(), imageArea.getHeight());
    auto dimension = std::min<float> (minImageAreaDimension, image.dimension);
    
    auto drawBounds  = imageArea.withSizeKeepingCentre (dimension, dimension).toNearestInt();
    auto imageBounds = image.image.getBounds();
    
    g.drawImage (image.image,
                 drawBounds.getX(),
                 drawBounds.getY(),
                 drawBounds.getWidth(),
                 drawBounds.getHeight(),
                 imageBounds.getX(),
                 imageBounds.getY(),
                 imageBounds.getWidth(),
                 imageBounds.getHeight());
}

void RasterPanel::paintImageResized (Graphics& g, RasterImage image)
{
    g.drawImage (image.image, imageArea, RectanglePlacement (RectanglePlacement::centred), false);
}

void RasterPanel::resized()
{
    auto innerBounds = getLocalBounds().toFloat().reduced (boundsInset);

    scalingMode.setBounds (innerBounds.getRight() - 200, innerBounds.getBottom() - 55, 200, 25);
    resamplingMode.setBounds (scalingMode.getX(), scalingMode.getBottom() + 5, scalingMode.getWidth(), scalingMode.getHeight());
    dimensionSlider.setBounds (innerBounds.getX(), scalingMode.getY(), scalingMode.getX() - 20 - innerBounds.getX(), scalingMode.getHeight());
    sliderLabel.setBounds (dimensionSlider.getX(), dimensionSlider.getBottom(), dimensionSlider.getWidth(), scalingMode.getHeight());

    imageArea = innerBounds.withBottom (scalingMode.getY() - 20);
    
    infoLabel.setBounds (imageArea.getX(), imageArea.getY(), imageArea.getWidth(), 20);
}

void RasterPanel::sliderValueChanged (Slider*)
{
    updateInfoLabel();
    repaint();
}

void RasterPanel::comboBoxChanged (ComboBox*)
{
    repaint();
}

void RasterPanel::updateInfoLabel()
{
    infoLabel.setText ("Image dimension: " + String (getImageForDimension().dimension), NotificationType::dontSendNotification);
}

int RasterPanel::getDimension() const
{
    return roundToInt (dimensionSlider.getValue());
}

RasterPanel::RasterImage RasterPanel::getImageForDimension()
{
    const auto resolution = getDimension();

    for (auto& image : images)
        if (image.dimension >= resolution)
            return image;
    
    return images.getLast();
}
