
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

int getMaxForRadix_rs(const std::vector<int>& array) {
    if (array.empty()) return 0;
    int mx = 0; 
    bool first = true;
    for (int val : array) {
        if (val < 0) return -1; 
        if (first) { mx = val; first = false;}
        else if (val > mx) mx = val;
    }
    return mx;
}


void countSortForRadixPass_rs(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, int exp, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg, int overall_max_val);

void countSortForRadixPass_rs(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, int exp, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg, int overall_max_val) {
    int n = array.size();
    std::vector<int> output(n); 
    std::vector<int> count(10, 0);
    std::string passName = "Radix Sort (Pass exp " + std::to_string(exp) + ")";

    for (int i = 0; i < n; i++) {
        
        if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
        if (isPaused) { 
            statusDisplay.setString("PAUSED. Delay: " + floatToString_core(delayMs) + "ms. (Space)");
            while(isPaused && window.isOpen()){
                window.clear(sf::Color(20,25,30)); window.draw(uiPanelBg); window.draw(statusDisplay);
                drawBarsWithNumbers(window, barAreaBounds, array, font, {i}, {}, {}, overall_max_val);
                window.display();
                if(pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
                if(!isPaused) { statusDisplay.setString(passName + ". Delay: " + floatToString_core(delayMs) + "ms"); break;}
                sleepMilliseconds(50);
            }
        }
        if (!window.isOpen()) return; if(!isPaused)statusDisplay.setString(passName + ". Delay: " + floatToString_core(delayMs) + "ms");
        
        count[(array[i] / exp) % 10]++;
        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {i}, {}, {}, overall_max_val);
        window.display();
        sleepMilliseconds(delayMs / 2.0f > 1.f ? delayMs / 2.0f : 1.f);
    }

    for (int i = 1; i < 10; i++) { 
        if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return; if (!window.isOpen()) return;
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        
        if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
        if (isPaused) { }
        if (!window.isOpen()) return; if(!isPaused)statusDisplay.setString(passName + ". Delay: " + floatToString_core(delayMs) + "ms");
        
        output[count[(array[i] / exp) % 10] - 1] = array[i];
        count[(array[i] / exp) % 10]--;
        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {i}, {}, {}, overall_max_val); 
        window.display();
        sleepMilliseconds(delayMs / 2.0f > 1.f ? delayMs / 2.0f : 1.f);
    }

    for (int i = 0; i < n; i++) { 
        if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return; if (!window.isOpen()) return;
        array[i] = output[i];
        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {i}, {}, overall_max_val); 
        window.display();
        sleepMilliseconds(delayMs / 2.0f > 1.f ? delayMs / 2.0f : 1.f);
    }
}

void visualizeRadixSort(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array,
                        float& delayMs, bool& isPaused, sf::Text& statusDisplay,
                        const sf::RectangleShape& uiPanelBg) {
    if (array.empty()) return;
    std::string algoName = "Radix Sort";
    if(!isPaused) statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms");

    int m = getMaxForRadix_rs(array);
    if (m == -1) { 
        statusDisplay.setString(algoName + ": Only non-negative numbers supported.");
        window.clear(sf::Color(20,25,30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {}, {});
        window.display();
        sleepMilliseconds(2000);
        return;
    }
    
    if (m == 0 && array.size() <=1) { 
         
    } else {
         for (int exp = 1; m / exp > 0; exp *= 10) {
            if (!window.isOpen()) return;
            if(!isPaused) statusDisplay.setString(algoName + " (Pass exp " + std::to_string(exp) + "). Delay: " + floatToString_core(delayMs) + "ms");
            countSortForRadixPass_rs(window, barAreaBounds, font, array, exp, delayMs, isPaused, statusDisplay, uiPanelBg, m);
        }
    }
    
    if (window.isOpen()) {
        std::vector<int> sorted_indices_list;
        for(size_t i_final=0; i_final<array.size(); ++i_final) sorted_indices_list.push_back(i_final);
        statusDisplay.setString(algoName + " Complete. Delay: " + floatToString_core(delayMs) + "ms");
        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {}, sorted_indices_list, m);
        window.display();
        sleepMilliseconds(delayMs * 3 > 200 ? delayMs * 3 : 200);
    }
}