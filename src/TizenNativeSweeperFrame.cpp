#include "TizenNativeSweeperFrame.h"
#include "TizenNativeSweeperForm.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

TizenNativeSweeperFrame::TizenNativeSweeperFrame(void)
{
}

TizenNativeSweeperFrame::~TizenNativeSweeperFrame(void)
{
}

result
TizenNativeSweeperFrame::OnInitializing(void)
{
	result r = E_SUCCESS;

	// Create a form
	TizenNativeSweeperForm* pTizenNativeSweeperForm = new TizenNativeSweeperForm();
	pTizenNativeSweeperForm->Initialize();

	// Add the form to the frame
	AddControl(pTizenNativeSweeperForm);

	// Set the current form
	SetCurrentForm(pTizenNativeSweeperForm);

	// Draw the form
	pTizenNativeSweeperForm->Invalidate(true);

	// TODO: Add your initialization code here

	return r;
}

result
TizenNativeSweeperFrame::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}


