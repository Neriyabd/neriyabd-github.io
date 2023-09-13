#################################################################
# File : boggle_controller.py
# WRITERS : Roey Hel-Or , Neriya Ben David
# EXERCISE : intro2cs2 ex12 2021
# Description: Controller for combining model and GUI
#################################################################
from typing import List, Callable

from boggle_gui import BoggleGui
from boggle_model import BoggleModel, BoggleResponse
from boggle_types import BBoard, BPath

HINT_SHOW_TIME = 1000 * 40


class BoggleController:
    def __init__(self, words: List[str], get_board_func: Callable[[], BBoard]):
        self.words = words
        self._get_board_function = get_board_func

        self._gui = BoggleGui()
        self._model = None
        self._gui.set_menu_button_command(self._init_game)
        self._gui.set_timer_ends_command(self._end_game)

    def _init_game(self):
        """
        Calls when game is initialized from menu
        """
        board = self._get_board_function()
        self._model = BoggleModel(self.words, board)
        self._gui.load_board(board)
        self._gui.set_path_command(self._guess_pack_action)
        self._gui.set_get_timer_function(self._model.get_timer)
        self._gui.show_board()
        self._gui.start_timer()
        self._gui.set_score(0)
        self._gui.set_msg("")
        self._gui.show_hint_button()
        self._gui.set_hint_command(self._get_hint_action)

    def _end_game(self):
        self._gui.hide_board()
        self._gui.set_menu_label("Game Over", "Play Again?")
        self._gui.set_msg("")
        self._gui.hide_hint_button()

    def _response_to_msg(self, response: BoggleResponse):
        """
        Converts a BoggleResponse to an indicative message
        """
        msgs = {
            BoggleResponse.OK: "Correct!",
            BoggleResponse.ERROR_PATH_WORD_SUBMITTED: "Word already submitted!",
            BoggleResponse.ERROR_PATH_INVALID_PATH: "Word does not exist.",
            BoggleResponse.ERROR_TIME_EXCEEDED: "Error! Time Exceeded."
        }
        return msgs[response]

    def _guess_pack_action(self, path: BPath):
        """
        Calls when a path is guessed
        """
        response, word, added_score = self._model.submit_path(path)
        self._gui.set_msg(self._response_to_msg(response))
        if response == BoggleResponse.OK:
            self._gui.set_score(self._model.get_score())
            self._gui.add_guessed_word(word, added_score)

    def _get_hint_action(self):
        """
        Calls when asked for hint
        """
        hint_cells = self._model.get_hint()
        if not hint_cells:
            self._gui.set_msg("Hint: No more words")
            return
        self._gui.show_hint_cells(hint_cells, HINT_SHOW_TIME)
        self._gui.set_score(self._model.get_score())

    def run(self):
        """
        Runs GUI
        """
        self._gui.run()
