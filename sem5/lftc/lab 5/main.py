from grammar import Grammar
from user_interface import UserInterface

if __name__ == "__main__":
    grammar = Grammar.from_file("inputs/language.txt")
    ui = UserInterface()
    ui.run()
