#################################################################
# File : ex12utils.py
# WRITERS : Roey Hel-Or , Neriya Ben David
# EXERCISE : intro2cs2 ex12 2021
# Description: Contains utils for EX12
#################################################################

from typing import List, Set, Iterator

from boggle_types import BBoard, BPath, BCell
# Dict which contain all the directions that can are legal
from utils import enumerate_board

DICT_DIRECTION = {"DOWN_LEFT": (1, -1), "DOWN": (1, 0), "DOWN_RIGHT": (1, 1),
                  "LEFT": (0, -1), "RIGHT": (0, 1),
                  "UP_LEFT": (-1, -1), "UP": (-1, 0), "UP_RIGHT": (-1, 1)}


def get_word(board: BBoard, path: BPath):
    """
    Gets word from board
    """
    return "".join([board[c[0]][c[1]] for c in path])


def _is_in_boundaries(board: BBoard, cell: BCell):
    """
    Checks if cell is in board boundaries
    """
    return 0 <= cell[0] < len(board) and 0 <= cell[1] < len(board[0])


def _is_valid_step(cell: BCell, prev_cell: BCell):
    """
    Check if step in path is legal
    """
    return abs(cell[0] - prev_cell[0]) <= 1 and abs(
        cell[1] - prev_cell[1]) <= 1


def is_valid_path(board: BBoard, path: BPath, words: List[str]):
    """
    get a path as an input and returns a word that composed by that path,
    if the path is valid
    :param board: A lists of lists of strings that contains the game's board
    :param path: A list of tuples that contain row and column
    :param words: A list of strings of words
    :return: A string if the input is valid and None if it is not.
    """
    # Check that path does not contain duplicate cells:
    if len(set(path)) != len(path):
        return None
    word = ""
    for i, cell in enumerate(path):
        # Check if in boundaries:
        if not _is_in_boundaries(board, cell):
            return None
        # Check if valid step
        if i != 0 and not _is_valid_step(cell, path[i - 1]):
            return None
        word += board[cell[0]][cell[1]]
    if word not in words:
        return None
    return word


def get_board_letters(board: BBoard) -> Set[str]:
    """
    create a list of the strings that are in the boggles board
    :param board: A lists of lists of strings that contains the game's board
    :return: A list of strings
    """
    return set(list(zip(*enumerate_board(board)))[1])


def _filter_words_for_path_n(board, words, n):
    """
    Filter word list so that will only contain letters from board and its path
    wont be too long. Used for find_length_n_paths
    """
    board_letters = get_board_letters(board)
    long_letters = [l for l in board_letters if len(l) > 1]
    filtered_words = []
    for word in words:
        long_letters_in_word = [l for l in long_letters if l in word]
        if len(word) == n or long_letters_in_word:
            filtered_words.append(word)
    return filtered_words


def _filter_words_by_length(words, n):
    """
    Filter word list by length
    Used for find_length_n_words
    """
    filtered_words = []
    for word in words:
        if len(word) == n:
            filtered_words.append(word)
    return filtered_words


def _filter_words_by_prefix(words: List[str], prefix: str):
    """
    Filter only words that start with prefix and return the words without
    their prefix
    """
    return [w[len(prefix):] for w in words if w.startswith(prefix)]


def _find_all_paths_helper(board: BBoard, words: List[str],
                           current_path: BPath, stop_function=None) -> \
        Iterator[BPath]:
    """
    Helper for find all paths
    """
    cell = current_path[-1]
    prefix = board[cell[0]][cell[1]]
    filtered_words = _filter_words_by_prefix(words, prefix)
    # Check if there could be any words from path
    if len(filtered_words) == 0:
        return []
    # Check if should stop route searching according to stop_function
    if stop_function and stop_function(current_path):
        return []

    # Check if path is word and yield it if necessary
    if "" in filtered_words:
        yield current_path

    # Check each direction
    for delta in DICT_DIRECTION.values():
        next_cell = (cell[0] + delta[0], cell[1] + delta[1])
        if _is_in_boundaries(board, next_cell) and \
                _is_valid_step(cell, next_cell) and \
                next_cell not in current_path:
            yield from _find_all_paths_helper(board, filtered_words,
                                              current_path + [next_cell])


def find_all_paths(board: BBoard, words: List[str], stop_function=None):
    """
    This is a recursive function that checks all the possible paths to find
    words in the board
    receives an optional stop_function paramater to indicate when to stop
    iterating on a specific path
    """
    # Start searching a path from each cell in board
    for cell, _ in enumerate_board(board):
        yield from _find_all_paths_helper(board, words, [cell],
                                          stop_function=stop_function)


def find_length_n_words(n: int, board: BBoard, words: List[str]) -> List[
    BPath]:
    """
    Find all paths for words that are of length n
    """
    # Filter only words that are of length n
    filtered_words = _filter_words_by_length(words, n)
    return list(find_all_paths(board, filtered_words))


def find_length_n_paths(n: int, board: BBoard, words: List[str]) -> List[
    BPath]:
    """
    This function finds all the possible routes to compose a word in the
    boggle board
    :param n: An int the represents the current path length
    :param board: A list of lists that contains the board of boggle
    :param words: A list of strings which contains all the given words
    :return: A list of lists of tuples
    """

    # Define a stop function to stop searching a path when its length is
    # bigger than n
    def _stop_function(path):
        return len(path) > n

    # Inital words filtering for, will reduce words_list greatly for
    # efficiency
    filtered_words = _filter_words_for_path_n(board, words, n)
    all_paths = find_all_paths(board, filtered_words,
                               stop_function=_stop_function)
    # Filter only paths that are of length n
    return [p for p in all_paths if len(p) == n]


def calculate_score(path: BPath) -> int:
    """
    Calculate score for a specific path
    """
    return len(path) ** 2


def max_score_paths(board: BBoard, words: List[str]) -> List[BPath]:
    """
    Will return all paths for each word, so that each word will have a maximum
    score.
    Will sort paths by scores
    """
    paths_dict = {}
    for path in find_all_paths(board, words):
        word = get_word(board, path)
        last_path = paths_dict.get(word, [])
        if calculate_score(last_path) <= calculate_score(path):
            paths_dict[word] = path
    return sorted(list(paths_dict.values()), key=calculate_score, reverse=True)
