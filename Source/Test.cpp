/*
  ==============================================================================

    Test.cpp
    Created: 9 Apr 2016 6:56:06pm
    Author:  geirm

  ==============================================================================
*/
#include "JuceHeader.h"
#include "Test.h"

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
	StringArray vstplugins = vstPluginFormat.searchPathsForPlugins(fsp, true);

	OwnedArray<PluginDescription> newTypes;
	for (String path : vstplugins) {
		kpl.scanAndAddFile(path, true, newTypes, vstPluginFormat);
	}
	DBG(kpl.getNumTypes());

	XmlElement* elem = kpl.createXml();
	elem->writeToFile(file, "");
	delete elem;
}