/*
	Symmetries
	Copyright (C) 2014 Alexey Kuzin <amkuzink@gmail.com>
	Copyright (C) 2014 Mikhail Barenboim <mikelbn@yandex.ru>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "MainWindow.h"
#include "AboutWindow.h"
#include "TensorListWidget.h"
#include "OutputViewWidget.h"
#include "CalculateWindow.h"
#include "Exceptions.h"
// Qt
#include <QMenuBar>
#include <QAction>
#include <QDialog>
#include <QHBoxLayout>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>

#define MINIMUM_WIDTH 800
#define MINIMUM_HEIGHT 600
#define CONTENT_MARGIN 20

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	createMenuBar();

	m_aboutWindow = new AboutWindow(this);
	m_tensorListWidget = new TensorListWidget(this);
	m_outputViewWidget = new OutputViewWidget(this);

	QHBoxLayout* mainLayout = new QHBoxLayout;
	mainLayout->addWidget(m_tensorListWidget, 0, Qt::AlignLeft);
	mainLayout->addWidget(m_outputViewWidget, 1);
	mainLayout->setSpacing(10);

	m_centralWidget = new QWidget(this);
	m_centralWidget->setLayout(mainLayout);

	setWindowTitle(tr("Symmetries"));
	setMinimumSize(QSize(MINIMUM_WIDTH, MINIMUM_HEIGHT));
	setObjectName(QString("MainWindow"));
	setCentralWidget(m_centralWidget);
	setContentsMargins(CONTENT_MARGIN, CONTENT_MARGIN, CONTENT_MARGIN, CONTENT_MARGIN);
}

///////////////////////////////////////////////////////////////////////////
void MainWindow::createMenuBar()
{
	m_menuBar = new QMenuBar(this);

	QMenu* fileMenu = m_menuBar->addMenu(tr("&File"));
	QMenu* helpMenu = m_menuBar->addMenu(tr("&Help"));

	m_actionAbout = new QAction(tr("About"), this);
	m_actionAbout->setMenuRole(QAction::AboutRole);
	helpMenu->addAction(m_actionAbout);

	m_actionImport = new QAction(tr("Import"), this);
	m_actionImport->setMenuRole(QAction::NoRole);
	fileMenu->addAction(m_actionImport);
	m_actionImport->setVisible(false);

	m_actionCalculate = new QAction(tr("Calculate"), this);
	m_actionCalculate->setMenuRole(QAction::NoRole);
	fileMenu->addAction(m_actionCalculate);

	m_actionExit = new QAction(tr("Exit"), this);
	m_actionExit->setMenuRole(QAction::QuitRole);
	fileMenu->addSeparator();
	fileMenu->addAction(m_actionExit);

	m_menuBar->setNativeMenuBar(true);
	setMenuBar(m_menuBar);

	if (!connect(m_actionAbout, SIGNAL(triggered(bool)), this, SLOT(onActionAboutTriggered(bool))))
	{
		qDebug("actionAbout connect is failed");
	}
	if (!connect(m_actionExit, SIGNAL(triggered(bool)), this, SLOT(onActionExitTriggered(bool))))
	{
		qDebug("actionExit connect is failed");
	}
	if (!connect(m_actionCalculate, SIGNAL(triggered(bool)), this,
		SLOT(onActionCalculateTriggered(bool))))
	{
		qDebug("actionCalculate connect is failed");
	}
}

///////////////////////////////////////////////////////////////////////////
void MainWindow::onActionAboutTriggered(bool bChecked)
{
	m_aboutWindow->show();
}

///////////////////////////////////////////////////////////////////////////
void MainWindow::onActionExitTriggered(bool bChecked)
{
	qApp->exit();
}

///////////////////////////////////////////////////////////////////////////
void MainWindow::onActionCalculateTriggered(bool bChecked)
{
	try
	{
		CalculateWindow* calcWindow = new CalculateWindow(this);
		connect(calcWindow, SIGNAL(connectionCalculated(MatrixVectorExp)), m_outputViewWidget,
			SLOT(onTensorCalculated(MatrixVectorExp)));
		connect(calcWindow, SIGNAL(lieAlgebraBuilt(QString)), m_outputViewWidget,
			SLOT(onOtherCalculated(QString)));
		calcWindow->exec();
	}
	CATCH_GUI("Error")
}
