from timeit import default_timer

class BigNumber:
    def __init__(self, value: str) -> None:
        assert len(value) > 0
        assert value[0] != '-'
        assert value[0] != '+'
        assert value.isdigit()

        self.__value = str(value)

    def __add(self, n1: str, n2: str) -> str:
        # compute the sum in the inverse order and then reverse the result

        n1 = n1[::-1]  # get the inverse of the n1
        n2 = n2[::-1]  # get the inverse of the n2
        carry = 0
        result = ''

        for i in range(max(len(n1), len(n2))):
            total = carry

            if i < len(n1):
                total += int(n1[i])
            if i < len(n2):
                total += int(n2[i])

            result += str(total % 10)
            carry = total // 10

        if carry:
            result += str(carry)

        return result[::-1]

    def __subtract(self, n1: str, n2: str) -> str:
        # compute the difference in the inverse order and then reverse the result

        n1 = n1[::-1]  # get the inverse of the n1
        n2 = n2[::-1]  # get the inverse of the n2
        borrow = 0
        result = ''

        for i in range(len(n1)):
            total = int(n1[i]) - borrow
            if i < len(n2):
                total -= int(n2[i])

            if total >= 0:
                result += str(total)
                borrow = 0
            else:
                result += str(total + 10)
                borrow = 1

        while len(result) > 1 and result.endswith('0'):
            result = result[:-1]

        return result[::-1]

    def __multiply(self, n1: str, n2: str) -> str:
        # compute the multiplication in the inverse order and then reverse the result

        n1 = n1[::-1]  # get the inverse of the n1
        n2 = n2[::-1]  # get the inverse of the n2
        result = [0] * (len(n1) + len(n2))

        for i in range(len(n1)):
            for j in range(len(n2)):
                result[i + j] += int(n1[i]) * int(n2[j])
                result[i + j + 1] += result[i + j] // 10
                result[i + j] %= 10

        while len(result) > 1 and result[-1] == 0:
            result = result[:-1]

        return ''.join(map(str, result[::-1]))  # convert reversed result which is represented as a list into a string

    def __divide(self, n1: str, n2: str) -> str:
        quotient = 0
        temp_dividend = ''
        for digit in n1:
            temp_dividend += digit
            count = 0
            while self.__is_greater_or_equal(temp_dividend, n2):
                temp_dividend = self.__subtract(temp_dividend, n2)
                count += 1
            quotient = quotient * 10 + count

        remainder = temp_dividend

        while len(remainder) > 1 and remainder.startswith('0'):
            remainder = remainder[1:]

        return str(quotient), remainder

    def __is_greater_or_equal(self, n1: str, n2: str) -> bool:
        if len(n1) > len(n2):
            return True
        if len(n1) < len(n2):
            return False
        return n1 >= n2

    def __add__(self, other: 'BigNumber') -> 'BigNumber':
        return BigNumber(self.__add(self.__value, other.__value))

    def __sub__(self, other: 'BigNumber') -> 'BigNumber':
        if self.__is_greater_or_equal(self.__value, other.__value):
            return BigNumber(self.__subtract(self.__value, other.__value))

        assert False, 'Could not substract a bigger number from a smaller number'

    def __mul__(self, other: 'BigNumber') -> 'BigNumber':
        return BigNumber(self.__multiply(self.__value, other.__value))

    def __floordiv__(self, other: 'BigNumber') -> 'BigNumber':
        assert not other.__value.startswith('0'), 'Cannot divide by zero'

        quotient, _ = self.__divide(self.__value, other.__value)
        return BigNumber(quotient)

    def __mod__(self, other: 'BigNumber') -> 'BigNumber':
        assert not other.__value.startswith('0'), 'Cannot divide by zero'

        _, remainder = self.__divide(self.__value, other.__value)
        return BigNumber(remainder)

    def __gt__(self, other: 'BigNumber') -> bool:
        return not self == other and not self <= other
    
    def __ge__(self, other: 'BigNumber') -> bool:
        return self.__is_greater_or_equal(self.__value, other.__value)
    
    def __lt__(self, other: 'BigNumber') -> bool:
        return not self >= other
    
    def __le__(self, other: 'BigNumber') -> bool:
        return other >= self

    def __ne__(self, other: 'BigNumber') -> bool:
        return self.__value != other.__value

    def __eq__(self, other: 'BigNumber') -> bool:
        return self.__value == other.__value

    def __str__(self) -> str:
        return self.__value

    def __repr__(self) -> str:
        return f"BigNumber('{self.__value}')"

def gcd_euclidean(a: str, b: str) -> 'BigNumber':
    assert isinstance(a, BigNumber) and isinstance(b, BigNumber), 'Inputs must be instances of BigNumber'

    zero = BigNumber("0")
    if a == zero or b == zero:
        return a + b

    while b != zero:
        a, b = b, a % b

    return a

def gcd_subtract(a: str, b: str) -> 'BigNumber':
    assert isinstance(a, BigNumber) and isinstance(b, BigNumber), 'Inputs must be instances of BigNumber'

    zero = BigNumber("0")

    if a == zero or b == zero:
        return a + b

    while a != b:
        a, b = (a - b, b) if a > b else (a, b - a)
    return a

def gcd_basic(a: str, b: str) -> 'BigNumber':
    assert isinstance(a, BigNumber) and isinstance(b, BigNumber), 'Inputs must be instances of BigNumber'

    min_val = min(a, b)

    zero = BigNumber("0")
    one = BigNumber("1")
    two = BigNumber("2")

    if a == zero or b == zero:
        return a + b

    if a % min_val == zero and b % min_val == zero:
        return min_val

    i = min_val // two
    while i >= two:
        if a % i == zero and b % i == zero:
            return i
        i = i - one

    return one

if __name__ == '__main__':
    tests = [('97', '83'),
             ('75', '93'),
             ('1868941', '2366421'),
             ('7780081759', '17165941'),
             ('919818517308088', '93271051765824'),
             ('1150590687713577', '98799493551215667'),
             ('9660311421525400430966757', '7741401414269368773212'),
             ('82767908391294', '57350483034690287'),
             ('56636183567463284533013618111958', '724276140627016024546508286929146'),
             ('9470954807727646950843219225972007083887723173443398431496690189207311204330', '17282988987707333730176626961292488328096677217318310593545474746241241741')]
    
    for index, test in enumerate(tests):
        print("Starting test #{} a={},b={}".format(index + 1, test[0], test[1]))

        a = BigNumber(test[0])
        b = BigNumber(test[1])

        start = default_timer()

        #gcd = gcd_euclidean(a, b)
        gcd = gcd_subtract(a, b)
        #gcd = gcd_basic(a,b)

        end = default_timer()

        print("Seconds elapsed {}".format(end - start))
        print("GCD is {}\n".format(gcd))