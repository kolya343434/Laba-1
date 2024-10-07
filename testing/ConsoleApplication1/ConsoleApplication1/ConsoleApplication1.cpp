#include <glew.h>
#include <glfw3.h>
#include <cmath>
#include <iostream>

// Определяем число Pi, если оно не определено
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Размеры окна
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Функция для инициализации OpenGL
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // Белый фон
    glPointSize(2.0f);                    // Размер точки
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);  // Устанавливаем 2D ортогональную проекцию
}

// Функция для отрисовки осей X и Y
void drawAxes() {
    glColor3f(0.0f, 0.0f, 1.0f);  // Цвет осей — синий

    // Ось X
    glBegin(GL_LINES);
    glVertex2f(-10.0f, 0.0f);
    glVertex2f(10.0f, 0.0f);
    glEnd();

    // Ось Y
    glBegin(GL_LINES);
    glVertex2f(0.0f, -10.0f);
    glVertex2f(0.0f, 10.0f);
    glEnd();
}

// Функция для отрисовки графика функции y = 1/tan(x)
void drawFunction() {
    glColor3f(0.0f, 0.0f, 0.0f);  // Цвет графика — черный

    glBegin(GL_LINE_STRIP);  // Начало рисования линий
    for (float x = -10.0f; x <= 10.0f; x += 0.01f) {
        // Избегаем точек, где тангенс равен 0 (разрывы функции)
        if (fmod(x, M_PI) != 0) {  // Проверка, что x не кратен pi
            float y = 1.0f / tan(x);  // Функция y = 1/tan(x)
            // Ограничим значения y для улучшенной визуализации
            if (y > 10.0f) y = 10.0f;
            if (y < -10.0f) y = -10.0f;
            glVertex2f(x, y);  // Задаем координаты точек
        }
        else {
            glEnd();   // Завершаем линию перед асимптотой
            glBegin(GL_LINE_STRIP);  // Начинаем новую линию после асимптоты
        }
    }
    glEnd();
}

// Главная функция
int main() {
    // Инициализация GLFW
    if (!glfwInit()) {
        std::cerr << "Не удалось инициализировать GLFW" << std::endl;
        return -1;
    }

    // Создание окна
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "График функции y = 1/tan(x) с осями", NULL, NULL);
    if (!window) {
        std::cerr << "Не удалось создать окно GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Задаем контекст для OpenGL
    glfwMakeContextCurrent(window);

    // Инициализация GLEW (после создания контекста OpenGL)
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Не удалось инициализировать GLEW" << std::endl;
        return -1;
    }

    // Инициализация OpenGL
    init();

    // Основной цикл
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);  // Очистка окна

        drawAxes();      // Отрисовка осей
        drawFunction();  // Отрисовка графика

        // Обмен буферов (двойная буферизация)
        glfwSwapBuffers(window);

        // Обработка событий
        glfwPollEvents();
    }

    // Очистка ресурсов
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
