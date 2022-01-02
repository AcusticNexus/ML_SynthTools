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
 * @file ml_midi_ctrl.h
 * @author Marcel Licence
 * @date 02.01.2021
 *
 * @brief   This is a little helper to make a midi split point
 *          Transpose is also supported
 */


#ifndef SRC_ML_MIDI_CTRL_H_
#define SRC_ML_MIDI_CTRL_H_


#include <Arduino.h>


void MidiCtrl_NoteOn(uint8_t ch, uint8_t note, float vel);
void MidiCtrl_NoteOff(uint8_t ch, uint8_t note);
void MidiCtrl_TransposeUp(uint8_t ch, float value);
void MidiCtrl_TransposeDown(uint8_t ch, float value);
void MidiCtrl_TransposeReset(uint8_t ch, float value);


/*
 * Following functions shall be implemented in your application
 * They will be called from the arp module
 */
void MidiCtrl_Cb_NoteOn(uint8_t ch, uint8_t note, float vel);
void MidiCtrl_Cb_NoteOff(uint8_t ch, uint8_t note);
void MidiCtrl_Status_ValueChangedIntArr(const char *descr, int value, int index);


#endif /* SRC_ML_MIDI_CTRL_H_ */
