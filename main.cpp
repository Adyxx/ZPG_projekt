
#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Application.h"


int main() {
   Application app;
   if (!app.init()) return -1;

   app.run();

   ShaderProgram::cleanup();
   return 0;
}

