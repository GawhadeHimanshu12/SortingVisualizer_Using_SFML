
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm> 
#include <cmath>
#include <iomanip> 
#include <sstream>   


const float CORE_MIN_DELAY_MS = 0.f;    
const float CORE_MAX_DELAY_MS = 300.f;  
const float CORE_DELAY_STEP_MS = 10.f;  



std::string floatToString_core(float value, int precision = 0) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << value;
    return ss.str();
}



enum class CoreEventAction { Continue, Exit };



CoreEventAction pollCoreAlgorithmEvents(sf::RenderWindow& window, bool& isPaused, float& delayMs) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return CoreEventAction::Exit;
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
                return CoreEventAction::Exit;
            }
            if (event.key.code == sf::Keyboard::Space) {
                isPaused = !isPaused; 
            } else if (event.key.code == sf::Keyboard::Add || event.key.code == sf::Keyboard::Equal) {
                delayMs -= CORE_DELAY_STEP_MS;
                if (delayMs < CORE_MIN_DELAY_MS) delayMs = CORE_MIN_DELAY_MS;
            } else if (event.key.code == sf::Keyboard::Subtract || event.key.code == sf::Keyboard::Hyphen) {
                delayMs += CORE_DELAY_STEP_MS;
                if (delayMs > CORE_MAX_DELAY_MS) delayMs = CORE_MAX_DELAY_MS;
            }
        }
    }
    return CoreEventAction::Continue;
}



float mapValueToHeightCore(int value, int actual_min_val, int actual_max_val, float drawingAreaHeight) {
    if (actual_max_val == actual_min_val) {
        return std::max(1.0f, drawingAreaHeight / 2.0f);
    }
    double percentage = static_cast<double>(value - actual_min_val) / (actual_max_val - actual_min_val);
    float height = static_cast<float>(percentage * drawingAreaHeight);
    return std::max(1.0f, height);
}


void drawBarsWithNumbers(sf::RenderWindow& window,
                         const sf::FloatRect& barAreaBounds, 
                         const std::vector<int>& array,
                         const sf::Font& font,
                         const std::vector<int>& comparing_indices,
                         const std::vector<int>& swapped_indices,
                         const std::vector<int>& sorted_indices,
                         int max_val_override) {
    if (array.empty()) {
        return;
    }
    
    float numbers_display_height = 30.f; 
    float bar_container_height = barAreaBounds.height - numbers_display_height;
    if (bar_container_height < 1.0f) bar_container_height = 1.0f; 
    float bar_container_width = barAreaBounds.width;
    float bar_area_left = barAreaBounds.left;
    float bar_area_top = barAreaBounds.top;
    size_t num_elements_to_draw = array.size();
    float bar_width_total = bar_container_width / static_cast<float>(num_elements_to_draw);
    float bar_gap = 2.0f;
    if (num_elements_to_draw > 100) bar_gap = 1.0f;
    if (num_elements_to_draw > 200) bar_gap = 0.0f;
    float current_bar_visual_width = std::max(1.0f, bar_width_total - bar_gap);
    int actual_min_val = 0, actual_max_val = 0;
    if (!array.empty()) {
        actual_min_val = *std::min_element(array.begin(), array.end());
        actual_max_val = *std::max_element(array.begin(), array.end());
    }
    if (max_val_override != -1) {
         actual_max_val = std::max(actual_max_val, max_val_override);
         if (actual_min_val > 0 && max_val_override >= actual_min_val) actual_min_val = 0;
    }
    sf::Text numberText;
    numberText.setFont(font);
    unsigned int charSize = 12;
    if (bar_width_total < 30) charSize = 10;
    if (bar_width_total < 15) charSize = 8;
    if (bar_width_total < 8 || bar_container_height < numbers_display_height + 10) charSize = 0; 
    numberText.setCharacterSize(charSize);
    for (size_t i = 0; i < num_elements_to_draw; ++i) {
        sf::RectangleShape bar;
        int display_value = array[i];
        float bar_height = mapValueToHeightCore(display_value, actual_min_val, actual_max_val, bar_container_height);
        bar.setSize(sf::Vector2f(current_bar_visual_width, bar_height));
        bar.setPosition(bar_area_left + i * bar_width_total + bar_gap / 2.0f,
                        bar_area_top + bar_container_height - bar_height); 
        bar.setFillColor(sf::Color(100, 160, 220)); 
        if (std::find(comparing_indices.begin(), comparing_indices.end(), static_cast<int>(i)) != comparing_indices.end()) {
            bar.setFillColor(sf::Color::Yellow);
        }
        if (std::find(swapped_indices.begin(), swapped_indices.end(), static_cast<int>(i)) != swapped_indices.end()) {
            bar.setFillColor(sf::Color::Red);
        }
        if (std::find(sorted_indices.begin(), sorted_indices.end(), static_cast<int>(i)) != sorted_indices.end()) {
            bar.setFillColor(sf::Color::Green);
        }
        window.draw(bar);
        if (charSize > 0) {
            numberText.setString(std::to_string(display_value));
            sf::FloatRect textBounds = numberText.getLocalBounds();
            numberText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top);
            numberText.setPosition(bar_area_left + i * bar_width_total + bar_width_total / 2.0f,
                                   bar_area_top + bar_container_height + 5.0f); 
            numberText.setFillColor(sf::Color::White);
            window.draw(numberText);
        }
    }
}


void sleepMilliseconds(float ms) {
    if (ms <= 0) return;
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(ms)));
}
