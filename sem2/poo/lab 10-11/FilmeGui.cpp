#include "FilmeGui.hpp"

void FilmeGUI::initGUI()
{
	setLayout(mainLayout);

	// partea stanga = lista filme
	QWidget* parteaStanga = new QWidget;
	QHBoxLayout* listaFilmeSiButoane = new QHBoxLayout;
	parteaStanga->setLayout(listaFilmeSiButoane);

	listaFilmeStanga = new QTableWidget;
	listaFilmeStanga->setMinimumWidth(394);
	listaFilmeStanga->setShowGrid(true);
	listaFilmeStanga->setEditTriggers(QAbstractItemView::NoEditTriggers);
	listaFilmeStanga->setFocusPolicy(Qt::NoFocus);
	listaFilmeStanga->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	listaFilmeStanga->horizontalHeader()->setVisible(false);
	listaFilmeStanga->verticalHeader()->setStretchLastSection(true);
	listaFilmeStanga->horizontalHeader()->setStretchLastSection(true);
	listaFilmeStanga->setColumnCount(5);
	listaFilmeStanga->insertRow(0);
	listaFilmeSiButoane->addWidget(listaFilmeStanga);

	// partea dreapta = butoane
	QWidget* parteaDreapta = new QWidget;
	QVBoxLayout* listaButoaneDreapta = new QVBoxLayout;
	parteaDreapta->setLayout(listaButoaneDreapta);

	btnAdauga = new QPushButton("&Adauga film");
	listaButoaneDreapta->addWidget(btnAdauga);
	btnSterge = new QPushButton("&Sterge film");
	listaButoaneDreapta->addWidget(btnSterge);
	btnModifica = new QPushButton("&Modifica film");
	listaButoaneDreapta->addWidget(btnModifica);
	btnCauta = new QPushButton("&Cauta film");
	listaButoaneDreapta->addWidget(btnCauta);
	btnFiltreaza = new QPushButton("&Filtreaza filme");
	listaButoaneDreapta->addWidget(btnFiltreaza);
	btnSorteaza = new QPushButton("&Sorteaza filme");
	listaButoaneDreapta->addWidget(btnSorteaza);
	btnInchiriaza = new QPushButton("&Inchiriaza film");
	listaButoaneDreapta->addWidget(btnInchiriaza);
	btnGolesteCos = new QPushButton("&Goleste cos");
	listaButoaneDreapta->addWidget(btnGolesteCos);
	btnRaportCos = new QPushButton("&Raport cos");
	listaButoaneDreapta->addWidget(btnRaportCos);
	btnExportCos = new QPushButton("&Export cos");
	listaButoaneDreapta->addWidget(btnExportCos);
	btnUndo = new QPushButton("&Undo");
	listaButoaneDreapta->addWidget(btnUndo);

	listaButoaneDreapta->addStretch();

	btnRefresh = new QPushButton("&Reimprospateaza");
	listaButoaneDreapta->addWidget(btnRefresh);

	mainLayout->addWidget(parteaStanga);
	mainLayout->addWidget(parteaDreapta);
}

void FilmeGUI::connectSignalsSlots() 
{
	QObject::connect(btnAdauga, &QPushButton::clicked, this, &FilmeGUI::adaugaFilmNou);
	QObject::connect(btnSterge, &QPushButton::clicked, this, &FilmeGUI::stergeFilmExistent);
	QObject::connect(btnModifica, &QPushButton::clicked, this, &FilmeGUI::modificaFilmExistent);
	QObject::connect(btnCauta, &QPushButton::clicked, this, &FilmeGUI::cautaFilmExistent);
	QObject::connect(btnFiltreaza, &QPushButton::clicked, this, &FilmeGUI::filtreazaFilmeExistente);
	QObject::connect(btnSorteaza, &QPushButton::clicked, this, &FilmeGUI::sorteazaFilmeExistente);
	QObject::connect(btnInchiriaza, &QPushButton::clicked, this, &FilmeGUI::inchiriazaFilmExistent);
	QObject::connect(btnGolesteCos, &QPushButton::clicked, this, [&]() { srv.golesteCos(); FilmeGUI::reincarcaLista(srv.getAll()); });
	QObject::connect(btnRaportCos, &QPushButton::clicked, this, &FilmeGUI::raportCosFilme);
	QObject::connect(btnExportCos, &QPushButton::clicked, this, &FilmeGUI::exportCosFilme);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &FilmeGUI::undo);
	QObject::connect(btnRefresh, &QPushButton::clicked, this, [&]() { FilmeGUI::reincarcaLista(srv.getAll()); });
}

