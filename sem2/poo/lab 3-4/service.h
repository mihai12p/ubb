#pragma once

#include "concurs.h"

int adauga(repository* repo, char* nume, char* prenume, int* scor);
participant* cauta(repository* repo, char* nume, char* prenume);
int actualizeaza(participant* cautat, char* nume, char* prenume, int* scor);
void* sterge(repository* repo, participant* cautat);
repository filter(repository* repo, int mode, char val);
repository sortBy(repository* repo, int byWhat, int ord);

void test_isValid();
void test_adauga();
void test_cauta();
void test_actualizeaza();
void test_sterge();
void test_filter();
void test_sort();
