#include "../JuceLibraryCode/JuceHeader.h"
#include "AppComponent.h"
#include "SecondaryComponent.h"

AppComponent::AppComponent() {
	DBG("In AppComponent()");
	setSize(800, 600);

	setEngine(&ae);

	addAndMakeVisible(nodeComponent);
	nodeComponent.setTopLeftPosition(10, 10);
}

AppComponent::~AppComponent() {
	DBG("In ~AppComponent()");
}

void AppComponent::paint(Graphics& g) {
	g.fillAll(Colour::fromHSV(0, 0, 0.9, 1));
}

void AppComponent::resized() {
	DBG("In AppComponent::resized()");
}
