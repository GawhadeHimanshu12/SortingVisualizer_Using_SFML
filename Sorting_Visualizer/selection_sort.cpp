
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <algorithm> 
#include <iostream> 
#include <iomanip>
#include <sstream>


void drawBarsWithNumbers(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, const std::vector<int>& array, const sf::Font& font, const std::vector<int>& comparing_indices, const std::vector<int>& swapped_indices, const std::vector<int>& sorted_indices, int max_val_override = -1);
void sleepMilliseconds(float ms);
enum class CoreEventAction { Continue, Exit };
CoreEventAction pollCoreAlgorithmEvents(sf::RenderWindow& window, bool& isPaused, float& delayMs);
std::string floatToString_core(float value, int precision = 0);

void visualizeSelectionSort(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array,
                            float& delayMs, bool& isPaused, sf::Text& statusDisplay,
                            const sf::RectangleShape& uiPanelBg) {
    if (array.empty()) return;
    int n = array.size();
    std::vector<int> sorted_indices_list;
    std::string algoName = "Selection Sort";

    if (!isPaused) {
        statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms");
    }

    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;

        
        if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
        if (isPaused) {
            statusDisplay.setString("PAUSED. Delay: " + floatToString_core(delayMs) + "ms. (Space)");
            while (isPaused && window.isOpen()) {
                window.clear(sf::Color(20,25,30)); window.draw(uiPanelBg); window.draw(statusDisplay);
                drawBarsWithNumbers(window, barAreaBounds, array, font, {min_idx}, {}, sorted_indices_list);
                window.display();
                if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
                if (!isPaused) { statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms"); break; }
                sleepMilliseconds(50);
            }
        }
        if (!window.isOpen()) return; if (!isPaused) statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms");
        

        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {min_idx}, {}, sorted_indices_list);
        window.display();
        sleepMilliseconds(delayMs);

        for (int j = i + 1; j < n; j++) {
            
            if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
            if (isPaused) { 
                statusDisplay.setString("PAUSED. Delay: " + floatToString_core(delayMs) + "ms. (Space)");
                 while (isPaused && window.isOpen()) {
                    window.clear(sf::Color(20,25,30)); window.draw(uiPanelBg); window.draw(statusDisplay);
                    drawBarsWithNumbers(window, barAreaBounds, array, font, {min_idx, j}, {}, sorted_indices_list);
                    window.display();
                    if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
                    if (!isPaused) { statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms"); break; }
                    sleepMilliseconds(50);
                }
            }
            if (!window.isOpen()) return; if (!isPaused) statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms");
            

            window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
            drawBarsWithNumbers(window, barAreaBounds, array, font, {min_idx, j}, {}, sorted_indices_list);
            window.display();
            sleepMilliseconds(delayMs);

            if (array[j] < array[min_idx]) {
                min_idx = j;
                window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
                drawBarsWithNumbers(window, barAreaBounds, array, font, {min_idx, i}, {}, sorted_indices_list);
                window.display();
                sleepMilliseconds(delayMs);
            }
        }

        if (min_idx != i) {
            std::swap(array[min_idx], array[i]);
            window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
            drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {min_idx, i}, sorted_indices_list);
            window.display();
            sleepMilliseconds(delayMs);
        }
        sorted_indices_list.push_back(i); 
    }
    if (n > 0 && std::find(sorted_indices_list.begin(), sorted_indices_list.end(), n - 1) == sorted_indices_list.end()) {
        sorted_indices_list.push_back(n - 1);
    }
    
    if (!window.isOpen()) return;
    statusDisplay.setString(algoName + " Complete. Delay: " + floatToString_core(delayMs) + "ms");
    window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
    drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {}, sorted_indices_list);
    window.display();
    sleepMilliseconds(delayMs * 3 > 200 ? delayMs * 3 : 200); 
}