/*
  ==============================================================================

    CardComponent.h
    Created: 4 Nov 2017 8:50:24pm
    Author:  Vlad Voina

  ==============================================================================
*/

#pragma once

class CardComponent : public Component
{
public:
    CardComponent (const String& text, bool shouldShowImage = false)
        : showImage (shouldShowImage)
    {
        textLabel.setText (text, dontSendNotification);
        textLabel.setJustificationType (Justification::centred);
        textLabel.setColour (Label::ColourIds::textColourId, ColourPalette::black);
        
        imageComponent.setImage (ImageFileFormat::loadFrom (BinaryData::trappistart_png, BinaryData::trappistart_pngSize));
        imageComponent.setImagePlacement (RectanglePlacement::fillDestination);
        
        addAndMakeVisible (textLabel);
        
        if (showImage)
            addAndMakeVisible (imageComponent);
    }
    
    //==============================================================================
    void setPadding (BorderSize<float> newPadding)
    {
        padding = newPadding;
    }
    
    void setPadding (float newPadding)
    {
        padding = BorderSize<float> (newPadding);
    }
    
    //==============================================================================
    String getText() const { return textLabel.getText(); }
    
    //==============================================================================
    float getDesiredWidth() const
    {
        return textLabel.getFont().getStringWidth (getText())
                        + padding.getLeft() + padding.getRight();
    }
    
    float getDesiredHeight() const
    {
        return textLabel.getFont().getHeight()
                        + padding.getTop() + padding.getBottom();
    }
    
    //==============================================================================
    void paint (Graphics& g) override
    {
        auto r = padding.subtractedFrom (getLocalBounds().toFloat());
        
        g.setColour (ColourPalette::white.withAlpha (0.75f));
        g.fillRect (r);
        
        g.setColour (Colours::black);
        g.drawRect (r, 1.0f);
    }
    
    void resized() override
    {
        auto r = padding.subtractedFrom (getLocalBounds().toFloat());
        const bool isPortrait = r.getWidth() < r.getHeight();
        
        FlexBox box;
        box.flexDirection = isPortrait ? FlexBox::Direction::column : FlexBox::Direction::row;
        
        if (showImage)
            box.items.add (FlexItem (imageComponent).withFlex (1));
        
        box.items.add (FlexItem (textLabel).withFlex (2));
        box.performLayout (r);
    }
    
    //==============================================================================
    bool showImage;
    BorderSize<float> padding;
    Label textLabel;
    ImageComponent imageComponent;
};
