#include <SFML/Audio.hpp>
#include "audio_handler.h"

#include <vector>
#include <algorithm>

// possible bug: vectors could technically change the address of the contents,
// so be careful
std::vector<sf::SoundBuffer *> sound_buffers;
std::vector<sf::Sound *> sounds;
std::vector<long> free_sounds;

std::vector<sf::Music *> musics;
std::vector<long> free_musics;

AudioHandler::~AudioHandler() {
    std::for_each(sound_buffers.begin(), sound_buffers.end(), delete_ptr());
    sound_buffers.clear();

    std::for_each(sounds.begin(), sounds.end(), delete_ptr());
    sounds.clear();

    std::for_each(musics.begin(), musics.end(), delete_ptr());
    musics.clear();
}

/*static*/ PyObject *AudioHandler::CreateSound(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 1) {
        printf("engine.create_sound expects a single string as an argument\n");
        PyErr_BadArgument();
    }
    PyObject *pName = PyTuple_GetItem(args, 0);
    
    printf("engine.create_sound: Creating String\n");
    
    std::string name = PyUnicode_AsUTF8(pName);
    
    printf("engine.create_sound: Creating SoundBuffer from %s\n", name.c_str());
    sf::SoundBuffer *sound_buffer = new sf::SoundBuffer();
    bool res = sound_buffer->loadFromFile(name.c_str());
    if (!res) {
        printf("engine.create_sound: Could not load file %s\n", name.c_str());
        PyErr_BadArgument();
    }
    
    printf("engine.create_sound: Checking for Free Sounds\n");
    long loc;
    if (!free_sounds.empty()) {
        printf("engine.create_sound: Using Free Sounds\n");
        loc = free_sounds.back();
        free_sounds.pop_back();
        printf("engine.create_sound: Adding to Vector\n");
        delete sound_buffers.at(loc);
        sound_buffers.at(loc) = sound_buffer;
        sf::Sound *sound = new sf::Sound(*sound_buffers.at(loc));
        //sound->setPosition({0, 0});
        delete sounds.at(loc);
        sounds.at(loc) = sound;
    } else {
        sound_buffers.push_back(sound_buffer);
        loc = sound_buffers.size() - 1;
        printf("engine.create_sound: Adding to Vector\n");
        sf::Sound *sprite = new sf::Sound(*sound_buffers.at(loc));
        //sprite->setPosition({0, 0});
        sounds.push_back(sprite);
        loc = sound_buffers.size() - 1;
    }
    
    printf("engine.create_sound: Returning ID\n");
    
    //Py_XDECREF(pName);
    
    return PyLong_FromLong(loc);
}

/*static*/ PyObject *AudioHandler::FreeSound(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 1) {
        printf("engine.free_sound expects a single long as an argument\n");
        PyErr_BadArgument();
    }
    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId)) {
        Py_XDECREF(pId);
        printf("engine.free_sound expects a single long as an argument\n");
        PyErr_BadArgument();
    }

    long id = PyLong_AsLong(pId);

    if (sounds.size() <= id || id < 0) {
        Py_XDECREF(pId);
        printf("engine.free_sound got a sprite id out of range\n");
        PyErr_BadArgument();
    }

    free_sounds.push_back(id);

    // Py_XDECREF(pId);

    Py_RETURN_NONE;
}

/*static*/ PyObject* AudioHandler::PlaySound(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 1) {
        printf("engine.play_sound expects a single long as an argument\n");
        PyErr_BadArgument();
    }
    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId)) {
        Py_XDECREF(pId);
        printf("engine.play_sound expects a single long as an argument\n");
        PyErr_BadArgument();
    }

    long id = PyLong_AsLong(pId);

    if (sounds.size() <= id || id < 0) {
        Py_XDECREF(pId);
        printf("engine.play_sound got a sprite id out of range\n");
        PyErr_BadArgument();
    }

    sounds.at(id)->play();

    Py_RETURN_NONE;
}

/*static*/ PyObject* AudioHandler::PauseSound(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 1) {
        printf("engine.pause_sound expects a single long as an argument\n");
        PyErr_BadArgument();
    }
    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId)) {
        Py_XDECREF(pId);
        printf("engine.pause_sound expects a single long as an argument\n");
        PyErr_BadArgument();
    }

    long id = PyLong_AsLong(pId);

    if (sounds.size() <= id || id < 0) {
        Py_XDECREF(pId);
        printf("engine.pause_sound got a sprite id out of range\n");
        PyErr_BadArgument();
    }

    sounds.at(id)->pause();

    Py_RETURN_NONE;
}

