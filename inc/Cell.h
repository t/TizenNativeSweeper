/*
 * Cell.h
 *
 *  Created on: Aug 24, 2013
 *      Author: taku
 */

#ifndef CELL_H_
#define CELL_H_

#include <FUiCtrlButton.h>

class Cell: public Tizen::Ui::Controls::Button {
public:
	Cell();
	virtual ~Cell();
	int x = 0;
	int y = 0;
	bool opened = false;
	bool is_mine = false;
	int value = 0;
	static const int CELL_VALUE_NONE = 0;
	static const int CELL_VALUE_MINE = -1;
protected:
};

#endif /* CELL_H_ */
