
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip> 


const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;

const float UI_PANEL_WIDTH = 320.f;
const float BAR_AREA_X_START = UI_PANEL_WIDTH;
const float BAR_AREA_WIDTH = WINDOW_WIDTH - UI_PANEL_WIDTH;


const unsigned int INPUT_CHAR_LIMIT = 5;
const unsigned int MAX_ARRAY_ELEMENTS_INPUT = BAR_AREA_WIDTH / 7; 


const float MIN_DELAY_MS = 0.f;
const float MAX_DELAY_MS = 300.f;
const float DELAY_STEP_MS = 10.f;


sf::Font mainFont;


void drawBarsWithNumbers(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, const std::vector<int>& array, const sf::Font& font, const std::vector<int>& comparing_indices, const std::vector<int>& swapped_indices, const std::vector<int>& sorted_indices, int max_val_override = -1);
void sleepMilliseconds(float ms);

enum class CoreEventAction { Continue, Exit };
CoreEventAction pollCoreAlgorithmEvents(sf::RenderWindow& window, bool& isPaused, float& delayMs);
std::string floatToString_core(float value, int precision = 0);




void visualizeBubbleSort(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg);
void visualizeInsertionSort(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg);
void visualizeSelectionSort(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg);
void visualizeMergeSort(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg);
void visualizeQuickSort(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg);
void visualizeHeapSort(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg);
void visualizeCountingSort(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg);
void visualizeRadixSort(sf::RenderWindow& window, const sf::FloatRect& barAreaBounds, sf::Font& font, std::vector<int>& array, float& delayMs, bool& isPaused, sf::Text& statusDisplay, const sf::RectangleShape& uiPanelBg);



struct Button {
    sf::RectangleShape shape;
    sf::Text text;
    std::string id;
    bool isActive = false;
    bool isEnabled = true;

    Button(const std::string& label, const sf::Font& font, unsigned int charSize,
           sf::Vector2f size, sf::Vector2f position)
        : id(label) {
        shape.setSize(size);
        shape.setPosition(position);
        shape.setOutlineThickness(1.f);
        shape.setOutlineColor(sf::Color(150, 180, 220, 150)); 

        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(charSize);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
        setDefaultStyle();
    }

    bool isMouseOver(const sf::RenderWindow& window) const { return isEnabled && shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))); }
    void draw(sf::RenderWindow& window) const { window.draw(shape); window.draw(text); }

    void setHoverStyle() {
        if (!isEnabled) return;
        if (!isActive) shape.setFillColor(sf::Color(100, 170, 230)); 
        text.setFillColor(sf::Color::White);
    }
    void setDefaultStyle() {
        if (!isEnabled) {
            shape.setFillColor(sf::Color(100, 100, 100)); 
            text.setFillColor(sf::Color(180, 180, 180));
        } else if (isActive) {
            shape.setFillColor(sf::Color(30, 80, 180)); 
            text.setFillColor(sf::Color::White);
        } else {
            shape.setFillColor(sf::Color(50, 120, 200)); 
            text.setFillColor(sf::Color::White);
        }
    }
    void setActive(bool active) { isActive = active; setDefaultStyle(); }
    void setEnabled(bool enabled_state) { isEnabled = enabled_state; setDefaultStyle(); }
};


void drawLeftUIPanel(sf::RenderWindow& window, const sf::RectangleShape& panelBg, const std::vector<Button>& buttons, const sf::Text& statusDisplay, const sf::Text& arrayInputLabel, const sf::Text& arrayInputDisplay, const sf::RectangleShape& inputBoxBg, bool isVisualizationActive, const std::string& currentInputStr) {
    window.draw(panelBg); 

    for (const auto& button : buttons) {
        button.draw(window);
    }
    window.draw(statusDisplay);
    window.draw(arrayInputLabel);
    window.draw(inputBoxBg); 
    window.draw(arrayInputDisplay);

    if (!isVisualizationActive && !currentInputStr.empty()) { 
        sf::Text tempText = arrayInputDisplay; 
        tempText.setString(currentInputStr); 
        sf::RectangleShape caret(sf::Vector2f(2, arrayInputDisplay.getCharacterSize() * 0.8f));
        caret.setFillColor(sf::Color::White);
        
        sf::Vector2f textStartPos = arrayInputDisplay.getPosition();
        sf::Vector2f charPos = tempText.findCharacterPos(currentInputStr.length()); 
        
        
        
        
        caret.setPosition(textStartPos.x + charPos.x, textStartPos.y + 2);
        window.draw(caret);
    }
}

