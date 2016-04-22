/*
  ==============================================================================

    SecondaryComponent.h
    Created: 21 Apr 2016 10:36:21pm
    Author:  geirm

  ==============================================================================
*/

#ifndef SECONDARYCOMPONENT_H_INCLUDED
#define SECONDARYCOMPONENT_H_INCLUDED

#include <memory>

class NodeComponent : public Component, public TextEditor::Listener {
public:
	NodeComponent();
	void textEditorReturnKeyPressed(TextEditor& editor) override;

private:
	TextEditor pluginName;
	TextEditor connectionSpec;
	TextEditor dllPath;
};

class SecondaryContentComponent : public Component {
public:
	SecondaryContentComponent();

private:
	NodeComponent nodeComponent;
};


#endif // SECONDARYCOMPONENT_H_INCLUDED