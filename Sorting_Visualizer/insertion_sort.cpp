
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

void visualizeInsertionSort(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array,
                            float& delayMs, bool& isPaused, sf::Text& statusDisplay,
                            const sf::RectangleShape& uiPanelBg) {
    if (array.empty()) return;
    int n = array.size();
    std::string algoName = "Insertion Sort";

    if (!isPaused) {
        statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms");
    }

    for (int i = 1; i < n; i++) {
        int key = array[i];
        int j = i - 1;
        std::vector<int> current_sorted_partition; 
        for(int k_s=0; k_s<i; ++k_s) current_sorted_partition.push_back(k_s);


        
        if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
        if (isPaused) {
            statusDisplay.setString("PAUSED. Delay: " + floatToString_core(delayMs) + "ms. (Space)");
            while (isPaused && window.isOpen()) {
                window.clear(sf::Color(20,25,30)); window.draw(uiPanelBg); window.draw(statusDisplay);
                drawBarsWithNumbers(window, barAreaBounds, array, font, {i}, {}, current_sorted_partition); 
                window.display();
                if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
                if (!isPaused) { statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms"); break; }
                sleepMilliseconds(50);
            }
        }
        if (!window.isOpen()) return; if (!isPaused) statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms");
        

        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {i}, {}, current_sorted_partition);
        window.display();
        sleepMilliseconds(delayMs);

        while (j >= 0 && array[j] > key) {
            
            if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
            if (isPaused) { 
                statusDisplay.setString("PAUSED. Delay: " + floatToString_core(delayMs) + "ms. (Space)");
                while (isPaused && window.isOpen()) {
                    window.clear(sf::Color(20,25,30)); window.draw(uiPanelBg); window.draw(statusDisplay);
                    drawBarsWithNumbers(window, barAreaBounds, array, font, {j,i}, {}, current_sorted_partition); 
                    window.display();
                    if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
                    if (!isPaused) { statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms"); break; }
                    sleepMilliseconds(50);
                }
            }
            if (!window.isOpen()) return; if (!isPaused) statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms");
            

            window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
            drawBarsWithNumbers(window, barAreaBounds, array, font, {j, i}, {}, current_sorted_partition); 
            window.display();
            sleepMilliseconds(delayMs);

            array[j + 1] = array[j]; 

            window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
            drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {j + 1}, current_sorted_partition); 
            window.display();
            sleepMilliseconds(delayMs);
            j = j - 1;
        }
        array[j + 1] = key; 

        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {j + 1}, current_sorted_partition); 
        window.display();
        sleepMilliseconds(delayMs);
    }
    
    if (!window.isOpen()) return;
    std::vector<int> final_sorted_indices; for(int k_f=0; k_f<n; ++k_f) final_sorted_indices.push_back(k_f);
    statusDisplay.setString(algoName + " Complete. Delay: " + floatToString_core(delayMs) + "ms");
    window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
    drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {}, final_sorted_indices); 
    window.display();
    sleepMilliseconds(delayMs * 3 > 200 ? delayMs * 3 : 200);
}