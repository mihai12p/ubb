#include "gui.h"

void gui::initGui()
{
	this->setLayout(mainLayout);

	QWidget* widget1 = new QWidget;
	QHBoxLayout* tabelJocuriLayout = new QHBoxLayout;
	widget1->setLayout(tabelJocuriLayout);

	listaJocuri->setEditTriggers(QAbstractItemView::NoEditTriggers);
	listaJocuri->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	listaJocuri->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	listaJocuri->horizontalHeader()->setStretchLastSection(true);
	listaJocuri->verticalHeader()->setStretchLastSection(true);
	tabelJocuriLayout->addWidget(listaJocuri);

	QWidget* widget2 = new QWidget;
	QVBoxLayout* butoaneDreapta = new QVBoxLayout;
	widget2->setLayout(butoaneDreapta);

	butoaneDreapta->addWidget(label);
	butoaneDreapta->addWidget(buton);
	butoaneDreapta->addWidget(butonFiltrare);
	butoaneDreapta->addWidget(butonRefresh);

	mainLayout->addWidget(widget1);
	mainLayout->addWidget(widget2);
}

void gui::connectButoane()
{
	QWidget::connect(listaJocuri, &QTableWidget::itemSelectionChanged, this, [&]() 
	{
		QList<QTableWidgetItem*> selectate = listaJocuri->selectedItems();
		for (const auto& game : srv.getAll())
		{
			if (selectate.size() == 2 && game.getTitlu() == selectate[0]->text().toStdString())
			{
				label->setText("Varsta minima: " + QString::number(game.getPegi()));
				break;
			}
		}
	});
	QWidget::connect(buton, &QPushButton::clicked, this, [&]() 
	{
		this->refreshLista(srv.sortare());
	});
	QWidget::connect(butonFiltrare, &QPushButton::clicked, this, [&]()
	{
		this->refreshLista(srv.filtrare());
	});
	QWidget::connect(butonRefresh, &QPushButton::clicked, this, [&]()
	{
		this->refreshLista(srv.getAll());
	});
}

void gui::refreshLista(const std::vector<joc>& lista)
{
	listaJocuri->clear();
	listaJocuri->setRowCount(lista.size());
	listaJocuri->setColumnCount(2);
	int idx = -1;
	for (const auto& g : lista)
	{
		++idx;
		QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(g.getTitlu()));
		if (g.getPlatf() == "PC")
			item->setBackground(Qt::black);
		else if (g.getPlatf() == "XBOX")
			item->setBackground(Qt::green);
		else if (g.getPlatf() == "PlayStation")
			item->setBackground(Qt::blue);
		else if (g.getPlatf() == "Nintendo")
			item->setBackground(Qt::red);
		listaJocuri->setItem(idx, 0, item);

		item = new QTableWidgetItem(QString::number(g.getPret()));
		if (g.getPlatf() == "PC")
			item->setBackground(Qt::black);
		else if (g.getPlatf() == "XBOX")
			item->setBackground(Qt::green);
		else if (g.getPlatf() == "PlayStation")
			item->setBackground(Qt::blue);
		else if (g.getPlatf() == "Nintendo")
			item->setBackground(Qt::red);
		listaJocuri->setItem(idx, 1, item);
	}
}
