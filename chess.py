from random import randint

class Game:
    """
    Should contain:
        - The players that are playing
        - The board state
        - Whose turn it is
    """
    def __init__(self, white_player: _Player, black_player: _Player, load_file=None):
        self.white_player = white_player
        self.black_player = black_player
        if load_file is not None:
            output_file = parse_path(load_file)
            self.board, self.turn = load_game(output_file)
        else:
            self.board, self.turn = self.new_game()

    def new_game(self):
        board = [[0]]

    @classmethod
    def random_colors(cls, player_1, player_2, load_file=None):
        if randint(0, 1) == 1:
            return cls(player_1, player_2, load_file)
        else:
            return cls(player_2, player_1, load_file)



class _Player:
    #   Player need game state to prevent cheating
    #       Game state includes pieces
    #   Hence, each player has a copy of the board, and a copy of the status of its pieces
    def __init__(self, pieces):
