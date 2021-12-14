import numpy as np
from copy import deepcopy

count_each_letter = np.zeros(26)
num_each_pair = {}
rules = {}
max_depth = 40


def increment_letter(letter, num_occurrences):
    count_each_letter[ord(letter) - ord("A")] += num_occurrences


def grow(pair, depth):
    if depth >= max_depth:
        return
    new_letter = rules[pair]
    increment_letter(new_letter)
    left = f"{pair[0]}{new_letter}"
    grow(left, depth + 1)
    right = f"{new_letter}{pair[1]}"
    grow(right, depth + 1)


with open("input14.txt", "r") as file:

    lines = file.read().splitlines()

    start_string = lines[0]
    rule_strings = lines[2:]
    for rule_string in rule_strings:
        rules[rule_string[:2]] = rule_string[6]
        num_each_pair[rule_string[:2]] = 0

    for letter in start_string:
        increment_letter(letter, 1)

    for i, _ in enumerate(start_string[:-1]):
        num_each_pair[start_string[i : i + 2]] += 1

    for i in range(max_depth):
        new_num_each_pair = deepcopy(num_each_pair)
        for pair in num_each_pair.keys():
            new_letter = rules[pair]
            num_new = num_each_pair[pair]
            if num_new > 0:
                increment_letter(new_letter, num_new)
                new_num_each_pair[pair] -= num_new

                for new_pair in f"{pair[0]}{new_letter}", f"{new_letter}{pair[1]}":
                    new_num_each_pair[new_pair] += num_new

        num_each_pair = new_num_each_pair

    nonzeros = count_each_letter[np.nonzero(count_each_letter)]

    print(np.max(nonzeros) - np.min(nonzeros))
