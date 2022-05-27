#pragma once

#include <qabstractitemview.h>
#include <vector>

#include "film.hpp"	

class MyQList : public QAbstractListModel
{
	std::vector<Film> filme;
	std::unique_ptr<Film> filmCautat;

	public:
		MyQList(const std::vector<Film>& filme) : filme{ filme } { }

		int rowCount(const QModelIndex& parent = QModelIndex()) const override
		{
			return filme.size();
		}

		QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override 
		{
			if (role == Qt::BackgroundRole)
			{
				const Film& film = filme[index.row()];
				if (this->filmCautat && film == *this->filmCautat.get())
					return QBrush{ Qt::green, Qt::SolidPattern };
			}
			if (role == Qt::DisplayRole) 
			{
				const Film& film = filme[index.row()];
				return QString::number(index.row() + 1) + " | " + QString::fromStdString(film.getTitlu() + " | " + film.getGen()) + " | " + QString::number(film.getAn()) + " | " + QString::fromStdString(film.getActor()) + " | " + QString::number(film.getInchiriat());
			}
			return QVariant{};
		}

		void setFilme(const std::vector<Film>& filme, std::unique_ptr<Film> filmCautat)
		{
			this->filme = filme;
			this->filmCautat = std::move(filmCautat);
			const QModelIndex& topLeft = createIndex(0, 0);
			const QModelIndex& bottomRight = createIndex(rowCount(), 0);
			emit dataChanged(topLeft, bottomRight);
		}
};
