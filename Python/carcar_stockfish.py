
from stockfish import Stockfish

class CarcarStockfish():
    
    def __init__(self, stockfish_path: str, level: int):
        self.stockfish = Stockfish(path=stockfish_path)
        self.stockfish.set_skill_level(level)
        self.stockfish.set_depth(15)

    def print_board(self):
        print(self.stockfish.get_board_visual())

    def get_best_move(self):
        return self.stockfish.get_best_move()
    
    def move_to(self, move: str) -> bool:
        if not self.stockfish.is_move_correct(move):
            print('The move is not legal!, move:', move)
            return False
        self.stockfish.make_moves_from_current_position([move])
        return True

def main():
    stockfish = CarcarStockfish("C:/Users/hansw/OneDrive/桌面/資料夾/NTU/Carcar_Chess/stockfish-11-win/stockfish-11-win/Windows/stockfish_20011801_x64.exe", 20)
    for i in range(60):
        move = stockfish.get_best_move()
        stockfish.move_to(move)
        print('Make move ', move)
        stockfish.print_board()

if __name__ == '__main__':
    main()