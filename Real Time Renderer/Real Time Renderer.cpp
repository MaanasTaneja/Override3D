#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "CRenderable.h"
#include "CRenderer.h"
#include "FlyCamera.h"
#include "globals.h"
#include "RenderableList.h"
#include "Scene.h"

#include <Windows.h>
#include <cstdlib>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);


void Revolve(Override::CRenderable* planet)
{
    float orbitRadius = 30.0f;
    float xPos = orbitRadius * sin(glfwGetTime() * 0.5f);           
    float zPos = orbitRadius * cos(glfwGetTime() * 0.5f);

    planet->setrotation(glm::vec3(0.0f, glfwGetTime() * 100, 0.0f)); //Make the planets rotate on the Y axis
    planet->setposition(glm::vec3(xPos, 1.0f, zPos));
}

Override::FlyCamera scenecam{ glm::vec3(-4.59293f , 6.61621f ,  1.95588f) };  

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(Globals::SCR_WIDTH, Globals::SCR_HEIGHT, "Override", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    scenecam.SetPerspective(glm::radians(45.0f), (float)Globals::SCR_WIDTH / (float)Globals::SCR_HEIGHT, 0.1f, 100.0f);

    Override::Scene currentScene{ &scenecam };
    Override::Shader shader{ "..\\Resources\\shaders\\testVert.txt", "..\\Resources\\shaders\\testFrag.txt" };




    Override::Transform windmillTrans{ 0.25f };
    windmillTrans.m_position = glm::vec3(-0.0f, 5.0f, -0.2f);
    Override::RenderableList windmill{};
    windmill = Override::Model{ "..\\Resources\\models\\windmill\\windmill2.obj", Globals::MATSPEC_PHONG, &shader, windmillTrans};
    currentScene.addSceneNode(windmill);




    Override::Transform knightTrans{ 0.5f };
    knightTrans.m_position = glm::vec3(-1.3f, 5.0f, 0.0f);
    knightTrans.m_rotation = glm::vec3(0.0f, -90.0f, 0.0f);
    Override::RenderableList knight{};
    knight = Override::Model{ "..\\Resources\\models\\knight\\knight.obj", Globals::MATSPEC_PHONG, &shader, knightTrans };
    currentScene.addSceneNode(knight);




    Override::RenderableList sunset{};
    sunset = Override::Model("..\\Resources\\models\\sunset\\sunset.obj", Globals::MATSPEC_PHONG, &shader);
    for (auto i : sunset.m_list)
    {
        i->m_type = Globals::RENDERABLE_BACKGROUND_STATIC; 
    }
    currentScene.addSceneNode(sunset);




    Override::Transform platTrans{ 0.25f };
    Override::RenderableList plat{};
    plat = Override::Model("..\\Resources\\models\\Plateau\\Plateau.obj", Globals::MATSPEC_PHONG, &shader, platTrans);
    currentScene.addSceneNode(plat);


    Override::Model planetModel{ "..\\Resources\\models\\planet\\planet.obj", Globals::MATSPEC_PHONG, &shader };
    glm::mat4 origin = glm::mat4(1.0f);     //Treat Origin as an empty parent to every planet (so as to change orbital planes)

    for (int i = 0; i < 10; i++)
    {
        Override::CRenderable* nextPlanet = new Override::CRenderable(planetModel.m_list.at(0)->getmesh(), planetModel.m_list.at(0)->getmaterial(), Globals::RENDERABLE_COMMON);   //This model always contains one mesh only.
        nextPlanet->setscale(glm::vec3(0.4f));


        origin = glm::mat4(1.0f);
        origin = glm::translate(origin, glm::vec3(0.0f));
        origin = glm::rotate(origin, glm::radians(static_cast<float>(rand() / 100 + i * 100)), glm::vec3(1.0f, 0.0f, 0.0f));
        origin = glm::rotate(origin, glm::radians(static_cast<float>(rand() / 100 + i * 100)), glm::vec3(0.0f, 1.0f, 0.0f));

        nextPlanet->m_transform.m_parentTransform = origin;  //Different Orbital planes
        nextPlanet->setcustomupdate(&Revolve);
        currentScene.addSceneNode(nextPlanet);

    }


    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        Globals::deltaTime = currentFrame - Globals::lastFrame;
        Globals::lastFrame = currentFrame;
        processInput(window);

        currentScene.beginframe();
        currentScene.updatescene(Globals::deltaTime);
        currentScene.renderscene();

        currentScene.endframe();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        scenecam.InputKey(Globals::deltaTime, Override::CAMERA_FORWARD);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        scenecam.InputKey(Globals::deltaTime, Override::CAMERA_BACK);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        scenecam.InputKey(Globals::deltaTime, Override::CAMERA_LEFT);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        scenecam.InputKey(Globals::deltaTime, Override::CAMERA_RIGHT);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    scenecam.InputMouse(xposIn, yposIn);
}
