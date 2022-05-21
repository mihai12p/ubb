#pragma once

#include "service.h"
#include <qwidget.h>
#include <qtablewidget.h>
#include <qlayout.h>
#include <qheaderview.h>
#include <qlabel.h>
#include <qpushbutton.h>

class gui : public QWidget
{
	service& srv;

	QHBoxLayout* mainLayout = new QHBoxLayout;
	QTableWidget* listaJocuri = new QTableWidget;
	QLabel* label = new QLabel("Varsta minima");
	QPushButton* buton = new QPushButton("Sortare pret");
	QPushButton* butonFiltrare = new QPushButton("Jocuri recomandate pentru copii");
	QPushButton* butonRefresh = new QPushButton("Refresh");

	void initGui();
	void connectButoane();
	void refreshLista(const std::vector<joc>& lista);

	public:
		gui(service& srv) : srv{ srv }
		{
			initGui();
			connectButoane();
			refreshLista(srv.getAll());
		}
};

