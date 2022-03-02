#include <iostream>

/*
Introduceti coordonatele (X, Y) punctului A din primul segment: -1 1
Introduceti coordonatele (X, Y) punctului B din primul segment: 3 -3
Introduceti coordonatele (X, Y) punctului C din al doilea segment: 0 -1
Introduceti coordonatele (X, Y) punctului D din al doilea segment: 1 1
Coordonatele punctului de intersectie sunt (0.333333, -0.333333).
*/

int main()
{
	float Ax, Ay;
	std::cout << "Introduceti coordonatele (X, Y) punctului A din primul segment: ";
	std::cin >> Ax >> Ay;

	float Bx, By;
	std::cout << "Introduceti coordonatele (X, Y) punctului B din primul segment: ";
	std::cin >> Bx >> By;

	float Cx, Cy;
	std::cout << "Introduceti coordonatele (X, Y) punctului C din al doilea segment: ";
	std::cin >> Cx >> Cy;

	float Dx, Dy;
	std::cout << "Introduceti coordonatele (X, Y) punctului D din al doilea segment: ";
	std::cin >> Dx >> Dy;

	/*
	ecuatia unui segment este x(By - Ay) + y(Ax - Bx) + (Ay*Bx - Ax*By) = 0
				       ^	    ^		   ^
				       |	    |		   |
				       M	    N		   P
					    => Mx + Ny + P = 0
	*/

	float M1 = By - Ay, N1 = Ax - Bx, P1 = Ay * Bx - Ax * By;
	float M2 = Dy - Cy, N2 = Cx - Dx, P2 = Cy * Dx - Cx * Dy;
	if (M1 * N2 == M2 * N1)
	{
		if (M1 * P2 != M2 * P1)
			std::cout << "Segmentele sunt paralele.\n";
		else
		{
			if (M1 == M2 && N1 == N2 && Ax == Cx)
				std::cout << "Segmentele coincid.\n";
			else
				std::cout << "Segmentul comun este [(" << Cx << ", " << Cy << "), (" << Bx << ", " << By << ")].";
		}

		return 0;
	}

	if (Ax == Cx && Ay == Cy)
		std::cout << "Coordonatele punctului de intersectie sunt (" << Ax << ", " << Ay << ").";
	else if (Bx == Dx && By == Dy)
		std::cout << "Coordonatele punctului de intersectie sunt (" << Bx << ", " << By << ").";
	else
	{
		float Intx, Inty;
		if (N1 != 0)
		{
			Intx = (N1 * P2 - P1) / float(N2 * M1 - N1 * M2);
			Inty = -(M1 * Intx + P1) / float(N1);
		}
		else
		{
			Intx = -P1 / float(M1);
			Inty = -(P2 + M2 * Intx) / float(N2);
		}

		std::cout << "Coordonatele punctului de intersectie sunt (" << Intx << ", " << Inty << ").";
	}

	return 0;
}
