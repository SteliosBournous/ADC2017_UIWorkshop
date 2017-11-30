#include "FontPanel.h"

FontPanel::FontPanel()
{
    drawFont = Typeface::createSystemTypefaceFor (BinaryData::icons_ttf, BinaryData::icons_ttfSize);
    
    icons = {
        CharPointer_UTF8 ("\xee\xa4\x97"),
        CharPointer_UTF8 ("\xee\xa4\x8d"),
        CharPointer_UTF8 ("\xee\xa4\x8e"),
        CharPointer_UTF8 ("\xee\xa4\xa3"),
        CharPointer_UTF8 ("\xee\xa4\xa8"),
        CharPointer_UTF8 ("\xee\xa4\x94")
    };
}

void FontPanel::paint (Graphics& g)
{
    g.fillAll (Colours::white);
    
    auto innerBounds = getLocalBounds().toFloat().reduced (20.0f, 20.0f);
    auto itemBounds  = innerBounds.withWidth (innerBounds.getWidth() / 3).withHeight (innerBounds.getHeight() / 2);

    for (auto& icon : icons)
    {
        drawIcon (g, itemBounds.reduced (5.0f, 5.0f), icon);
        itemBounds.translate (itemBounds.getWidth(), 0.0f);
        if (itemBounds.getX() >= innerBounds.getWidth())
            itemBounds.translate (-innerBounds.getWidth(), itemBounds.getHeight());
    }
}

void FontPanel::drawIcon (Graphics& g, Rectangle<float> area, CharPointer_UTF8 character)
{
    g.setFont (drawFont.withHeight (std::min<float> (area.getWidth(), area.getHeight())));
    g.drawText (character, area, Justification::centred);
}
