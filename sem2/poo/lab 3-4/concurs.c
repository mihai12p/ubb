#include <string.h>
#include "concurs.h"

void adauga(repository* repo, participant newUser)
{
	repo->user[repo->len] = newUser;
	++repo->len;
}

void reset(repository* repo)
{
	memset(repo, 0, sizeof(*repo));
}

int cauta(repository* repo, participant existingUser)
{
	for (int i = 0; i < repo->len; ++i)
		if (!strcmp(repo->user[i].nume, existingUser.nume) && !strcmp(repo->user[i].prenume, existingUser.prenume))
			return i;

	return -1;
}

void actualizeaza(repository* repo, participant newUser, int poz)
{
	repo->user[poz] = newUser;
}

void sterge(repository* repo, int poz)
{
	for (int i = poz; i < repo->len - 1; ++i)
		repo->user[i] = repo->user[i + 1];

	memset(&repo->user[repo->len - 1], 0, sizeof(repo->user[repo->len - 1]));
	--repo->len;
}
