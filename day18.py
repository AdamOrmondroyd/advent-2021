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


def idx_first_max_depth(depths):
    depths = np.array(depths)
    return np.where(depths == np.amax(depths))[0][0]


def magnitude_deepest(numbers, depths):
    idx = idx_first_max_depth(depths)
    mag = 3 * numbers[idx] + 2 * numbers[idx + 1]
    numbers[idx] = mag
    depths[idx] -= 1
    del numbers[idx + 1]
    del depths[idx + 1]


def magnitude(numbers, depths):
    while len(numbers) > 1:
        magnitude_deepest(numbers, depths)
    return numbers[0]


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


def add_lines(lines):
    depth = -1
    numbers = []
    depths = []
    for line in lines:

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
            if need_explode(depths):
                explode(numbers, depths)
                exploded = True
            else:
                exploded = False
            if not exploded and need_split(numbers):
                split(numbers, depths)
                splitted = True
            else:
                splitted = False
            if not exploded and not splitted:
                keep_going = False

    return magnitude(numbers, depths)


with open("input_example.txt") as file:
    lines = file.read().splitlines()

    # part a
    print(f"part a: {add_lines(lines)}")

    # part b
    magnitudes = np.zeros((len(lines), len(lines)))
    for ii, _ in enumerate(lines):
        for i, _ in enumerate(lines):
            if i != ii:
                magnitudes[ii, i] = add_lines([lines[i], lines[ii]])
                print(f"{i}, {ii} {magnitudes[ii, i]}")

    print(f"part b: {np.amax(magnitudes)}")
