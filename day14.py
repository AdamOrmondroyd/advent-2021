import numpy as np

count_each_letter = np.zeros(26)
rules = {}
max_depth = 40

def increment_letter(letter):
    count_each_letter[ord(letter)-ord("A")]+=1

def grow(pair, depth):
    if depth >= max_depth:
        return
    new_letter = rules[pair]
    increment_letter(new_letter)
    left = f"{pair[0]}{new_letter}"
    grow(left, depth+1)
    right = f"{new_letter}{pair[1]}"
    grow(right, depth+1)


with open("input_example.txt", "r") as file:

    lines = file.read().splitlines()

    start_string = lines[0]
    rule_strings = lines[2:]
    for rule_string in rule_strings:
        rules[rule_string[:2]] = rule_string[6]
    
    for letter in start_string:
        increment_letter(letter)

    for i, _ in enumerate(start_string[:-1]):
        print(i)
        grow(start_string[i:i+2], 0)
        
    nonzeros = count_each_letter[np.nonzero(count_each_letter)]
    print(nonzeros)

    print(np.max(nonzeros)-np.min(nonzeros))