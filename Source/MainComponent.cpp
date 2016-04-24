/*
  ==============================================================================

	This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "SecondaryComponent.h"
#include "AudioEngine.h"

class MainContentComponent : public AudioAppComponent {
public:
	MainContentComponent() {
		setSize(800, 600);
		setAudioChannels(2, 2);

		addAndMakeVisible(scc);
		scc.setBounds(20, 20, getWidth()-40, getHeight()-40);
	}

	~MainContentComponent() {
		shutdownAudio();
	}

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {
		fillKnownPluginList(knownPluginList);
		//app.setProcessor(&apg);
		//formatManager.addDefaultFormats();
		//AudioProcessorGraph::AudioGraphIOProcessor* output = new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::IODeviceType::audioOutputNode);
		//AudioProcessorGraph::Node* outputnode = apg.addNode(output);
		//MyAudioProcessor* map = new MyAudioProcessor();
		//AudioProcessorGraph::Node* mapnode = apg.addNode(map);
		//String error;
		//AudioPluginInstance* fm8 = formatManager.createPluginInstance(*internalTypes[0], apg.getSampleRate(), apg.getBlockSize(), error);
		//AudioProcessorGraph::Node* fm8node = apg.addNode(fm8);
		//apg.addConnection(3, 0, 1, 0);
		//apg.addConnection(2, 4096, 3, 4096);
		//apg.addConnection(2, 0, 1, 1);
		//deviceManager.addAudioCallback(&app);
		//map->addDllUnit("C:\\code\\c++\\Juce\\Control\\x64\\Debug\\LittleDLL.dll");
	}

	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override {
		bufferToFill.clearActiveBufferRegion();
	}

	void releaseResources() override {}

	void paint(Graphics& g) override { 
		//g.fillAll(Colours::black); 
	}

	void resized() override {}

	void mouseDown(const MouseEvent& e) override {}

private:
	AudioProcessorPlayer app{ false };
	AudioProcessorGraph apg;
	AudioPluginFormatManager formatManager;
	OwnedArray <PluginDescription> internalTypes;
	KnownPluginList knownPluginList;
	KnownPluginList::SortMethod pluginSortMethod;

	SecondaryContentComponent scc;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};

Component* createMainContentComponent() { return new MainContentComponent(); }
#endif  // MAINCOMPONENT_H_INCLUDED
