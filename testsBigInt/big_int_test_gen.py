import random
import argparse


def random_big_int():
    abs_nums = [random.randint(1_000_000_000_000_000_000, 9_999_999_999_999_999_999_999_999_999_999_999_999),
                random.randint(1, 9_999_999), random.randint(1_000_000_000, 9_999_999_999_999_999)]
    return random.choice([-1, 1]) * random.choice(abs_nums)


def generate_test(test_cases_number, filename):
    with open(filename, 'w') as f:
        for _ in range(test_cases_number):
            a, b = random_big_int(), random_big_int()
            quotient = (1 if a // b > 0 else -1) * (abs(a) // abs(b))
            rest = a - quotient * b
            f.write(f'{a} {b} {a + b} {a - b} {a * b} {quotient} {rest} {a % b}\n')

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-t', '--testnum', type=int, help='Number of testcases')
    parser.add_argument('-f', '--filename', type=str, help='Filename you want to create')
    args = parser.parse_args()

    generate_test(args.testnum, args.filename)

