
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


void heapify_hs_revised(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, int n_heap, int i_root, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg, const std::vector<int>& sorted_indices_vis_tracker);

void heapify_hs_revised(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, int n_heap, int i_root, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg, const std::vector<int>& sorted_indices_vis_tracker) {
    int largest = i_root; 
    int l = 2 * i_root + 1; 
    int r = 2 * i_root + 2; 
    std::string algoName = "Heap Sort"; 

    
    if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
    if (isPaused) { 
        statusDisplay.setString("PAUSED. Delay: " + floatToString_core(delayMs) + "ms. (Space)");
        while(isPaused && window.isOpen()){
            window.clear(sf::Color(20,25,30)); window.draw(uiPanelBg); window.draw(statusDisplay);
            std::vector<int> comp_h = {i_root}; if(l<n_heap && (size_t)l<array.size()) comp_h.push_back(l); if(r<n_heap && (size_t)r<array.size()) comp_h.push_back(r);
            drawBarsWithNumbers(window, barAreaBounds, array, font, comp_h, {}, sorted_indices_vis_tracker);
            window.display();
            if(pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
            if(!isPaused) { statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms"); break;}
            sleepMilliseconds(50);
        }
    }
    if (!window.isOpen()) return; if (!isPaused) statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms");
    
    
    std::vector<int> comparing_h = {i_root};
    if (l < n_heap && (size_t)l < array.size()) comparing_h.push_back(l);
    if (r < n_heap && (size_t)r < array.size()) comparing_h.push_back(r);
    window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
    drawBarsWithNumbers(window, barAreaBounds, array, font, comparing_h, {}, sorted_indices_vis_tracker);
    window.display();
    sleepMilliseconds(delayMs);

    if (l < n_heap && (size_t)l < array.size() && array[l] > array[largest]) largest = l;
    if (r < n_heap && (size_t)r < array.size() && array[r] > array[largest]) largest = r;

    if (largest != i_root) {
        std::swap(array[i_root], array[largest]);
        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {i_root, largest}, sorted_indices_vis_tracker);
        window.display();
        sleepMilliseconds(delayMs);
        heapify_hs_revised(window, barAreaBounds, font, array, n_heap, largest, delayMs, isPaused, statusDisplay, uiPanelBg, sorted_indices_vis_tracker);
    }
}

void visualizeHeapSort(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array,
                       float& delayMs, bool& isPaused, sf::Text& statusDisplay,
                       const sf::RectangleShape& uiPanelBg) {
    if (array.empty()) return;
    int n = array.size();
    std::vector<int> sorted_indices_vis_tracker;
    std::string algoName = "Heap Sort";

    if(!isPaused) statusDisplay.setString(algoName + " (Build Heap). Delay: " + floatToString_core(delayMs) + "ms");

    for (int i = n / 2 - 1; i >= 0; i--) {
        if (!window.isOpen()) return;
        heapify_hs_revised(window, barAreaBounds, font, array, n, i, delayMs, isPaused, statusDisplay, uiPanelBg, sorted_indices_vis_tracker);
    }

    if(!isPaused && window.isOpen()) statusDisplay.setString(algoName + " (Extract Max). Delay: " + floatToString_core(delayMs) + "ms");

    for (int i = n - 1; i > 0; i--) {
        if (!window.isOpen()) return;
        
        if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
        if (isPaused) { 
            statusDisplay.setString("PAUSED. Delay: " + floatToString_core(delayMs) + "ms. (Space)");
            while(isPaused && window.isOpen()){
                window.clear(sf::Color(20,25,30)); window.draw(uiPanelBg); window.draw(statusDisplay);
                drawBarsWithNumbers(window, barAreaBounds, array, font, {0,i}, {}, sorted_indices_vis_tracker);
                window.display();
                if(pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
                if(!isPaused) { statusDisplay.setString(algoName + " (Extract Max). Delay: " + floatToString_core(delayMs) + "ms"); break;}
                sleepMilliseconds(50);
            }
        }
        if (!window.isOpen()) return; if(!isPaused) statusDisplay.setString(algoName + " (Extract Max). Delay: " + floatToString_core(delayMs) + "ms");
        

        std::swap(array[0], array[i]);
        sorted_indices_vis_tracker.push_back(i); 

        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {0, i}, sorted_indices_vis_tracker);
        window.display();
        sleepMilliseconds(delayMs);

        heapify_hs_revised(window, barAreaBounds, font, array, i, 0, delayMs, isPaused, statusDisplay, uiPanelBg, sorted_indices_vis_tracker);
    }
    if (n > 0 && std::find(sorted_indices_vis_tracker.begin(), sorted_indices_vis_tracker.end(), 0) == sorted_indices_vis_tracker.end()) {
         sorted_indices_vis_tracker.push_back(0);
    }
    
    if (window.isOpen()) {
        for(int k=0; k<n; ++k) if(std::find(sorted_indices_vis_tracker.begin(), sorted_indices_vis_tracker.end(), k) == sorted_indices_vis_tracker.end()) sorted_indices_vis_tracker.push_back(k);
        std::sort(sorted_indices_vis_tracker.begin(), sorted_indices_vis_tracker.end());

        statusDisplay.setString(algoName + " Complete. Delay: " + floatToString_core(delayMs) + "ms");
        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {}, sorted_indices_vis_tracker);
        window.display();
        sleepMilliseconds(delayMs * 3 > 200 ? delayMs * 3 : 200);
    }
}