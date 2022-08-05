from cs50 import get_string

string = get_string("Text: ").strip()
num_words = num_letters = num_setences = 0

for i in range(len(string)):
    if (i == 0 and string[i] != ' ') or (i != len(string) - 1 and string[i] == ' ' and string[i + 1] != ' '):
        num_words += 1
    if string[i].isalpha():
        num_letters += 1
    if string[i] == '.' or string[i] == '?' or string[i] == '!':
        num_setences += 1

L = num_letters / num_words * 100
S = num_setences / num_words * 100
index = round(0.0588 * L - 0.296 * S - 15.8)
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")