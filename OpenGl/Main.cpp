#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() 
{
	//inicializuje GLFW
	glfwInit();	
	//poradi glfw jakou Main verzi pouzivame
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//poradi glfw jakou Minor verzi pouzivame
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//nastaveni profilu OpenGL (to moc nevim co dela, ale je to potreba)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//vytvoreni okna GLFWwindow* NAZEV = glfwCreateWindow(width, height, "name", fullscreen, sdílení resources? nevím co to je);
	GLFWwindow* window = glfwCreateWindow(800, 600, "OKNOOOOO", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//rekne at to okno zapne a bude se zobrazovat
	glfwMakeContextCurrent(window);

	//nacte vsechny OpenGL funkce (aby se daly pouzivat)
	gladLoadGL();
	//nastavi kde se openGl bude vykreslovat (x, y, width, height)
	glViewport(0, 0, 800, 600);

	//nastavi barvu pozadi (r, g, b, alpha) poziva dcimal rgb hodnoty (0.0f - 1.0f)
	glClearColor(0.7f, 0.5f, 0.1f, 1.0f);
	//vycisti barvu pozadi
	glClear(GL_COLOR_BUFFER_BIT);
	//zmeni buffery takze se zobrazi barva pozadi (jinak by to bylo jen cerny
	glfwSwapBuffers(window);


	// tohle je aby kod nepokracoval protoze se to jinak zavre
	while (!glfwWindowShouldClose(window)) {

		//aby umelo zpracovat ruzna prikazy (posouvani atd)
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}