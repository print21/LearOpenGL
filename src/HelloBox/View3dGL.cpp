
#include <gl/glew.h>
#include "View3dGL.h"

#include <QDebug>
#include <QtMath>

#include <teapot.h>

View3dGL::View3dGL(QWidget * parent /*= nullptr*/, Qt::WindowFlags f /*= Qt::WindowFlags()*/)
    :QOpenGLWidget(parent, f)
{
    shaderProgram = 0;
    VBO = 0;
    VAO = 0;
    EBO = 0;

    modelMatrix.identity();
    viewMatrix.identity();
    projectMatrix.identity();
}

View3dGL::~View3dGL()
{
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
}

void View3dGL::initializeGL()
{
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        qWarning() << "Error: " << glewGetErrorString(err);
    }

    qInfo() << "Status: OpenGL version supported " << (char *)(glGetString(GL_VERSION));
    qInfo() << "Status: Renderer " << (char *)(glGetString(GL_RENDERER));
    qInfo() << "Status: Using GLEW " << (char *)(glewGetString(GLEW_VERSION));
}

void View3dGL::resizeGL(int w, int h)
{
    if (w > 0 && h > 0)
    {
        setViewport(0, 0, w, h);
    }
}

void View3dGL::paintGL()
{
    static bool firstDraw = true;
    if (firstDraw)
    {
        firstDraw = false;

        const char * vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "uniform mat4 transform;\n"
            "uniform mat4 projection;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = projection * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";

        const char * fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n\0";

        // build and compile our shader program
        // ------------------------------------
        // vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            qWarning() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
        }

        // fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            qWarning() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
        }

        // link shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            qWarning() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[] = {
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f
        };

        unsigned int indices[] = {
            2, 1, 0,
            3, 2, 0,

            0, 1, 5,
            5, 4, 0,

            1, 2, 6,
            6, 5, 1,

            2, 3, 7,
            7, 6, 2,

            0, 4, 7,
            7, 3, 0,

            4, 5, 6,
            6, 7, 4
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
    }

    // render
    // ------
    QSize s = this->size();
    glViewport(0, 0, s.width(), s.height());

    glClearColor(0.3f, 0.4f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

#if 1
    // draw our first triangle
    glUseProgram(shaderProgram);

    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, this->modelMatrix.get());

    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, this->projectMatrix.get());

    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
#else
    drawTeapot();
#endif
}

void View3dGL::setViewport(int x, int y, int w, int h)
{
    glViewport((GLsizei)x, (GLsizei)y, (GLsizei)w, (GLsizei)w);
    setOrthoProjection(0.0, w, 0, h, 0.0, 100.0);
}

void View3dGL::setOrthoProjection(float left, float right, float bottom, float top, float nnear, float ffar)
{
    projectMatrix.identity();
    projectMatrix[0] = 2 / (right - left);
    projectMatrix[5] = 2 / (top - bottom);
    projectMatrix[10] = -2 / (ffar - nnear);
    projectMatrix[12] = -(right + left) / (right - left);
    projectMatrix[13] = -(top + bottom) / (top - bottom);
    projectMatrix[14] = -(ffar + nnear) / (ffar - nnear);
}

static void setMatrix(int posx, int posy, int posz, int rotp, int roty, int rotr, Matrix4 & matrix)
{
    // The Euler angles (yaw,pitch,roll) are in XY'Z''-notation
    // convert to radians
    double ry = (roty / 180.0) * M_PI;
    double rp = (rotp / 180.0) * M_PI;
    double rr = (rotr / 180.0) * M_PI;

    double c1 = cos(ry / 2.0);
    double s1 = sin(ry / 2.0);
    double c2 = cos(rp / 2.0);
    double s2 = sin(rp / 2.0);
    double c3 = cos(rr / 2.0);
    double s3 = sin(rr / 2.0);

    double quat[4] = { 0.0 };
    quat[0] = c1 * c2 * s3 - s1 * s2 * c3;
    quat[1] = c1 * s2 * c3 + s1 * c2 * s3;
    quat[2] = s1 * c2 * c3 - c1 * s2 * s3;
    quat[3] = c1 * c2 * c3 + s1 * s2 * s3;


    // Taken from <http://de.wikipedia.org/wiki/Quaternionen>
    //
    const double x = quat[0];
    const double y = quat[1];
    const double z = quat[2];
    const double w = quat[3];

    float row[4] = { 0.0 };
    row[0] = 1.0 - 2.0 * (y * y + z * z);
    row[1] = 2.0 * (x * y - z * w);
    row[2] = 2.0 * (x * z + y * w);
    row[3] = 0.0f;
    matrix.setRow(0, row);

    row[0] = 2.0 * (x * y + z * w);
    row[1] = 1.0 - 2.0 * (x * x + z * z);
    row[2] = 2.0 * (y * z - x * w);
    row[3] = 0.0f;
    matrix.setRow(1, row);

    row[0] = 2.0 * (x * z - y * w);
    row[1] = 2.0 * (y * z + x * w);
    row[2] = 1.0 - 2.0 * (x * x + y * y);
    row[3] = 0.0f;
    matrix.setRow(2, row);

    row[0] = posx;
    row[1] = posy;
    row[2] = posz;
    row[3] = 0.1f;
    matrix.setRow(3, row);
}

void View3dGL::slotModelValueChanged(int posx, int posy, int posz, int rotp, int roty, int rotr)
{
    modelMatrix.identity();
    setMatrix(posx, posy, posz, rotp, roty, rotr, modelMatrix);
    this->update();
}

void View3dGL::slotViewValueChanged(int posx, int posy, int posz, int rotp, int roty, int rotr)
{
    viewMatrix.identity();
    setMatrix(posx, posy, posz, rotp, roty, rotr, viewMatrix);
}

