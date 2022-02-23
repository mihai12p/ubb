def binarySearchIterative(list, low, high, el):
    while low <= high:
        mid = (low + high) // 2
        if el == list[mid]:
            return mid
        elif el < list[mid]:
            high = mid - 1
        else:
            low = mid + 1

    return -1
    
def binarySearchRecursive(list, low, high, el):
    if low > high:
        return -1

    mid = (low + high) // 2
    if el == list[mid]:
        return mid
    elif el < list[mid]:
        return binarySearchRecursive(list, low, mid - 1, el)
    else:
        return binarySearchRecursive(list, mid + 1, high, el)

def selectionSort(list):
    for i in range(len(list) - 1):
        index = i
        for j in range(i + 1, len(list)):
            if list[j] < list[index]:
                index = j
        list[i], list[index] = list[index], list[i]

def directSelectionSort(list):
    for i in range(len(list) - 1):
        for j in range(i + 1, len(list)):
            if list[i] > list[j]:
                list[i], list[j] = list[j], list[i]

def bubbleSort(list):
    for i in range(len(list) - 1):
        for j in range(len(list) - i - 1):
            if list[j] > list[j + 1]:
                list[j], list[j + 1] = list[j + 1], list[j]

def insertionSort(list):
    for i in range(1, len(list)):
        el = list[i]
        j = i - 1
        while (j >= 0 and el < list[j]):
            list[j + 1] = list[j]
            j -= 1
        list[j + 1] = el

def quickSortWithListComprehension(list):
    if list == []:
        return []

    pivot = list.pop()
    lowPart = quickSort([x for x in list if x < pivot])
    highPart = quickSort([x for x in list if x >= pivot])
    return lowPart + [pivot] + highPart

def partition(list, low, high):
    pivot = list[high]
    i = low - 1

    for j in range(low, high):
        if list[j] <= pivot:
            i += 1
            list[i], list[j] = list[j], list[i]
    list[i + 1], list[high] = list[high], list[i + 1]
    return i + 1

def quickSort(list, low, high):
    if low < high:
        p = partition(list, low, high)
        quickSort(list, low, p - 1)
        quickSort(list, p + 1, high)

def merge(list1, list2):
    i = 0
    j = 0
    list3 = []

    while (i < len(list1) and j < len(list2)):
        if list1[i] < list2[j]:
            list3.append(list1[i])
            i += 1
        else:
            list3.append(list2[j])
            j += 1

    list3.extend(list1[i:])
    list3.extend(list2[j:])
    
    return list3

def mergeSort(list):
    if len(list) == 1:
        return list

    mid = len(list) // 2
    l1 = mergeSort(list[mid:])
    l2 = mergeSort(list[:mid])
    return merge(l1, l2)