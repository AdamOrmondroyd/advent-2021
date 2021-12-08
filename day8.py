from copy import deepcopy

file = open("input8.txt")

one_counter = 0
four_counter = 0
seven_counter = 0
eight_counter = 0
result = 0


def string_to_set(string_to_split):
    return set([char for char in string_to_split])


lines = file.readlines()
for line in lines:

    # check for and remove \n character at end of line
    line = line.strip()

    [first_half, second_half] = line.split("|")

    for output in second_half.split(" "):
        if len(output) == 2:
            one_counter += 1
        if len(output) == 3:
            seven_counter += 1
        if len(output) == 4:
            four_counter += 1
        if len(output) == 7:
            eight_counter += 1

    total = one_counter + four_counter + seven_counter + eight_counter

    unique_strings = first_half.split(" ")[:-1]

    numbers = {}
    remaining_numbers = []
    sixes = []
    cde = set()

    # start by dealing with easy 1, 4, 7 and 8
    for unique in unique_strings:
        if len(unique) == 2:
            numbers["1"] = string_to_set(unique)
        elif len(unique) == 4:
            numbers["4"] = string_to_set(unique)
        elif len(unique) == 3:
            numbers["7"] = string_to_set(unique)
        elif len(unique) == 7:
            numbers["8"] = string_to_set(unique)
        elif len(unique) == 6:
            sixes.append(string_to_set(unique))
        else:
            remaining_numbers.append(string_to_set(unique))

    # 9 is the six which contains 4
    for six in deepcopy(sixes):
        if six.intersection(numbers["4"]) == numbers["4"]:
            numbers["9"] = six
            break

    # look for letters which only occur in two of the sixes, and the one also in 1 is c
    for i, j, k in [(0, 1, 2), (1, 2, 0), (2, 0, 1)]:
        cde.update(sixes[i].intersection(sixes[j]).difference(sixes[k]))

    c = numbers["1"].intersection(cde)
    f = numbers["1"].difference(c)

    # whichever six which isn't 9 and doesn't contain c is 6
    sixes.remove(numbers["9"])
    for six in sixes:
        if c.issubset(six):
            numbers["0"] = six
        else:
            numbers["6"] = six

    # 5 is 9 without c
    numbers["5"] = numbers["9"].difference(c)
    remaining_numbers.remove(numbers["5"])

    # 2 is the one remaining not containing f
    for remaining_number in remaining_numbers:
        if len(f.intersection(remaining_number)) == 0:
            numbers["2"] = remaining_number
            remaining_numbers.remove(remaining_number)
            break

    # last one is 3
    numbers["3"] = remaining_numbers[0]

    result_string = ""

    for output in second_half.split(" "):
        for i in range(10):
            if string_to_set(output) == numbers[str(i)]:
                result_string += str(i)

    result += int(result_string)

# part a
print(
    "there are {} ones, {} fours, {} sevens and {} eights, which add to {}".format(
        one_counter, four_counter, seven_counter, eight_counter, total
    )
)

# part b
print("The sum of all the output numbers is {}".format(result))
