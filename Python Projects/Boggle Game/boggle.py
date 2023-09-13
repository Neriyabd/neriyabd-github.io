#################################################################
# File : boggle.py
# WRITERS : Roey Hel-Or , Neriya Ben David
# EXERCISE : intro2cs2 ex12 2021
# Description: Main file for running Boggle GUI
#################################################################
from boggle_board_randomizer import randomize_board
from boggle_controller import BoggleController


def main():
    words = open("boggle_dict.txt", "r").read().splitlines()
    controller = BoggleController(words, randomize_board)
    controller.run()


if __name__ == "__main__":
    main()
