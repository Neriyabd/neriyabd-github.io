#################################################################
# File : boggle_gui/board.py
# WRITERS : Roey Hel-Or , Neriya Ben David
# EXERCISE : intro2cs2 ex12 2021
# Description: Implements special GUI widgets for Boggle board
#################################################################
import tkinter as tk
from typing import List

from boggle_gui.images import get_image_dicts
from boggle_types import BCell
from ex12_utils import get_board_letters
from utils import enumerate_board

BOARD_BACKGROUND = "orange"
BOARD_BORDER = "black"
CELL_PADDING = 10
CELL_DRAW_PADDING = 10
LINE_WIDTH = 20
LINE_COLOR = "#a80000"


class PathBoard:
    """
    Class representing the a board that draws a path
    Wraps Tkinter canvas as a path list
    """

    def __init__(self, root, width, height):
        self._path = []
        self.width = width
        self.height = height
        self._root = root

        self._board = None
        self._btn_img, self._btn_img_clicked, self._btn_img_hint = \
            None, None, None
        self._grid_size = 0
        self._cell_w = 0
        self._cell_h = 0
        self._cell_padding = CELL_PADDING
        self._cell_draw_padding = CELL_DRAW_PADDING

        self._path = []
        self._line = None

        self._canvas = tk.Canvas(root, width=width, height=height,
                                 background=BOARD_BACKGROUND,
                                 highlightbackground=BOARD_BORDER)

    def load_board(self, board):
        """
        Loads board to Canvas
        """
        self._board = board
        self._grid_size = len(board)
        self._cell_w = self.width // self._grid_size
        self._cell_h = self.height // self._grid_size
        self._btn_img, self._btn_img_clicked, self._btn_img_hint = \
            get_image_dicts(self._cell_w - self._cell_draw_padding * 2,
                            self._cell_h - self._cell_draw_padding * 2,
                            get_board_letters(board))

        self._draw_board()

    def pack(self, *args, **kwargs):
        """
        Wraps canvas pack function
        """
        return self._canvas.pack(*args, **kwargs)

    def _draw_board(self):
        """
        Draw board in canvas
        """
        # Clear board
        self._canvas.delete("all")
        self._path = []
        self._line = None

        self._cells = []
        for index_y in range(self._grid_size):
            cells_row = []
            for index_x in range(self._grid_size):
                img_x1 = self._cell_w * index_x + self._cell_draw_padding
                img_y1 = self._cell_h * index_y + self._cell_draw_padding
                text = self._board[index_y][index_x]
                item = self._canvas.create_image(img_x1, img_y1,
                                                 image=self._btn_img[text],
                                                 anchor=tk.NW)
                cells_row.append(item)
            self._cells.append(cells_row)

    def bind(self, sequence=None, func=None):
        """
        Wraps bind function
        """
        return self._canvas.bind(sequence, func)

    def append(self, coord):
        """
        Append coord to path
        """
        if not self._board:
            raise ValueError("Board is not loaded to board widget")
        item = self._cells[coord[0]][coord[1]]
        text = self._board[coord[0]][coord[1]]
        self._canvas.itemconfig(item, image=self._btn_img_clicked[text])
        self._path.append(coord)
        self._redraw_line()

    def show_hint_cells(self, hint_cells: List[BCell]):
        """
        Draw cells of hint
        """
        if not self._board:
            raise ValueError("Board is not loaded to board widget")
        if self._path:
            raise ValueError(
                "Cannot change board cell images if path is drawn")
        for i, j in hint_cells:
            text = self._board[i][j]
            item = self._cells[i][j]
            self._canvas.itemconfig(item, image=self._btn_img_hint[text])

    def hide_hint_cells(self):
        """
        Hide hint cells
        """
        for (i, j), item in enumerate_board(self._cells):
            # If cell is in path, then it is not hint
            if (i, j) in self._path:
                continue
            text = self._board[i][j]
            self._canvas.itemconfig(item, image=self._btn_img[text])

    def clear(self):
        """
        Clear path list
        """
        if not self._board:
            raise ValueError("Board is not loaded to board widget")
        self._path.clear()
        # Clear board in canvas
        for (i, j), item in enumerate_board(self._cells):
            text = self._board[i][j]
            self._canvas.itemconfig(item, image=self._btn_img[text])
        self._redraw_line()

    def pop(self):
        """
        Pops last coord from path
        """
        if not self._board:
            raise ValueError("Board is not loaded to board widget")
        last = self._path.pop()
        text = self._board[last[0]][last[1]]
        self._canvas.itemconfig(
            self._cells[last[0]][last[1]],
            image=self._btn_img[text])
        self._redraw_line()

    def _redraw_line(self):
        """
        Update drawn line
        """
        # Delete line if no cells are selected
        if not self._path:
            if self._line:
                self._canvas.delete(self._line)
            self._line = None
            return
        # Redefine coords for line
        coords = [self.index_to_coord(self._path[0])]
        coords += [self.index_to_coord(ind) for ind in self._path]
        # Flatten coords
        coords = [val for coord in coords for val in coord]
        # Create line if needed
        if not self._line:
            self._line = self._canvas.create_line(*coords,
                                                  fill=LINE_COLOR,
                                                  width=LINE_WIDTH)
            self._canvas.tag_lower(self._line)
        else:
            self._canvas.coords(self._line, *coords)

    def coord_to_index(self, y, x):
        """
        Return index of cell in coords
        """
        index_y = int(y // self._cell_h)
        index_x = int(x // self._cell_w)
        # Check in bounds
        if not 0 <= index_x < self._grid_size or \
                not 0 <= index_y < self._grid_size:
            return None
        # Check if not on padding
        # Calculate relative distances
        from_left = x - self._cell_w * index_x
        from_top = y - self._cell_h * index_y
        from_right = self._cell_w - from_left
        from_bottom = self._cell_h - from_top
        if list(filter(lambda p: p < self._cell_padding,
                       [from_left, from_top, from_right, from_bottom])):
            return None
        # Return index
        return index_y, index_x

    def index_to_coord(self, ind):
        """
        Return coords of middle of cell in coordinated ind
        """
        return self._cell_w * ind[1] + self._cell_w // 2, \
               self._cell_h * ind[0] + self._cell_h // 2

    def __contains__(self, *args, **kwargs):
        return self._path.__contains__(*args, **kwargs)

    def __eq__(self, *args, **kwargs):
        return self._path.__eq__(*args, **kwargs)

    def __getitem__(self, *args, **kwargs):
        return self._path.__getitem__(*args, **kwargs)

    def __iter__(self, *args, **kwargs):
        return self._path.__iter__(*args, **kwargs)

    def __len__(self, *args, **kwargs):
        return self._path.__len__(*args, **kwargs)

    def __repr__(self, *args, **kwargs):
        return self._path.__repr__(*args, **kwargs)

    def __bool__(self):
        return bool(self._path)


class Board:
    """
    Represents a Boggle board in Gui, that allows path selection
    """

    def __init__(self, root, width, height,
                 draw_command=None, select_command=None):
        self.root = root
        self._board = []
        self.select_command = select_command
        self.draw_command = draw_command

        self._pathb = PathBoard(root, width, height)

        self._is_drawing = False

        self._pathb.bind("<Button-1>", self._action_on_click)
        self._pathb.bind("<ButtonRelease-1>", self._action_on_release)
        self._pathb.bind("<Motion>", self._action_on_motion)

    def show_hint_cells(self, hint_cells: List[BCell]):
        """
        Draw cells of hint
        """
        self._pathb.clear()
        self._pathb.show_hint_cells(hint_cells)

    def hide_hint_cells(self):
        """
        Hide cells of hint
        """
        self._pathb.hide_hint_cells()

    def load_board(self, board):
        """
        Loads board to GUI
        """
        self._board = board
        self._pathb.load_board(board)

    def pack(self, *args, **kwargs):
        """
        Wraps canvas pack function
        """
        return self._pathb.pack(*args, **kwargs)

    def _action_on_click(self, e):
        """
        Called when mouse is clicked on board canvas
        """
        self._is_drawing = True

    def _action_on_release(self, e):
        """
        Called when mouse is released on board canvas
        """
        self._is_drawing = False
        if self._pathb and self.select_command:
            self.select_command(list(self._pathb))
        self._pathb.clear()

    def _is_legal_to_path(self, cell_index):
        """
        Checks if index can be legally appended to path according to path rules
        """
        if not self._pathb:
            return True
        if cell_index in self._pathb:
            return False
        return abs(self._pathb[-1][0] - cell_index[0]) <= 1 and \
               abs(self._pathb[-1][1] - cell_index[1]) <= 1

    def _action_on_motion(self, e):
        """
        Called when mouse is moved over board canvas
        """
        if not self._is_drawing:
            return
        cell_index = self._pathb.coord_to_index(e.y, e.x)
        # Check mouse is on cell
        if not cell_index:
            return
        # Check if first in path
        if self._pathb:
            # Check that a new cell is selected
            last_selected = self._pathb[-1]
            if last_selected == cell_index:
                return
            # Check whether user wants to revert last selected
            if len(self._pathb) >= 2 and self._pathb[-2] == cell_index:
                self._pathb.pop()
                return
            # Check cell is legal according to path rules
            if not self._is_legal_to_path(cell_index):
                return
        self._pathb.append(cell_index)
        # Call draw command if exists
        if self.draw_command:
            self.draw_command(list(self._pathb))

    def __contains__(self, *args, **kwargs):
        return self._board.__contains__(*args, **kwargs)

    def __eq__(self, *args, **kwargs):
        return self._board.__eq__(*args, **kwargs)

    def __getitem__(self, *args, **kwargs):
        return self._board.__getitem__(*args, **kwargs)

    def __iter__(self, *args, **kwargs):
        return self._board.__iter__(*args, **kwargs)

    def __len__(self, *args, **kwargs):
        return self._board.__len__(*args, **kwargs)

    def __repr__(self, *args, **kwargs):
        return self._board.__repr__(*args, **kwargs)
