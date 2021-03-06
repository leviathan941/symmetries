/*
	Symmetries
	Copyright (C) 2014 Alexey Kuzin <amkuzink@gmail.com>

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


#ifndef ABOUT_WINDOW_H
#define ABOUT_WINDOW_H

#include <QDialog>

class QLabel;
class QTextEdit;
class QPushButton;

class AboutWindow : public QDialog
{
	Q_OBJECT
public:
	explicit AboutWindow(QWidget *parent = 0);

private:
	QLabel* m_appNameLabel;
	QLabel* m_appVersionLabel;
	QTextEdit* m_developInfo;
	QPushButton* m_pushBtnOk;

};

#endif // ABOUT_WINDOW_H
