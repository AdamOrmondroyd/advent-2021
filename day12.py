from copy import deepcopy

nodes = {}


def look_for_end_a(path_so_far, nodes, lowercase_visited):
    num_paths_count = 0

    current_node = path_so_far[-1]
    for next in nodes[current_node]:
        path_so_far_copy = deepcopy(path_so_far)
        lowercase_visited_copy = deepcopy(lowercase_visited)
        path_so_far_copy.append(next)
        if "end" == next:
            print(path_so_far_copy)
            num_paths_count += 1
        elif not (next.islower() and lowercase_visited_copy[next]):
            if next.islower():
                lowercase_visited_copy[next] = True
            num_paths_count += look_for_end_a(
                path_so_far_copy, nodes, lowercase_visited_copy
            )

    return num_paths_count


def look_for_end_b(path_so_far, nodes, lowercase_visited, used_double_visit):
    num_paths_count = 0

    current_node = path_so_far[-1]
    nexts = nodes[current_node]

    for next in nexts:
        path_so_far_copy = deepcopy(path_so_far)
        lowercase_visited_copy = deepcopy(lowercase_visited)
        used_double_visit_copy = used_double_visit
        path_so_far_copy.append(next)
        proceed = False
        if "end" == next:
            # print(path_so_far_copy)
            num_paths_count += 1
        elif not next.islower():
            proceed = True
        elif not lowercase_visited_copy[next]:
            proceed = True
            lowercase_visited_copy[next] = True

        elif not used_double_visit and next != "start":
            proceed = True
            used_double_visit_copy = True

        if proceed:
            num_paths_count += look_for_end_b(
                path_so_far_copy, nodes, lowercase_visited_copy, used_double_visit_copy
            )

    return num_paths_count


with open("input12.txt", "r") as file:

    lines = file.read().splitlines()
    lowercase_visited = {}

    for line in lines:
        [left, right] = line.split("-")

        for (a, b) in (left, right), (right, left):
            if a in nodes.keys():
                nodes[a].append(b)
            else:
                nodes[a] = [b]
                if a.islower():
                    lowercase_visited[a] = False

        path = []

    print(nodes)
    print(lowercase_visited)
    lowercase_visited["start"] = True
    # print(look_for_end_a(["start"], nodes, lowercase_visited))
    print(look_for_end_b(["start"], nodes, lowercase_visited, False))
