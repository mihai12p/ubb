#pragma once

#include "Service.hpp"
#include <qwidget.h>
#include <qboxlayout.h>
#include <qlistwidget.h>
#include <qformlayout.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qtablewidget.h>
#include <qheaderview.h>

class FilmeGUI : public QWidget
{
	Service& srv;

	QHBoxLayout* mainLayout = new QHBoxLayout;
	QTableWidget* listaFilmeStanga;
	QPushButton* btnAdauga;
	QPushButton* btnSterge;
	QPushButton* btnModifica;
	QPushButton* btnCauta;

	void initGUI();
	void connectSignalsSlots();
	void reincarcaLista(const std::vector<Film>& filme, const std::unique_ptr<Film> filmCautat = nullptr);
	void adaugaFilmNou();
	void stergeFilmExistent();
	void modificaFilmExistent();
	void cautaFilmExistent();

	public:
		FilmeGUI(Service& srv) : srv{ srv }
		{
			initGUI();
			connectSignalsSlots();
			reincarcaLista(srv.getAll());
		}
};
