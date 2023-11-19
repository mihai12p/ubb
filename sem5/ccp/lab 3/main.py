# https://ro.frwiki.wiki/wiki/Algorithme_rho_de_Pollard

import math

def pollards_rho(n, func_str=None) -> int:
    if func_str is None:
        func = lambda x: (x * x + 1) % n
    else:
        def custom_function(x):
            local_vars = {"x": x, "n": n, "math": math}
            return eval(func_str, {}, local_vars) % n

        func = custom_function

    index, x, y, d = 1, 2, 2, 1
    while d == 1:
        x = func(x)                     # calculate Xj = f(Xj-1)
        y = func(func(y))               # calculate X2j = f(f(Xj-1))
        d = math.gcd(abs(x - y), n)     # calculate gcd(|X2j - Xj|, n)
        print("x{} = {}, x{} = {}, d = {}".format(index, x, index*2, y, d))
        index += 1

    return d if d != n else None

if __name__ == '__main__':
    n = 5617
    func_str = input("Enter the function (in terms of 'x') or press Enter to use the default function: ")
    if not func_str.strip():
        func_str = None

    factor = pollards_rho(n, func_str)
    print(f"A nontrivial factor of {n} is {factor}")