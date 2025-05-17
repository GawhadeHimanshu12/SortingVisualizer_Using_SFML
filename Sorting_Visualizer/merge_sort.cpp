
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


void merge_ms(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, int l, int m, int r, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg, std::vector<int>& sorted_indices_vis_tracker);
void mergeSort_recursive_impl_ms(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, int l, int r, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg, std::vector<int>& sorted_indices_vis_tracker);

void merge_ms(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, int l, int m, int r, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg, std::vector<int>& sorted_indices_vis_tracker) {
    int n1 = m - l + 1;
    int n2 = r - m;
    std::vector<int> L(n1), R_arr(n2);
    for (int i_copy = 0; i_copy < n1; i_copy++) L[i_copy] = array[l + i_copy];
    for (int j_copy = 0; j_copy < n2; j_copy++) R_arr[j_copy] = array[m + 1 + j_copy];

    int i = 0, j = 0, k = l;
    std::string algoName = "Merge Sort"; 

    while (i < n1 && j < n2) {
        
        if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
        if (isPaused) { 
            statusDisplay.setString("PAUSED. Delay: " + floatToString_core(delayMs) + "ms. (Space)");
            while(isPaused && window.isOpen()){
                window.clear(sf::Color(20,25,30)); window.draw(uiPanelBg); window.draw(statusDisplay);
                drawBarsWithNumbers(window, barAreaBounds, array, font, {(l+i < array.size() ? l+i : -1), (m+1+j < array.size() ? m+1+j : -1)}, {}, sorted_indices_vis_tracker);
                window.display();
                if(pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
                if(!isPaused) { statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms"); break;}
                sleepMilliseconds(50);
            }
        }
        if (!window.isOpen()) return; if (!isPaused) statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms");
        

        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {l + i, m + 1 + j}, {}, sorted_indices_vis_tracker);
        window.display();
        sleepMilliseconds(delayMs);

        if (L[i] <= R_arr[j]) { array[k] = L[i]; i++; } 
        else { array[k] = R_arr[j]; j++; }

        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {k}, sorted_indices_vis_tracker);
        window.display();
        sleepMilliseconds(delayMs);
        k++;
    }
    while (i < n1) { 
        if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return; 
        if (isPaused) { } if (!window.isOpen()) return; if(!isPaused)statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms");
        array[k] = L[i]; window.clear(sf::Color(20,25,30)); window.draw(uiPanelBg); window.draw(statusDisplay); drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {k}, sorted_indices_vis_tracker); window.display(); sleepMilliseconds(delayMs); i++; k++;
    }
    while (j < n2) { 
        if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
        if (isPaused) { } if (!window.isOpen()) return; if(!isPaused)statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms");
        array[k] = R_arr[j]; window.clear(sf::Color(20,25,30)); window.draw(uiPanelBg); window.draw(statusDisplay); drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {k}, sorted_indices_vis_tracker); window.display(); sleepMilliseconds(delayMs); j++; k++;
    }
}

void mergeSort_recursive_impl_ms(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, int l, int r, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg, std::vector<int>& sorted_indices_vis_tracker) {
    if (!window.isOpen() || l >= r) return;
    
    int m = l + (r - l) / 2;

    if (pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return;
    
    if (isPaused) { while(isPaused && window.isOpen()){ if(pollCoreAlgorithmEvents(window, isPaused, delayMs) == CoreEventAction::Exit) return; if(!isPaused) break; sleepMilliseconds(50);}}
    if(!window.isOpen()) return;


    mergeSort_recursive_impl_ms(window, barAreaBounds, font, array, l, m, delayMs, isPaused, statusDisplay, uiPanelBg, sorted_indices_vis_tracker);
    if (!window.isOpen()) return;
    mergeSort_recursive_impl_ms(window, barAreaBounds, font, array, m + 1, r, delayMs, isPaused, statusDisplay, uiPanelBg, sorted_indices_vis_tracker);
    if (!window.isOpen()) return;
    
    merge_ms(window, barAreaBounds, font, array, l, m, r, delayMs, isPaused, statusDisplay, uiPanelBg, sorted_indices_vis_tracker);

    if(window.isOpen()){ 
        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        std::vector<int> merged_range; for(int mi=l; mi<=r; ++mi) merged_range.push_back(mi);
        drawBarsWithNumbers(window, barAreaBounds, array, font, merged_range, {}, sorted_indices_vis_tracker); 
        window.display();
        sleepMilliseconds(delayMs / 1.5f > 10.f ? delayMs / 1.5f : 10.f); 
    }
}

void visualizeMergeSort(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array,
                        float& delayMs, bool& isPaused, sf::Text& statusDisplay,
                        const sf::RectangleShape& uiPanelBg) {
    if (array.empty()) return;
    int n = array.size();
    std::vector<int> sorted_indices_vis_tracker; 
    std::string algoName = "Merge Sort";

    if(!isPaused) statusDisplay.setString(algoName + ". Delay: " + floatToString_core(delayMs) + "ms");
    mergeSort_recursive_impl_ms(window, barAreaBounds, font, array, 0, n - 1, delayMs, isPaused, statusDisplay, uiPanelBg, sorted_indices_vis_tracker);

    if (window.isOpen()) {
        for(int i_final=0; i_final<n; ++i_final) sorted_indices_vis_tracker.push_back(i_final); 
        statusDisplay.setString(algoName + " Complete. Delay: " + floatToString_core(delayMs) + "ms");
        window.clear(sf::Color(20, 25, 30)); window.draw(uiPanelBg); window.draw(statusDisplay);
        drawBarsWithNumbers(window, barAreaBounds, array, font, {}, {}, sorted_indices_vis_tracker);
        window.display();
        sleepMilliseconds(delayMs * 3 > 200 ? delayMs * 3 : 200);
    }
}