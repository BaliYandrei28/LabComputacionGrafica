#include <iostream>

//#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;

int main() {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D", NULL, NULL);
    glfwSetFramebufferSizeCallback(window, resize);

    // Verificación de errores de creación de ventana
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    // Verificación de errores de inicialización de glew
    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Información de OpenGL
    std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    // Vértices del delfín low-poly: Posición (X, Y, Z) y Color (R, G, B)
    float vertices[] = {
        // Posición (X, Y, Z)          // Color (R, G, B)
        // 0: Punta del hocico
         0.60f, -0.15f, 0.0f,          0.55f, 0.75f, 0.90f,
         // 1: Mandíbula inferior
          0.48f, -0.17f, 0.0f,          0.35f, 0.55f, 0.85f,
          // 2: Frente superior
           0.45f, -0.05f, 0.0f,          0.75f, 0.60f, 0.85f,
           // 3: Cabeza superior
            0.35f,  0.08f, 0.0f,          0.55f, 0.40f, 0.70f,
            // 4: Cabeza centro
             0.32f, -0.05f, 0.0f,          0.55f, 0.75f, 0.90f,
             // 5: Garganta/Pecho superior
              0.35f, -0.16f, 0.0f,          0.35f, 0.55f, 0.85f,
              // 6: Lomo alto (inicio aleta dorsal)
               0.15f,  0.12f, 0.0f,          0.75f, 0.60f, 0.85f,
               // 7: Punta aleta dorsal
                0.02f,  0.10f, 0.0f,          0.45f, 0.30f, 0.60f,
                // 8: Base aleta dorsal
                 0.08f,  0.00f, 0.0f,          0.55f, 0.40f, 0.70f,
                 // 9: Torso centro
                  0.15f, -0.08f, 0.0f,          0.55f, 0.75f, 0.90f,
                  // 10: Pecho / Base aleta pectoral
                   0.20f, -0.22f, 0.0f,          0.35f, 0.55f, 0.85f,
                   // 11: Punta aleta pectoral
                    0.18f, -0.32f, 0.0f,          0.55f, 0.75f, 0.90f,
                    // 12: Borde posterior aleta pectoral
                     0.26f, -0.30f, 0.0f,          0.35f, 0.55f, 0.85f,
                     // 13: Lomo medio
                     -0.08f, -0.02f, 0.0f,          0.75f, 0.60f, 0.85f,
                     // 14: Vientre medio
                     -0.02f, -0.20f, 0.0f,          0.45f, 0.30f, 0.60f,
                     // 15: Lomo bajo
                     -0.18f, -0.15f, 0.0f,          0.35f, 0.55f, 0.85f,
                     // 16: Vientre bajo
                     -0.10f, -0.32f, 0.0f,          0.55f, 0.40f, 0.70f,
                     // 17: Cola superior
                     -0.28f, -0.38f, 0.0f,          0.75f, 0.60f, 0.85f,
                     // 18: Cola inferior / pedúnculo
                     -0.20f, -0.50f, 0.0f,          0.45f, 0.30f, 0.60f,
                     // 19: Aleta caudal izquierda
                     -0.35f, -0.60f, 0.0f,          0.35f, 0.55f, 0.85f,
                     // 20: Aleta caudal centro
                     -0.28f, -0.52f, 0.0f,          0.55f, 0.75f, 0.90f,
                     // 21: Aleta caudal derecha
                     -0.18f, -0.58f, 0.0f,          0.55f, 0.40f, 0.70f
    };

    unsigned int indices[] = {
        // Hocico y Cabeza
        0, 2, 1,
        2, 4, 1,
        2, 3, 4,
        1, 4, 5,

        // Aleta dorsal y Torso superior
        7, 6, 8,
        6, 3, 8,
        3, 4, 8,
        8, 4, 9,
        4, 5, 9,
        5, 10, 9,

        // Aleta Pectoral
        10, 11, 12,
        10, 12, 9,

        // Torso medio y Vientre
        8, 13, 9,
        13, 14, 9,
        9, 14, 10,

        // Parte posterior / Lomo bajo
        13, 15, 14,
        15, 16, 14,
        15, 17, 16,
        17, 18, 16,

        // Aleta Caudal (Cola)
        17, 19, 20,
        17, 20, 18,
        18, 20, 21
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Enlazar Vertex Array Object
    glBindVertexArray(VAO);

    // Buffer de vértices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Buffer de elementos (índices)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Atributo 0: Posición
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Atributo 1: Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Limpiar pantalla con fondo blanco como en la imagen
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.Use();
        glBindVertexArray(VAO);

        // Dibujar los triángulos indexados
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}