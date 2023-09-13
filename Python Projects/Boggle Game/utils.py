#################################################################
# File : utils.py
# WRITERS : Roey Hel-Or , Neriya Ben David
# EXERCISE : intro2cs2 ex12 2021
# Description: Contains miscellaneous utils
#################################################################
from typing import List, Any


def enumerate_board(board: List[List[Any]]):
    """
    Enumerate over 2d Array
    """
    if not board:
        return
    for y in range(len(board)):
        for x in range(len(board[0])):
            yield (y, x), board[y][x]
