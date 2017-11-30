ADC 2017 User Interface Workshop

Thanks for attending the GUI Workshop at the 2017 ADC. We hope that you find it useful
This repository contains examples and worked code showing some of the concepts that we discussed in the workshop.

It is structure thus:

ADC GUI Workshop.key - This is the keynote that we presented from. It contains all the slides from the day, including our speaking notes. It is in Apple Keynote format. We can provide it in PDF if Keynote format is not suitable for you.
ADC GUI Workshop Quick Tip Cards.pages - This is a set of quick tips covering the major areas we discussed. Use them to jog your memory after the fact! They are provided in Apple Pages format as well as a PDF

GraphicalAssets - This project shows examples of the different drawing functionality mentioned. 
	Once you have opened the project in your IDE, navigate to the "Panels" folder. Each of the classes inside this folder show a different aspect of graphical interface drawing (Specifically - Fonts, Vectors, Rasters, Paths and Drawables)
	When run, you can use the top tabs to switch between the panels, to see the different effects and the different drawing styles

MVCFilter - This project implements a simple filter / distortion audio plugin. We use it as the basis for our use of AudioProcessorValueTreeState conversion.
    Structurally we have broken the folders up in to the key "Model" / "View" / "Controller" areas. The controller class is responsible for the actual processing / save / restoring etc.
    The DSP on display is not intended to be super exciting, so please dont blame us for the slightly lacklustre implementations!

VTFilter - This project is the MVCFilter once it has been improved by using AudioProcessorValueTreeState
	The structure matches the MVCFilter (many classes are identical). All the key changes take place in the "Controller" class...

ResponsiveLayout - This project shows the Flexbox and Grid examples. To best follow these, we recommend referring to the keynote slides.

JUCE - This is a copy of the JUCE master branch to make these projects self contained
