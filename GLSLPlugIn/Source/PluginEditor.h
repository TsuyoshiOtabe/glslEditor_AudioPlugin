/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "GLSLComponent.h"

#include <queue>
//==============================================================================
/**
*/
class GlslplugInAudioProcessorEditor  : public AudioProcessorEditor,
										private CodeDocument::Listener,
										//private ComboBox::Listener,
										//private Slider::Listener,
										//private Button::Listener,
										public KeyListener,
										private Timer
{
public:
    GlslplugInAudioProcessorEditor (GlslplugInAudioProcessor&);
    ~GlslplugInAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	
	Label m_statusLabel;
	CodeDocument /*vertexDocument,*/ fragmentDocument;
	CodeEditorComponent /*vertexEditorComp,*/ fragmentEditorComp;

	void timerCallback() override;
	void setMidiCCValue(juce::MidiMessage midiCC);

	enum
	{
		fftOrder = 9,
		fftSize = 1 << fftOrder
	};

	void pushNextSampleIntoFifo(float sample) noexcept;
	

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GlslplugInAudioProcessor& processor;
	GLSLComponent m_GLSLCompo;
	enum { shaderLinkDelay = 500 };
	void codeDocumentTextInserted(const String& /*newText*/, int /*insertIndex*/) override;
	void codeDocumentTextDeleted(int /*startIndex*/, int /*endIndex*/) override;

	std::queue<juce::MidiMessage> m_midiCCqueue;
	void sendMidiCCValue();
	void sendNextSpectrum();
	void sendNextWave();

	// FFT 
	FFT forwardFFT;
	float fifo[fftSize];
	float fftData[2 * fftSize];
	int fifoIndex;
	bool nextFFTBlockReady;

	// Wave
	bool nextWaveBlockReady;
	float waveData[fftSize];

	// KeyListener
	// こっちは走らず
	//bool keyPressed(const KeyPress& key) override;
	// 走るのはこっち
	bool keyPressed(const KeyPress& key, Component* originatingComponent) override;
	bool isCodeEditorShow = true;

	bool isNeedShaderCompile = false;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GlslplugInAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
