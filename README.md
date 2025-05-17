# 🎨 SFML Sorting Visualizer: Watch Algorithms in Motion! 🚀

Hello there, fellow code enthusiast!

Ever wondered how different sorting algorithms *actually* work their magic? I built this **SFML Sorting Visualizer** because, for me, seeing is believing (and understanding!). This C++ application brings classic sorting algorithms to life, letting you visualize their step-by-step process in a simple, interactive graphical interface powered by the fantastic SFML library.

It's a personal project born out of a love for algorithms and a desire to make them a bit more tangible and fun.

## ✨ Features At a Glance

* **Live Visualization:** See bars representing numbers dynamically rearrange as the chosen algorithm does its work.
* **Interactive Array Input:** Don't just watch pre-set data!
    * Type in your own numbers to create a custom array.
    * Generate a random array with a single click.
    * Easily clear the current array to start over.
* **You're in Control!**
    * **Speed Adjustment:** Use the `+` and `-` keys to speed up or slow down the animation, finding the perfect pace for your observation.
    * **Pause & Resume:** Hit `Spacebar` to pause the action at any critical step, then press it again to continue.
    * **Quick Exit:** Press `Escape` anytime to close the visualizer.
* **User-Friendly Interface:** A dedicated panel on the left side of the window houses all controls, status messages (including current delay and pause state), and the number input field, keeping the right side clear for the bar visualization.

## 🛠️ Algorithms Implemented

Dive into the mechanics of these sorting techniques:

* Bubble Sort
* Insertion Sort
* Selection Sort
* Merge Sort
* Quick Sort
* Heap Sort
* Counting Sort
* Radix Sort _(currently optimized for non-negative integers)_

## 🖼️ See it to Believe It! (Add Your Screenshots/GIFs Here)

This is where the visualizer truly shines! I strongly encourage you to add a few snapshots or a short GIF to showcase:

* The main interface with the left UI panel and the bar display area.
* An algorithm in the middle of sorting, perhaps with bars highlighted for comparison or swap.
* The "PAUSED" state or the status display showing the current delay.
## 💻 Under the Hood: Tech & Design

* **Core Language:** C++ (leveraging C++17 standards).
* **Graphics & Windowing:** [SFML (Simple and Fast Multimedia Library)](https://www.sfml-dev.org/) – A wonderful cross-platform library that makes multimedia and game development in C++ much more accessible.
* **A Little Design Note:** As a personal challenge and learning exercise, this project was built *without using custom header files (.h/.hpp)*. All functions needed across different `.cpp` files are made available through forward declarations. Each sorting algorithm is neatly contained in its own `.cpp` file, and common helper functions (like event polling and drawing utilities) reside in `visualizer_core.cpp`.

## 🚀 Get It Running!

Excited to try it out? Here’s how you can get the SFML Sorting Visualizer running on your machine.

### You'll Need:

1.  **A C++ Compiler:** One that supports C++17 (like a recent version of g++).
2.  **SFML Library:** Make sure SFML is installed on your system and that your compiler knows where to find its headers and libraries. You can grab SFML from [their official website](https://www.sfml-dev.org/download.php). You'll need the `graphics`, `window`, and `system` modules.

### Build Steps:

1.  **Get the Code:** If you haven't yet, clone this repository or download the source files.
    ```bash
    git clone https://github.com/GawhadeHimanshu12/SortingVisualizer_Using_SFML
    cd [YOUR_REPOSITORY_DIRECTORY]
    ```
2.  **Compile:** Navigate to the project's root directory (where `main.cpp` and the other source files are) in your terminal or command prompt. Then, compile using a command like this:
    ```bash
    g++ main.cpp visualizer_core.cpp bubble_sort.cpp insertion_sort.cpp selection_sort.cpp merge_sort.cpp quick_sort.cpp heap_sort.cpp counting_sort.cpp radix_sort.cpp -o AlgorithmVisualizer -lsfml-graphics -lsfml-window -lsfml-system -std=c++17
    ```
    * **Important Font Note:** This visualizer looks for an `arial.ttf` font file in the same directory as the executable. If you use a different font or have it elsewhere, please update the font loading path in `main.cpp`.

3.  **Launch!**
    Execute the compiled program:
    ```bash
    ./AlgorithmVisualizer
    ```
    (On Windows, this might be `AlgorithmVisualizer.exe`.)

## 🎮 Interacting with the Visualizer

The interface is designed to be straightforward:

* **Left UI Panel:**
    * **`Random Array` / `Clear Array` Buttons:** Manage your dataset.
    * **Algorithm Buttons:** Select the sorting algorithm you want to see. Clicking one will start the visualization on the current array.
    * **Status Display:** This area provides feedback on what the visualizer is doing (e.g., "Bubble Sort. Delay: 50ms", "PAUSED. Delay: 70ms. (Space)", "Quick Sort Complete."), including the current animation delay.
    * **Number Input (at the bottom):** Type numbers and press `Enter` to add them to your array. `Backspace` works for corrections.
* **Keyboard Shortcuts:**
    * `Escape`: Closes the application immediately.
    * `Spacebar` (when a sort is active): Toggles Pause/Resume for the animation.
    * `+` or `=`: Decreases the delay between visualization steps (speeds up). Works when idle or during visualization.
    * `-` or `_`: Increases the delay (slows down). Works when idle or during visualization.

## 🌱 What's Next? (Potential Enhancements)

While this visualizer serves its purpose, there are always more ideas to explore!
* Adding even more sorting algorithms (and perhaps some non-comparison sorts).
* Visual cues for array access counts, comparisons, or swaps.
* More customization options (colors, array size for random generation).

## 🙌 Contributions & Feedback

This was a learning project for me, and I'm always open to suggestions or contributions! If you have an idea for an improvement, find a bug, or want to add a new algorithm:
* Feel free to fork the repository and submit a pull request.
* Open an issue to discuss changes or report problems.


Thanks for checking out the SFML Sorting Visualizer! I hope it provides some visual insight into the elegant world of sorting algorithms.

Happy visualizing! 😊





