#################################################################
# File : boggle_gui/images.py
# WRITERS : Roey Hel-Or , Neriya Ben David
# EXERCISE : intro2cs2 ex12 2021
# Description: Contains functions for loading image resources
#################################################################
from enum import Enum, auto
from string import ascii_uppercase

from PIL import Image, ImageTk, ImageDraw, ImageFont


class LetterState(Enum):
    """
    Represents a letter state
    """
    DEFAULT = auto()
    CLICKED = auto()
    HINT = auto()


LETTER_IMAGE_PATH = "images/letters/{}.png"
LETTER_CLICKED_IMAGE_PATH = "images/letters_clicked/{}.png"
LETTER_HINT_IMAGE_PATH = "images/letters_hint/{}.png"

STATE_TO_PATH = {
    LetterState.DEFAULT: LETTER_IMAGE_PATH,
    LetterState.CLICKED: LETTER_CLICKED_IMAGE_PATH,
    LetterState.HINT: LETTER_HINT_IMAGE_PATH
}

STATE_TO_COLOR = {
    LetterState.DEFAULT: (254, 234, 76),
    LetterState.CLICKED: (248, 255, 172),
    LetterState.HINT: (91, 136, 252)
}


def get_image_dicts(width, height, letters):
    """
    Loads images from files into dicts
    """
    letters_default = {}
    letters_clicked = {}
    letters_hint = {}
    for l in letters:
        letters_default[l] = load_letter_image(width, height, l,
                                               LetterState.DEFAULT)
        letters_clicked[l] = load_letter_image(width, height, l,
                                               LetterState.CLICKED)
        letters_hint[l] = load_letter_image(width, height, l, LetterState.HINT)
    return letters_default, letters_clicked, letters_hint


def load_letter_image(width, height, letter, state: LetterState):
    """
    Load letter image
    """
    img_path = STATE_TO_PATH[state]
    ready_letter = letter in list(ascii_uppercase) + ["QU"]
    filename = letter if ready_letter else "CUSTOM"
    image = Image.open(img_path.format(filename))
    if not ready_letter:
        img_w, img_h = image.size
        draw = ImageDraw.Draw(image)
        # Check font size:
        for font_size in range(300, 0, -5):
            font_highlight = ImageFont.truetype("images/COOPBL.TTF", font_size)
            texth_w, texth_h = font_highlight.getsize(letter)
            if texth_w < img_w - 50:
                break
        draw.text(((img_w - texth_w) // 2, (img_h - texth_h) // 2), letter,
                  (0, 0, 0), font=font_highlight)
        font_body = ImageFont.truetype("images/COOPBL.TTF", font_size - 10)
        textb_w, textb_h = font_highlight.getsize(letter)
        color = STATE_TO_COLOR[state]
        draw.text(((img_w - textb_w) // 2, (img_h - textb_h) // 2), letter,
                  color, font=font_body)

    return ImageTk.PhotoImage(image.resize((width, height), Image.ANTIALIAS))
