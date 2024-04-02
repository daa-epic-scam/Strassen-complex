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
    return s + "#\n"

def main():
    s = matrix_gen(8192, 8192)

    print(s.strip())

if __name__ == "__main__":
    main()
