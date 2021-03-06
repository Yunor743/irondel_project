 
#pragma once
#include <unordered_map>
#include <string>
#include <ctime>
#include <random>
#include <chrono>
#include <iostream>
#include <fstream>
#include <array>

using uint = unsigned int; //On pourra utiliser uint pour représenter un unsigned int

enum class BookState : int //état du livre (empreinté, perdu, en achat, dispo)
{
  AVAILABLE,
  BORROWED,
  LOST,
  ORDERED
};
constexpr std::array<const char*, 4> book_states = {
  "AVAILABLE",
  "BORROWED",
  "LOST",
  "ORDERED"
};
struct BookInfo // on stock toute les informations relatives à un livre
{
  std::string title;          //titre du livre
  float price;                //prix théorique du livre si il doit y avoir un remboursement
  BookState state;            //état du livre (empreinté, perdu, en achat, dispo)
  uint id_borrower;           //id du membre qui à empreinté le livre
  std::time_t return_date;    //Date où le livre doit être retourner à la bibliothèque
};
struct Books
{
protected: //On crée notre générateur, il sera protégé, donc appelable seulement dans cette classe et les classe enfant
  std::mt19937 generator;

public:   //On retourne au public, les éléments seront à nouveau appelables en dehors de l'instance de la classe
  std::unordered_map<uint, BookInfo> table;   // table de tout les livres
  std::string save_path = "";   //cette variable contient le chemin d'accès au fichier de sauvegarde de la table (il faut set cette variable grace a fileSearch())
  void save();    //cette fonction sauvegarde la table dans un fichier externe
  void load(char delimiter = '/', char end_line = '\\');    //cette fonction charge la table depuis un fichier externe
  void insert(std::string title, float price, BookState state = BookState::AVAILABLE, uint id_borrower = 0, std::time_t return_date = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) ); //on déclare la fonction membre qui permet d'insérer une nouvelle entrée dans la table
  void delOne(uint id);   //fonction permettant de supprimer une ligne précise en fonction de l'id de la key
  void disp() const;    //fonction permettant l'affichage de la table
  uint BorrowedBooksByMember(uint member_id);
};

