#include "glwidget.h"
#include "qopenglwidget.h"
#include <QOpenGLFunctions_3_3_Core>
#include "qdebug.h"
#include "qopenglshaderprogram.h"
#include "vertex.h"

// Creates a quad
Vertex sg_vertices[] = {
    // Vertex Array Object
    // Left bottom triangle
    Vertex( QVector3D( -1.00f,  1.00f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector2D(1.0f, 1.0f) ), // Top left
    Vertex( QVector3D( -1.00f, -1.00f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector2D(1.0f, 0.0f) ), // Bottom left
    Vertex( QVector3D(  1.00f, -1.00f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector2D(0.0f, 0.0f) ), // Bottom right
    // Right top triangle
    Vertex( QVector3D( 1.00f, -1.00f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector2D(-1.0f, -1.0f) ),// Bottom right
    Vertex( QVector3D( 1.00f,  1.00f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector2D(-1.0f, 0.0f) ), // Top right
    Vertex( QVector3D(-1.00f,  1.00f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector2D(0.0f, 0.0f) )   // Top left

    /* Element Buffer Object
    Vertex( QVector3D( 1.0f, 1.0f, 0.0f), QVector2D( 1.0f, 1.0f)), // Top Right
    Vertex( QVector3D( 1.0f,-1.0f, 0.0f), QVector2D( 1.0f,-1.0f)), // Bottom Right
    Vertex( QVector3D(-1.0f,-1.0f, 0.0f), QVector2D(-1.0f,-1.0f)), // Bottom Left
    Vertex( QVector3D(-1.0f,-1.0f, 0.0f), QVector2D(-1.0f, 1.0f))  // Top Left*/
};

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void GLWidget::initializeGL()
{
    //QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    //qDebug() << "initializeGL called.";

    // Initializes to white background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);

    // Create Shader and bind it so it is the active shader for this program
    // Vertex shaders create interpolated fragment data.
    // The Fragment shader takes that data and outputs final data to a buffer
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/simple.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/simple.frag");
    m_program->link();
    m_program->bind();

    // Create Buffer

    m_vertex.create();
    m_vertex.bind();
    m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertex.allocate(sg_vertices, sizeof(sg_vertices));


    // Create the Vertex Array Object (vao)
    m_object.create();
    m_object.bind();
    //f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //f->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),(GLvoid*)0);
    //EBO.bind();
    m_program->enableAttributeArray(0); // position
    m_program->enableAttributeArray(1); // color
    m_program->enableAttributeArray(2); // texture coords
    m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
    m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());
    m_program->setAttributeBuffer(2,GL_FLOAT, Vertex::textureOffset(), Vertex::textureTupleSize, Vertex::stride());

    // Unbind them all in the opposite order in which they occurred.
    m_object.release();
    m_vertex.release();
    m_program->release();

     //glEnable(GL_TEXTURE_2D);
}

void GLWidget::resizeGL(int width, int height)
{
   //qDebug() << "ResizeGL called.\nWidth: " << width << "\nHeight: " << height << "\n";

   if(currentImage.isNull() != true)
   {
        loadTextureImg(currentImage);
   }
   else
   {
        emitGLStartup();
   }
}

void GLWidget::emitGLStartup()
{
    emit GLStartup();
    emit imageChanged(currentImage);
}

void GLWidget::paintGL()
{
    //qDebug() << "paintGL called";
    m_vertex.bind();
        // Render using the shader
        m_program->bind();
        {
            m_object.bind();
            glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertices) / sizeof(sg_vertices[0]));
            m_object.release();
        }
        m_program->release();
}

void GLWidget::tearDownGL()
{
    // Destroy OpenGL info
    m_object.destroy();
    m_vertex.destroy();
    delete m_program;
}

void GLWidget::loadTextureImg(QString imagePath)
{
    makeCurrent();

    //creates Qimage object
    imageObject = new QImage();
    imageObject->load(imagePath);

    //qDebug() << imagePath;
    if(imagePath == ":/noImageAvailable.jpg")
    {
        *imageObject = imageObject->mirrored(true,false);
    }

    *imageObject = QGLWidget::convertToGLFormat(*imageObject);

    GLuint tex;

    //turns image into a texture and binds it
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D,tex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageObject->width(), imageObject->height(), 0, GL_RGBA,GL_UNSIGNED_BYTE, imageObject->bits());

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    //glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_ADD);

    m_program->bind();
    {
        m_object.bind();
        glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertices) / sizeof(sg_vertices[0]));
        m_object.release();
    }
    m_program->release();

    // Unbinds the texture... good practice apparently. But, to allow for tinting, I keep it bound.
    //glBindTexture(GL_TEXTURE_2D, 0);

    //QOpenGLFunctions::glGenerateMipmap(GL_TEXTURE_2D);

    doneCurrent();

    currentImage = imagePath;
    emit imageChanged(currentImage);
}

void GLWidget::setCurrentImage(QString imagePath)
{
    currentImage = imagePath;
}

void GLWidget::changeValue(int value,char* name)
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    GLfloat glValue;

    std::string str(name);

    if(str != "contrast")
    {
        glValue = (float)value / 100.0f;
    }
    else
    {
        glValue = (float)value / 10.0f;
    }

    m_program->bind();
    int loc = f->glGetUniformLocation(m_program->programId(),name);

    if(loc != -1)
    {
        m_program->setUniformValue(loc,glValue);
    }
    m_program->release();
}
