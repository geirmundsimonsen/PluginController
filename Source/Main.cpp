#include "../JuceLibraryCode/JuceHeader.h"
#include "AppComponent.h"

Component* createMainContentComponent();

class PluginControllerApplication : public JUCEApplication {
public:
	PluginControllerApplication() {}

	const String getApplicationName() override { return ProjectInfo::projectName; }
	const String getApplicationVersion() override { return ProjectInfo::versionString; }
	bool moreThanOneInstanceAllowed() override { return true; }

	void initialise(const String& commandLine) override {
		mainWindow = new MainWindow(getApplicationName());
	}

	void shutdown() override {
		mainWindow = nullptr; // (deletes our window)
	}

	void systemRequestedQuit() override {
		quit();
	}

	void anotherInstanceStarted(const String& commandLine) override {
		
	}

	class MainWindow : public DocumentWindow {
	public:
		MainWindow(String name) : DocumentWindow(name, Colours::lightgrey, DocumentWindow::allButtons) {
			setUsingNativeTitleBar(true);
			//setContentOwned(createMainContentComponent(), true);
			setContentOwned(new AppComponent(), true);
			DBG("After AppComponent()");
			setResizable(true, true);

			centreWithSize(getWidth(), getHeight());
			setVisible(true);
		}

		void closeButtonPressed() override {
			JUCEApplication::getInstance()->systemRequestedQuit();
		}

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
	};

private:
	ScopedPointer<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(PluginControllerApplication)
