/*
  ==============================================================================

    SecondaryComponent.cpp
    Created: 21 Apr 2016 10:36:21pm
    Author:  geirm

  ==============================================================================
*/

#include "JuceHeader.h"
#include "SecondaryComponent.h"
#include "AudioEngine.h"

NodeComponent::NodeComponent() {
	setSize(600, 25);

	addAndMakeVisible(pluginName);
	pluginName.setBounds(0, 0, 120, 25);
	pluginName.addListener(this);

	addAndMakeVisible(connectionSpec);
	connectionSpec.setBounds(pluginName.getX() + pluginName.getWidth() + 10, 0, 180, 25);
	connectionSpec.addListener(this);

	addAndMakeVisible(dllPath);
	dllPath.setBounds(connectionSpec.getX() + connectionSpec.getWidth() + 10, 0, 150, 25);
	dllPath.addListener(this);

	addAndMakeVisible(openEditorButton);
	openEditorButton.setBounds(dllPath.getX() + dllPath.getWidth() + 10, 0, 25, 25);
	openEditorButton.addListener(this);
}

void NodeComponent::textEditorReturnKeyPressed(TextEditor& editor) {
	if (&editor == &pluginName) {
		bool success = engine()->addRemovePlugin(editor.getText(), 105482);
		if (success) {
			engine()->addConnection(2, 4096, 105482, 4096);
			engine()->addConnection(105482, 0, 1, 0);
			engine()->addConnection(105482, 1, 1, 1);
		}
	} else if (&editor == &connectionSpec) {
		DBG("connection specification");
	} else if (&editor == &dllPath) {
		DBG("dll path");
	}
}

void NodeComponent::buttonClicked(Button* button) {
	if (button = &openEditorButton) {
		AudioProcessorEditor* ape = engine()->getEditor(105482);
		ape->addToDesktop(ComponentPeer::windowHasCloseButton);
	}
}

SecondaryContentComponent::SecondaryContentComponent() {
	addAndMakeVisible(nodeComponent);
	DBG("SecondaryContentComponent width: " + getWidth());
	nodeComponent.setBounds(0, 0, 400, 25);
}