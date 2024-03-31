import numpy as np

def matrix_gen(rows, cols):
    s = f"{rows},{cols}\n"
    for _ in range(rows):
        for j in range(cols):
            real, im = np.round(np.random.rand(2) * 100, 2)
            if j < cols-1:
                s += f"{real}+{im}i,"
            else:
                s += f"{real}+{im}i\n"
    return s

def main():
    rows = 1024
    cols = 1024
    s = matrix_gen(rows, cols)
    with open("output.txt", "w") as file:
        file.write(s)

if __name__ == "__main__":
    main()
