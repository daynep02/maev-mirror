#ifndef _CALLBACK_HANDLER_H_
#define _CALLBACK_HANDLER_H_

#include <Python.h>
#include <SFML/Graphics.hpp>

class CallbackHandler {
    public:
    CallbackHandler() = default;
    ~CallbackHandler() = default;

    void HandleEvent(sf::RenderWindow* window, const std::optional<sf::Event>& event);

    static PyObject* SetOnClose(PyObject *self, PyObject *args);
};

//// PYTHON DOCS ////

// corresponding documentation for engine_set_on_close
PyDoc_STRVAR(
	engine_set_on_close_doc,
	".. function:: set_on_close(callback)\n"
	"\n"
	"  Sets a function callback on the event for the window closing, to be called before it actually closes.\n"
	"\n"
	"  :return: Nothing.\n");

#endif //_CALLBACK_HANDLER_H_