void FilmeGUI::reincarcaLista(const std::vector<Film>& filme, const std::unique_ptr<Film> filmCautat)
{
	listaFilmeStanga->clear();
	listaFilmeStanga->setRowCount(int(filme.size()) + 1);
	listaFilmeStanga->setItem(0, 0, new QTableWidgetItem("Titlu"));
	listaFilmeStanga->setItem(0, 1, new QTableWidgetItem("Gen"));
	listaFilmeStanga->setItem(0, 2, new QTableWidgetItem("An"));
	listaFilmeStanga->setItem(0, 3, new QTableWidgetItem("Actor"));
	listaFilmeStanga->setItem(0, 4, new QTableWidgetItem("Inchiriat"));
	int index = 1;
	for (const auto& film : filme) 
	{
		QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(film.getTitlu()));
		if (filmCautat && film == *filmCautat.get())
			item->setData(Qt::BackgroundRole, QBrush{ Qt::green, Qt::SolidPattern });
		listaFilmeStanga->setItem(index, 0, item);
		item = new QTableWidgetItem(QString::fromStdString(film.getGen()));
		if (filmCautat && film == *filmCautat.get())
			item->setData(Qt::BackgroundRole, QBrush{ Qt::green, Qt::SolidPattern });
		listaFilmeStanga->setItem(index, 1, item);
		item = new QTableWidgetItem(QString::number(film.getAn()));
		if (filmCautat && film == *filmCautat.get())
			item->setData(Qt::BackgroundRole, QBrush{ Qt::green, Qt::SolidPattern });
		listaFilmeStanga->setItem(index, 2, item);
		item = new QTableWidgetItem(QString::fromStdString(film.getActor()));
		if (filmCautat && film == *filmCautat.get())
			item->setData(Qt::BackgroundRole, QBrush{ Qt::green, Qt::SolidPattern });
		listaFilmeStanga->setItem(index, 3, item);
		item = new QTableWidgetItem(QString::number(film.getInchiriat()));
		if (filmCautat && film == *filmCautat.get())
			item->setData(Qt::BackgroundRole, QBrush{ Qt::green, Qt::SolidPattern });
		listaFilmeStanga->setItem(index, 4, item);
		++index;
	}
}

void FilmeGUI::adaugaFilmNou()
{
	QWidget* adaugaFilmDetalii = new QWidget;
	QFormLayout* detaliiFilmNou = new QFormLayout;
	adaugaFilmDetalii->setLayout(detaliiFilmNou);

	QLineEdit* txtTitlu = new QLineEdit;
	detaliiFilmNou->addRow(new QLabel("Titlu:"), txtTitlu);
	QLineEdit* txtGen = new QLineEdit;
	detaliiFilmNou->addRow(new QLabel("Gen:"), txtGen);
	QLineEdit* txtAn = new QLineEdit;
	detaliiFilmNou->addRow(new QLabel("An aparitie:"), txtAn);
	QLineEdit* txtActor = new QLineEdit;
	detaliiFilmNou->addRow(new QLabel("Actor principal:"), txtActor);
	QPushButton* btnAdaugaFereastra = new QPushButton("Adauga");
	detaliiFilmNou->addRow(btnAdaugaFereastra);

	adaugaFilmDetalii->move(this->x() + this->size().width(), this->y());
	adaugaFilmDetalii->show();

	QObject::connect(btnAdaugaFereastra, &QPushButton::clicked, this, [&, txtTitlu, txtGen, txtAn, txtActor]()
	{
		try
		{
			srv.adaugaFilm(txtTitlu->text().toStdString(), txtGen->text().toStdString(), txtAn->text().toInt(), txtActor->text().toStdString());
			reincarcaLista(srv.getAll());
		}
		catch (const FilmeException& ex)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
		}
		catch (const ValidateException& ex)
		{
			std::string allEx = "";
			for (const auto& msg : ex.getMsg())
				allEx += msg + '\n';

			QMessageBox::warning(this, "Warning", QString::fromStdString(allEx));
		}
	});
}

