#include "glwidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>

bool GLWidget::m_transparent = false;

GLWidget::GLWidget(QWidget *parent)
	: QOpenGLWidget(parent),
	m_xRot(0),
	m_yRot(0),
	m_zRot(0),
	m_program(0)
{
	m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
	// --transparent causes the clear color to be transparent. Therefore, on systems that
	// support it, the widget will become transparent apart from the logo.
	if (m_transparent) {
		QSurfaceFormat fmt = format();
		fmt.setAlphaBufferSize(8);
		setFormat(fmt);
	}
}

GLWidget::~GLWidget()
{
	cleanup();
}


QSize GLWidget::minimumSizeHint() const
{
	return QSize(800, 800);
}

QSize GLWidget::sizeHint() const
{
	return QSize(800, 800);
}


void GLWidget::reflectionsToggled(int state) {
	if (state == 0) {
		reflexions = 0;
	}
	else {
		reflexions = 1;
	}
	reloadShaders();
}

void GLWidget::softShadowsToggled(int state) {
	if (state == 0) {
		ombresSuaus = 0;
	}
	else {
		ombresSuaus = 1;
	}
	reloadShaders();
}

void GLWidget::ambientOcclusionToggled(int state) {
	if (state == 0) {
		ambientOcclusion = 0;
	}
	else {
		ambientOcclusion = 1;
	}
	reloadShaders();
}
static void qNormalizeAngle(int &angle)
{
	while (angle < 0)
		angle = 0;
	while (angle > 100)
		angle = 100;
}

void GLWidget::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	float angleAdaptat = (float)angle / 100;
	//bool actualitzo = false;
	//if (abs(angleAdaptat - intLlumX) > 0.1) actualitzo = true;
	if (angleAdaptat != intLlumX) {
		intLlumX = angleAdaptat;
		emit xRotationChanged(angle);
	}
	//if (actualitzo) reloadShaders();
}

void GLWidget::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	float angleAdaptat = (float)angle / 100;
	//bool actualitzo = false;
	//if (abs(angleAdaptat - intLlumY) > 0.1) actualitzo = true;
	if (angleAdaptat != intLlumY) {
		intLlumY = angleAdaptat;
		emit yRotationChanged(angle);
	}
	//if (actualitzo) reloadShaders();
}

void GLWidget::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	float angleAdaptat = (float)angle / 100;
	//bool actualitzo = false;
	//if (abs(angleAdaptat - intLlumZ) > 0.1) actualitzo = true;
	if (angleAdaptat != intLlumZ) {
		intLlumZ = angleAdaptat;
		emit zRotationChanged(angle);
	}
	//if (actualitzo) reloadShaders();
}

void GLWidget::toggleAutoTimerUpdate(int state) {
	if (state != 0) {
		connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
		timer->start(50);
	}
	else {
		timer->stop();
	}
	/*
	timer.start(100);
	pastTime = timer.elapsed();
	*/
}

void GLWidget::updateTime() {
	currentTime += 0.05;
	reloadShaders();
}

void GLWidget::reloadShaders()
	{
	
	m_program->removeAllShaders();

	m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "shader.vs");
	m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "shader.fs");
	m_program->bindAttributeLocation("vertex", 0);
	m_program->link();

	m_program->bind();

	m_program->setUniformValue(m_program->uniformLocation("oBSxu"), oBSx);
	m_program->setUniformValue(m_program->uniformLocation("oBSyu"), oBSy);
	m_program->setUniformValue(m_program->uniformLocation("oBSzu"), oBSz);

	m_program->setUniformValue(m_program->uniformLocation("vRPxu"), vRPx);
	m_program->setUniformValue(m_program->uniformLocation("vRPyu"), vRPy);
	m_program->setUniformValue(m_program->uniformLocation("vRPzu"), vRPz);

	m_program->setUniformValue(m_program->uniformLocation("uPxu"), uPx);
	m_program->setUniformValue(m_program->uniformLocation("uPyu"), uPy);
	m_program->setUniformValue(m_program->uniformLocation("uPzu"), uPz);

	m_program->setUniformValue(m_program->uniformLocation("fovyu"), fovy);
	m_program->setUniformValue(m_program->uniformLocation("aspectu"), aspect);
	m_program->setUniformValue(m_program->uniformLocation("znearu"), zNear);
	m_program->setUniformValue(m_program->uniformLocation("zfaru"), zFar);
	m_program->setUniformValue(m_program->uniformLocation("widthpixelsu"), (float)sizeHint().width());
	m_program->setUniformValue(m_program->uniformLocation("heightpixelsu"), (float)sizeHint().height());
	
	m_program->setUniformValue(m_program->uniformLocation("timeu"), currentTime);

	m_program->setUniformValue(m_program->uniformLocation("intLlumXu"), intLlumX);
	m_program->setUniformValue(m_program->uniformLocation("intLlumYu"), intLlumY);
	m_program->setUniformValue(m_program->uniformLocation("intLlumZu"), intLlumZ);
	
	m_program->setUniformValue(m_program->uniformLocation("reflexionsu"), reflexions);
	m_program->setUniformValue(m_program->uniformLocation("ombresSuausu"), ombresSuaus);
	m_program->setUniformValue(m_program->uniformLocation("ambientOcclusionu"), ambientOcclusion);
	
	m_program->release();
	
	update();

}

