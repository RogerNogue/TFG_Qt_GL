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

	etiq1 = createLabel("Intensitat llum 1");
	etiq2 = createLabel("Intensitat llum 2");
	etiq3 = createLabel("Intensitat llum 3");
	
	etiq1->setBuddy(xSlider);
	etiq2->setBuddy(ySlider);
	etiq3->setBuddy(zSlider);

	reflections = new QCheckBox("Reflexions");
	reflections->setChecked(1);
	softShadows = new QCheckBox("Ombres suaus");
	softShadows->setChecked(1);
	ambientOcclusion = new QCheckBox("Ambient occlusion");
	ambientOcclusion->setChecked(1);
	tempsReal = new QCheckBox("Actualitzacio temps real");
	tempsReal->setChecked(0);

	connect(reflections, &QCheckBox::stateChanged, glWidget, &GLWidget::reflectionsToggled);
	connect(softShadows, &QCheckBox::stateChanged, glWidget, &GLWidget::softShadowsToggled);
	connect(ambientOcclusion, &QCheckBox::stateChanged, glWidget, &GLWidget::ambientOcclusionToggled);
	connect(tempsReal, &QCheckBox::stateChanged, glWidget, &GLWidget::toggleAutoTimerUpdate);

	connect(xSlider, &QSlider::valueChanged, glWidget, &GLWidget::setXRotation);
	connect(glWidget, &GLWidget::xRotationChanged, xSlider, &QSlider::setValue);
	connect(ySlider, &QSlider::valueChanged, glWidget, &GLWidget::setYRotation);
	connect(glWidget, &GLWidget::yRotationChanged, ySlider, &QSlider::setValue);
	connect(zSlider, &QSlider::valueChanged, glWidget, &GLWidget::setZRotation);
	connect(glWidget, &GLWidget::zRotationChanged, zSlider, &QSlider::setValue);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	QHBoxLayout *container = new QHBoxLayout;
	QVBoxLayout *controlButtons = new QVBoxLayout;
	QHBoxLayout *Slider1 = new QHBoxLayout;
	QHBoxLayout *Slider2 = new QHBoxLayout;
	QHBoxLayout *Slider3 = new QHBoxLayout;
	
	
	container->addWidget(glWidget);
	
	Slider1->addWidget(etiq1);
	Slider1->addWidget(xSlider);
	
	Slider2->addWidget(etiq2);
	Slider2->addWidget(ySlider);

	Slider3->addWidget(etiq3);
	Slider3->addWidget(zSlider);
	
	controlButtons->addLayout(Slider1);
	controlButtons->addLayout(Slider2);
	controlButtons->addLayout(Slider3);

	controlButtons->addWidget(reflections);
	controlButtons->addWidget(softShadows);
	controlButtons->addWidget(ambientOcclusion);
	controlButtons->addWidget(tempsReal);

	controlButtons->insertStretch(-6, -2);

	container->addLayout(controlButtons);

	QWidget *w = new QWidget;
	w->setLayout(container);
	//w->setLayout(controlButtons);
	mainLayout->addWidget(w);
	dockBtn = new QPushButton(tr("Update"), this);
	connect(dockBtn, &QPushButton::clicked, glWidget, &GLWidget::reloadShaders);
	mainLayout->addWidget(dockBtn);

	setLayout(mainLayout);

	xSlider->setValue(50);
	ySlider->setValue(50);
	zSlider->setValue(50);

	setWindowTitle(tr("Visualizer"));
}

QSlider *Window::createSlider()
{
	QSlider *slider = new QSlider(Qt::Horizontal);
	slider->setRange(0, 100);
	slider->setSingleStep(20);
	slider->setPageStep(20);
	slider->setTickInterval(20);
	slider->setTickPosition(QSlider::TicksRight);
	return slider;
}

QLabel *Window::createLabel(QString nom) {
	QLabel *label = new QLabel(this);
	label->setText(nom);
	return label;
}

void Window::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Escape)
		close();
	else
		QWidget::keyPressEvent(e);
}
