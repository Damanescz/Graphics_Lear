/*Poznamky
	priste pozmenit nejake hodnoty abych to lepe pochopil


*/
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
//typek vysvetliv jinem videu
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

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
	
	//souradnice kde jsou body sqrt je tam aby to bylo presnejsi
	GLfloat vertices[] = {
		-0.5f, -0.5f * float (sqrt(3)) / 3, 0.0f,
		 0.5f, -0.5f * float (sqrt(3)) / 3, 0.0f, 
		 0.0f,  0.5f * float (sqrt(3))*2 / 3, 0.0f 
	};


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

	//vytvoreni vertex shaderu (podobne jako vytvareni tridy)
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//preda shaderu zdrojovy kod (kolik shaderu, zdrojovy kod, NULL)
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//kompiluje pro GPU aby to pochopilo
	glCompileShader(vertexShader);

	//to stejne jenom pro fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// vytvoreni shader programu 
	GLuint shaderProgram = glCreateProgram();
	//pripoji teb sgader k programu (Logicky)
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//propoji shadery a overi jestli funguji
	glLinkProgram(shaderProgram);

	//smazeme shadery protoze uz je nepotrebujeme protoze jsme je uz propojili s programem
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//udelame buffer a vertex array object (VAO)
	GLuint VAO, VBO;
	//vytvorime vertex array object (VAO) a ulozime jeho ID do VAO
	glGenVertexArrays(1, &VAO);
	//vytvorime buffer a ulozime jeho ID do VBO
	glGenBuffers(1, &VBO);
	//pripojime vertex array VAO k OpenGL
	glBindVertexArray(VAO);
	//pripojime buffer k OpenGL (GL_ARRAY_BUFFER = typ bufferu, VBO = ID bufferu)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//vlozime data do bufferu (GL_ARRAY_BUFFER = typ bufferu, sizeof(vertices) = velikost dat, vertices = data, GL_STATIC_DRAW = jak se bude buffer pouzivat)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//nastavime jak se budou data z bufferu pouzivat (0 = index atributu, 3 = pocet hodnot, GL_FLOAT = typ dat, GL_FALSE = normalizace, 3 * sizeof(float) = velikost jednoho vertexu, (void*)0 = offset)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//povolime pouziti atributu (0 = index atributu)
	glEnableVertexAttribArray(0);

	//neni povine (odpojime buffer a vertex array object od OpenGL aby jsme to nezmenili kdyz to bezi)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);







	//nastavi barvu pozadi (r, g, b, alpha) poziva dcimal rgb hodnoty (0.0f - 1.0f)
	glClearColor(0.7f, 0.5f, 0.1f, 1.0f);
	//vycisti barvu pozadi
	glClear(GL_COLOR_BUFFER_BIT);
	//zmeni buffery takze se zobrazi barva pozadi (jinak by to bylo jen cerny
	glfwSwapBuffers(window);


	// tohle je aby kod nepokracoval protoze se to jinak zavre
	while (!glfwWindowShouldClose(window)) {
		//nevim proc to tu je
		glClearColor(0.7f, 0.5f, 0.1f, 1.0f);
		//vycisti barvu pozadi (bez toho to zacne v pozadi blikat)
		glClear(GL_COLOR_BUFFER_BIT);
		//pouzije shader program (aby se vykreslovalo s timto shaderem)
		glUseProgram(shaderProgram);
		//pripoji VAO k OpenGL (aby se vykreslovalo s timto VAO)
		glBindVertexArray(VAO);
		//vykresli trojuhelnik (GL_TRIANGLES = typ vykreslovani, 0 = index prvniho vertexu, 3 = pocet vertexu)
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//zmeni buffery takze se zobrazi trojuhelnik
		glfwSwapBuffers(window);
		//aby umelo zpracovat ruzna prikazy (posouvani atd)
		glfwPollEvents();
	}

	//smazeme vsechny objekty
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	//smazeme okno
	glfwDestroyWindow(window);
	//ukoncime glfw
	glfwTerminate();
	return 0;
}