void GLWidget::cleanup()
{
	if (m_program == nullptr)
		return;
	makeCurrent();
	m_logoVbo.destroy();
	delete m_program;
	m_program = 0;
	doneCurrent();
}

/*
static const char *fragmentShaderSourceCore =
"#version 330\n"
"in highp vec3 vert;\n"
"in highp vec3 vertNormal;\n"
"out highp vec4 fragColor;\n"
"uniform highp vec3 lightPos;\n"
"void main() {\n"
"   highp vec3 L = normalize(lightPos - vert);\n"
"   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
"   highp vec3 color = vec3(1, 1.0, 0.0);\n"
"   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
"   fragColor = vec4(color, 1.0);\n"
"}\n";
*/

void GLWidget::initializeGL()
{
	// In this example the widget's corresponding top-level window can change
	// several times during the widget's lifetime. Whenever this happens, the
	// QOpenGLWidget's associated context is destroyed and a new one is created.
	// Therefore we have to be prepared to clean up the resources on the
	// aboutToBeDestroyed() signal, instead of the destructor. The emission of
	// the signal will be followed by an invocation of initializeGL() where we
	// can recreate all resources.
	connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

	initializeOpenGLFunctions();
	glClearColor(0, 0, 0, m_transparent ? 0 : 1);

	m_program = new QOpenGLShaderProgram;

	m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "shader.vs");
	m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "shader.fs");
	m_program->bindAttributeLocation("vertex", 0);
	m_program->link();
	
	m_program->bind();
	/*
	m_projMatrixLoc = m_program->uniformLocation("projMatrix");
	m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
	m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
	m_lightPosLoc = m_program->uniformLocation("lightPos");
	*/

	// Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
	// implementations this is optional and support may not be present
	// at all. Nonetheless the below code works in all cases and makes
	// sure there is a VAO when one is needed.
	m_vao.create();
	QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

	// Setup our vertex buffer object.
	m_logoVbo.create();
	m_logoVbo.bind();
	m_logoVbo.allocate(m_logo.constData(), m_logo.count() * sizeof(GLfloat));

	// Store the vertex attribute bindings for the program.
	setupVertexAttribs();

	// Our camera never changes in this example.
	m_camera.setToIdentity();
	m_camera.translate(0, 0, -1);

	// Light position is fixed.
	//m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

	m_program->setUniformValue(m_program->uniformLocation("oBSxu"), oBSx);
	m_program->setUniformValue(m_program->uniformLocation("oBSyu"), oBSy);
	m_program->setUniformValue(m_program->uniformLocation("oBSzu"), oBSz);

	m_program->setUniformValue(m_program->uniformLocation("vRPxu"), vRPx);
	m_program->setUniformValue(m_program->uniformLocation("vRPyu"), vRPy);
	m_program->setUniformValue(m_program->uniformLocation("vRPzu"), vRPz);

	m_program->setUniformValue(m_program->uniformLocation("uPxu"), uPx);
	m_program->setUniformValue(m_program->uniformLocation("uPyu"), uPy);
	m_program->setUniformValue(m_program->uniformLocation("uPzu"), uPz);

	m_program->setUniformValue(m_program->uniformLocation("fovyu"), fovy);
	m_program->setUniformValue(m_program->uniformLocation("aspectu"), aspect);
	m_program->setUniformValue(m_program->uniformLocation("znearu"), zNear);
	m_program->setUniformValue(m_program->uniformLocation("zfaru"), zFar);
	m_program->setUniformValue(m_program->uniformLocation("widthpixelsu"), (float)sizeHint().width());
	m_program->setUniformValue(m_program->uniformLocation("heightpixelsu"), (float)sizeHint().height());
	m_program->setUniformValue(m_program->uniformLocation("timeu"), currentTime);

	m_program->setUniformValue(m_program->uniformLocation("intLlumXu"), intLlumX);
	m_program->setUniformValue(m_program->uniformLocation("intLlumYu"), intLlumY);
	m_program->setUniformValue(m_program->uniformLocation("intLlumZu"), intLlumZ);
	
	m_program->setUniformValue(m_program->uniformLocation("reflexionsu"), reflexions);
	m_program->setUniformValue(m_program->uniformLocation("ombresSuausu"), ombresSuaus);
	m_program->setUniformValue(m_program->uniformLocation("ambientOcclusionu"), ambientOcclusion);
	
	m_program->release();
}

void GLWidget::setupVertexAttribs()
{
	m_logoVbo.bind();
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
	f->glEnableVertexAttribArray(0);
	f->glEnableVertexAttribArray(1);
	f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
	m_logoVbo.release();
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	m_world.setToIdentity();
	m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
	m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
	m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

	QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
	m_program->bind();
	/*
	m_program->setUniformValue(m_projMatrixLoc, m_proj);
	m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
	QMatrix3x3 normalMatrix = m_world.normalMatrix();
	m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);
	*/

	glDrawArrays(GL_TRIANGLES, 0, m_logo.vertexCount());

	m_program->release();
}

void GLWidget::resizeGL(int w, int h)
{
	m_proj.setToIdentity();
	m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	m_lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{/*
	int dx = event->x() - m_lastPos.x();
	int dy = event->y() - m_lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(m_xRot + 8 * dy);
		setYRotation(m_yRot + 8 * dx);
	}
	else if (event->buttons() & Qt::RightButton) {
		setXRotation(m_xRot + 8 * dy);
		setZRotation(m_zRot + 8 * dx);
	}
	m_lastPos = event->pos();*/
}