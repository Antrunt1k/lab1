#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <windows.h>
#include <sstream>

class AnimatedText
{
private:
    double m_duration = 0;
    std::string m_text;
public:
    AnimatedText(const double& duration, std::string text)
    {
        m_duration = duration;
        m_text = text;
    }

    double count() { return (m_duration) / size(m_text); }
    double GetDuration() { return m_duration; }

    std::string update(float time_main)
    {
        std::string Out;
        for (int i = 0; i <= (time_main / count()); i++)
        {
            Out += m_text[i];
        }
        return (Out);
    }

    ~AnimatedText() {}
};
bool Checking(float timing, double duration)
{
    if (timing > duration)
    {
        Sleep(500); exit(0);
    }
}

int main()
{

    sf::Font font_1;                                      //Создаём шрифт 
    font_1.loadFromFile("Metroplex Shadow.ttf");          //Загружаем файл шрифта
    sf::Text Font("", font_1, 30);                        //Создаем текст, куда помещаем строку, шрифт и размер шрифта
    Font.setStyle(sf::Text::Bold | sf::Text::Underlined); //Стиль шрифта
    Font.setColor(sf::Color::Green);

    double duration;
    std::cout << "Duration: "; std::cin >> duration;      //Указываем продолжительность
    std::string txt, a;
    std::cout << "Text: "; std::cin >> txt;               //Вводим текст
    a = txt;
    std::getline(std::cin, txt);
    txt = a + txt;                                        //Введённый текст с учётом разделителей

    AnimatedText Main_text(duration, txt);                //Отдаём в функцию полученные данные

    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");

    sf::Clock clock_main;
    sf::Clock clock_restart;

    while (window.isOpen())
    {
        float time_main = clock_main.getElapsedTime().asMicroseconds();
        float time_restart = clock_restart.getElapsedTime().asMicroseconds();
        time_main = time_main / 800 / 1000;
        time_restart = time_restart / 800 / 1000;

        std::ostringstream AnimationOfText;                   //Строковый поток
        AnimationOfText << Main_text.update(time_main);       //Вставляем текст в поток
        Font.setString("Text: " + AnimationOfText.str());     //Указываем строку для "шрифта"

        if (time_restart > Main_text.count())
        {
            std::cout << time_restart << std::endl;
            clock_restart.restart();                          //Перезагружаем время
        }

        Font.setPosition(50, 150);                            //Место размещения текста

        Checking(time_main, Main_text.GetDuration());


        sf::Event event;
        while (window.pollEvent(event))                       //Пока есть события, они обрабатываются
        {                                                     //
            if (event.type == sf::Event::Closed)              //Срабатывает, когда закрывается окно
                window.close();
        }
        window.clear();                                       //Очистка окна от прошлого текста
        window.draw(Font);                                    //Отрисовываем текст
        window.display();                                     //Вывод на экран
    }
    return 0;
}