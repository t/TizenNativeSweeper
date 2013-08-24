#ifndef _TIZENNATIVESWEEPERFORM_H_
#define _TIZENNATIVESWEEPERFORM_H_

#include "tizenx.h"

class TizenNativeSweeperForm
	: public Tizen::Ui::Controls::Form
	, public Tizen::Ui::IActionEventListener
	, public Tizen::Ui::Controls::IFormBackEventListener
{
public:
	TizenNativeSweeperForm(void);
	virtual ~TizenNativeSweeperForm(void);
	bool Initialize(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);


protected:
	std::vector<Cell *> cells;
	static const int ID_BUTTON_RESET = 101;
	static const int ID_BUTTON_TILE = 102;
	static const int CELL_X_COUNT = 15;
	static const int CELL_Y_COUNT = 15;
	static const int CELL_MINE_COUNT = 20;
	bool OpenCell(int x, int y);
	void OpenAllCell();
	int GetCellValue(Cell *);
	void InitBoard();
	void ResetBoard();
};

#endif	//_TIZENNATIVESWEEPERFORM_H_
