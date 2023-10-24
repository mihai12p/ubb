from collections.abc import MutableSequence

class LexiTable(MutableSequence):
    def __init__(self) -> None:
        self.__capacity = 4  # initial capacity
        self.__size = 0
        self.__data = [None] * self.__capacity

    def __len__(self) -> int:
        return self.__size
    
    def __delitem__(self, index: int) -> None:
        assert type(index) == int
        assert index >= 0 and index <= self.__size

        for i in range(index, self.__size - 1):
            self.__data[i] = self.__data[i + 1]

        self.__size -= 1
        self.__data[self.__size] = None

        if 0 < self.__size < self.__capacity // 4:  # resize down if we're using a quarter of the capacity.
            self.__resize(self.__capacity // 2)

    def __getitem__(self, index: int) -> str:
        assert type(index) == int
        assert index >= 0 and index <= self.__size

        return self.__data[index]
    
    def __setitem__(self, index: int, value: str) -> None:
        assert type(index) == int
        assert type(value) == str
        assert index >= 0 and index <= self.__size

        self.__data[index] = value

    def __resize(self, new_capacity: int) -> None:
        assert type(new_capacity) == int

        new_data = [None] * new_capacity

        for i in range(self.__size):
            new_data[i] = self.__data[i]

        self.__data = new_data
        self.__capacity = new_capacity

    def get_elements(self) -> list:
        elements = {}

        for i in range(self.__size):
            elements[self.__data[i]] = i + 1
        
        return elements

    def insert(self, index: int, value: str) -> None:
        assert type(index) == int
        assert type(value) == str
        assert index >= 0 and index <= self.__size

        if self.__size == self.__capacity:
            self.__resize(2 * self.__capacity)

        for i in range(self.__size, index, -1):
            self.__data[i] = self.__data[i - 1]

        self.__size += 1
        self.__data[index] = value

    def append(self, value: str) -> None:
        assert type(value) == str

        start = 0
        end = self.__len__() - 1
        index = 0
        while start <= end:
            mid = start + (end - start) // 2
            existing_value = self.__data[mid]

            if value == existing_value:
                return
            elif value < existing_value:
                end = mid - 1
                index = mid
            else:
                start = mid + 1
                index = start
        
        self.insert(index, value)