void setAllButtonsEnabled(std::vector<Button>& buttons, bool enabled) {
    for (auto& button : buttons) {
        button.setEnabled(enabled);
    }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Sorting Visualizer", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);

    if (!mainFont.loadFromFile("arial.ttf")) {
        std::cerr << "Error: Could not load font 'arial.ttf'." << std::endl;
        return -1;
    }

    std::vector<int> dataArray;
    std::string currentInputString = "";

    sf::RectangleShape uiPanelBackground(sf::Vector2f(UI_PANEL_WIDTH, WINDOW_HEIGHT));
    uiPanelBackground.setPosition(0, 0);
    uiPanelBackground.setFillColor(sf::Color(45, 50, 55)); 

    std::vector<Button> uiButtons;
    float currentY = 20.f;
    float padding = 10.f;
    float sidePadding = 20.f;
    sf::Vector2f controlButtonSize(UI_PANEL_WIDTH - 2 * sidePadding, 35.f);
    float controlButtonX = sidePadding;

    uiButtons.emplace_back("Random Array", mainFont, 16, controlButtonSize, sf::Vector2f(controlButtonX, currentY));
    uiButtons.back().id = "random_array";
    currentY += controlButtonSize.y + padding;
    uiButtons.emplace_back("Clear Array", mainFont, 16, controlButtonSize, sf::Vector2f(controlButtonX, currentY));
    uiButtons.back().id = "clear_array";
    currentY += controlButtonSize.y + padding * 2.5f;

    std::vector<std::pair<std::string, std::string>> sortAlgos = {
        {"Bubble Sort", "bubble_sort"}, {"Insertion Sort", "insertion_sort"},
        {"Selection Sort", "selection_sort"}, {"Merge Sort", "merge_sort"},
        {"Quick Sort", "quick_sort"}, {"Heap Sort", "heap_sort"},
        {"Counting Sort", "counting_sort"}, {"Radix Sort", "radix_sort"}
    };
    sf::Vector2f algoButtonSize((UI_PANEL_WIDTH - 2 * sidePadding - padding) / 2.f, 30.f);
    float algoButtonStartX1 = sidePadding;
    float algoButtonStartX2 = sidePadding + algoButtonSize.x + padding;

    for (size_t i = 0; i < sortAlgos.size(); ++i) {
        float posX = (i % 2 == 0) ? algoButtonStartX1 : algoButtonStartX2;
        if (i > 0 && i % 2 == 0) currentY += algoButtonSize.y + padding / 1.5f;
        uiButtons.emplace_back(sortAlgos[i].first, mainFont, 12, algoButtonSize, sf::Vector2f(posX, currentY));
        uiButtons.back().id = sortAlgos[i].second;
    }
    currentY += algoButtonSize.y + padding * 2.5f;

    sf::Text statusDisplay("", mainFont, 14); 
    statusDisplay.setFillColor(sf::Color::Yellow);
    statusDisplay.setPosition(sidePadding, currentY);
    
    sf::Text arrayInputLabel("Add Number:", mainFont, 16);
    arrayInputLabel.setFillColor(sf::Color(200, 200, 200));
    arrayInputLabel.setPosition(sidePadding, WINDOW_HEIGHT - 65.f);

    sf::RectangleShape arrayInputBoxBg(sf::Vector2f(UI_PANEL_WIDTH - 2 * sidePadding, 30.f));
    arrayInputBoxBg.setPosition(sidePadding, WINDOW_HEIGHT - 40.f);
    arrayInputBoxBg.setFillColor(sf::Color(70, 75, 80));
    arrayInputBoxBg.setOutlineColor(sf::Color(120,120,120));
    arrayInputBoxBg.setOutlineThickness(1.f);

    sf::Text arrayInputDisplay("", mainFont, 18);
    arrayInputDisplay.setFillColor(sf::Color::White);
    arrayInputDisplay.setPosition(sidePadding + 5.f, WINDOW_HEIGHT - 38.f); 

    bool isVisualizationActive = false;
    bool isPaused = false; 
    float visualizationDelayMs = 50.f; 
    std::string activeAlgorithmId = "";

    sf::FloatRect barAreaBounds(BAR_AREA_X_START, 0, BAR_AREA_WIDTH, WINDOW_HEIGHT);
    std::string baseStatusMessage = "Delay: " + floatToString_core(visualizationDelayMs) + "ms. Add numbers or select sort.";
    statusDisplay.setString(baseStatusMessage);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close(); 
            }

            
            if (!isVisualizationActive && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Add || event.key.code == sf::Keyboard::Equal) {
                    visualizationDelayMs -= DELAY_STEP_MS;
                    if (visualizationDelayMs < MIN_DELAY_MS) visualizationDelayMs = MIN_DELAY_MS;
                    baseStatusMessage = "Delay: " + floatToString_core(visualizationDelayMs) + "ms. Add numbers or select sort.";
                } else if (event.key.code == sf::Keyboard::Subtract || event.key.code == sf::Keyboard::Hyphen) {
                    visualizationDelayMs += DELAY_STEP_MS;
                    if (visualizationDelayMs > MAX_DELAY_MS) visualizationDelayMs = MAX_DELAY_MS;
                     baseStatusMessage = "Delay: " + floatToString_core(visualizationDelayMs) + "ms. Add numbers or select sort.";
                }
            }

            if (!isVisualizationActive) { 
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') { 
                        if (!currentInputString.empty()) currentInputString.pop_back();
                    } else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                        if (currentInputString.length() < INPUT_CHAR_LIMIT) {
                            currentInputString += static_cast<char>(event.text.unicode);
                        }
                    } else if ((event.text.unicode == '\r' || event.text.unicode == '\n') && !currentInputString.empty()) { 
                        if (dataArray.size() < MAX_ARRAY_ELEMENTS_INPUT) {
                            try {
                                int num = std::stoi(currentInputString);
                                dataArray.push_back(num);
                                currentInputString.clear();
                                baseStatusMessage = "Num added. Total: " + std::to_string(dataArray.size()) + ". Delay: " + floatToString_core(visualizationDelayMs) + "ms";
                            } catch (const std::exception& e) {
                                baseStatusMessage = "Error: Invalid number. Delay: " + floatToString_core(visualizationDelayMs) + "ms"; currentInputString.clear();
                            }
                        } else {
                            baseStatusMessage = "Max array size. Delay: " + floatToString_core(visualizationDelayMs) + "ms"; currentInputString.clear();
                        }
                    }
                    arrayInputDisplay.setString(currentInputString);
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        for (auto& button : uiButtons) {
                            if (button.isMouseOver(window) && button.isEnabled) {
                                for (auto& btn : uiButtons) btn.setActive(false);
                                button.setActive(true);
                                activeAlgorithmId = button.id;

                                if (button.id == "clear_array") {
                                    dataArray.clear(); currentInputString.clear(); arrayInputDisplay.setString("");
                                    baseStatusMessage = "Array cleared. Delay: " + floatToString_core(visualizationDelayMs) + "ms";
                                    button.setActive(false); activeAlgorithmId = "";
                                } else if (button.id == "random_array") {
                                    dataArray.clear(); std::random_device rd; std::mt19937 gen(rd());
                                    std::uniform_int_distribution<> distrib(1, 200);
                                    int array_size = std::min((unsigned int)50, MAX_ARRAY_ELEMENTS_INPUT);
                                    for (int i = 0; i < array_size; ++i) dataArray.push_back(distrib(gen));
                                    baseStatusMessage = "Rand. array (sz " + std::to_string(dataArray.size()) + "). Delay: " + floatToString_core(visualizationDelayMs) + "ms";
                                    button.setActive(false); activeAlgorithmId = "";
                                } else { 
                                    if (dataArray.empty()) {
                                        baseStatusMessage = "Array is empty! Delay: " + floatToString_core(visualizationDelayMs) + "ms";
                                        button.setActive(false); activeAlgorithmId = "";
                                        continue;
                                    }
                                    isVisualizationActive = true; isPaused = false;
                                    setAllButtonsEnabled(uiButtons, false);
                                    
                                    
                                    if (button.id == "bubble_sort") visualizeBubbleSort(window, barAreaBounds, mainFont, dataArray, visualizationDelayMs, isPaused, statusDisplay, uiPanelBackground);
                                    else if (button.id == "insertion_sort") visualizeInsertionSort(window, barAreaBounds, mainFont, dataArray, visualizationDelayMs, isPaused, statusDisplay, uiPanelBackground);
                                    else if (button.id == "selection_sort") visualizeSelectionSort(window, barAreaBounds, mainFont, dataArray, visualizationDelayMs, isPaused, statusDisplay, uiPanelBackground);
                                    else if (button.id == "merge_sort") visualizeMergeSort(window, barAreaBounds, mainFont, dataArray, visualizationDelayMs, isPaused, statusDisplay, uiPanelBackground);
                                    else if (button.id == "quick_sort") visualizeQuickSort(window, barAreaBounds, mainFont, dataArray, visualizationDelayMs, isPaused, statusDisplay, uiPanelBackground);
                                    else if (button.id == "heap_sort") visualizeHeapSort(window, barAreaBounds, mainFont, dataArray, visualizationDelayMs, isPaused, statusDisplay, uiPanelBackground);
                                    else if (button.id == "counting_sort") visualizeCountingSort(window, barAreaBounds, mainFont, dataArray, visualizationDelayMs, isPaused, statusDisplay, uiPanelBackground);
                                    else if (button.id == "radix_sort") visualizeRadixSort(window, barAreaBounds, mainFont, dataArray, visualizationDelayMs, isPaused, statusDisplay, uiPanelBackground);

                                    isVisualizationActive = false; setAllButtonsEnabled(uiButtons, true);
                                    
                                    for(auto& btn : uiButtons) {
                                        if (btn.id == activeAlgorithmId && btn.id != "clear_array" && btn.id != "random_array") {
                                            btn.setActive(true);
                                        } else {
                                            btn.setActive(false);
                                        }
                                    }
                                    if(window.isOpen()) baseStatusMessage = button.text.getString().toAnsiString() + " complete. Delay: " + floatToString_core(visualizationDelayMs) + "ms";
                                }
                                break; 
                            }
                        }
                    }
                }
                for (auto& button : uiButtons) {
                    if (button.isMouseOver(window)) button.setHoverStyle();
                    else button.setDefaultStyle(); 
                }
            }
            
            
        } 

        
        if (!isVisualizationActive) {
            statusDisplay.setString(baseStatusMessage); 
        }
        

        window.clear(sf::Color(20, 25, 30)); 
        drawBarsWithNumbers(window, barAreaBounds, dataArray, mainFont, {}, {}, {}, -1);
        drawLeftUIPanel(window, uiPanelBackground, uiButtons, statusDisplay, arrayInputLabel, arrayInputDisplay, arrayInputBoxBg, isVisualizationActive, currentInputString);
        window.display();
    }
    return 0;
}