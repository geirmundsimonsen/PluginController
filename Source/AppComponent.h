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
	NodeComponent nodeComponent;
	AudioEngine ae{ 256, 256 };
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppComponent)
};


#endif  // APPCOMPONENT_H_INCLUDED
