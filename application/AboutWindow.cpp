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


#include "AboutWindow.h"
#include "Commons.h"

#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QTextDocument>
#include <QVBoxLayout>

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 280
#define APPNAME_FONT_POINT_SIZE 24

AboutWindow::AboutWindow(QWidget *parent) :
	QDialog(parent)
{
	setWindowTitle(tr("About Symmetries"));
	setFixedSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));

	m_appNameLabel = new QLabel(PROGRAM_NAME, this);
	QFont font = m_appNameLabel->font();
	font.setPointSize(APPNAME_FONT_POINT_SIZE);
	font.setBold(true);
	m_appNameLabel->setFont(font);

	QString appVersion("Version: ");
	appVersion.append(PROGRAM_VERSION);
	m_appVersionLabel = new QLabel(appVersion, this);

	QTextDocument* developersInfo = new QTextDocument(this);
	developersInfo->setHtml("<b>Copyright (C) 2014</b><br><br>"
		"<i>Alexey Kuzin (amkuzink@gmail.com)</i><br>"
		"Author, Maintainer, Designer<br><br>"
		"<i>Mikhail Barenboim (mikelbn@yandex.ru)</i><br>"
		"Designer");
	m_developInfo = new QTextEdit(this);
	m_developInfo->setDocument(developersInfo);
	m_developInfo->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	m_developInfo->setReadOnly(true);

	m_pushBtnOk = new QPushButton(tr("OK"), this);
	m_pushBtnOk->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(m_appNameLabel, 0, Qt::AlignLeft);
	mainLayout->addWidget(m_appVersionLabel, 0, Qt::AlignLeft);
	mainLayout->addWidget(m_developInfo, 1);
	mainLayout->addWidget(m_pushBtnOk, 0, Qt::AlignRight);
	setLayout(mainLayout);

	connect(m_pushBtnOk, SIGNAL(clicked()), this, SLOT(close()));
}
