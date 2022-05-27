#pragma once

#include "Service.hpp"
#include "Observer.h"
#include "MyQList.h"

#include <qwidget.h>
#include <qboxlayout.h>
#include <qlistwidget.h>
#include <qformlayout.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qheaderview.h>
#include <qcheckbox.h>
#include <qplaintextedit.h>
#include <qpainter.h>

class FilmeGUI : public QWidget, public Observer
{
	Service& srv;

	QHBoxLayout* mainLayout = new QHBoxLayout;

	MyQList* model;
	QListView* listaFilmeStanga = new QListView;

	QPushButton* btnCosCRUDGUI = new QPushButton("&Cos CRUD");
	QPushButton* btnCosReadOnly = new QPushButton("&Cos artistic");

	QPushButton* btnAdauga = new QPushButton("&Adauga film");
	QPushButton* btnSterge = new QPushButton("&Sterge film");
	QPushButton* btnModifica = new QPushButton("&Modifica film");
	QPushButton* btnCauta = new QPushButton("&Cauta film");
	QPushButton* btnFiltreaza = new QPushButton("&Filtreaza filme");
	QPushButton* btnSorteaza = new QPushButton("&Sorteaza filme");
	QPushButton* btnInchiriaza = new QPushButton("&Inchiriaza film");
	QPushButton* btnGolesteCos = new QPushButton("&Goleste cos");
	QPushButton* btnRaportCos = new QPushButton("&Raport cos");
	QPushButton* btnGenereazaCos = new QPushButton("&Genereaza cos");
	QPushButton* btnExportCos = new QPushButton("&Export cos");
	QPushButton* btnUndo = new QPushButton("&Undo");
	QPushButton* btnRefresh = new QPushButton("&Reimprospateaza");

	void initGUI();
	void connectSignalsSlots();
	void reincarcaLista(const std::vector<Film>& filme, std::unique_ptr<Film> filmCautat = nullptr);
	void adaugaFilmNou();
	void stergeFilmExistent();
	void modificaFilmExistent();
	void cautaFilmExistent();
	void filtreazaFilmeExistente();
	void sorteazaFilmeExistente();
	void inchiriazaFilmExistent();
	void raportCosFilme();
	void exportCosFilme();
	void undo();

	public:
		FilmeGUI(Service& srv) : srv{ srv }
		{
			initGUI();
			model = new MyQList{ srv.getAll() };
			listaFilmeStanga->setModel(model);
			connectSignalsSlots();
			reincarcaLista(srv.getAll());
		}

		~FilmeGUI()
		{
			srv.stergeObserver(this);
		}

		void update() override
		{
			reincarcaLista(srv.getAll());
		}
};

class CosCRUDGUI : public QWidget, public Observer
{
	Service& srv;

	QHBoxLayout* mainLayout = new QHBoxLayout;
	QListWidget* listaCos = new QListWidget;
	QPushButton* btnGenereazaCos = new QPushButton("&Genereaza cos");
	QPushButton* btnGolesteCos = new QPushButton("&Goleste cos");

	void initGUI();
	void connectSignalsSlots();
	void reincarcaCos(const std::vector<Film>& filme);

	public:
		CosCRUDGUI(Service& srv) : srv{ srv }
		{
			initGUI();
			connectSignalsSlots();
			reincarcaCos(srv.getAll());
		}

		~CosCRUDGUI()
		{
			srv.stergeObserver(this);
		}

		void update() override
		{
			reincarcaCos(srv.getAll());
		}
};

class CosROnlyGUI : public QWidget, public Observer
{
	Service& srv;

	QHBoxLayout* mainLayout = new QHBoxLayout;
	int cate = 0;

	void initGUI()
	{
		setLayout(mainLayout);

		this->setMinimumWidth(370);
		this->setMinimumHeight(103);
		this->move(78, 458);
	}

	void deseneaza(const std::vector<Film>& filme)
	{
		cate = 0;
		for (const auto& film : filme)
			cate += film.getInchiriat();

		QWidget::update();
	}

	public:
		CosROnlyGUI(Service& srv) : srv{ srv }
		{
			initGUI();
			srv.adaugaObserver(this);
			deseneaza(srv.getAll());
		}

		~CosROnlyGUI()
		{
			srv.stergeObserver(this);
		}

		void paintEvent(QPaintEvent* ev) override
		{
			for (int i = 0; i < cate; ++i)
			{
				QPainter x{ this };
				x.drawRoundedRect(rand() % (width() - 20), rand() % (height() - 20), 20, 20, 20, 20);
			}
		}

		void update() override
		{
			deseneaza(srv.getAll());
		}
};
