/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mplayer.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:52:04 by sbzizal           #+#    #+#             */
/*   Updated: 2024/02/12 21:56:37 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <dirent.h>
#include <sstream>

void add_allmp3(const std::string &dirPath, std::vector<std::string> &mp3List) {
    DIR* directory = opendir(dirPath.c_str());
    if (directory) {
        dirent* entry;
        while ((entry = readdir(directory))) {
            if (std::strstr(entry->d_name, ".mp3")) {
                mp3List.push_back(entry->d_name);
            }
        }
        closedir(directory);
    }
}

void print_mp3list(const std::vector<std::string> &mp3List) {
    std::cout << "Public Playlist: " << std::endl;
    std::cout << "---------------------" << std::endl;

    for (int i = 0; i < (int)mp3List.size(); i++) {
        std::cout << i + 1 << " - " << mp3List[i] << std::endl;
    }
    std::cout << "---------------------" << std::endl;
}

void play_song(const std::vector<std::string> &mp3List, int index) {
    if (index >= 0 && index < (int)mp3List.size()){
        std::string command = "cd songs && afplay \"" + mp3List[index] + "\" &";
        system(command.c_str());
        std::system("clear");
        std::cout << "Now playing: " << mp3List[index] << std::endl;
        std::cout << "\033[1;32m ♬ the song is playing... \033[0m" << std::endl;
    }
    else
        std::cout << "Invalid song index." << std::endl;
}

void play_random(const std::vector<std::string> &mp3List) {
    int index = std::rand() % mp3List.size();
    play_song(mp3List, index);
}

int main() {
    static int play = 0;
    std::vector<std::string> mp3List;
    add_allmp3("songs", mp3List); // Add MP3 files from the directory

    std::system("clear");
    std::cout << "\033[1;32m ♬ welcome to the music player ♬ \033[0m" << std::endl;
    std::cout << std::endl;
    
    print_mp3list(mp3List);
    std::string line;
    while (true){
        std::cout << "\033[1;34m > \033[0m";
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "list"){
            std::system("clear");
            print_mp3list(mp3List);
        }
        else if (command == "play"){
            if (play == 0){
                play = 1;
            }
            if (play == 1){
                system("killall afplay");
            }
            int index;
            if (iss >> index) // Try to read the index after the command
                play_song(mp3List, index - 1);
            else
                play_random(mp3List);
        }
        else if (command == "stop"){
            system("killall afplay");
            std::system("clear");
            std::cout << "\033[1;31m ♬ the song is stopped... \033[0m" << std::endl;
        }
        else if (command == "quit"){
            if (play == 1){
                system("killall afplay");
            }
            break;
        } 
        else {
            std::cout << "Unknown command. Available commands: list, play <index>, stop, quit" << std::endl;
        }
    }
    return 0;
}
