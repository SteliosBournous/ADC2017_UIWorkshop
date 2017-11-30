#include "DrawablesPanel.h"

DrawablesPanel::DrawablesPanel()
{
    const String svgData (CharPointer_UTF8 (BinaryData::juceLogo_svg), BinaryData::juceLogo_svgSize);
    if (ScopedPointer<XmlElement> root = XmlDocument::parse (svgData))
        svg = Drawable::createFromSVG (*root);
}

void DrawablesPanel::paint (Graphics& g)
{
    g.fillAll (Colours::white);
    
    if (svg != nullptr)
        svg->drawWithin (g, getLocalBounds().toFloat().reduced (30.0f, 10.0f), RectanglePlacement (RectanglePlacement::centred), 1.0f);
}
