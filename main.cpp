#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "dirent.h"
#include <windows.h>
#include <vector>
#include <cmath>

class MPlayer {
private:
    sf::Music Music;
    bool IsPaused = true;
    bool IsStopped = false;
    std::string Current = " ";
public:
    void SetMusic(std::string path);
    void SetVolume(float volume);
    void SetLoop();
    void Stop();
    void Rewind(float sec);
    void Play();
    void Pause();
    void SetCurrent(std::string cur);
    void SetOffset(float sec);


    sf::Time GetOffset();
    sf::Time GetDuration();
    float GetVolume();
    bool GetPause();
    bool GetStop();
    bool GetLoop();
    sf::SoundSource::Status GetStatus();
    std::string GetCurrent();

};

void MPlayer::Rewind(float sec) {

    if (sec > .0f) {
        Music.setPlayingOffset(Music.getPlayingOffset() + sf::seconds(sec));

    }
    else if (Music.getPlayingOffset().asSeconds() > 10.0f) {
        Music.setPlayingOffset(Music.getPlayingOffset() + sf::seconds(sec));
    }
    else {
        Music.setPlayingOffset(sf::seconds(0.0f));
    }





}

void  MPlayer::SetOffset(float sec) {
    Music.setPlayingOffset(sf::seconds(sec));
}

void MPlayer::SetMusic(std::string path) {
    if (!Music.openFromFile(path))
        true;
}

void MPlayer::Stop() {
    if (this->IsStopped == 0) {
        Music.stop();
        this->IsStopped = true;
    }
    else {
        Music.play();
        this->IsStopped = false;
    }
}

void MPlayer::SetVolume(float volume) {
    if (volume <= 0) {
        Music.setVolume(.0f);
    }
    else if (volume >= 100.0f) {

        Music.setVolume(100.0f);
    }
    else {
        Music.setVolume(volume);
    }
}

void MPlayer::SetLoop() {
    Music.setLoop(!Music.getLoop());
}

bool MPlayer::GetLoop() {
    return Music.getLoop();
}

void MPlayer::Pause() {
    if (this->IsPaused == 0) {
        Music.pause();
        this->IsPaused = true;
    }
    else {
        Music.play();
        this->IsPaused = false;
    }
}

bool MPlayer::GetPause() {
    return IsPaused;
}

sf::Time MPlayer::GetOffset() {
    return Music.getPlayingOffset();
}

sf::Time MPlayer::GetDuration() {
    return Music.getDuration();
}

float MPlayer::GetVolume() {
    return Music.getVolume();

}

sf::SoundSource::Status MPlayer::GetStatus() {
    return Music.getStatus();

}

bool MPlayer::GetStop() {
    return this->IsStopped;
}

void MPlayer::Play() {
    Music.play();
}

void MPlayer::SetCurrent(std::string cur) {
    this->Current = cur;
}

std::string MPlayer::GetCurrent() {
    return this->Current;
}






