#include "common.h"
#include "Image.h"
#include "Player.h"
#include "Map.h"

#define GLFW_DLL

#include <GLFW/glfw3.h>

constexpr GLsizei WINDOW_WIDTH = 700, WINDOW_HEIGHT = 550, MAP_WIDTH = 47, MAP_HEIGHT = 33;

struct InputState {
    bool keys[1024]{}; //массив состояний кнопок - нажата/не нажата
    GLfloat lastX = 400, lastY = 300; //исходное положение мыши
    bool firstMouse = true;
    bool captureMouse = true;  // Мышка захвачена нашим приложением или нет?
    bool capturedMouseJustNow = false;
} static Input;


GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
int FrameCounter = 0;


void OnKeyboardPressed(GLFWwindow *window, int key, int scancode, int action, int mode) {
    switch (key) {
        case GLFW_KEY_ESCAPE:
            if (action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        case GLFW_KEY_1:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            break;
        case GLFW_KEY_2:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            break;
        default:
            if (action == GLFW_PRESS)
                Input.keys[key] = true;
            else if (action == GLFW_RELEASE)
                Input.keys[key] = false;
    }
}

void processPlayerMovement(Player &player) {
    if (Input.keys[GLFW_KEY_W])
        player.ProcessInput(MovementDir::UP, (FrameCounter / 10) % 4 );
    else if (Input.keys[GLFW_KEY_S])
        player.ProcessInput(MovementDir::DOWN, (FrameCounter / 10) % 4 );
    if (Input.keys[GLFW_KEY_A])
        player.ProcessInput(MovementDir::LEFT, (FrameCounter / 10) % 4 );
    else if (Input.keys[GLFW_KEY_D])
        player.ProcessInput(MovementDir::RIGHT, (FrameCounter / 10) % 4 );
}

void OnMouseButtonClicked(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        Input.captureMouse = !Input.captureMouse;

    if (Input.captureMouse) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        Input.capturedMouseJustNow = true;
    } else
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

}

void OnMouseMove(GLFWwindow *window, double xpos, double ypos) {
    if (Input.firstMouse) {
        Input.lastX = float(xpos);
        Input.lastY = float(ypos);
        Input.firstMouse = false;
    }

    GLfloat xoffset = float(xpos) - Input.lastX;
    GLfloat yoffset = Input.lastY - float(ypos);

    Input.lastX = float(xpos);
    Input.lastY = float(ypos);
}


void OnMouseScroll(GLFWwindow *window, double xoffset, double yoffset) {
    // ...
}


int initGL() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    std::cout << "Controls: " << std::endl;
    std::cout << "press right mouse button to capture/release mouse cursor  " << std::endl;
    std::cout << "W, A, S, D - movement  " << std::endl;
    std::cout << "press ESC to exit" << std::endl;

    return 0;
}

void drawTexture(Texture texture) {
    glWindowPos2i(texture.x_pos, texture.y_pos);
    glDrawPixels(texture.img->Width(), texture.img->Height(), GL_RGBA, GL_UNSIGNED_BYTE, texture.img->Data()); GL_CHECK_ERRORS;
}

void ChangeImg(int n, Image screenBuffer, Image *img, Image *dungeon, Texture player, GLFWwindow *window) {
    FrameCounter = 0;
    while (!glfwWindowShouldClose(window) && FrameCounter < 60) {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;

        if (!n) {
            if (player.img) {
                player.img->FadeOut(5);
            }
            if (dungeon) {
                dungeon->FadeOut(5);
            }
            img->Display(5);
        }
        else {
            player.img->Display(5);
            dungeon->Display(5);
            img->FadeOut(5);
        }
        glWindowPos2i(0, 0);
        glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data()); GL_CHECK_ERRORS;
        glDrawPixels(MAP_WIDTH * 16, MAP_HEIGHT * 16, GL_RGBA, GL_UNSIGNED_BYTE, dungeon->Data()); GL_CHECK_ERRORS;
        drawTexture(player);
        glDrawPixels(img->Width(), img->Height(), GL_RGBA, GL_UNSIGNED_BYTE, img->Data()); GL_CHECK_ERRORS;

        glfwSwapBuffers(window);
        FrameCounter = (FrameCounter + 1) % 10000;
    }
}

