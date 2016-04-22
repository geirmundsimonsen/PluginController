/*
  ==============================================================================

	Test.h
	Created: 9 Apr 2016 6:56:06pm
	Author:  geirm

  ==============================================================================
*/

#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <queue>
#include <list>
#include <Windows.h>

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
		for (DllUnit& dllunit : dllunits) {
			dllunit.sendBuffers(buffer, midiMessages);
		}
	}
	double getTailLengthSeconds() const override { return 0; }
	bool acceptsMidi() const override { return false; }
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

#endif  // TEST_H_INCLUDED