void FilmeGUI::stergeFilmExistent()
{
	QWidget* stergeFilmDetalii = new QWidget;
	QFormLayout* detaliiFilmExistent = new QFormLayout;
	stergeFilmDetalii->setLayout(detaliiFilmExistent);

	QLineEdit* txtTitlu = new QLineEdit;
	detaliiFilmExistent->addRow(new QLabel("Titlu:"), txtTitlu);
	QLineEdit* txtGen = new QLineEdit;
	detaliiFilmExistent->addRow(new QLabel("Gen:"), txtGen);
	QLineEdit* txtAn = new QLineEdit;
	detaliiFilmExistent->addRow(new QLabel("An aparitie:"), txtAn);
	QLineEdit* txtActor = new QLineEdit;
	detaliiFilmExistent->addRow(new QLabel("Actor principal:"), txtActor);
	QPushButton* btnStergeFereastra = new QPushButton("Sterge");
	detaliiFilmExistent->addRow(btnStergeFereastra);

	stergeFilmDetalii->move(this->x() + this->size().width(), this->y());
	stergeFilmDetalii->show();

	QObject::connect(btnStergeFereastra, &QPushButton::clicked, this, [&, txtTitlu, txtGen, txtAn, txtActor]()
	{
		try
		{
			srv.stergeFilm(txtTitlu->text().toStdString(), txtGen->text().toStdString(), txtAn->text().toInt(), txtActor->text().toStdString());
			reincarcaLista(srv.getAll());
		}
		catch (const FilmeException& ex)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
		}
		catch (const ValidateException& ex)
		{
			std::string allEx = "";
			for (const auto& msg : ex.getMsg())
				allEx += msg + '\n';

			QMessageBox::warning(this, "Warning", QString::fromStdString(allEx));
		}
	});
}

void FilmeGUI::modificaFilmExistent()
{
	QWidget* modificaFilmDetalii = new QWidget;
	QFormLayout* detaliiFilmExistent = new QFormLayout;
	modificaFilmDetalii->setLayout(detaliiFilmExistent);

	QLineEdit* txtTitlu = new QLineEdit;
	detaliiFilmExistent->addRow(new QLabel("Titlu:"), txtTitlu);
	QLineEdit* txtTitluNou = new QLineEdit;
	detaliiFilmExistent->addRow(new QLabel("Titlu nou:"), txtTitluNou);
	QLineEdit* txtGenNou = new QLineEdit;
	detaliiFilmExistent->addRow(new QLabel("Gen nou:"), txtGenNou);
	QLineEdit* txtAnNou = new QLineEdit;
	detaliiFilmExistent->addRow(new QLabel("An aparitie nou:"), txtAnNou);
	QLineEdit* txtActorNou = new QLineEdit;
	detaliiFilmExistent->addRow(new QLabel("Actor principal nou:"), txtActorNou);
	QPushButton* btnModificaFereastra = new QPushButton("Modifica");
	detaliiFilmExistent->addRow(btnModificaFereastra);

	modificaFilmDetalii->move(this->x() + this->size().width(), this->y());
	modificaFilmDetalii->show();

	QObject::connect(btnModificaFereastra, &QPushButton::clicked, this, [&, txtTitlu, txtTitluNou, txtGenNou, txtAnNou, txtActorNou]()
	{
		try
		{
			srv.modificaFilm(txtTitlu->text().toStdString(), txtTitluNou->text().toStdString(), txtGenNou->text().toStdString(), txtAnNou->text().toInt(), txtActorNou->text().toStdString());
			reincarcaLista(srv.getAll());
		}
		catch (const FilmeException& ex)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
		}
		catch (const ValidateException& ex)
		{
			std::string allEx = "";
			for (const auto& msg : ex.getMsg())
				allEx += msg + '\n';

			QMessageBox::warning(this, "Warning", QString::fromStdString(allEx));
		}
	});
}

void FilmeGUI::cautaFilmExistent()
{
	QWidget* cautaFilmDetalii = new QWidget;
	QFormLayout* detaliiFilmExistent = new QFormLayout;
	cautaFilmDetalii->setLayout(detaliiFilmExistent);

	QLineEdit* txtTitlu = new QLineEdit;
	detaliiFilmExistent->addRow(new QLabel("Titlu:"), txtTitlu);
	QPushButton* btnCautaFereastra = new QPushButton("Cauta");
	detaliiFilmExistent->addRow(btnCautaFereastra);

	cautaFilmDetalii->move(this->x() + this->size().width(), this->y());
	cautaFilmDetalii->show();

	QObject::connect(btnCautaFereastra, &QPushButton::clicked, this, [&, txtTitlu]()
	{
		try
		{
			reincarcaLista(srv.getAll(), srv.cautaFilm(txtTitlu->text().toStdString()));
		}
		catch (const FilmeException& ex)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
		}
		catch (const ValidateException& ex)
		{
			std::string allEx = "";
			for (const auto& msg : ex.getMsg())
				allEx += msg + '\n';

			QMessageBox::warning(this, "Warning", QString::fromStdString(allEx));
		}
	});
}

