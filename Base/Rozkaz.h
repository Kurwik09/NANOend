#pragma once

#include <string>
#include <regex>
#include <functional>

struct Rozkaz {
	class Invalid{};

	const std::string rozkaz, opis;
	std::function<void()> handler;
	std::string topLabel, optionLabel, paramLabel, entryName;

	Rozkaz(const std::string&, std::function<void()>, const std::string);
	~Rozkaz();

private:
	static const std::regex regexp; };


//Klawisz

class Klawisz {
protected:
	const int kod;
public:
	Klawisz(const int kodKlawiszowy) : kod(kodKlawiszowy) {};
	virtual std::string toString() const = 0;
	virtual ~Klawisz() {};
	int podajKod() const { return kod; };

};

//KlawiszKlawiatury

class PrzyciskKlawiatury final : public Klawisz {
public:
	PrzyciskKlawiatury(const int);
	std::string toString() const override;
};

