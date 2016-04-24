/*
  ==============================================================================

    AudioEngine.h
    Created: 22 Apr 2016 7:55:07pm
    Author:  User

  ==============================================================================
*/

#ifndef AUDIOENGINE_H_INCLUDED
#define AUDIOENGINE_H_INCLUDED

class AudioEngine {
public:
	AudioEngine(int, int);
	~AudioEngine();
	bool addRemovePlugin(String pluginName, uint32 nodeid);
	bool addConnection(uint32 sourceNodeId, int sourceChannelIndex, uint32 destNodeId, int destChannelIndex);
	AudioProcessorEditor* getEditor(uint32 nodeid);
	bool isDeviceAvailable(String deviceName);
	void printDeviceInfo();

private:
	AudioDeviceManager deviceManager;
	AudioProcessorPlayer app{ false };
	AudioProcessorGraph apg;
	AudioPluginFormatManager formatManager;
	KnownPluginList knownPluginList;
	KnownPluginList::SortMethod pluginSortMethod;
};


void setEngine(AudioEngine* e);
AudioEngine* engine();

void fillKnownPluginList(KnownPluginList& kpl);

class DllUnit {
public:
	DllUnit(String pathToDll) {
		dl = new DynamicLibrary;
		dl->open(pathToDll);
		sendBuffers = static_cast<void(*)(AudioBuffer<float>&, MidiBuffer&)>(dl->getFunction("sendBuffers"));
	}
	~DllUnit() {
		delete(dl);
	}

	DynamicLibrary* dl;
	void(*sendBuffers)(AudioBuffer<float>&, MidiBuffer&);
};

class MyAudioProcessor : public AudioProcessor {
public:
	~MyAudioProcessor() override {}
	const String getName() const override { return "MyAudioProcessor"; }
	void prepareToPlay(double, int) override {/* query busArrangement*/ }
	void releaseResources() override {}
	void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override {
		/*
		for (DllUnit& dllunit : dllunits) {
			dllunit.sendBuffers(buffer, midiMessages);
		}
		*/
	}

	double getTailLengthSeconds() const override { return 0; }
	bool acceptsMidi() const override { return true; }
	bool producesMidi() const override { return true; }
	AudioProcessorEditor* createEditor() override { return nullptr; }
	bool hasEditor() const override { return false; }
	int getNumPrograms() override { return 0; }
	int getCurrentProgram() override { return 0; }
	void setCurrentProgram(int index) override {}
	const String getProgramName(int index) override { return ""; }
	void changeProgramName(int index, const String& newName) override {}
	void getStateInformation(MemoryBlock& destData) override {}
	void setStateInformation(const void* data, int sizeInBytes) override {}
	bool silenceInProducesSilenceOut() const override { return true; }

	void addDllUnit(String path) {
		dllunits.emplace_back(path);
	}
private:
	std::vector<DllUnit> dllunits;
};


#endif  // AUDIOENGINE_H_INCLUDED
