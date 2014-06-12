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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QMenuBar;
class QMenu;
class QAction;

class AboutWindow;
class TensorListWidget;
class OutputViewWidget;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);

private:
	// Fields
	QMenuBar* m_menuBar;

	QAction* m_actionImport;
	QAction* m_actionExit;
	QAction* m_actionAbout;

	QWidget* m_centralWidget;

	AboutWindow* m_aboutWindow;
	TensorListWidget* m_tensorListWidget;
	OutputViewWidget* m_outputViewWidget;

	// Methods
	void createMenuBar();

private slots:
	void onActionAboutTriggered(bool bChecked);
	void onActionExitTriggered(bool bChecked);
};

#endif // MAINWINDOW_H
