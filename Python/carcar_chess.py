
from carcar_stockfish import CarcarStockfish
from bluetooth import Bluetooth

def main():
    bt = Bluetooth("COM10")
    stockfish = CarcarStockfish("C:/Users/hansw/OneDrive/桌面/資料夾/NTU/Carcar_Chess/stockfish-11-win/stockfish-11-win/Windows/stockfish_20011801_x64.exe", 20)
    move = stockfish.get_best_move()
    stockfish.move_to(move)
    print('Make move ', move)
    bt.write(move)


if __name__ == '__main__':
    main()