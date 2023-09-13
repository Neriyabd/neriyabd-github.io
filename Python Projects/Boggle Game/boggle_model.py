#################################################################
# File : boogle_model.py
# WRITERS : Roey Hel-Or , Neriya Ben David
# EXERCISE : intro2cs2 ex12 2021
# Description: Implementation of Boggle game logic
#################################################################
import time
from enum import Enum, auto
from typing import List, Tuple, Optional

from boggle_types import BBoard, BPath
from ex12_utils import is_valid_path, get_word, max_score_paths, \
    calculate_score

TIMER = 3 * 60 + 1
HINT_PRICE = 10


class BoggleResponse(Enum):
    """
    Represents a response when an action is made
    """
    # The action was submitted successfully
    OK = auto()
    # Reached the time limit
    ERROR_TIME_EXCEEDED = auto()

    # Responses for submitting paths #
    # Path is invalid
    ERROR_PATH_INVALID_PATH = auto()
    # Word was already submitted
    ERROR_PATH_WORD_SUBMITTED = auto()


class BoggleModel:
    """
    Class representing a running boggle game
    """

    def __init__(self, words: List[str], board: BBoard, time_limit=TIMER):
        self._board = board
        self._words = words
        self._words_submitted = []
        self._time_limit = time_limit
        self._start_time = time.time()
        self._score = 0

    def get_hint(self) -> Optional[BPath]:
        """
        Gets a hint for word, reduces score by a constant amount
        """
        paths = max_score_paths(self._board, self._words)
        unguessed_paths = [p for p in paths if get_word(self._board,
                                                        p) not in self._words_submitted]
        if not unguessed_paths:
            return None
        self._score -= HINT_PRICE
        return sorted(unguessed_paths[0])

    def get_board(self):
        """
        Returns game board
        """
        return self._board

    def get_word_from_path(self, path: BPath):
        """
        Returns word from path
        """
        return get_word(self._board, path)

    def get_timer(self):
        """
        Get how much time until game ends
        """
        return self._start_time + self._time_limit - time.time()

    def _check_time(self):
        """
        Checks if time limit wasn't reached
        """
        return time.time() - self._start_time <= self._time_limit

    def get_score(self) -> int:
        """
        Returns score
        """
        return self._score

    def submit_path(self, path: BPath) -> \
            Tuple[BoggleResponse, Optional[str], Optional[int]]:
        """
        Submits a path
        Returns a BoogleResponse, the word and the added score
        """
        # Check time
        if not self._check_time():
            return BoggleResponse.ERROR_TIME_EXCEEDED, None, None
        # Check path
        word = is_valid_path(self._board, path, self._words)
        if not word:
            return BoggleResponse.ERROR_PATH_INVALID_PATH, None, None
        # Check word was not already submitted
        if word in self._words_submitted:
            return BoggleResponse.ERROR_PATH_WORD_SUBMITTED, None, None
        # Submit word
        self._words_submitted.append(word)
        added_score = calculate_score(path)
        self._score += added_score
        return BoggleResponse.OK, word, added_score
