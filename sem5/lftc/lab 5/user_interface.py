import os

from grammar import Grammar
from lr1_parser import LR1Parser


class UserInterface:
    @classmethod
    def _parse_strings(cls, parser: LR1Parser):
        while True:
            string = input("String to be parsed: ")
            if string == "":
                break
            print(parser.parse_string(string))

    @classmethod
    def run(cls):
        print("Tip: Enter empty string if you want to break :D\n")
        while True:
            file_name = input("Enter the name of the file with the grammar: ")
            if file_name == "":
                print("Bye!")
                break
            file_path = os.path.join("inputs", file_name)
            grammar = Grammar.from_file(file_path)
            parser = LR1Parser(grammar)

            while True:
                print("1. Parse some input strings")
                print("2. Parse some input files")
                print("0. Exit")
                option = int(input("> "))

                if option not in [0, 1, 2]:
                    raise ValueError("Invalid option!")

                if option == 1:
                    cls._parse_strings(parser)
                elif option == 2:
                    cls._parse_files(grammar)
                else:
                    break
