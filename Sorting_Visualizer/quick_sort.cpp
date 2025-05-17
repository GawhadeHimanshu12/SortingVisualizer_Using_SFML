
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


int partition_qs_revised(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, int low, int high, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg, std::vector<int>& sorted_indices_vis_tracker);
void quickSort_recursive_impl_qs_revised(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, int low, int high, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg, std::vector<int>& sorted_indices_vis_tracker);

int partition_qs_revised(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, int low, int high, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg, std::vector<int>& sorted_indices_vis_tracker) {
    int pivot = array[high];
    int i = (low - 1);
    std::string algoName = "Quick Sort";

    for (int j = low; j <= high - 1; j++) {
        
        if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return -2; 
        if (isPaused) { 
            statusDisplay.setString("PAUSED. Delay: " + floatToString_core(delayMs) + "ms. (Space)");
            while(isPaused && window.isOpen()){
                window.clear(sf::Color(20,25,30)); window.draw(uiPanelBg); window.draw(statusDisplay);
                drawBarsWithNumbers(window, barAreaBounds, array, font, {j, high, (i>=low?i:-1)}, {}, sorted_indices_vis_tracker);
                window.display();
                if(pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return -2;
                if(!isPaused) { statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms"); break;}
                sleepMilliseconds(50);
            }
        }
        if (!window.isOpen()) return -2; if (!isPaused) statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms");
        

        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {j, high}, {}, sorted_indices_vis_tracker);
        window.display();
        sleepMilliseconds(delayMs);

        if (array[j] < pivot) {
            i++;
            std::swap(array[i], array[j]);
            window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
            drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {i, j}, sorted_indices_vis_tracker);
            window.display();
            sleepMilliseconds(delayMs);
        }
    }
    std::swap(array[i + 1], array[high]);
    window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
    drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {i + 1, high}, sorted_indices_vis_tracker);
    window.display();
    sleepMilliseconds(delayMs);
    
    if (std::find(sorted_indices_vis_tracker.begin(), sorted_indices_vis_tracker.end(), i + 1) == sorted_indices_vis_tracker.end()) {
        sorted_indices_vis_tracker.push_back(i + 1);
    }
    window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
    drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {}, sorted_indices_vis_tracker);
    window.display();
    sleepMilliseconds(delayMs / 1.5f > 10.f ? delayMs / 1.5f : 10.f);

    return (i + 1);
}

void quickSort_recursive_impl_qs_revised(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, int low, int high, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg, std::vector<int>& sorted_indices_vis_tracker) {
    if (!window.isOpen()) return;
    if (low < high) {
        if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
        if (isPaused) { 
            
            while(isPaused && window.isOpen()){ if(pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return; if(!isPaused)break; sleepMilliseconds(50); }
        }
        if (!window.isOpen()) return;

        int pi = partition_qs_revised(window, barAreaBounds, font, array, low, high, delayMs, isPaused, statusDisplay, uiPanelBg, sorted_indices_vis_tracker);
        if (!window.isOpen() || pi == -2) return;

        quickSort_recursive_impl_qs_revised(window, barAreaBounds, font, array, low, pi - 1, delayMs, isPaused, statusDisplay, uiPanelBg, sorted_indices_vis_tracker);
        if (!window.isOpen()) return;
        quickSort_recursive_impl_qs_revised(window, barAreaBounds, font, array, pi + 1, high, delayMs, isPaused, statusDisplay, uiPanelBg, sorted_indices_vis_tracker);
    } else if (low == high && low >=0 && (size_t)low < array.size()) { 
        if (std::find(sorted_indices_vis_tracker.begin(), sorted_indices_vis_tracker.end(), low) == sorted_indices_vis_tracker.end()) {
            sorted_indices_vis_tracker.push_back(low);
            if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return; 
            window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
            drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {}, sorted_indices_vis_tracker);
            window.display();
            sleepMilliseconds(delayMs / 2.0f > 5.f ? delayMs / 2.0f : 5.f);
        }
    }
}

void visualizeQuickSort(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array,
                        float& delayMs, bool& isPaused, sf::Text& statusDisplay,
                        const sf::RectangleShape& uiPanelBg) {
    if (array.empty()) return;
    int n = array.size();
    std::vector<int> sorted_indices_vis_tracker;
    std::string algoName = "Quick Sort";

    if(!isPaused) statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms");
    quickSort_recursive_impl_qs_revised(window, barAreaBounds, font, array, 0, n - 1, delayMs, isPaused, statusDisplay, uiPanelBg, sorted_indices_vis_tracker);
    
    if(window.isOpen()){
        for(int k=0; k<n; ++k) { 
            if(std::find(sorted_indices_vis_tracker.begin(), sorted_indices_vis_tracker.end(), k) == sorted_indices_vis_tracker.end()) {
                sorted_indices_vis_tracker.push_back(k);
            }
        }
        statusDisplay.setString(algoName + " Complete. Delay: " + floatToString_core(delayMs) + "ms");
        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {}, sorted_indices_vis_tracker);
        window.display();
        sleepMilliseconds(delayMs * 3 > 200 ? delayMs * 3 : 200);
    }
}