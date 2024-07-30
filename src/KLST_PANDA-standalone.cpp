#include "KlangstromEnvironment.h"

#ifdef KLST_PANDA_STM32

#include "ApplicationStub.h" // this is important for C++

#include "Klangstrom.h"
#include "KlangstromMechanicalKey.h"
#include "KlangstromAudioCodec.h"
#include "KlangstromSerialDebug.h"
#include "KlangstromLEDs.h"
#include "KlangstromSDCard.h"
#include "Wavetable.h"

Klangstrom  klangstrom;
AudioCodec  audiocodec;
SerialDebug console;
LEDs        leds;
SDCard      sdcard;

float*    wavetable = new float[512];
Wavetable oscillator{wavetable, 512, 48000};

float mFrequency = 27.5f;
float mIntensity = 0.0f;

static const char     text[]      = "Klangstrom (KLST) is an infrastructure to facilitate generative, networked, embedded sound + music + composition."; /* File write buffer */
static const uint32_t text_length = strlen((char*) text);

void setup() {
    /* init section */
    klangstrom.init();
    console.init();
    console.println("---------------------------------------------------------");
    console.println("\033[H\033[J");
    console.info();
    console.timestamp();
    console.println("starting init");
    audiocodec.init(48000, 2, 2, 128, 16, AUDIO_DEVICE_KLST_PANDA_AUDIO_CODEC);
    leds.init();
    sdcard.init();

    console.timestamp();
    console.println("finished init");

    /* setup section */
    console.timestamp();
    console.println("starting setup");
    klangstrom.setup();

    Wavetable::fill(wavetable, 512, Wavetable::WAVEFORM_SINE);

    sdcard.status();
    sdcard.mount();

    std::vector<std::string> files;
    std::vector<std::string> directories;
    sdcard.list("/", files, directories);
    console.println("Files: %i", files.size());
    console.println("Directories: %i", directories.size());

    console.timestamp();
    sdcard.open_file("KLST.TXT", SDCard::WRITE | SDCard::CREATE_ALWAYS);
    sdcard.write((uint8_t*) text, text_length);
    sdcard.close_file();

    console.timestamp();
    sdcard.open_file("KLST.TXT", SDCard::READ);
    uint8_t bytes_read_buffer[text_length];
    sdcard.read(bytes_read_buffer, text_length);
    for (uint32_t i = 0; i < text_length; ++i) {
        console.print("%c", bytes_read_buffer[i]);
    }
    console.println("");
    sdcard.close_file();

    sdcard.unmount();

    console.timestamp();
    console.println("finished setup");
    console.println("---------------------------------------------------------");
}

void loop() {
    klangstrom.loop();
    mFrequency *= 2;
    if (mFrequency > 440) {
        mFrequency = 27.5f;
    }
    oscillator.set_frequency(mFrequency);

    mIntensity += 0.1f;
    if (mIntensity > 1.0f) {
        mIntensity = 0.0f;
    }
    leds.set(0, mIntensity);
    leds.toggle(1);
    console.println("LED intensity: %f", leds.get(0));

    console.timestamp();
    console.println("EOF");

    if (sdcard.detected()) {
        sdcard.mount();
        sdcard.open_file("KLST.TXT", SDCard::READ);
        uint8_t bytes_read_buffer[text_length];
        sdcard.read(bytes_read_buffer, text_length);
        sdcard.close_file();
        sdcard.unmount();
    }

    delay(2000);
}

void event(int event_type, uint8_t event_data) {
}

//void WEAK event(int event_type, uint8_t event_data) {}
//void WEAK encoder_event() {}

void audioblock(AudioBlock* audio_block) {
    for (int i = 0; i < audio_block->block_size; ++i) {
        audio_block->output[0][i] = oscillator.process();
        for (int j = 1; j < audio_block->output_channels; ++j) {
            audio_block->output[j][i] = audio_block->output[0][i];
        }
    }
}

#endif // KLST_PANDA_STM32
