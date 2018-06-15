#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtWidgets>

class QSlider;
class QPushButton;
class QLabel;
class QCheckBox;

class GLWidget;
class MainWindow;

class Window : public QWidget
{
	Q_OBJECT

public:
	Window(MainWindow *mw);

protected:
	void keyPressEvent(QKeyEvent *event) override;

private slots:

private:
	QSlider *createSlider();
	QLabel *createLabel(QString nom);
	QCheckBox *reflections;
	QCheckBox *softShadows;
	QCheckBox *ambientOcclusion;
	QCheckBox *tempsReal;
	GLWidget *glWidget;
	QLabel *etiq1;
	QLabel *etiq2;
	QLabel *etiq3;
	QSlider *xSlider;
	QSlider *ySlider;
	QSlider *zSlider;
	QPushButton *dockBtn;
	MainWindow *mainWindow;
};

#endif