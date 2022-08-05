import csv
import sys


def main():
    # test files are correct
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)
    # open file
    d = open(sys.argv[2], "r").read()

    with open(sys.argv[1]) as file:
        r = csv.DictReader(file)
        test = r.fieldnames[1:]
        count = {}

        for i in test:
            temp = seqMaior = atualSeq = 0

            while temp < len(d):
                tempString = d[temp: temp + len(i)]
                # count sequences
                if tempString == i:
                    atualSeq += 1
                    temp = temp + len(i)
                else:
                #found the longest sequence
                    if seqMaior < atualSeq:
                        seqMaior = atualSeq
                    atualSeq = 0
                    temp += 1

            count[i] = seqMaior

        for p in r:
            nome = p["name"]
            founded = True

            for i in test:
                if count[i] != int(p[i]):
                    founded = False
                    break

            if founded:
                print(nome)
                sys.exit(0)

        print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