/*static*/ PyObject* AudioHandler::SetSoundPitch(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 2) {
        printf("engine.set_sound_pitch expects a single long and a single float as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId)) {
        Py_XDECREF(pId);
        printf("engine.set_sound_pitch expects a single long and a single float as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pPitch = PyTuple_GetItem(args, 1);
    if (!PyFloat_Check(pPitch)) {
        Py_XDECREF(pPitch);
        printf("engine.set_sound_pitch expects a single long and a single float as arguments\n");
        PyErr_BadArgument();
    }

    long id = PyLong_AsLong(pId);
    float pitch = PyFloat_AsDouble(pPitch);

    if (sounds.size() <= id || id < 0) {
        Py_XDECREF(pId);
        printf("engine.set_sound_pitch got a sound id out of range\n");
        PyErr_BadArgument();
    }

    sounds.at(id)->setPitch(pitch);

    Py_RETURN_NONE;
}

/*static*/ PyObject* AudioHandler::SetSoundVolume(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 2) {
        printf("engine.set_sound_volume expects a single long and a single float as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId)) {
        Py_XDECREF(pId);
        printf("engine.set_sound_volume expects a single long and a single float as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pVolume = PyTuple_GetItem(args, 1);
    if (!PyFloat_Check(pVolume)) {
        Py_XDECREF(pVolume);
        printf("engine.set_sound_volume expects a single long and a single float as arguments\n");
        PyErr_BadArgument();
    }

    long id = PyLong_AsLong(pId);
    float volume = PyFloat_AsDouble(pVolume);
    if (volume > 100.0f) volume = 100.0f;
    if (volume < 0.0f) volume = 0.0f;

    if (sounds.size() <= id || id < 0) {
        Py_XDECREF(pId);
        printf("engine.set_sound_volume got a sound id out of range\n");
        PyErr_BadArgument();
    }

    sounds.at(id)->setVolume(volume);

    Py_RETURN_NONE;
}

/*static*/ PyObject* AudioHandler::SetSoundLoop(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 2) {
        printf("engine.set_sound_pitch expects a single long and a single bool as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId)) {
        Py_XDECREF(pId);
        printf("engine.set_sound_pitch expects a single long and a single bool as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pLoop = PyTuple_GetItem(args, 1);
    if (!PyBool_Check(pLoop)) {
        Py_XDECREF(pLoop);
        printf("engine.set_sound_pitch expects a single long and a single bool as arguments\n");
        PyErr_BadArgument();
    }

    long id = PyLong_AsLong(pId);
    bool loop = PyLong_AsLong(pLoop);

    if (sounds.size() <= id || id < 0) {
        Py_XDECREF(pId);
        printf("engine.set_sound_pitch got a sound id out of range\n");
        PyErr_BadArgument();
    }

    sounds.at(id)->setLooping(loop);

    Py_RETURN_NONE;
}

/*static*/ PyObject *AudioHandler::CreateMusic(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 1) {
        printf("engine.create_music expects a single string as an argument\n");
        PyErr_BadArgument();
    }
    PyObject *pName = PyTuple_GetItem(args, 0);
    
    printf("engine.create_music: Creating String\n");
    
    std::string name = PyUnicode_AsUTF8(pName);
    
    printf("engine.create_music: Checking for Free Musics\n");
    long loc;
    if (!free_musics.empty()) {
        printf("engine.create_music: Using Free Musics\n");
        loc = free_musics.back();
        free_musics.pop_back();
        printf("engine.create_music: Adding to Vector\n");
        sf::Music* music;
        if (!music->openFromFile(name.c_str())) {
            printf("engine.create_music: Could not load file %s\n", name.c_str());
            PyErr_BadArgument();
            return PyLong_FromLong(-1);
        }

        delete musics.at(loc);
        musics.at(loc) = music;
    } else {
        printf("engine.create_music: Adding to Vector\n");
        sf::Music* music = new sf::Music;
        if (!music->openFromFile(name.c_str())) {
            printf("engine.create_music: Could not load file %s\n", name.c_str());
            PyErr_BadArgument();
            return PyLong_FromLong(-1);
        }
        musics.push_back(music);
        loc = musics.size() - 1;
    }
    
    printf("engine.create_music: Returning ID\n");
    
    //Py_XDECREF(pName);
    
    return PyLong_FromLong(loc);
}

/*static*/ PyObject *AudioHandler::FreeMusic(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 1) {
        printf("engine.free_music expects a single long as an argument\n");
        PyErr_BadArgument();
    }
    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId)) {
        Py_XDECREF(pId);
        printf("engine.free_music expects a single long as an argument\n");
        PyErr_BadArgument();
    }

    long id = PyLong_AsLong(pId);

    if (musics.size() <= id || id < 0) {
        Py_XDECREF(pId);
        printf("engine.free_music got a sprite id out of range\n");
        PyErr_BadArgument();
    }

    free_musics.push_back(id);

    // Py_XDECREF(pId);

    Py_RETURN_NONE;
}

/*static*/ PyObject* AudioHandler::PlayMusic(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 1) {
        printf("engine.play_music expects a single long as an argument\n");
        PyErr_BadArgument();
    }
    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId)) {
        Py_XDECREF(pId);
        printf("engine.play_music expects a single long as an argument\n");
        PyErr_BadArgument();
    }

    long id = PyLong_AsLong(pId);

    if (musics.size() <= id || id < 0) {
        Py_XDECREF(pId);
        printf("engine.play_music got a sprite id out of range\n");
        PyErr_BadArgument();
    }

    musics.at(id)->play();

    Py_RETURN_NONE;
}