int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Music Player Nigeria", sf::Style::Titlebar | sf::Style::Close);

    sf::Font font, font2;
    if (!font.loadFromFile("Smack Boom Outline 400.ttf") || !font2.loadFromFile("calibri.ttf"))
    {
        return 1;
    }

    sf::Text Current("None", font2, 15);
    sf::Text izveleT("Kompozicijas izvele...", font2, 15);
    sf::Text text("Music Player Nigeria", font, 50);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

    MPlayer player;

    player.SetVolume(0.01f);

    sf::RectangleShape stopBar;
    stopBar.setSize(sf::Vector2f(35, 35));
    stopBar.setFillColor(sf::Color(255, 0, 0, 100));
    stopBar.setPosition(30, 490);
    stopBar.setOutlineThickness(2);
    stopBar.setOutlineColor(sf::Color::Black);


    sf::RectangleShape progressBar;
    progressBar.setSize(sf::Vector2f(705, 20));
    progressBar.setFillColor(sf::Color::White);
    progressBar.setPosition(30, 550);
    progressBar.setOutlineThickness(2);
    progressBar.setOutlineColor(sf::Color::Black);
    sf::RectangleShape progressBarAll;
    progressBarAll.setSize(sf::Vector2f(705, 20));
    progressBarAll.setFillColor(sf::Color(255, 255, 255, 100));
    progressBarAll.setPosition(30, 550);
    progressBarAll.setOutlineThickness(2);
    progressBarAll.setOutlineColor(sf::Color::Black);


    sf::RectangleShape volumeBar;
    volumeBar.setSize(sf::Vector2f(15, 100));
    volumeBar.setFillColor(sf::Color::Blue);
    volumeBar.setPosition(720, 520);
    volumeBar.setOutlineThickness(2);
    volumeBar.setOutlineColor(sf::Color::Black);
    sf::RectangleShape volumeBarAll;
    volumeBarAll.setSize(sf::Vector2f(15, 100));
    volumeBarAll.setFillColor(sf::Color(0, 0, 255, 100));
    volumeBarAll.setPosition(720, 420);
    volumeBarAll.setOutlineThickness(2);
    volumeBarAll.setOutlineColor(sf::Color::Black);


    sf::RectangleShape pauseBar1;
    pauseBar1.setSize(sf::Vector2f(10, 35));
    pauseBar1.setFillColor(sf::Color::Yellow);
    pauseBar1.setPosition(80, 490);
    pauseBar1.setOutlineThickness(2);
    pauseBar1.setOutlineColor(sf::Color::Black);
    sf::RectangleShape pauseBar2;
    pauseBar2.setSize(sf::Vector2f(10, 35));
    pauseBar2.setFillColor(sf::Color::Yellow);
    pauseBar2.setPosition(100, 490);
    pauseBar2.setOutlineThickness(2);
    pauseBar2.setOutlineColor(sf::Color::Black);


    sf::CircleShape playBar(80, 3);
    playBar.setFillColor(sf::Color::Green);
    playBar.setPosition(110, 487);
    playBar.setOutlineThickness(2);
    playBar.setOutlineColor(sf::Color::Black);
    playBar.setRotation(90.f);
    playBar.setRadius(20.3);


    sf::CircleShape previoussongstart(80, 3);
    previoussongstart.setFillColor(sf::Color(103, 242, 209, 100));
    previoussongstart.setPosition(140, 527);
    previoussongstart.setOutlineThickness(2);
    previoussongstart.setOutlineColor(sf::Color::Black);
    previoussongstart.setRotation(-90.f);
    previoussongstart.setRadius(20.3);
    sf::RectangleShape previoussongend;
    previoussongend.setSize(sf::Vector2f(5, 35));
    previoussongend.setFillColor(sf::Color(103, 242, 209, 100));
    previoussongend.setPosition(130, 490);
    previoussongend.setOutlineThickness(2);
    previoussongend.setOutlineColor(sf::Color::Black);




    sf::CircleShape nextsongstart(80, 3);
    nextsongstart.setFillColor(sf::Color(103, 242, 209, 100));
    nextsongstart.setPosition(220, 487);
    nextsongstart.setOutlineThickness(2);
    nextsongstart.setOutlineColor(sf::Color::Black);
    nextsongstart.setRotation(90.f);
    nextsongstart.setRadius(20.3);


    sf::RectangleShape nextsongend;
    nextsongend.setSize(sf::Vector2f(5, 35));
    nextsongend.setFillColor(sf::Color(103, 242, 209, 100));
    nextsongend.setPosition(225, 490);
    nextsongend.setOutlineThickness(2);
    nextsongend.setOutlineColor(sf::Color::Black);


    sf::CircleShape repeat(50);
    repeat.setRadius(18.7);
    repeat.setFillColor(sf::Color::Black);
    repeat.setPosition(250, 487);
    repeat.setOutlineThickness(3);
    repeat.setOutlineColor(sf::Color(255, 0, 255, 100));

    sf::RectangleShape one;
    one.setSize(sf::Vector2f(3, 20));
    one.setFillColor(sf::Color(255, 0, 255, 100));
    one.setPosition(268, 495);
    one.setOutlineThickness(2);
    one.setOutlineColor(sf::Color::Black);

    sf::RectangleShape oneI;
    oneI.setSize(sf::Vector2f(3, 10));
    oneI.setFillColor(sf::Color(255, 0, 255, 100));
    oneI.setPosition(268, 495);
    oneI.setOutlineThickness(2);
    oneI.setOutlineColor(sf::Color::Black);
    oneI.setRotation(45.f);

    sf::RectangleShape oneL;
    oneL.setSize(sf::Vector2f(3, 15));
    oneL.setFillColor(sf::Color(255, 0, 255, 100));
    oneL.setPosition(277, 512);
    oneL.setOutlineThickness(2);
    oneL.setOutlineColor(sf::Color::Black);
    oneL.setRotation(90.f);

    sf::RectangleShape izvele;
    izvele.setSize(sf::Vector2f(150, 35));
    izvele.setFillColor(sf::Color(200, 94, 5, 100));
    izvele.setPosition(0, -10);
    izvele.setOutlineThickness(2);
    izvele.setOutlineColor(sf::Color::Black);




    bool stopBR = false;
    pauseBar1.setScale(1, 0);
    pauseBar2.setScale(1, 0);



    std::string name;

    sf::Time time1;
    sf::Clock clock;
    sf::Time time2;
    sf::Clock clock2;


    std::vector<std::string> queue;
    std::vector<std::string> backqueue;

    float time = 0.0f;

    while (window.isOpen())
    {


        time += 0.001f;
        int r = (sin(time) + 1) * 127.5f;
        int g = (sin(time + 2 * 3.1415 / 3) + 1) * 127.5f;
        int b = (sin(time + 4 * 3.1415 / 3) + 1) * 127.5f;
        text.setFillColor(sf::Color(r, g, b));
        sf::Event event;
        while (window.pollEvent(event))
        {

            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f pos = window.mapPixelToCoords(pixelPos);

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) {
                system("CLS");
                std::cout << std::endl;
                std::cout << "-------------------RINDA:------------------" << std::endl;
                std::cout << "-------------------------------------------" << std::endl;
                for (int i = 0; i < queue.size(); i++) {
                    std::cout << i + 1 << ". " << queue[i] << std::endl;
                }
                std::cout << std::endl;
                std::cout << "------------------RINDA END----------------" << std::endl;
                std::cout << "-------------------------------------------" << std::endl << std::endl;

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) || event.key.code == sf::Mouse::Left && nextsongstart.getGlobalBounds().contains(pos.x, pos.y) || event.key.code == sf::Mouse::Left && nextsongend.getGlobalBounds().contains(pos.x, pos.y)) {


                    nextsongstart.setFillColor(sf::Color(103, 242, 209, 255));
                    nextsongend.setFillColor(sf::Color(103, 242, 209, 255));

                    if (queue.size() > 0) {
                        backqueue.insert(backqueue.begin(), player.GetCurrent());
                        player.SetCurrent(queue[0]);
                        queue.erase(queue.begin());
                        player.SetMusic("music/" + player.GetCurrent() + ".wav");
                        player.Play();


                    }

                    clock.restart();

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) || event.key.code == sf::Mouse::Left && previoussongstart.getGlobalBounds().contains(pos.x, pos.y) || event.key.code == sf::Mouse::Left && previoussongend.getGlobalBounds().contains(pos.x, pos.y)) {


                    previoussongstart.setFillColor(sf::Color(103, 242, 209, 255));
                    previoussongend.setFillColor(sf::Color(103, 242, 209, 255));

                    if (backqueue.size() > 0) {
                        queue.insert(queue.begin(), player.GetCurrent());
                        player.SetCurrent(backqueue[0]);
                        backqueue.erase(backqueue.begin());
                        player.SetMusic("music/" + player.GetCurrent() + ".wav");
                        player.Play();

                    }
                    else if (backqueue.size() == 0) {
                        player.Stop();
                        player.Play();
                    }

                    clock2.restart();

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) || event.key.code == sf::Mouse::Left && one.getGlobalBounds().contains(pos.x, pos.y)) {

                    if (player.GetLoop() == 0) {

                        repeat.setOutlineColor(sf::Color(255, 0, 255, 255));
                        one.setFillColor(sf::Color(255, 0, 255, 255));
                        oneI.setFillColor(sf::Color(255, 0, 255, 255));
                        oneL.setFillColor(sf::Color(255, 0, 255, 255));
                    }
                    else {
                        repeat.setOutlineColor(sf::Color(255, 0, 255, 100));
                        one.setFillColor(sf::Color(255, 0, 255, 100));
                        oneI.setFillColor(sf::Color(255, 0, 255, 100));
                        oneL.setFillColor(sf::Color(255, 0, 255, 100));
                    }
                    player.SetLoop();

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    player.Rewind(10.0f);



                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    player.Rewind(-10.0f);
                }
                if (event.key.code == sf::Mouse::Left && progressBarAll.getGlobalBounds().contains(pos.x, pos.y)) {

                    player.SetOffset(round((float)player.GetDuration().asSeconds()) * (sf::Mouse::getPosition().x - window.getPosition().x - 36) / 708);

                }




                if (event.key.code == sf::Keyboard::Up) {
                    if (player.GetVolume() <= 95.01f)
                        player.SetVolume(player.GetVolume() + 4.99f);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    if (player.GetVolume() >= 4.99f)
                        player.SetVolume(player.GetVolume() - 4.99f);
                }

                if (event.key.code == sf::Mouse::Left && volumeBarAll.getGlobalBounds().contains(pos.x, pos.y)) {

                    player.SetVolume(100 - (sf::Mouse::getPosition().y - window.getPosition().y - 452));
                }


                if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Mouse::Left && playBar.getGlobalBounds().contains(pos.x, pos.y) || event.key.code == sf::Mouse::Left && pauseBar1.getGlobalBounds().contains(pos.x, pos.y) || event.key.code == sf::Mouse::Left && pauseBar2.getGlobalBounds().contains(pos.x, pos.y)) {
                    if (player.GetPause() == 1) {
                        playBar.setScale(1, 0);
                        pauseBar1.setScale(1, 1);
                        pauseBar2.setScale(1, 1);
                        stopBar.setFillColor(sf::Color(255, 0, 0, 100));
                    }
                    else if (player.GetPause() == 0) {
                        playBar.setScale(1, 1);
                        pauseBar1.setScale(1, 0);
                        pauseBar2.setScale(1, 0);
                        stopBar.setFillColor(sf::Color(255, 0, 0, 100));
                    }
                    player.Pause();
                }
                if (event.key.code == sf::Keyboard::S || event.key.code == sf::Mouse::Left && stopBar.getGlobalBounds().contains(pos.x, pos.y)) {
                    player.Stop();
                    if (stopBR == 0) {
                        stopBar.setFillColor(sf::Color(255, 0, 0, 255));
                        playBar.setScale(1, 1);
                        pauseBar1.setScale(1, 0);
                        pauseBar2.setScale(1, 0);
                    }
                    else if (stopBR == 1) {
                        stopBar.setFillColor(sf::Color(255, 0, 0, 100));
                        playBar.setScale(1, 0);
                        pauseBar1.setScale(1, 1);
                        pauseBar2.setScale(1, 1);
                    }
                    stopBR = !stopBR;
                }

                if (event.key.code == sf::Keyboard::Q) {


                }

                if (event.key.code == sf::Keyboard::E) {
                    int deletet;
                    std::cout << "What you want to  remove?" << std::endl;
                    std::cin >> deletet;
                    queue.erase(queue.begin() + deletet - 1);



                }

                if (event.key.code == sf::Keyboard::P || event.key.code == sf::Mouse::Left && izvele.getGlobalBounds().contains(pos.x, pos.y)) {


        

                    DIR* dir;
                    struct dirent* ent;
                    if ((dir = opendir("music/")) != NULL) {
                        while ((ent = readdir(dir)) != NULL) {

                            std::cout << ent->d_name << std::endl;
                        }
                        closedir(dir);
                    }
                    else {
                        perror("");
                        return EXIT_FAILURE;
                    }

                    std::cout << std::endl;
                    std::cin >> name;

                    system("CLS");




                    if (queue.size() == 0 && player.GetDuration() == sf::seconds(0)) {

                        player.SetMusic("music/" + name + ".wav");
                        player.SetCurrent(name);
                    }
                    else {
                        queue.push_back(name);
                    }



                }

            }


        }

        time1 = clock.getElapsedTime();


        if (time1 > sf::seconds(0.2f)) {
            nextsongstart.setFillColor(sf::Color(103, 242, 209, 100));
            nextsongend.setFillColor(sf::Color(103, 242, 209, 100));
        }

        time2 = clock2.getElapsedTime();


        if (time2 > sf::seconds(0.2f)) {
            previoussongstart.setFillColor(sf::Color(103, 242, 209, 100));
            previoussongend.setFillColor(sf::Color(103, 242, 209, 100));
        }

        int currentInt = round((float)player.GetOffset().asSeconds() / 60);
        int totalInt = round((float)player.GetDuration().asSeconds() / 60);

        int currentIntSec = (int)player.GetOffset().asSeconds() % 60;
        int totalIntSec = (int)player.GetDuration().asSeconds() % 60;


        std::string currentStr = std::to_string(currentInt);
        std::string currentStrSec = std::to_string(currentIntSec);
        std::string totalStr = std::to_string(totalInt);
        std::string totalStrSec = std::to_string(totalIntSec);
        std::string c = "/";


        sf::Text laiks(currentStr + ":" + currentStrSec + c + totalStr + ":" + totalStrSec, font2, 15);
        laiks.setPosition(370, 550);
        laiks.setFillColor(sf::Color::Black);

        float progress = (float)player.GetOffset().asSeconds() / (float)player.GetDuration().asSeconds();
        progressBar.setScale(progress, 1);

        float volume = player.GetVolume() / 100.f;
        volumeBar.setScale(1, -volume);


        sf::Text Current(player.GetCurrent(), font2, 15);
        Current.setPosition(370, 570);
        Current.setFillColor(sf::Color::White);


        if (player.GetStatus() == sf::SoundSource::Stopped && player.GetStop() == 0 && player.GetLoop() == 0 && player.GetPause() == 0) {
            if (queue.size() > 0) {
                backqueue.push_back(player.GetCurrent());
                player.SetCurrent(queue[0]);
                queue.erase(queue.begin());
                player.SetMusic("music/" + player.GetCurrent() + ".wav");
                player.Play();

            }
            else {
                backqueue.push_back(player.GetCurrent());
                player.SetCurrent("");
            }

        }




        window.clear(sf::Color::Black);
        window.draw(progressBar);
        window.draw(volumeBar);
        window.draw(stopBar);
        window.draw(pauseBar1);
        window.draw(pauseBar2);
        window.draw(playBar);
        window.draw(volumeBarAll);
        window.draw(progressBarAll);
        window.draw(laiks);

        window.draw(nextsongstart);
        window.draw(nextsongend);

        window.draw(previoussongend);
        window.draw(previoussongstart);

        window.draw(repeat);

        window.draw(oneI);
        window.draw(one);
        window.draw(oneL);

        window.draw(text);

        window.draw(izvele);

        window.draw(izveleT);
        window.draw(Current);

        window.display();
    }
    return 0;
}
