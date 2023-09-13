#################################################################
# File : types.py
# WRITERS : Roey Hel-Or , Neriya Ben David
# EXERCISE : intro2cs2 ex12 2021
# Description: Contains custom types definitions for Boggle project
#################################################################
from typing import NewType, Tuple, List

# Represents Boggle Board
BBoard = NewType("BBoard", List[List[str]])
BCell = NewType("BCell", Tuple[int, int])
BPath = NewType("BPath", List[BCell])
