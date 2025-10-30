🟢 Othello (Qt GUI Application)

A simple visual Othello (Reversi) game built with C++ and Qt.
Play against another player on an interactive GUI board with automatic move validation and score tracking.

🎮 Features

🧩 Interactive 8×8 Othello board

🔄 Automatic piece flipping and move validation

👥 Computer vs Player mode

🧮 Real-time score updates

🪟 GUI built with Qt Widgets and Qt Designer

🗂️ Project Structure
Othello/
├── Othello.pro        # Qt project file
├── Headers/
│   └── othello.h      # Class definitions and game logic
├── Sources/
│   ├── main.cpp       # Entry point
│   └── othello.cpp    # Game logic implementation
└── Forms/
    └── othello.ui     # GUI layout (Qt Designer)

⚙️ Build & Run
🧱 Using Qt Creator

Open Othello.pro in Qt Creator

Configure the build kit (e.g., Desktop Qt 6.x)

Click Build ▶️ Run

💻 Using Terminal
qmake Othello.pro
make
./Othello

🚧 Future Improvements

🤖 Add advanced AI opponent (minimax or heuristic-based)

⏪ Add move history / undo feature

🎨 Add visual themes or animations

🪪 License

This project is licensed under the MIT License
.
