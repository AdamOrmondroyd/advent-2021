import statistics

scores_b = []

with open("input10.txt", "r") as file:

    lines = file.read().splitlines()

    pairs = {
        ")": "(",
        "]": "[",
        "}": "{",
        ">": "<",
    }
    scores_a_map = {
        ")": 3,
        "]": 57,
        "}": 1197,
        ">": 25137,
    }
    scores_b_map = {
        "(": 1,
        "[": 2,
        "{": 3,
        "<": 4,
    }

    score_a = 0

    scores_b = []

    for line in lines:
        score_b = 0
        incorrect = False
        stack = []
        for bracket in line:
            # if it's an open bracket, append
            if bracket in pairs.values():
                stack.append(bracket)
            # close bracket so check it matches using the pairs dict
            else:
                open = stack.pop()
                if open != pairs[bracket]:
                    score_a += scores_a_map[bracket]
                    incorrect = True

        if not incorrect:
            while len(stack) > 0:
                score_b *= 5
                score_b += scores_b_map[stack.pop()]

            if score_b > 0:
                scores_b.append(score_b)

    score_b = statistics.median(scores_b)

    print(f"part a: {score_a}, part b: {score_b}")
