#include "Teste.hpp"
#include "FilmeGui.hpp"
#include <QtWidgets/QApplication>

void teste()
{
	testAdauga();
	testSterge();
	testModifica();
	testCauta();
	testFiltrare();
	testSortare();
	testAdaugaCos();
	testGolesteCos();
	testRaport();
	testSaveToFile();
	testUndo();
}

void adaugaCateva(Service& srv)
{
	srv.adaugaFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry");
	srv.adaugaFilm("Miami Bici", "Amuzzament", 2020, "Codin Maticiuc");
	srv.adaugaFilm("Moartea", "Documentar", 2022, "Ion Iliescu");
	srv.adaugaFilm("Soacra mea e o scorpie", "Romance", 2005, "Jane Fonda");
}

int main(int argc, char *argv[])
{
	teste();

	{
		QApplication a(argc, argv);

		Filme repo;
		Valid validator;
		Service srv{ repo, validator };
		adaugaCateva(srv);

		FilmeGUI filmeGui{ srv };
		filmeGui.show();

		a.exec();
	}

	return 0;
}
