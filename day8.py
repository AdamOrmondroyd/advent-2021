file = open("input8.txt")

one_counter = 0
four_counter = 0
seven_counter = 0
eight_counter = 0

lines = file.readlines()
for line in lines:

    # check for \n character at end of line
    line = line.strip()
    print(line)

    [first_half, second_half] = line.split("|")

    print(second_half.split(" "))
    for output in second_half.split(" "):
        print(output)
        if len(output) == 2:
            one_counter += 1
        if len(output) == 3:
            seven_counter += 1
        if len(output) == 4:
            four_counter += 1
        if len(output) == 7:
            eight_counter += 1

    total = one_counter + four_counter + seven_counter + eight_counter

    print(
        "there are {} ones, {} fours, {} sevens and {} eights, which add to {}".format(
            one_counter, four_counter, seven_counter, eight_counter, total
        )
    )
