#################################################################
# File : boggle_gui/__init__.py
# WRITERS : Roey Hel-Or , Neriya Ben David
# EXERCISE : intro2cs2 ex12 2021
# Description: Implements GUI for Boggle game
#################################################################
import tkinter as tk
from typing import Callable, List

from boggle_gui.board import Board
from boggle_types import BBoard, BPath, BCell
from ex12_utils import get_word

BOARD_WIDTH, BOARD_HEIGHT = 410, 400

BG_COLOR = "White"
DEFAULT_RELIEF = "ridge"
DEFAULT_FONTSTYLE = "Courier"
TITLE_FONT = (DEFAULT_FONTSTYLE, 30)
LABEL_FONT = (DEFAULT_FONTSTYLE, 15)
BUTTON_ACTIVE_COLOR = "grey"
BUTTON_STYLE = {"font": ("Courier", 16), "borderwidth": 1, "relief": tk.RAISED,
                "bg": BG_COLOR,
                "activebackground": BUTTON_ACTIVE_COLOR}
BUTTON_HOVER_COLOR = "Blue"
BUTTON_COLOR_ON_CLICK = "grey"

SCORE_TEXT = "Score: {}"

GUESSED_WORDS_SCORE_COLOR = "green"


class BoggleGui:
    def __init__(self):
        self._root = tk.Tk()
        self._root.title("my Boggle")
        self._root.resizable(False, False)

        self._outer_frame = tk.Frame(self._root, bg=BG_COLOR)
        self._outer_frame.pack(side=tk.TOP, fill=tk.BOTH, expand=True)

        self._upper_frame = tk.Frame(self._outer_frame, bg=BG_COLOR)
        self._upper_frame.pack(side=tk.TOP, fill=tk.BOTH, expand=True)

        self._score_label = tk.Label(self._upper_frame,
                                     font=TITLE_FONT, bg=BG_COLOR,
                                     width=17,
                                     relief=DEFAULT_RELIEF)
        self._score_label.pack(side=tk.LEFT, fill=tk.BOTH)

        self._timer_label = tk.Label(self._upper_frame,
                                     font=TITLE_FONT, bg=BG_COLOR,
                                     width=6,
                                     relief=DEFAULT_RELIEF)
        self._timer_label.pack(side=tk.LEFT, fill=tk.BOTH)

        self._msg_label = tk.Label(self._outer_frame, font=LABEL_FONT,
                                   bg=BG_COLOR, width=10,
                                   relief=DEFAULT_RELIEF)
        self._msg_label.pack(side=tk.BOTTOM, fill=tk.BOTH)

        self._side_frame = tk.Frame(self._outer_frame, bg=BG_COLOR)
        self._side_frame.pack(side=tk.RIGHT, fill=tk.BOTH)

        self._words_guessed_label = tk.Text(self._side_frame,
                                            font=LABEL_FONT,
                                            bg=BG_COLOR, width=12,
                                            height=16, relief=DEFAULT_RELIEF)

        self._words_guessed_label.pack(side=tk.TOP, fill=tk.BOTH)
        self._words_guessed_label.tag_config("score",
                                             foreground=GUESSED_WORDS_SCORE_COLOR)

        self._hint_button = tk.Button(self._side_frame, text="Hint", width=11,
                                      **BUTTON_STYLE)

        self._menu_frame = tk.Frame(self._outer_frame, bg=BG_COLOR)
        self._menu_frame.pack(fill=tk.BOTH, expand=tk.YES)
        self._menu_label = tk.Label(self._menu_frame, borderwidth=0,
                                    font=TITLE_FONT, bg=BG_COLOR,
                                    relief=DEFAULT_RELIEF, text="Boggle")
        self._menu_label.pack(side=tk.TOP, expand=tk.YES)
        self._menu_button = tk.Button(self._menu_frame,
                                      text="Play", **BUTTON_STYLE)
        self._menu_button.pack(side=tk.TOP, expand=tk.YES)

        self._board_frame = tk.Frame(self._outer_frame)
        self._board = Board(self._board_frame, BOARD_WIDTH, BOARD_HEIGHT)
        self._board.pack()

        def _board_draw_action(path: BPath):
            """
            Will be called whenever a new cell is drawn on board
            """
            self._msg_label["text"] = get_word(self._board, path)

        self._board.draw_command = _board_draw_action

        self._get_timer_function = None
        self._timer_ends_command = None

    def load_board(self, board: BBoard):
        """
        Loads board array into GUI
        """
        self._board.load_board(board)

    def show_board(self):
        """
        Show game board
        """
        self._board_frame.pack()
        self._menu_frame.pack_forget()

    def hide_board(self):
        """
        Hide game Board
        """
        self._board_frame.pack_forget()
        self._menu_frame.pack(fill=tk.BOTH, expand=tk.YES)

    def show_hint_button(self):
        """
        Show hint button
        """
        self._hint_button.pack(side=tk.BOTTOM)

    def hide_hint_button(self):
        """
        Hide hint button
        """
        self._hint_button.pack_forget()

    def show_hint_cells(self, hint_cells: List[BCell], time: int):
        """
        Display hint cells for a given time
        """
        self._board.show_hint_cells(hint_cells)
        self._root.after(time, self._hide_hint_cells)

    def _hide_hint_cells(self):
        """
        Hide hint cells
        """
        self._board.hide_hint_cells()

    def set_menu_label(self, menu_text, button_text):
        """
        Sets menu text
        """
        self._menu_label["text"] = menu_text
        self._menu_button["text"] = button_text

    def start_timer(self):
        """
        Start timer
        """
        self._update_clock()

    def set_get_timer_function(self, func: Callable[[], float]):
        """
        Set function that returns timer
        """
        self._get_timer_function = func

    def _update_clock(self):
        """
        Interval function that calls every second
        """
        if not self._get_timer_function:
            return

        timer = max(int(self._get_timer_function()), 0)
        timer_text = "{:0>2}:{:0>2}".format(timer // 60, timer % 60)
        self._timer_label["text"] = timer_text
        if timer == 0:
            if self._timer_ends_command:
                self._timer_ends_command()
        else:
            self._root.after(1000, self._update_clock)

    def clear_guessed_words(self):
        """
        Clear guessed words list
        """
        self._words_guessed_label.delete('1.0', tk.END)

    def set_score(self, score: int):
        """
        Sets the score label
        """
        self._score_label["text"] = SCORE_TEXT.format(score)

    def set_msg(self, msg: str):
        """
        Set msg label
        """
        self._msg_label["text"] = msg

    def add_guessed_word(self, word: str, added_score=None):
        """
        Add word to guessed words label
        """
        self._words_guessed_label.insert(tk.END, word)
        if added_score is not None:
            text_len = len(self._words_guessed_label.get("1.0", 'end-1c'))
            added_score_text = "+" + str(added_score)
            self._words_guessed_label.insert(tk.END, " " + added_score_text)
            self._words_guessed_label.tag_add("score",
                                              "insert -1 char wordstart -1 char",
                                              "insert")
        self._words_guessed_label.insert(tk.END, "\n")
        self._words_guessed_label.see("end")

    def set_path_command(self, cmd: Callable[[BPath], None]):
        """
        Sets command to run when path is selected
        """
        self._board.select_command = cmd

    def set_hint_command(self, cmd: Callable[[], None]):
        self._hint_button["command"] = cmd

    def set_menu_button_command(self, cmd: Callable[[], None]):
        """
        Sets command to run when menu button is clicked
        """
        self._menu_button["command"] = cmd

    def set_timer_ends_command(self, cmd: Callable[[], None]):
        """
        Sets command to run when timer ends.
        """
        self._timer_ends_command = cmd

    def run(self):
        self._root.mainloop()
