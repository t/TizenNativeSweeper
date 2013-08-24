#include "TizenNativeSweeperForm.h"
#include "AppResourceId.h"

using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

int
TizenNativeSweeperForm::GetCellValue(Cell * cell){

	int count = 0;

	if(cell->is_mine){
		return Cell::CELL_VALUE_MINE;
	}else{
		for(int i = -1; i < 2; i++){
			for(int j = -1; j < 2; j++){
				int idx = (cell->y + j) * CELL_Y_COUNT + (cell->x + i);
				if(idx < 0 || idx >= CELL_X_COUNT * CELL_Y_COUNT) continue;

				Cell * c = (Cell *)cells[idx];
				if(c->is_mine){
					count++;
				}
			}
		}
    }
    if(count == 0){
      return 0;
    }else{
      return count;
    }
}

bool
TizenNativeSweeperForm::OpenCell(int x, int y)
{
    if(! ( x >= 0 && x < CELL_X_COUNT && y >= 0 && y < CELL_Y_COUNT) ) return false;

    Cell * cell = (Cell *)cells[y * CELL_Y_COUNT + x];

    if(cell->opened) return false;

	cell->SetEnabled(false);
	int v = GetCellValue(cell);

    //cell->setText(L"@");
	String str;
	if(v > 0){
		str.Append(v);
	}else if(v == Cell::CELL_VALUE_MINE){
		str.Append("X");
	}
	cell->SetText(str);

	if(v == Cell::CELL_VALUE_MINE){
		MessageBox messageBox;
	    messageBox.Construct(L"TizenNativeSweeper", L"GameOver", MSGBOX_STYLE_OK);
	    int msg_result = 0;
	    messageBox.ShowAndWait(msg_result);
	}

    cell->opened = true;
    if(v == 0){
    	OpenCell(x, y - 1);
    	OpenCell(x + 1, y);
    	OpenCell(x, y + 1);
    	OpenCell(x - 1, y);
    }

    return (cell->value == Cell::CELL_VALUE_MINE);
}

void
TizenNativeSweeperForm::OpenAllCell()
{
	for(int x = 0; x < CELL_X_COUNT; x++){
		for(int y = 0; y < CELL_Y_COUNT; y++){
			Cell * cell = (Cell *)cells[y * CELL_Y_COUNT + x];
			if(cell->is_mine){
				OpenCell(cell->x, cell->y);
			}
		}
     }
}


TizenNativeSweeperForm::TizenNativeSweeperForm(void)
{
}

TizenNativeSweeperForm::~TizenNativeSweeperForm(void)
{
}

bool
TizenNativeSweeperForm::Initialize(void)
{
	Construct(IDF_FORM);

	return true;
}


void
TizenNativeSweeperForm::InitBoard(void)
{
	for(int y = 0; y < CELL_Y_COUNT; y++)	{
		for(int x = 0; x < CELL_X_COUNT; x++){
			// Create a Button
			Cell * cell = new (std::nothrow) Cell();
			cell->x = x;
			cell->y = y;
			cell->Construct(Rectangle(x * 48, y * 48, 48, 48));
			cell->SetText(L"■");
			cell->SetActionId(ID_BUTTON_TILE);
			cell->AddActionEventListener(*this);
			cells.push_back(cell);
			AddControl(cell);
		}
	}

	srand((unsigned int)time(NULL));
	for(int i = 0; i < CELL_MINE_COUNT; i++){
		//while(true){
			int r = rand() % (CELL_X_COUNT * CELL_Y_COUNT);
			Cell * cell = cells[r];
			//if(! cell->is_mine){
				cell->is_mine = true;
				AppLog("Mine is x:[%d] y:[%d]\n", cell->x, cell->y);

			//	break;
			//}
		//}
	}

}

void
TizenNativeSweeperForm::ResetBoard(void){

	for(std::vector<Cell *>::const_iterator i = cells.begin(); i < cells.end(); ++i){
		Cell * cell = *i;
		RemoveControl(cell);
		//delete cell;
	}
	cells.clear();
	InitBoard();
}

result
TizenNativeSweeperForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO:
	// Add your initialization code here

	// Setup back event listener
	SetFormBackEventListener(this);

	// Get a button via resource ID
	Tizen::Ui::Controls::Button *pButtonOk = static_cast<Button*>(GetControl(IDC_BUTTON_RESET));
	if (pButtonOk != null)
	{
		pButtonOk->SetActionId(ID_BUTTON_RESET);
		pButtonOk->AddActionEventListener(*this);
	}

	InitBoard();

	return r;
}

result
TizenNativeSweeperForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
TizenNativeSweeperForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
	switch(actionId)
	{
	case ID_BUTTON_RESET:
		{
			AppLog("Reset Button is clicked!\n");
			ResetBoard();
		}
		break;
	case ID_BUTTON_TILE:
		{
			Cell& cell = (Cell &)source;
			AppLog("Tile clicked! x:[%d] y:[%d]\n", cell.x, cell.y);
			if( OpenCell(cell.x, cell.y) ){
				OpenAllCell();
				AppLog("GameOver\n");
		    }
		}
		break;
	default:
		break;
	}
}

void
TizenNativeSweeperForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
	UiApp* pApp = UiApp::GetInstance();
	AppAssert(pApp);
	pApp->Terminate();
}


