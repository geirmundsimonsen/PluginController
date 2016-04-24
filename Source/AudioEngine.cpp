/*
  ==============================================================================

	AudioEngine.cpp
	Created: 22 Apr 2016 7:55:07pm
	Author:  User

  ==============================================================================
*/

#include "JuceHeader.h"
#include "AudioEngine.h"
#include <exception>

AudioEngine* audioEngine;

void setEngine(AudioEngine* e) { audioEngine = e; }
AudioEngine* engine() { return audioEngine; }


AudioEngine::AudioEngine(int inChannels, int outChannels) {


	String error = deviceManager.initialise(inChannels, outChannels, nullptr, true);
	if (error != "") {
		DBG(error);
		throw std::exception{ error.toRawUTF8() };
	}

	printDeviceInfo();

	if (isDeviceAvailable("ASIO Hammerfall DSP")) {
		deviceManager.setCurrentAudioDeviceType("ASIO", false);
		AudioDeviceManager::AudioDeviceSetup ads;
		deviceManager.getAudioDeviceSetup(ads);
		ads.inputDeviceName = "ASIO Hammerfall DSP";
		ads.outputDeviceName = "ASIO Hammerfall DSP";
		deviceManager.setAudioDeviceSetup(ads, true);
	}

	fillKnownPluginList(knownPluginList);
	app.setProcessor(&apg);
	formatManager.addDefaultFormats();
	AudioProcessorGraph::AudioGraphIOProcessor* output = new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::IODeviceType::audioOutputNode);
	AudioProcessorGraph::Node* outputnode = apg.addNode(output);
	AudioProcessorGraph::AudioGraphIOProcessor* midiinput = new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::IODeviceType::midiInputNode);
	AudioProcessorGraph::Node* midiinputnode = apg.addNode(midiinput);

	//MyAudioProcessor* map = new MyAudioProcessor();
	//AudioProcessorGraph::Node* mapnode = apg.addNode(map);

	deviceManager.setMidiInputEnabled("UC Midi Port 1", true);
	deviceManager.addMidiInputCallback("UC Midi Port 1", &app);
	deviceManager.addAudioCallback(&app);


	//map->addDllUnit("C:\\code\\c++\\Juce\\Control\\x64\\Debug\\LittleDLL.dll");
}

AudioEngine::~AudioEngine() {
	app.setProcessor(nullptr);
	deviceManager.removeAudioCallback(&app);
	deviceManager.removeMidiInputCallback(String::empty, &app.getMidiMessageCollector());
	deviceManager.closeAudioDevice();
}

bool AudioEngine::addRemovePlugin(String pluginName, uint32 nodeid) {	
	apg.removeNode(nodeid);
	

	PluginDescription* plugin = nullptr;
	for (PluginDescription* pd : knownPluginList) {
		if (pd->name == pluginName) {
			plugin = pd;
			break;
		}
	}
	if (plugin == nullptr) {
		DBG("plugin not found");
		return false;
	}
	DBG(plugin->name);

	String error;
	AudioPluginInstance* plugininstance = formatManager.createPluginInstance(*plugin, apg.getSampleRate(), apg.getBlockSize(), error);
	if (error != "") {
		DBG(error);
		return false;
	}

	AudioProcessorGraph::Node* plugininstancenode = apg.addNode(plugininstance, nodeid);
	if (plugininstancenode == nullptr) {
		DBG("node creation failed");
		return false;
	}

	return true;
}

bool AudioEngine::addConnection(uint32 sourceNodeId, int sourceChannelIndex, uint32 destNodeId, int destChannelIndex) {
	bool success = apg.addConnection(sourceNodeId, sourceChannelIndex, destNodeId, destChannelIndex);
	if (!success) {
		DBG("couldn't create connection");
	}
	return success;
}

AudioProcessorEditor* AudioEngine::getEditor(uint32 nodeid) {
	AudioProcessorGraph::Node* node = apg.getNodeForId(nodeid);
	if (node == nullptr) {
		DBG("node not found");
		return nullptr;
	}

	AudioProcessor* processor = node->getProcessor();
	if (processor == nullptr) {
		DBG("processor not found");
		return nullptr;
	}

	AudioProcessorEditor* editor = processor->createEditorIfNeeded();
	if (editor == nullptr) {
		DBG("couldn't create editor");
		return nullptr;
	}

	return editor;
}

void fillKnownPluginList(KnownPluginList& kpl) {
	File exedir{ File::getSpecialLocation(File::SpecialLocationType::currentExecutableFile).getParentDirectory() };

	File file{ exedir.getFullPathName() + "\\plugins.xml" };
	DBG(file.getFullPathName());

	if (file.exists()) {
		XmlDocument plugins{ file };
		XmlElement* pluginList{ plugins.getDocumentElement() };
		kpl.recreateFromXml(*pluginList);
		delete pluginList;
	} else {
		Result result = file.create();
	}

	FileSearchPath fsp{ "C:/Program Files/Native Instruments/VSTPlugins 64 bit" };
	VSTPluginFormat vstPluginFormat;
	StringArray vstplugins = vstPluginFormat.searchPathsForPlugins(fsp, true, true);

	OwnedArray<PluginDescription> newTypes;
	for (String path : vstplugins) {
		kpl.scanAndAddFile(path, true, newTypes, vstPluginFormat);
	}
	DBG(kpl.getNumTypes());

	XmlElement* elem = kpl.createXml();
	elem->writeToFile(file, "");
	delete elem;
}

bool AudioEngine::isDeviceAvailable(String deviceName) {
	const OwnedArray<AudioIODeviceType>& deviceTypes = deviceManager.getAvailableDeviceTypes();
	for (AudioIODeviceType* dt : deviceTypes) {
		dt->scanForDevices();
		StringArray sa = dt->getDeviceNames();
		for (String s : sa) {
			if (s == "deviceName") {
				return true;
			}
		}
	}
}

void AudioEngine::printDeviceInfo() {
	DBG("available devices");
	const OwnedArray<AudioIODeviceType>& deviceTypes = deviceManager.getAvailableDeviceTypes();
	for (AudioIODeviceType* dt : deviceTypes) {
		DBG(dt->getTypeName());
		dt->scanForDevices();
		StringArray sa = dt->getDeviceNames();
		for (String s : sa) {
			DBG(s);
		}
		DBG("");
	}
	DBG("current device settings");
	AudioDeviceManager::AudioDeviceSetup ads;
	deviceManager.getAudioDeviceSetup(ads);
	DBG(ads.bufferSize);
	DBG(ads.inputDeviceName);
	DBG(ads.outputDeviceName);
	DBG(ads.sampleRate);
	DBG(String{ ads.useDefaultInputChannels });
	AudioIODevice* aiod = deviceManager.getCurrentAudioDevice();
	
	DBG(deviceManager.getCurrentAudioDeviceType());
	AudioIODeviceType* aiodt = deviceManager.getCurrentDeviceTypeObject();

	DBG("");
}