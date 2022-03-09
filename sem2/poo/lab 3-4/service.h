#pragma once

#include "concurs.h"

participant* adauga(repository* repo, char* nume, char* prenume, int* scor);
participant* cauta(repository* repo, char* nume, char* prenume);
participant* actualizeaza(participant* cautat, char* nume, char* prenume, int* scor);
void* sterge(repository* repo, participant* cautat);

void test_adauga();
void test_reset();
void test_cauta();
void test_actualizeaza();
void test_sterge();
