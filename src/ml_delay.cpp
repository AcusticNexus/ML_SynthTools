/*
 * Copyright (c) 2021 Marcel Licence
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Dieses Programm ist Freie Software: Sie k�nnen es unter den Bedingungen
 * der GNU General Public License, wie von der Free Software Foundation,
 * Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
 * ver�ffentlichten Version, weiter verteilen und/oder modifizieren.
 *
 * Dieses Programm wird in der Hoffnung bereitgestellt, dass es n�tzlich sein wird, jedoch
 * OHNE JEDE GEW�HR,; sogar ohne die implizite
 * Gew�hr der MARKTF�HIGKEIT oder EIGNUNG F�R EINEN BESTIMMTEN ZWECK.
 * Siehe die GNU General Public License f�r weitere Einzelheiten.
 *
 * Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
 * Programm erhalten haben. Wenn nicht, siehe <https://www.gnu.org/licenses/>.
 */

/**
 * @file ml_delay.cpp
 * @author Marcel Licence
 * @date 06.01.2022
 *
 * @brief This is a simple implementation of a stereo s16 delay line
 * - level adjustable
 * - feedback
 * - length adjustable
 */


#ifdef __CDT_PARSER__
#include <cdt.h>
#endif


#include <ml_delay.h>


/*
 * module variables
 */
static int16_t *delayLine_l;

static float delayToMix = 0;
static float delayInLvl = 1.0f;
static float delayFeedback = 0;
static uint32_t delayLenMax = 0;
static uint32_t delayLen = 11098;
static uint32_t delayIn = 0;
static uint32_t delayOut = 0;
//static uint32_t sampleRate = 44100;

void Delay_Init(int16_t *buffer, uint32_t len)
{
    psramInit();
    Serial.printf("Total PSRAM: %d\n", ESP.getPsramSize());
    Serial.printf("Free PSRAM: %d\n", ESP.getFreePsram());

    delayLine_l = buffer;
    delayLenMax = len;

    if (delayLine_l == NULL)
    {
        Serial.printf("Not memory available!\n");
    }

    Delay_Reset();
}

void Delay_Reset(void)
{
    for (int i = 0; i < delayLenMax; i++)
    {
        delayLine_l[i] = 0;
    }
}

void Delay_Process(float *signal_l, float *signal_r)
{
#if 0
    *signal_l *= (1.0f - delayFeedback);
    *signal_r *= (1.0f - delayFeedback);
#endif

    delayLine_l[delayIn] = (((float)0x8000) * *signal_l * delayInLvl);


    delayOut = delayIn + (1 + delayLenMax - delayLen);

    if (delayOut >= delayLenMax)
    {
        delayOut -= delayLenMax;
    }

    *signal_l += ((float)delayLine_l[delayOut]) * delayToMix / ((float)0x8000);


    delayLine_l[delayIn] += (((float)delayLine_l[delayOut]) * delayFeedback);


    delayIn ++;

    if (delayIn >= delayLenMax)
    {
        delayIn = 0;
    }
}

void Delay_Process_Buff(float *signal_l, int buffLen)
{
#if 0
    *signal_l *= (1.0f - delayFeedback);
    *signal_r *= (1.0f - delayFeedback);
#endif

    for (int n = 0; n < buffLen; n++)
    {
        delayLine_l[delayIn] = (((float)0x8000) * signal_l[n] * delayInLvl);

        delayOut = delayIn + (1 + delayLenMax - delayLen);

        if (delayOut >= delayLenMax)
        {
            delayOut -= delayLenMax;
        }

        signal_l[n] += ((float)delayLine_l[delayOut]) * delayToMix / ((float)0x8000);

        delayLine_l[delayIn] += (((float)delayLine_l[delayOut]) * delayFeedback);

        delayIn ++;

        if (delayIn >= delayLenMax)
        {
            delayIn = 0;
        }
    }
}

void Delay_SetInputLevel(uint8_t unused, float value)
{
    delayInLvl = value;
    // Status_ValueChangedFloat("DelayInputLevel", value);
}

void Delay_SetFeedback(uint8_t unused, float value)
{
    delayFeedback = value;
    // Status_ValueChangedFloat("DelayFeedback", value);
}

void Delay_SetOutputLevel(uint8_t unused, float value)
{
    delayToMix = value;
    // Status_ValueChangedFloat("DelayOutputLevel", value);
}

void Delay_SetLength(uint8_t unused, float value)
{
    delayLen = (uint32_t)(((float)delayLenMax - 1.0f) * value);
    // Status_ValueChangedFloat("DelayLenMs", delayLen * (1000.0f / ((float)sampleRate)));
}
