/*
  ==============================================================================

    SecondaryComponent.cpp
    Created: 21 Apr 2016 10:36:21pm
    Author:  geirm

  ==============================================================================
*/

#include "JuceHeader.h"
#include "SecondaryComponent.h"

NodeComponent::NodeComponent() {
	addAndMakeVisible(pluginName);
	pluginName.setBounds(0, 0, 120, 25);

	addAndMakeVisible(connectionSpec);
	connectionSpec.setBounds(pluginName.getX() + pluginName.getWidth() + 10, 0, 180, 25);

	addAndMakeVisible(dllPath);
	dllPath.setBounds(connectionSpec.getX() + connectionSpec.getWidth() + 10, 0, 150, 25);
}

void NodeComponent::textEditorReturnKeyPressed(TextEditor& editor) {
	if (&editor == &pluginName) {
		DBG("plugin name");
	} else if (&editor == &connectionSpec) {
		DBG("connection specification");
	} else if (&editor == &dllPath) {
		DBG("dll path");
	}
}

SecondaryContentComponent::SecondaryContentComponent() {
	addAndMakeVisible(nodeComponent);
	DBG("SecondaryContentComponent width: " + getWidth());
	nodeComponent.setBounds(0, 0, 400, 25);
}