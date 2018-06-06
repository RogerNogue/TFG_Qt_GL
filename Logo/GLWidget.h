#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include "logo.h"
#include <iostream>
#include <stdio.h>

using namespace std;

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent = 0);
	~GLWidget();

	static bool isTransparent() { return m_transparent; }
	static void setTransparent(bool t) { m_transparent = t; }

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

	//funcions codi meu
	
	void RenderSceneCB();
	void CreateVertexBuffer();
	
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);

	//void cameraDeclaration();
	void uniformDeclaration(GLuint ShaderProgram);
	void CompileShaders();
	void processKeys(unsigned char key, int x, int y);
	void updateWindowValues(int width, int height);
	void idle();
	void InitializeGlutCallbacks();
	bool llegeixArxiu(const char* pFileName, string& outFile);
	


public slots:
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);
	void cleanup();
	void reloadShaders();

signals:
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);

protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	

private:
	void setupVertexAttribs();

	bool m_core;
	int m_xRot;
	int m_yRot;
	int m_zRot;
	QPoint m_lastPos;
	Logo m_logo;
	QOpenGLVertexArrayObject m_vao;
	QOpenGLBuffer m_logoVbo;
	QOpenGLShaderProgram *m_program;
	int m_projMatrixLoc;
	int m_mvMatrixLoc;
	int m_normalMatrixLoc;
	int m_lightPosLoc;
	QMatrix4x4 m_proj;
	QMatrix4x4 m_camera;
	QMatrix4x4 m_world;
	static bool m_transparent;

	GLuint VBO;

	const char* pVSFileName = "shader.vs";
	const char* pFSFileName = "shader.fs";
	
	//uniforms fragment shader
	const float oBSx = 20;
	const float oBSy = 15;
	const float oBSz = 25;
	const QVector3D vObs = QVector3D(oBSx, oBSy, oBSz);
	const float vRPx = 0;
	const float vRPy = 0;
	const float vRPz = 0;
	const QVector3D vVrp = QVector3D(vRPx, vRPy, vRPz);
	const float uPx = 0;
	const float uPy = 1;
	const float uPz = 0;
	const QVector3D vUp = QVector3D(uPx, uPy, uPz);
	const float fovy = 45;
	const float aspect = 1.;
	const float zNear = 0.1;
	const float zFar = 100;
	float widthPixels = 400;
	float heightPixels = 400;
	float currentTime = 0;							
	float intLlumX = 0.5;
	float intLlumY = 0.5;
	float intLlumZ = 0.5;
};

#endif