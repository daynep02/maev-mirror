#include "callback_handler.h"

// callbacks
PyObject* OnCloseCallback = NULL;

void CallbackHandler::HandleEvent(sf::RenderWindow* window, const std::optional<sf::Event>& event) {
    if (event->is<sf::Event::Closed>()) {
        if (OnCloseCallback != NULL) {
            PyObject_CallNoArgs(OnCloseCallback);
        }
    }
}

/*static*/ PyObject* CallbackHandler::SetOnClose(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
	if (nargs != 1)
	{
		printf("engine.set_on_close expects a function reference as an "
			   "argument\n");
		PyErr_BadArgument();
	}
	PyObject *pCallback = PyTuple_GetItem(args, 0);
	if (!PyCallable_Check(pCallback))
	{
		Py_XDECREF(pCallback);
		printf("engine.set_on_close expects a function reference as an "
			   "argument\n");
		PyErr_BadArgument();
	}

    OnCloseCallback = pCallback;

	Py_RETURN_NONE;
}