#ifndef APPCOMPONENT_H_INCLUDED
#define APPCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "SecondaryComponent.h"
#include "AudioEngine.h"

class AppComponent : public Component {
public:
	AppComponent();
	~AppComponent();

	void paint(Graphics&);
	void resized();

private:
	AudioEngine ae{ 256, 256 }; // created first; destroyed last - important for editors
	NodeComponent nodeComponent;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppComponent)
};


#endif  // APPCOMPONENT_H_INCLUDED
