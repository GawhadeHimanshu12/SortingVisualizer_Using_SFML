
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iostream>
#include <iomanip>
#include <sstream>


void drawBarsWithNumbers(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, const std::vector<int>& array, const sf::Font& font, const std::vector<int>& comparing_indices, const std::vector<int>& swapped_indices, const std::vector<int>& sorted_indices, int max_val_override = -1);
void sleepMilliseconds(float ms);
enum class CoreEventAction { Continue, Exit };
CoreEventAction pollCoreAlgorithmEvents(sf::RenderWindow& window, bool& isPaused, float& delayMs);
std::string floatToString_core(float value, int precision = 0);

void visualizeCountingSort(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array,
                           float& delayMs, bool& isPaused, sf::Text& statusDisplay,
                           const sf::RectangleShape& uiPanelBg) {
    if (array.empty()) return;
    int n = array.size();
    std::string algoName = "Counting Sort";

    if(!isPaused) statusDisplay.setString(algoName + " (Count). Delay: " + floatToString_core(delayMs) + "ms");

    int max_val = array[0];
    int min_val = array[0];
    for (int x : array) {
        if (x > max_val) max_val = x;
        if (x < min_val) min_val = x;
    }

    int range = max_val - min_val + 1;
    if (range <=0 && n > 0) { 
        statusDisplay.setString(algoName + ": Invalid data range.");
        std::vector<int> sorted_final; for(int k=0; k<n; ++k) sorted_final.push_back(k);
        window.clear(sf::Color(20,25,30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {}, sorted_final, max_val);
        window.display(); sleepMilliseconds(1000);
        return;
    } else if (range <=0 && n==0) return; 

    std::vector<int> count(range, 0);
    std::vector<int> output(n);
    std::vector<int> sorted_indices_list; 

    for (int i = 0; i < n; i++) {
        
        if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
        if (isPaused) { 
            statusDisplay.setString("PAUSED. Delay: " + floatToString_core(delayMs) + "ms. (Space)");
            while(isPaused && window.isOpen()){
                window.clear(sf::Color(20,25,30)); window.draw(uiPanelBg); window.draw(statusDisplay);
                drawBarsWithNumbers(window, barAreaBounds, array, font, {i}, {}, {}, max_val);
                window.display();
                if(pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
                if(!isPaused) { statusDisplay.setString(algoName + " (Count). Delay: " + floatToString_core(delayMs) + "ms"); break;}
                sleepMilliseconds(50);
            }
        }
        if (!window.isOpen()) return; if(!isPaused)statusDisplay.setString(algoName + " (Count). Delay: " + floatToString_core(delayMs) + "ms");
        
        
        count[array[i] - min_val]++;
        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {i}, {}, {}, max_val);
        window.display();
        sleepMilliseconds(delayMs / 2.0f > 1.f ? delayMs / 2.0f : 1.f); 
    }

    if(!isPaused && window.isOpen()) statusDisplay.setString(algoName + " (Sum). Delay: " + floatToString_core(delayMs) + "ms");
    for (int i = 1; i < range; i++) {
        if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return; 
        if (!window.isOpen()) return;
        
        count[i] += count[i - 1];
    }

    if(!isPaused && window.isOpen()) statusDisplay.setString(algoName + " (Output). Delay: " + floatToString_core(delayMs) + "ms");
    for (int i = n - 1; i >= 0; i--) {
        
        if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
        if (isPaused) {
            statusDisplay.setString("PAUSED. Delay: " + floatToString_core(delayMs) + "ms. (Space)");
            while(isPaused && window.isOpen()){
                window.clear(sf::Color(20,25,30)); window.draw(uiPanelBg); window.draw(statusDisplay);
                int targetIdx = count[array[i] - min_val] -1;
                drawBarsWithNumbers(window, barAreaBounds, array, font, {i}, {targetIdx >=0 && targetIdx < n ? targetIdx : i}, {}, max_val);
                window.display();
                if(pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
                if(!isPaused) { statusDisplay.setString(algoName + " (Output). Delay: " + floatToString_core(delayMs) + "ms"); break;}
                sleepMilliseconds(50);
            }
        }
        if (!window.isOpen()) return; if(!isPaused)statusDisplay.setString(algoName + " (Output). Delay: " + floatToString_core(delayMs) + "ms");
        

        output[count[array[i] - min_val] - 1] = array[i];
        count[array[i] - min_val]--;
        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {i}, {}, {}, max_val); 
        window.display();
        sleepMilliseconds(delayMs);
    }

    if(!isPaused && window.isOpen()) statusDisplay.setString(algoName + " (Copy back). Delay: " + floatToString_core(delayMs) + "ms");
    for (int i = 0; i < n; i++) {
        if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return; 
        if (!window.isOpen()) return;
        

        array[i] = output[i];
        sorted_indices_list.push_back(i);
        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {i}, sorted_indices_list, max_val);
        window.display();
        sleepMilliseconds(delayMs);
    }
    
    if (!window.isOpen()) return;
    statusDisplay.setString(algoName + " Complete. Delay: " + floatToString_core(delayMs) + "ms");
    window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
    drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {}, sorted_indices_list, max_val);
    window.display();
    sleepMilliseconds(delayMs * 3 > 200 ? delayMs * 3 : 200);
}