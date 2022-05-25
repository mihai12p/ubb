#pragma once

#include <vector>
#include <algorithm>

class Observer
{
	public:
		virtual void update() = 0;
};

class Observable
{
	std::vector<Observer*> observers;

	public:
		void adaugaObserver(Observer* obs)
		{
			observers.push_back(obs);
		}

		void stergeObserver(Observer* obs)
		{
			observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
		}

		void notifica()
		{
			for_each(observers.begin(), observers.end(), [](Observer* obs) { obs->update(); });
		}
};
