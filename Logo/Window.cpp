#include "glwidget.h"
#include "window.h"
#include "mainwindow.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>

Window::Window(MainWindow *mw)
	: mainWindow(mw)
{
	glWidget = new GLWidget;

	xSlider = createSlider();
	ySlider = createSlider();
	zSlider = createSlider();

	connect(xSlider, &QSlider::valueChanged, glWidget, &GLWidget::setXRotation);
	connect(glWidget, &GLWidget::xRotationChanged, xSlider, &QSlider::setValue);
	connect(ySlider, &QSlider::valueChanged, glWidget, &GLWidget::setYRotation);
	connect(glWidget, &GLWidget::yRotationChanged, ySlider, &QSlider::setValue);
	connect(zSlider, &QSlider::valueChanged, glWidget, &GLWidget::setZRotation);
	connect(glWidget, &GLWidget::zRotationChanged, zSlider, &QSlider::setValue);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	QHBoxLayout *container = new QHBoxLayout;
	container->addWidget(glWidget);
	container->addWidget(xSlider);
	container->addWidget(ySlider);
	container->addWidget(zSlider);

	QWidget *w = new QWidget;
	w->setLayout(container);
	mainLayout->addWidget(w);
	dockBtn = new QPushButton(tr("Update"), this);
	connect(dockBtn, &QPushButton::clicked, glWidget, &GLWidget::reloadShaders);
	mainLayout->addWidget(dockBtn);

	setLayout(mainLayout);

	xSlider->setValue(50);
	ySlider->setValue(50);
	zSlider->setValue(50);

	setWindowTitle(tr("Hello GL"));
}

QSlider *Window::createSlider()
{
	QSlider *slider = new QSlider(Qt::Vertical);
	slider->setRange(0, 100);
	slider->setSingleStep(10);
	slider->setPageStep(10);
	slider->setTickInterval(10);
	slider->setTickPosition(QSlider::TicksRight);
	return slider;
}

void Window::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Escape)
		close();
	else
		QWidget::keyPressEvent(e);
}
