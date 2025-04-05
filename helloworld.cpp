#include <GLFW/glfw3.h>
#include <Python.h>

// Example code from https://www.glfw.org/documentation.html

int main(int argc, char* argv[]) {
    // Python init
	wchar_t* program = Py_DecodeLocale(argv[0], NULL);
	if (program == NULL) {
		fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
		exit(1);
	}

	Py_Initialize();

	#if 1
	PyRun_SimpleString("print('Python initialized!')");
	#endif

	GLFWwindow* window;
    if (!glfwInit()) {
        return -1;
	}

    /* Create a windowed mode window and its OpenGL context */
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    window = glfwCreateWindow(640, 480, "Game Engine Moment", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

	// Main loop for GLFW graphics
    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

