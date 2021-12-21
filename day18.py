import numpy as np

numbers = []
depths = []
depth = -1


def need_explode(depths):
    return np.any(np.array(depths) >= 4)


def explode(numbers, depths):
    idx = 0
    exploded = False
    while idx < len(numbers) and not exploded:
        if depths[idx] >= 4:
            if idx > 0:
                numbers[idx - 1] += numbers[idx]
            if idx < len(numbers) - 2:
                numbers[idx + 2] += numbers[idx + 1]
            numbers[idx] = 0
            depths[idx] = 3
            del numbers[idx + 1]
            del depths[idx + 1]
            exploded = True

        idx += 1


def need_split(numbers):
    return np.any(np.array(numbers) >= 10)


def split(numbers, depths):
    idx = 0
    splitted = False
    while idx < len(numbers) and not splitted:
        if numbers[idx] >= 10:
            number = numbers[idx]
            numbers[idx] = int(np.floor(number / 2))
            numbers.insert(idx + 1, int(np.ceil(number / 2)))
            depths[idx] += 1
            depths.insert(idx + 1, depths[idx])
            splitted = True

        idx += 1


with open("input_example.txt") as file:
    lines = file.read().splitlines()
    for line in lines:
        print(line)

        for i, depth in enumerate(depths):
            depths[i] += 1
        if len(depths) != 0:
            depth = 0

        for _, character in enumerate(line):
            if "," == character:
                continue
            elif "[" == character:
                depth += 1
            elif "]" == character:
                depth -= 1
            else:
                numbers.append(int(character))
                depths.append(depth)

        exploded = False
        splitted = False
        keep_going = True

        while keep_going:
            print(numbers)
            print(depths)
            if need_explode(depths):
                print("explode")
                explode(numbers, depths)
                exploded = True
            else:
                exploded = False
            if not exploded and need_split(numbers):
                print("split")
                split(numbers, depths)
                splitted = True
            else:
                splitted = False
            if not exploded and not splitted:
                keep_going = False

        print(numbers)
        print(depths)

        # while not check_if_reduced(numbers, depths):
