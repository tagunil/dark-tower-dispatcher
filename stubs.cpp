#include "bsp.h"

#include <cstdio>

#include "localcharacter.h"

// General
void Vibro(uint32_t Duration_ms)
{
    printf("Vibration for %u ms\n", Duration_ms);
}

void PowerOff()
{
    printf("Power off\n");
}

void SleepEnable()
{
    printf("Enable sleep\n");
}

void SleepDisable()
{
    printf("Disable sleep\n");
}

// Sound
void PlayerVolumeUp()
{
    printf("Volume up\n");
}

void PlayerVolumeDown()
{
    printf("Volume down\n");
}

// Screen
void ScreenHighlight(uint32_t Value_percent)
{
    printf("Screen brightness set to %u%%\n", Value_percent);
}

void ScreenAddBMPToQueue(const char* AFilename)
{
    printf("File %s added to queue\n", AFilename);
}

void ScreenShowNextBMP()
{
    printf("Show next BMP\n");
}

void ScreenShowActualBMP()
{
    printf("Show actual BMP\n");
}

uint32_t GetBMPQueueLength()
{
    return 5;
}

void ScreenShowPicture(const char* AFilename)
{
        printf("File %s displayed\n", AFilename);
}

// Character
void SaveState(int Dogan, bool Dead, bool Corrupted)
{
    printf("State saved: %d %d %d\n", Dogan, Dead, Corrupted);
}

void SaveKatet(const KaTetLinks *)
{
    printf("Links saved\n");
}

void SaveCounters(const KaTetCounters *)
{
    printf("Counters saved\n");
}