/*static*/ PyObject* AudioHandler::PauseMusic(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 1) {
        printf("engine.pause_music expects a single long as an argument\n");
        PyErr_BadArgument();
    }
    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId)) {
        Py_XDECREF(pId);
        printf("engine.pause_music expects a single long as an argument\n");
        PyErr_BadArgument();
    }

    long id = PyLong_AsLong(pId);

    if (musics.size() <= id || id < 0) {
        Py_XDECREF(pId);
        printf("engine.pause_music got a sprite id out of range\n");
        PyErr_BadArgument();
    }

    musics.at(id)->pause();

    Py_RETURN_NONE;
}

/*static*/ PyObject* AudioHandler::SetMusicPitch(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 2) {
        printf("engine.set_music_pitch expects a single long and a single float as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId)) {
        Py_XDECREF(pId);
        printf("engine.set_music_pitch expects a single long and a single float as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pPitch = PyTuple_GetItem(args, 1);
    if (!PyFloat_Check(pPitch)) {
        Py_XDECREF(pPitch);
        printf("engine.set_music_pitch expects a single long and a single float as arguments\n");
        PyErr_BadArgument();
    }

    long id = PyLong_AsLong(pId);
    float pitch = PyFloat_AsDouble(pPitch);

    if (musics.size() <= id || id < 0) {
        Py_XDECREF(pId);
        printf("engine.set_music_pitch got a sound id out of range\n");
        PyErr_BadArgument();
    }

    musics.at(id)->setPitch(pitch);

    Py_RETURN_NONE;
}

/*static*/ PyObject* AudioHandler::SetMusicVolume(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 2) {
        printf("engine.set_music_volume expects a single long and a single float as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId)) {
        Py_XDECREF(pId);
        printf("engine.set_music_volume expects a single long and a single float as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pVolume = PyTuple_GetItem(args, 1);
    if (!PyFloat_Check(pVolume)) {
        Py_XDECREF(pVolume);
        printf("engine.set_music_volume expects a single long and a single float as arguments\n");
        PyErr_BadArgument();
    }

    long id = PyLong_AsLong(pId);
    float volume = PyFloat_AsDouble(pVolume);
    if (volume > 100.0f) volume = 100.0f;
    if (volume < 0.0f) volume = 0.0f;

    if (musics.size() <= id || id < 0) {
        Py_XDECREF(pId);
        printf("engine.set_music_volume got a sound id out of range\n");
        PyErr_BadArgument();
    }

    musics.at(id)->setVolume(volume);

    Py_RETURN_NONE;
}

/*static*/ PyObject* AudioHandler::SetMusicLoop(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if (nargs != 2) {
        printf("engine.set_music_pitch expects a single long and a single bool as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pId = PyTuple_GetItem(args, 0);
    if (!PyLong_Check(pId)) {
        Py_XDECREF(pId);
        printf("engine.set_music_pitch expects a single long and a single bool as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pLoop = PyTuple_GetItem(args, 1);
    if (!PyBool_Check(pLoop)) {
        Py_XDECREF(pLoop);
        printf("engine.set_music_pitch expects a single long and a single bool as arguments\n");
        PyErr_BadArgument();
    }

    long id = PyLong_AsLong(pId);
    bool loop = PyLong_AsLong(pLoop);

    if (musics.size() <= id || id < 0) {
        Py_XDECREF(pId);
        printf("engine.set_music_pitch got a sound id out of range\n");
        PyErr_BadArgument();
    }

    musics.at(id)->setLooping(loop);

    Py_RETURN_NONE;
}