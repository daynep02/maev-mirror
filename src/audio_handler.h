#ifndef _AUDIO_HANDLER_H_
#define _AUDIO_HANDLER_H_

#include <Python.h>
#include <SFML/Graphics.hpp>

#include "common_helpers.h"

class AudioHandler {
    public:
    AudioHandler() = default;
    ~AudioHandler();

    static PyObject* CreateSound(PyObject *self, PyObject *args);
    static PyObject* FreeSound(PyObject *self, PyObject *args);
    static PyObject* PlaySound(PyObject *self, PyObject *args);
    static PyObject* PauseSound(PyObject *self, PyObject *args);
    static PyObject* SetSoundPitch(PyObject *self, PyObject *args);
    static PyObject* SetSoundVolume(PyObject *self, PyObject *args);
    static PyObject* SetSoundLoop(PyObject *self, PyObject *args);

    static PyObject* CreateMusic(PyObject *self, PyObject *args);
    static PyObject* FreeMusic(PyObject *self, PyObject *args);
    static PyObject* PlayMusic(PyObject *self, PyObject *args);
    static PyObject* PauseMusic(PyObject *self, PyObject *args);
    static PyObject* SetMusicPitch(PyObject *self, PyObject *args);
    static PyObject* SetMusicVolume(PyObject *self, PyObject *args);
    static PyObject* SetMusicLoop(PyObject *self, PyObject *args);
};

//// PYTHON DOCS ////

// corresponding documentation for engine_create_sound
PyDoc_STRVAR(
	engine_create_sound_doc,
	".. function:: create_sound(filename)\n"
	"\n"
	"  Creates a sound from the given file name.\n"
	"\n"
	"  :return: an integer representing the sound's id.\n");

// corresponding documentation for engine_free_sound
PyDoc_STRVAR(
	engine_free_sound_doc,
	".. function:: free_sound(id)\n"
	"\n"
	"  Frees the sound with the given id, allowing the id to be initialized to something else when calling create_sound\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for engine_play_sound
PyDoc_STRVAR(
	engine_play_sound_doc,
	".. function:: play_sound(id)\n"
	"\n"
	"  Plays the sound with the given id.\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for engine_pause_sound
PyDoc_STRVAR(
	engine_pause_sound_doc,
	".. function:: pause_sound(id)\n"
	"\n"
	"  Pauses the sound with the given id.\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for engine_set_sound_pitch
PyDoc_STRVAR(
	engine_set_sound_pitch_doc,
	".. function:: set_sound_pitch(id, pitch)\n"
	"\n"
	"  Sets the pitch of the sound with the given id.\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for engine_set_sound_volume
PyDoc_STRVAR(
	engine_set_sound_volume_doc,
	".. function:: set_sound_pitch(id, volume)\n"
	"\n"
	"  Sets the volume of the sound with the given id.\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for engine_set_sound_loop
PyDoc_STRVAR(
	engine_set_sound_loop_doc,
	".. function:: set_sound_loop(id, bool)\n"
	"\n"
	"  Sets the sound with the given id to loop.\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for engine_create_music
PyDoc_STRVAR(
	engine_create_music_doc,
	".. function:: create_music(filename)\n"
	"\n"
	"  Creates a music object from the given file name.\n"
	"\n"
	"  :return: an integer representing the music object's id.\n");

// corresponding documentation for engine_free_music
PyDoc_STRVAR(
	engine_free_music_doc,
	".. function:: free_music(id)\n"
	"\n"
	"  Frees the music object with the given id, allowing the id to be initialized to something else when calling create_music\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for engine_play_music
PyDoc_STRVAR(
	engine_play_music_doc,
	".. function:: play_music(id)\n"
	"\n"
	"  Plays the music with the given id.\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for engine_pause_music
PyDoc_STRVAR(
	engine_pause_music_doc,
	".. function:: pause_music(id)\n"
	"\n"
	"  Pauses the music with the given id.\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for engine_set_music_pitch
PyDoc_STRVAR(
	engine_set_music_pitch_doc,
	".. function:: set_music_pitch(id, pitch)\n"
	"\n"
	"  Sets the pitch of the music with the given id.\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for engine_set_music_volume
PyDoc_STRVAR(
	engine_set_music_volume_doc,
	".. function:: set_music_pitch(id, volume)\n"
	"\n"
	"  Sets the volume of the music with the given id.\n"
	"\n"
	"  :return: Nothing.\n");

// corresponding documentation for engine_set_music_loop
PyDoc_STRVAR(
	engine_set_music_loop_doc,
	".. function:: set_music_loop(id, bool)\n"
	"\n"
	"  Sets the music with the given id to loop.\n"
	"\n"
	"  :return: Nothing.\n");

#endif //_AUDIO_HANDLER_H_