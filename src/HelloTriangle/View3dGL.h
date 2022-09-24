

#include <QOpenGLWidget>

class View3dGL : public QOpenGLWidget
{
    Q_OBJECT;
public:
    explicit View3dGL(QWidget * parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~View3dGL();

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

protected:
    unsigned int shaderProgram;
    unsigned int VBO;
    unsigned int VAO;
};

