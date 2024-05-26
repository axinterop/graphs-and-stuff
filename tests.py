import os

LENGTH_ERROR_CODE = -2

tests_dir = "tests"

in_files = [
    "test_2p_in.txt",
    "test_10_in.txt",
    "test_20_in.txt",
    "test_Pl_in.txt",
]
test_input_files = [os.path.join(tests_dir, file) for file in in_files]

out_files = [
    "test_2p_out.txt",
    "test_10_out.txt",
    "test_20_out.txt",
    "test_Pl_out.txt",
]
test_output_files = [os.path.join(tests_dir, file) for file in out_files]

program_output = [tests_dir + "/_py_" + f for f in out_files]


def get_program_output(test_num) -> list:
    os.system(
        f"cmake-build-debug/project3 < {test_input_files[test_num]} > {program_output[test_num]}")
    with open(program_output[test_num], 'r') as f:
        return [line.strip() for line in f.readlines()]


def get_graph_line(test_num: int, graph_num: int):
    with open(test_input_files[test_num], 'r') as f:
        lines = [line.strip() for line in f.readlines()]
        num_of_graphs = int(lines[0])
        if graph_num > num_of_graphs:
            print("get_graph_line: graph_num > num_of_graphs")
            exit(1)
        how_much_to_skip = -1
        skip = 2
        for i in range(1, graph_num):
            how_much_to_skip += int(lines[how_much_to_skip + skip])
            skip += 1
        return how_much_to_skip + skip + 1


def compare_results(test_num: int, test: list, program: list, ignore_question: bool = True):
    print()
    print(f"-------------- TEST #{test_num + 1} --------------")

    if len(test) != len(program):
        print("Test and program output lengths are not equal, terminating...")
        return LENGTH_ERROR_CODE, False

    error_counter = 0
    graph_num = 0
    graph_num_print = True
    has_question = False

    for line_num in range(len(program)):
        if line_num % 10 == 0:
            graph_num = line_num // 10 + 1
            graph_num_print = True

        p = program[line_num]
        t = test[line_num]

        if ignore_question and p == "?":
            has_question = True
            error_counter += 1
            continue
        if p == t:
            continue

        if graph_num_print:
            print(f"           Graph #{
                  test_num+1}.{graph_num}:{get_graph_line(test_num, graph_num)}")
            graph_num_print = False

        error_counter += 1

        graph_line_num = line_num % 10

        if graph_line_num == 0:
            print("1. Wrong degree sequence")
        elif graph_line_num == 1:
            print("2. Wrong number of components")
        elif graph_line_num == 2:
            print("3. Incorrect bipartiteness detection")
        elif graph_line_num == 3:
            print("4. Wrong eccentricity of vertices")
        elif graph_line_num == 4:
            print("5. Incorrect planarity detection")
        elif graph_line_num == 5:
            print("6(a). Incorrect coloring using greedy method")
        elif graph_line_num == 6:
            print("6(b). Incorrect coloring using LF method")
        elif graph_line_num == 7:
            print("6(c). Incorrect coloring using SLF method")
        elif graph_line_num == 8:
            print("7. Wrong number of different C4 subgraphs")
        elif graph_line_num == 9:
            print("8. Wrong number of the graph complement's edges")
    return error_counter, has_question


def main():
    test_num = 4
    ignore_q = True
    total_errors = 0
    total_cases = 0
    has_question = False

    for t in range(test_num):
        f_out = open(test_output_files[t], 'r')
        test_lines = [line.strip() for line in f_out.readlines()]
        program_lines = get_program_output(t)
        total_cases += len(test_lines)

        result, has_question = compare_results(
            t, test_lines, program_lines, ignore_q)
        if result == LENGTH_ERROR_CODE:  # different lengths
            total_errors += len(test_lines)
        else:
            total_errors += result

        f_out.close()

    print()
    print(f"-------------- SUMMARY --------------")
    print(f"Configuration:")
    print(f"> Number of tests: {4}")
    print(f"> Ignore question mark: {ignore_q}")
    if total_errors == 0:
        print("All tests passed")
    else:
        if has_question:
            print("Some features have not been implemented ('?' in output)")
        print(f"Total errors: {total_errors}")
    print(f"Result: {(total_cases - total_errors) / total_cases * 100}%")


if __name__ == "__main__":
    main()
