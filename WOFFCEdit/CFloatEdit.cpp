#include "CFloatEdit.h"

#include <string>

BEGIN_MESSAGE_MAP(CFloatEdit, CEdit)
	ON_WM_KEYDOWN()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

void CFloatEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// Kill focus if applying.
	if (nChar == VK_RETURN || nChar == VK_TAB)
	{
		this->EnableWindow(false);
		this->EnableWindow(true);
	}

	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CFloatEdit::UpdateContents()
{
	CString contents;
	GetWindowTextW(contents);

	std::wstring c = (LPCTSTR)contents;
	
	try
	{
		auto finalValue = std::stof(c);
		SetWindowTextW(CString(std::to_wstring(finalValue).c_str()));
	}
	catch (...)
	{
		SetWindowTextW(contents);
	}
}


void CFloatEdit::OnKillFocus(CWnd* pNewWnd)
{
	UpdateContents();

	CEdit::OnKillFocus(pNewWnd);
}