void FilmeGUI::filtreazaFilmeExistente()
{
	QWidget* filtreazaFilmeDetalii = new QWidget;
	QFormLayout* detaliiFilmExistent = new QFormLayout;
	filtreazaFilmeDetalii->setLayout(detaliiFilmExistent);

	QLineEdit* txtTitlu = new QLineEdit;
	detaliiFilmExistent->addRow(new QLabel("Titlu:"), txtTitlu);
	QLineEdit* txtAn = new QLineEdit;
	detaliiFilmExistent->addRow(new QLabel("An aparitie:"), txtAn);
	QPushButton* btnFiltreazaFereastra = new QPushButton("Filtreaza");
	detaliiFilmExistent->addRow(btnFiltreazaFereastra);

	filtreazaFilmeDetalii->move(this->x() + this->size().width(), this->y());
	filtreazaFilmeDetalii->show();

	QObject::connect(btnFiltreazaFereastra, &QPushButton::clicked, this, [&, txtTitlu, txtAn]()
	{
		try
		{
			reincarcaLista(srv.filtrare(txtTitlu->text().toStdString(), txtAn->text().toInt()));
		}
		catch (const FilmeException& ex)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
		}
		catch (const ValidateException& ex)
		{
			std::string allEx = "";
			for (const auto& msg : ex.getMsg())
				allEx += msg + '\n';

			QMessageBox::warning(this, "Warning", QString::fromStdString(allEx));
		}
	});
}

void FilmeGUI::sorteazaFilmeExistente()
{
	QWidget* sorteazaFilmDetalii = new QWidget;
	QFormLayout* detaliiFilmExistent = new QFormLayout;
	sorteazaFilmDetalii->setLayout(detaliiFilmExistent);

	QCheckBox* checkBoxDupaTitlu = new QCheckBox("&Dupa titlu");
	QCheckBox* checkBoxDupaActor = new QCheckBox("&Dupa actor");
	QCheckBox* checkBoxDupaGenAn = new QCheckBox("&Dupa gen apoi dupa an");

	detaliiFilmExistent->addRow(checkBoxDupaTitlu);
	detaliiFilmExistent->addRow(checkBoxDupaActor);
	detaliiFilmExistent->addRow(checkBoxDupaGenAn);
	QObject::connect(checkBoxDupaTitlu, &QCheckBox::stateChanged, this, [=]() 
	{ 
		bool checked = checkBoxDupaTitlu->checkState() == Qt::CheckState::Checked;
		checkBoxDupaActor->setDisabled(checked); checkBoxDupaGenAn->setDisabled(checked);
	});
	QObject::connect(checkBoxDupaActor, &QCheckBox::stateChanged, this, [=]() 
	{ 
		bool checked = checkBoxDupaActor->checkState() == Qt::CheckState::Checked;
		checkBoxDupaTitlu->setDisabled(checked); checkBoxDupaGenAn->setDisabled(checked);
	});
	QObject::connect(checkBoxDupaGenAn, &QCheckBox::stateChanged, this, [=]()
	{
		bool checked = checkBoxDupaGenAn->checkState() == Qt::CheckState::Checked;
		checkBoxDupaTitlu->setDisabled(checked); checkBoxDupaActor->setDisabled(checked);
	});
	QPushButton* btnSorteazaFereastra = new QPushButton("Sorteaza");
	detaliiFilmExistent->addRow(btnSorteazaFereastra);

	sorteazaFilmDetalii->move(this->x() + this->size().width(), this->y());
	sorteazaFilmDetalii->show();

	QObject::connect(btnSorteazaFereastra, &QPushButton::clicked, this, [=]()
	{
		try
		{
			int criteriu = 0;
			while (!criteriu)
			{
				if (checkBoxDupaTitlu->checkState() == Qt::CheckState::Checked)
				{
					criteriu = 1;
					break;
				}
				if (checkBoxDupaActor->checkState() == Qt::CheckState::Checked)
				{
					criteriu = 2;
					break;
				}
				if (checkBoxDupaGenAn->checkState() == Qt::CheckState::Checked)
				{
					criteriu = 3;
					break;
				}
				criteriu = 1;
			}
			reincarcaLista(srv.sortare(criteriu));
		}
		catch (const FilmeException& ex)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
		}
		catch (const ValidateException& ex)
		{
			std::string allEx = "";
			for (const auto& msg : ex.getMsg())
				allEx += msg + '\n';

			QMessageBox::warning(this, "Warning", QString::fromStdString(allEx));
		}
	});
}

