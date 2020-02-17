#pragma once
#include "BaseBackend.h"

#include "ResizeKey.h"
#include "KeyboardKey.h"
#include "Menu.h"


constexpr int
ALERT_MARGIN = 2,
PARAM_INPUT_WIDTH = 25;



class NANOBackend :
	public BaseBackend
{
	bool isOpen;
	WINDOW* menuWindow, * toolWindow, * overlayWindow;
	std::function<void()> editionHandler;
	std::string editionDescription;
	Menu* menu;
	void (NANOBackend::* currentFunction)();
	int paramHeaderHeight;
	std::string paramBuffer;

	static const std::string unsavedAlert;

	Key* getKey() const;

	void drawTerm();
	void drawMenuWindow();
	void drawToolWindow();
	void drawOverlayWindow(const int, const int, const int, const int);
	void hideOverlayWindow();
	void eraseWindow(WINDOW*&);
	void eraseTerm();

	void handleResizeKey(const ResizeKey* const);
	void handleKeyboardKey(const KeyboardKey* const);

	void callEditionHandler() const;

	bool isTooSmall() const;

	void renderMenu();
	

	void showAlert(const std::string&);

	void main();
	void tooSmall();
	void popup();

	void help();
	void renderHelp(WINDOW* const, const std::vector<std::string>&, const size_t);
	void quit();

public:
	NANOBackend(BaseTool* const);
	~NANOBackend() override;

	void bind(const std::string&, std::function<void()>, const std::string&) override;
	virtual void start() override;
};