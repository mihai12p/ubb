#include <stdio.h>

struct punct
{
	float x, y;
} A, B, C, D;

int main()
{
	printf("Introduceti coordonatele (X, Y) punctului A din primul segment: ");
	scanf_s("%f %f", &A.x, &A.y);
	printf("Introduceti coordonatele (X, Y) punctului B din primul segment: ");
	scanf_s("%f %f", &B.x, &B.y);
	printf("Introduceti coordonatele (X, Y) punctului C din al doilea segment: ");
	scanf_s("%f %f", &C.x, &C.y);
	printf("Introduceti coordonatele (X, Y) punctului D din al doilea segment: ");
	scanf_s("%f %f", &D.x, &D.y);

	/*
	ecuatia unui segment este x(B.y - A.y) + y(A.x - B.x) + (A.y*B.x - A.x*B.y) = 0
				       ^	    ^		   ^
				       |	    |		   |
				       M	    N		   P
					    => Mx + Ny + P = 0
	*/

	float M1 = B.y - A.y, N1 = A.x - B.x, P1 = A.y * B.x - A.x * B.y;
	float M2 = D.y - C.y, N2 = C.x - D.x, P2 = C.y * D.x - C.x * D.y;
	if (M1 * N2 == M2 * N1)
	{
		if (M1 * P2 != M2 * P1)
			printf("Segmentele sunt paralele.\n");
		else
		{
			if (M1 == M2 && N1 == N2 && A.x == C.x)
				printf("Segmentele coincid.\n");
			else
				printf("Segmentul comun este [(%f, %f), (%f, %f)].", C.x, C.y, B.x, B.y);
		}

		return 0;
	}

	if (A.x == C.x && A.y == C.y)
		printf("Coordonatele punctului de intersectie sunt (%f, %f).", A.x, A.y);
	else if (B.x == D.x && B.y == D.y)
		printf("Coordonatele punctului de intersectie sunt (%f, %f).", B.x, B.y);
	else
	{
		float Intx, Inty;
		if (N1 != 0)
		{
			Intx = (N1 * P2 - P1) / (N2 * M1 - N1 * M2);
			Inty = -(M1 * Intx + P1) / N1;
		}
		else
		{
			Intx = -P1 / M1;
			Inty = -(P2 + M2 * Intx) / N2;
		}

		if ((abs(B.x - A.x) >= Intx && abs(B.y - A.y) >= Inty) && (abs(D.x - C.x) >= Intx && abs(D.y - C.y) >= Inty))
			printf("Coordonatele punctului de intersectie sunt (%f, %f).", Intx, Inty);
		else
			printf("Segmentele nu se intersecteaza.");
	}

	return 0;
}