#include "bsp.h"

#include <cstdio>

#include "localcharacter.h"

// General
void Vibro(uint32_t Duration_ms, int count)
{
    printf("Vibration for %u ms, %d times\n", Duration_ms, count);
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

void PlayerStart(uint8_t SlotN, uint16_t Volume, const char* Emo, bool Repeat)
{
    printf("Start emotion %s in slot %u with volume %u and repeat mode %u\n",
           Emo, SlotN, Volume, Repeat);
}

void PlayerSetVolume(uint8_t SlotN, uint16_t Volume)
{
    printf("Change emotion volume in slot %u to %u\n", SlotN, Volume);
}

void PlayerStop(uint8_t SlotN)
{
    printf("Stop emotion in slot %u\n", SlotN);
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
void SetTodash(bool Todash)
{
    printf("Set todash flag to %d\n", Todash);
}

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
