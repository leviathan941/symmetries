/*
	Symmetries
	Copyright (C) 2014 Mikhail Barenboim <mikelbn@yandex.ru>
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

#ifndef IMPORT_TENSOR_WINDOW_H
#define IMPORT_TENSOR_WINDOW_H

#include <QDialog>
#include <boost/numeric/ublas/matrix.hpp>

class QPushButton;
class QLabel;
class QLineEdit;
class TabsWidget;

class ImportTensorWindow : public QDialog
{
	Q_OBJECT
public:
	explicit ImportTensorWindow(QWidget *parent = 0, int nDimension = 0, int nCompCount = 0);

private:
	QPushButton* m_importButton;
	QPushButton* m_okButton;
	QPushButton* m_cancelButton;
	QLabel* m_nameLabel;
	QLineEdit* m_nameLine;
	TabsWidget* m_inputTabsWidget;

	boost::numeric::ublas::matrix<QString> getMatrixFromTab(int nTab);

private slots:
	void onImportClicked();
	void onOkClicked();
	void onCancelClicked();

protected:
	void closeEvent(QCloseEvent* event);
};

#endif // IMPORT_TENSOR_WINDOW_H