int main(int argc, char **argv) {
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "task1 base project", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, OnKeyboardPressed);
    glfwSetCursorPosCallback(window, OnMouseMove);
    glfwSetMouseButtonCallback(window, OnMouseButtonClicked);
    glfwSetScrollCallback(window, OnMouseScroll);

    if (initGL() != 0)
        return -1;
    //Reset any OpenGL errors which could be present for some reason
    GLenum gl_error = glGetError();
    while (gl_error != GL_NO_ERROR)
        gl_error = glGetError();

    Image screenBuffer(WINDOW_WIDTH, WINDOW_HEIGHT, 4);
    Map *dungeon = nullptr;
    Player *player = nullptr;
    Image *img;
    Image coin("../resources/dungeon_V.1.0.0_nyknck/Gold/G001/G001_01.png") ;
    Image heart("../resources/heart.png") ;
    coin.doublesize();
    heart.doublesize();
    int lvlCount = 3;
    std::string lvlstr[3] = {"../resources/lvl1.png", "../resources/lvl1.png", "../resources/lvl1.png"};
    std::string dungeonstr[3] = {"../resources/map", "../resources/map", "../resources/map"};

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); GL_CHECK_ERRORS;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); GL_CHECK_ERRORS;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //game loop
    for (int i = 0; i < lvlCount; ++i){
        if (i) {
            img = new Image(lvlstr[i]);
            img->FadeOut(254);
            ChangeImg(0, screenBuffer, dungeon->Img(), img, player->TextureData(), window);
            dungeon = new Map(MAP_WIDTH, MAP_HEIGHT, dungeonstr[i]);
            Point starting_pos = dungeon->MapCoordToPoint(dungeon->Start());
            player = new Player(starting_pos, dungeon);
            dungeon->Img()->FadeOut(254);
            player->TextureData().img->FadeOut(254);
            ChangeImg(1, screenBuffer, img, dungeon->Img(), player->TextureData(), window);
        } else {
            dungeon = new Map(MAP_WIDTH, MAP_HEIGHT, dungeonstr[i]);
            Point starting_pos = dungeon->MapCoordToPoint(dungeon->Start());
            player = new Player(starting_pos, dungeon);
        }
        while (!glfwWindowShouldClose(window) && !dungeon->Win() && !dungeon->Death()) {
            GLfloat currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            glfwPollEvents();

            processPlayerMovement(*player);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            GL_CHECK_ERRORS;

            glWindowPos2i(0, 0);
            glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data());
            GL_CHECK_ERRORS;
            glWindowPos2i(0, 0);
            glDrawPixels(MAP_WIDTH * 16, MAP_HEIGHT * 16, GL_RGBA, GL_UNSIGNED_BYTE, dungeon->Data());
            GL_CHECK_ERRORS;
            glDrawPixels(coin.Width(), coin.Height(), GL_RGBA, GL_UNSIGNED_BYTE, coin.Data());
            GL_CHECK_ERRORS;
            glWindowPos2i(64, 0);
            glDrawPixels(heart.Width(), heart.Height(), GL_RGBA, GL_UNSIGNED_BYTE, heart.Data());
            GL_CHECK_ERRORS;
            //glDrawPixels(health.Width(), health.Height(), GL_RGBA, GL_UNSIGNED_BYTE, health.Data()); GL_CHECK_ERRORS;
            drawTexture(player->TextureData());

            glfwSwapBuffers(window);
            FrameCounter = (FrameCounter + 1) % 10000;
        }
        if (glfwWindowShouldClose(window)) {
            glfwTerminate();
            return 0;
        }
        if (dungeon->Death()) {
            img = new Image("../resources/death.png");
            ChangeImg(0, screenBuffer, dungeon->Img(), img, player->TextureData(), window);
            break;
        }
    }
    if (dungeon->Win()) {
        img = new Image("../resources/win.png");
        ChangeImg(0, screenBuffer, dungeon->Img(), img, player->TextureData(), window);
    }
    glfwTerminate();
    return 0;
}