void FilmeGUI::inchiriazaFilmExistent()
{
	QWidget* inchiriazaFilmDetalii = new QWidget;
	QFormLayout* detaliiFilmExistent = new QFormLayout;
	inchiriazaFilmDetalii->setLayout(detaliiFilmExistent);

	QLineEdit* txtTitlu = new QLineEdit;
	detaliiFilmExistent->addRow(new QLabel("Titlu:"), txtTitlu);
	QPushButton* btnInchiriazaFereastra = new QPushButton("Inchiriaza");
	detaliiFilmExistent->addRow(btnInchiriazaFereastra);

	inchiriazaFilmDetalii->move(this->x() + this->size().width(), this->y());
	inchiriazaFilmDetalii->show();

	QObject::connect(btnInchiriazaFereastra, &QPushButton::clicked, this, [&, txtTitlu]()
	{
		try
		{
			srv.inchiriazaFilm(txtTitlu->text().toStdString());
			reincarcaLista(srv.getAll());
		}
		catch (const FilmeException& ex)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
		}
		catch (const ValidateException& ex)
		{
			std::string allEx = "";
			for (const auto& msg : ex.getMsg())
				allEx += msg + '\n';

			QMessageBox::warning(this, "Warning", QString::fromStdString(allEx));
		}
	});
}

void FilmeGUI::raportCosFilme()
{
	QWidget* raportCosFilmeDetalii = new QWidget;
	QFormLayout* detaliiFilmExistent = new QFormLayout;
	raportCosFilmeDetalii->setLayout(detaliiFilmExistent);

	const std::unordered_map<int, int> raportCos = srv.raport();

	QPlainTextEdit* textRaport = new QPlainTextEdit;
	textRaport->setReadOnly(true);
	for (const auto& i : raportCos)
		textRaport->appendPlainText("An: " + QString::number(i.first) + " - Inchirieri: " + QString::number(i.second));

	detaliiFilmExistent->addRow(textRaport);

	raportCosFilmeDetalii->move(this->x() + this->size().width(), this->y());
	raportCosFilmeDetalii->show();
}

void FilmeGUI::exportCosFilme()
{
	QWidget* exportCosFilmeDetalii = new QWidget;
	QFormLayout* detaliiFilmExistent = new QFormLayout;
	exportCosFilmeDetalii->setLayout(detaliiFilmExistent);

	QLineEdit* txtFisier = new QLineEdit;
	detaliiFilmExistent->addRow(new QLabel("Nume fisier:"), txtFisier);
	QPushButton* btnExportCosFereastra = new QPushButton("Export cos");
	detaliiFilmExistent->addRow(btnExportCosFereastra);

	exportCosFilmeDetalii->move(this->x() + this->size().width(), this->y());
	exportCosFilmeDetalii->show();

	QObject::connect(btnExportCosFereastra, &QPushButton::clicked, this, [&, txtFisier]()
	{
		try
		{
			srv.saveToFile(txtFisier->text().toStdString());
		}
		catch (const FilmeException& ex)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
		}
		catch (const ValidateException& ex)
		{
			std::string allEx = "";
			for (const auto& msg : ex.getMsg())
				allEx += msg + '\n';

			QMessageBox::warning(this, "Warning", QString::fromStdString(allEx));
		}
	});
}

void FilmeGUI::undo()
{
	try
	{
		srv.undoLast();
		reincarcaLista(srv.getAll());
	}
	catch (const FilmeException& ex)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
	catch (const ValidateException& ex)
	{
		std::string allEx = "";
		for (const auto& msg : ex.getMsg())
			allEx += msg + '\n';

		QMessageBox::warning(this, "Warning", QString::fromStdString(allEx));
	}
}
